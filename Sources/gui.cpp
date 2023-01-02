//
// Created by Robert Haranguș on 10/05/2022.
//

#include <fstream>
#include <QOpenGLContext>
#include <QOpenGLContextGroup>
#include <QtGui>
#include "../Headers/gui.h"

GUI::GUI(Service &service, QWidget *parent):service(service) {
    read_data();
    this->initGUI();
    this->populate_coat_list();

}

void GUI::read_data() {
    std::ifstream in("data.txt");
    while (!in.eof()) {
        Coat tmp;
        in >> tmp;
        this->service.get_repo().add(tmp);
    }
    in.close();
}

void GUI::write_data() {
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

GUI::~GUI() {
    this->close_app();
}

void GUI::initGUI() {
    //General layout of the window
    auto* layout = new QHBoxLayout{ this };

/// ------------------------------- LEFT SIDE
    /// -----------------------LIST
    this->filter_bar = new QLineEdit{};
    QFont filter{"Verdana", 10};
    this->filter_bar->setFont(filter);

    this->coat_list = new QListWidget{};
    this->coat_list->setSelectionMode(QAbstractItemView::SingleSelection);

    auto* allCoatsLabel = new QLabel{"All Coats" };

    auto* leftSide = new QWidget{};
    auto* leftLayout = new QVBoxLayout{leftSide};

    QObject::connect(this->filter_bar, &QLineEdit::textChanged, this, &GUI::textEdited);

    leftLayout->addWidget(allCoatsLabel);
    leftLayout->addWidget(this->filter_bar);
    leftLayout->addWidget(this->coat_list);

    /// -----------------------Coat DATA
    auto* formLayout = new QWidget{};
    auto* CoatLayout = new QFormLayout{formLayout };

    this->size_field = new QLineEdit{};
    this->color_field = new QLineEdit{};
    this->price_field = new QLineEdit{};
    this->quantity_field = new QLineEdit{};
    this->photo_field = new QLineEdit{};

    QFont f{ "Verdana", 10 };
    auto* size_label = new QLabel{"&Size:" };
    size_label->setBuddy(this->size_field);
    auto* color_label = new QLabel{"&Color:" };
    color_label->setBuddy(this->color_field);
    auto* price_label = new QLabel{"&Quantity:" };
    price_label->setBuddy(this->price_field);
    auto* quantity_label = new QLabel{"&Price:" };
    quantity_label->setBuddy(this->quantity_field);
    auto* photo_label = new QLabel{"&Photo:" };
    photo_label->setBuddy(this->photo_field);

    size_label->setFont(f);
    color_label->setFont(f);
    price_label->setFont(f);
    quantity_label->setFont(f);
    photo_label->setFont(f);

    this->size_field->setFont(f);
    this->color_field->setFont(f);
    this->price_field->setFont(f);
    this->quantity_field->setFont(f);
    this->photo_field->setFont(f);

    CoatLayout->addRow(size_label, this->size_field);
    CoatLayout->addRow(color_label, this->color_field);
    CoatLayout->addRow(price_label, this->price_field);
    CoatLayout->addRow(quantity_label, this->quantity_field);
    CoatLayout->addRow(photo_label, this->photo_field);

    leftLayout->addWidget(formLayout);

    ///----------------------- BUTTONS
    auto* buttonsWidget = new QWidget{};
    auto* gridLayout = new QGridLayout{buttonsWidget};

    this->add_coat = new QPushButton("Add");
    this->add_coat->setFont(f);
    this->remove_coat = new QPushButton("Remove");
    this->remove_coat->setFont(f);
    this->update_coat = new QPushButton("Update");
    this->update_coat->setFont(f);


    gridLayout->addWidget(this->add_coat, 0, 0);
    gridLayout->addWidget(this->remove_coat, 0, 1);
    gridLayout->addWidget(this->update_coat, 0, 2);


    leftLayout->addWidget(buttonsWidget);

///------------------------------- MID SIDE
    auto* middleSide = new QWidget{};
    auto* middleLayout = new QVBoxLayout{middleSide};

    this->b_add_to_basket = new QPushButton(">");
    this->b_add_to_basket->setFont(f);

    middleLayout->addWidget(this->b_add_to_basket);


///------------------------------- RIGHT SIDE
    auto* rightSide = new QWidget{};
    auto* rightLayout = new QVBoxLayout{rightSide};

    this->basket_list = new QListWidget{};
    this->basket_list->setSelectionMode(QAbstractItemView::SingleSelection);
    auto* basket_label = new QLabel{"Basket" };

    rightLayout->addWidget(basket_label);
    rightLayout->addWidget(this->basket_list);

    auto* basket_buttons = new QWidget{};
    auto* basket_grid = new QGridLayout{basket_buttons};

    this->b_open_photo = new QPushButton("Show Photo");
    this->b_open_photo->setFont(f);
    this->html = new QPushButton("Save HTML");
    this->html->setFont(f);
    this->csv = new QPushButton("Save CSV");
    this->csv->setFont(f);
    this->b_next = new QPushButton("Next");
    this->b_next->setFont(f);

    basket_grid->addWidget(this->b_open_photo, 0, 0);
    basket_grid->addWidget(this->b_next, 0, 1);
    basket_grid->addWidget(this->html, 1, 0);
    basket_grid->addWidget(this->csv, 1, 1);

    rightLayout->addWidget(basket_buttons);

    /// ------------------------------- ADD ALL
    layout->addWidget(leftSide);
    layout->addWidget(middleSide);
    layout->addWidget(rightSide);

    QObject::connect(this->coat_list, &QListWidget::currentTextChanged, this, &GUI::currentTextChanged);
    QObject::connect(this->b_add_to_basket, &QPushButton::released, this, &GUI::addToBasket);
    QObject::connect(this->add_coat, &QPushButton::released, this, &GUI::add);
    QObject::connect(this->remove_coat, &QPushButton::released, this, &GUI::remove);
    QObject::connect(this->update_coat, &QPushButton::released, this, &GUI::update_button_function_too_many_names_aaaaa);
    QObject::connect(this->b_open_photo, &QPushButton::released, this, &GUI::open_photo);
    QObject::connect(this->b_next, &QPushButton::released, this, &GUI::next);
    QObject::connect(this->html, &QPushButton::released, this, &GUI::save_html);
    QObject::connect(this->csv, &QPushButton::released, this, &GUI::save_csv);

    QLinearGradient grad(0, 0, 0, this->basket_list->height());
    grad.setColorAt(0, Qt::white);
    grad.setColorAt(1, Qt::black);

    QPalette pal = this->basket_list->palette();
    pal.setBrush(QPalette::ColorRole::Base, QBrush(grad));
    this->basket_list->setPalette(pal);

}

void GUI::populate_coat_list() {
    this->coat_list->clear();

    for(Coat m : this->service.get_repo().get_data())
        this->coat_list->addItem(QString::fromStdString(m.to_string()));
    this->coat_list->setCurrentRow(this->current_list_index);
}

void GUI::textEdited(const QString &new_text) {
    this->coat_list->clear();
    this->size_field->clear();
    this->color_field->clear();
    this->price_field->clear();
    this->quantity_field->clear();
    this->photo_field->clear();

    int count = 0;
    for (Coat m: this->service.get_repo().get_data())
        if (m.to_string().find(new_text.toStdString()) != std::variant_npos) {
            this->coat_list->addItem(QString::fromStdString(m.to_string()));
            count++;
        }
    if(this->current_list_index == count) {
        this->current_list_index = 0;
    }
    this->coat_list->setCurrentRow(this->current_list_index);
}

void GUI::currentTextChanged(const QString &currentText) {
    std::cout << "selected: " << currentText.toStdString() << std::endl;

    if(!this->coat_list->currentItem())
        return;

    std::string selection = this->coat_list->currentItem()->text().toStdString();
    Coat c = this->get_coat_from_string(selection);

    this->size_field->setText(QString::fromStdString(std::to_string(c.get_size())));
    this->color_field->setText(QString::fromStdString(c.get_color()));
    this->price_field->setText(QString::fromStdString(std::to_string(c.get_price())));
    this->quantity_field->setText(QString::fromStdString(std::to_string(c.get_quantity())));
    this->photo_field->setText(QString::fromStdString(c.get_photo()));
}

void GUI::addToBasket() {
    if(!this->coat_list->currentItem())
        return;

    std::string selection_color, selection_size;
    selection_color = this->color_field->text().toStdString();
    selection_size = this->size_field->text().toStdString();
    Coat selection = this->service.get_repo().get_at(this->service.get_repo().get_index(stoi(selection_size), selection_color));
    this->basket_vector.push_back(selection);

    this->current_list_index++;
    if(this->current_list_index == this->service.get_size()) {
        this->current_list_index = 0;
    }
    this->coat_list->setCurrentRow(this->current_list_index);
    populate_basket_list();
}

void GUI::populate_basket_list() {
    this->basket_list->clear();

    for(Coat m : this->basket_vector)
        this->basket_list->addItem(QString::fromStdString(m.to_string()));
    this->basket_list->setCurrentRow(this->current_basket_index);
}

void GUI::add() {
    if(this->size_field->text().isEmpty() || this->color_field->text().isEmpty() || this->price_field->text().isEmpty() || this->quantity_field->text().isEmpty() || this->photo_field->text().isEmpty())
        return;
    int size;
    std::string color;
    float price;
    int quantity;
    std::string photo;

    try {
        size = stoi(this->size_field->text().toStdString());
        color = this->color_field->text().toStdString();
        price = stof(this->price_field->text().toStdString());
        quantity = stoi(this->quantity_field->text().toStdString());
        photo = this->photo_field->text().toStdString();
    } catch(...) {
        std::cout << "Invalid Arguments\n";
        return;
    }

    if(!this->service.get_repo().has(size, color)) {
        this->service.add(size, color, price, quantity, photo);
    }
    populate_coat_list();
}

void GUI::update_button_function_too_many_names_aaaaa() {
    if(this->size_field->text().isEmpty() || this->color_field->text().isEmpty() || this->price_field->text().isEmpty() || this->quantity_field->text().isEmpty() || this->photo_field->text().isEmpty())
        return;
    int size;
    std::string color;
    float price;
    int quantity;
    std::string photo;

    try {
        size = stoi(this->size_field->text().toStdString());
        color = this->color_field->text().toStdString();
        price = stof(this->price_field->text().toStdString());
        quantity = stoi(this->quantity_field->text().toStdString());
        photo = this->photo_field->text().toStdString();
    } catch(...) {
        std::cout << "Invalid Arguments\n";
        return;
    }

    if(!this->service.get_repo().has(size, color)) {
        return;
    }

    this->service.update(size, color, price, quantity, photo);
    populate_coat_list();
}

void GUI::remove() {
    if(this->size_field->text().isEmpty() || this->color_field->text().isEmpty())
        return;

    int size;
    std::string color;
    try {

        size = stoi(this->size_field->text().toStdString());
        color = this->color_field->text().toStdString();
    } catch (...) {
        std::cout << "Invalid Arguments\n";
        return;
    }

    if(!this->service.get_repo().has(size, color)) {
        return;
    }
    this->service.remove(size, color);
    populate_coat_list();
}

void GUI::open_photo() {
    if(!this->basket_list->currentItem())
        return;
    std::string selection = this->basket_list->currentItem()->text().toStdString();
    Coat c = this->get_coat_from_string(selection);
    QDesktopServices::openUrl(QUrl(c.get_photo().c_str(), QUrl::TolerantMode));
}

void GUI::next() {
    this->current_list_index++;
    if(this->current_list_index == this->service.get_size()) {
        this->current_list_index = 0;
    }
    this->coat_list->setCurrentRow(this->current_list_index);
}

Coat GUI::get_coat_from_string(std::string selection) {
    selection += "|";
    std::vector<std::string> tokens_bad, tokens;

    size_t pos = 0;
    while ((pos = selection.find("|")) != std::string::npos) {
        tokens_bad.push_back(selection.substr(0, pos));
        selection.erase(0, pos+1);
    }

    pos = 0;
    for(auto & i : tokens_bad) {
        while ((pos = i.find(":")) != std::string::npos) {
            i.erase(0, pos+1);
            tokens.push_back(i);
        }
    }
    auto c = Coat(std::stoi(tokens[0]), tokens_bad[1], std::stof(tokens_bad[2]), std::stoi(tokens_bad[3]), tokens_bad[4]);

    return c;
}

void GUI::close_app() {
    this->write_data();
}

void GUI::save_html() {
    this->html_handler.save(this->basket_vector);
    QDesktopServices::openUrl(QUrl("C:/Users/rober/Desktop/University/Repos/A5-6-OOP/cmake-build-debug-coverage/basket_list.html", QUrl::TolerantMode));
}

void GUI::save_csv() {
    this->csv_handler.save(this->basket_vector);
    QDesktopServices::openUrl(QUrl("C:/Users/rober/Desktop/University/Repos/A5-6-OOP/cmake-build-debug-coverage/basket_list.csv", QUrl::TolerantMode));
}
