#include <iostream>
#include <fstream>
#include "../Headers/ui.h"
#include "../Headers/CSVHandler.h"
#include "../Headers/HTMLHandler.h"

UI::UI(Service service) : service{service} {

}

int get_int() {
    std::string s;
    std::cin >> s;
    return stoi(s);
}

float get_float() {
    std::string s;
    std::cin >> s;
    return stof(s);
}

void print_menu(int mode) {
    if (mode == 1) {
        std::cout << "\nADMINISTRATOR MODE MENU\n";
        std::cout << "1.add coat\n";
        std::cout << "2.remove coat\n";
        std::cout << "3.update_button_function_too_many_names_aaaaa coat\n";
        std::cout << "4.list coats\n";
        std::cout << "0.exit\n";
    } else {
        std::cout << "USER MODE MENU\n";
    }
}

int get_command() {
    int t;
    std::cin >> t;
    return t;
}

void UI::generate() {
    for (int i = 1; i <= 15; i++) {
        this->service.add(i, std::to_string(i), float(i), i, std::to_string(i));
    }
}

void UI::handle_user(int size, const std::string& extension) {
    Repo basket, queue;
    for (const Coat &j: this->service.get_repo().get_data()) {
        if (size == -1 || size == j.get_size()) {
            queue.add(j);
        }
    }
    if(queue.get_size() == 0) {
        std::cout << "No available coats with that size\n";
        return;
    }

    bool total = false;
    int i = 0;
    float sum;
    while (!total) {
        if (i == queue.get_size())
            i = 0;

        std::cout << "Current Coat: \n" << queue.get_at(i).to_string();
        std::cout << "\nOPTIONS:\n";
        std::cout << "1. Add\n";
        std::cout << "2. Next\n";
        std::cout << "3. Total\n";
        std::cout << "4. Display the basket_list\n";
        int cmd;
        try {
            cmd = get_int();
        } catch(...) {
            std::cout << "INVALID COMMAND";
            continue;
        }
        switch (cmd) {
            case 3:
                total = true;
                break;
            case 1:// ADD
                basket.add(queue.get_at(i));
                std::cout << "\n Current basket_list total: ";
                sum = 0;
                for (const Coat j: basket.get_data()) {
                    sum += j.get_price();
                }
                std::cout << sum << "\n";

                this->service.save(basket.get_data());
                break;
            case 2:// NEXT
                std::cout << "\n Current basket_list total: ";
                sum = 0;
                for (const Coat j: basket.get_data()) {
                    sum += j.get_price();
                }
                std::cout << sum << "\n";

                break;
            case 4: {//display the file
                std::string command = "xdg-open C:/Users/rober/Desktop/University/Repos/A5-6-OOP/cmake-build-debug-coverage/basket_list."+extension;
                std::system(command.c_str());
            }
                break;
            default:
                std::cout << "\nINVALID COMMAND\n\n";
                break;

        }
        i++;
    }


    std::cout << "\n Current basket_list total: ";
    sum = 0;
    for (const Coat &j: basket.get_data()) {
        sum += j.get_price();
    }
    std::cout << sum << "\n";

    this->running = false;
}

void UI::handle_admin(int cmd) {
    int size;
    std::string color;
    float price;
    int quantity;
    std::string photo;

    switch (cmd) {
        case 0:
            this->running = false;
            break;
        case 1:

            std::cout << "Introduce new coat size";
            try {
                size = get_int();
            } catch(...) {
                std::cout << "INVALID SIZE";
                break;
            }
            std::cout << "Introduce new coat color";
            std::cin >> color;
            std::cout << "Introduce new coat price";
            try {
                price = get_float();
            } catch(...) {
                std::cout << "INVALID PRICE";
                break;
            }
            std::cout << "Introduce new coat quantity";
            try {
                quantity = get_int();
            } catch(...) {
                std::cout << "INVALID QUANTITY";
                break;
            }
            std::cout << "Introduce new coat photo link";
            std::cin >> photo;


            if (this->service.get_repo().has(size, color)) {
                std::cout << "\nCoat already exists\n\n";
                break;
            }


            try {
                this->service.add(size, color, price, quantity, photo);
            } catch(...) {
                std::cout << "INVALID PRICE";
                break;
            }

            break;
        case 2:
            std::cout << "Introduce new coat size";
            try {
                size = get_int();
            } catch(...) {
                std::cout << "INVALID SIZE";
                break;
            }
            std::cout << "Introduce new coat color";
            std::cin >> color;


            if (!this->service.get_repo().has(size, color)) {
                std::cout << "\nCoat does not exists\n\n";
                break;
            }
            this->service.remove(size, color);
            break;
        case 3:
            std::cout << "Introduce existing coat size";
            try {
                size = get_int();
            } catch(...) {
                std::cout << "INVALID SIZE";
                break;
            }
            std::cout << "Introduce existing coat color";
            std::cin >> color;
            std::cout << "Introduce new coat price";
            try {
                price = get_float();
            } catch(...) {
                std::cout << "INVALID PRICE";
                break;
            }
            std::cout << "Introduce new coat quantity";
            try {
                quantity = get_int();
            } catch(...) {
                std::cout << "INVALID QUANTITY";
                break;
            }
            std::cout << "Introduce new coat photo link";
            std::cin >> photo;

            if (!this->service.get_repo().has(size, color)) {
                std::cout << "\nCoat does not exists\n\n";
                break;
            }
            this->service.update(size, color, price, quantity, photo);
            break;

        case 4: {
            for (Coat i: this->service.get_repo().get_data()) {
                std::cout << i.to_string() << std::endl;
            }
        }
            break;
        default:
            std::cout << "\nINVALID COMMAND\n\n";
            break;
    }
}

void UI::read_data() {
    std::ifstream in("data.txt");
    while (!in.eof()) {
        Coat tmp;
        in >> tmp;
        this->service.get_repo().add(tmp);
    }
    in.close();
}

void UI::write_data() {
    std::ofstream ot("data.txt");
    int x = 0;
    for (Coat i: this->service.get_repo().get_data()) {
        ot << i;
        x++;
        if (x != this->service.get_repo().get_data().size()) {
            ot << "\n";
        }
    }
}

void UI::start_ui() {
    read_data();

    //generate();
    std::cout << "Enter 1 for admin mode or 0 for user mode: ";
    std::cin >> this->mode;
    while (this->running) {
        print_menu(this->mode);
        if (this->mode == 1) {
            int cmd;
            try {
                cmd = get_int();
            } catch(...) {
                std::cout << "INVALID COMMAND";
                continue;
            }
            handle_admin(cmd);
        } else {
            std::string extension;
            while (this->service.get_handler() == nullptr) {
                std::cout << "Enter 1 for CSV or 0 for HTML: ";
                std::string input;
                std::cin >> input;
                if (input == "1") {
                    extension="csv";
                    this->service.h = new CSVHandler;
                } else if (input == "0") {
                    extension="html";
                    this->service.h = new HTMLHandler;
                } else {
                    std::cout << "INVALID";
                }
            }

            int size;
            std::cout << "Enter the size of the coat you are looking for or -1 to display all coats: ";
            try {
                size = get_int();
            } catch(...) {
                std::cout << "INVALID SIZE";
                continue;
            }
            handle_user(size, extension);
        }
    }

    write_data();
}

