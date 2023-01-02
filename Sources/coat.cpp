#include <vector>
#include "../Headers/coat.h"

Coat::Coat(int size, const std::string &color, float price, int quantity, const std::string &photo) : size{size}, color{color}, price{price}, quantity{quantity}, photo{photo}{

}

std::string Coat::to_string() {
    std::string s;
    s += "Size:" + std::to_string(this->size) + "| ";
    s += "Color:" + this->color + "| ";
    s += "Price:" + std::to_string(this->price) + "| ";
    s += "Quantity:" + std::to_string(this->quantity) + "| ";
    s += "Photo:" + this->photo;
    return s;
}

void Coat::update(int size, const std::string &color, float price, int quantity, const std::string &photo) {
    this->size = size;
    this->color = color;
    this->price = price;
    this->quantity = quantity;
    this->photo = photo;
}

bool Coat::compare_coats(Coat c1, Coat c2) {
    if(c1.get_size() == c2.get_size() && c1.get_color() == c2.get_color())
        return true;
    return false;
}

std::istream &operator>>(std::istream &in, Coat &c) {
    std::string buffer;
    std::getline(in, buffer);

    buffer+=" ";
    std::vector<std::string> tokens;

    size_t pos = 0;
    while ((pos = buffer.find(" ")) != std::string::npos) {
        tokens.push_back(buffer.substr(0, pos));
        buffer.erase(0, pos+1);
    }

    c.size = std::stoi(tokens[0]);
    c.color = tokens[1];
    c.price = std::stof(tokens[2]);
    c.quantity = std::stoi(tokens[3]);
    c.photo = tokens[4];

    return in;
}

std::ostream &operator<<(std::ostream &out, const Coat &c) {
    out << c.size << " " << c.color << " " << c.price << " ";
    out << c.quantity << " " << c.photo;
    return out;
}
