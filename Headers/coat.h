#pragma once

#include <string>
#include <iostream>

/*
 * COATS IDENTIFIED BY SIZE AND COLOR
 */
class Coat {
public:
    Coat() : size{0}, color{""}, price{0.0f}, quantity{0}, photo{""} {};

    Coat(int size, const std::string &color, float price, int quantity, const std::string &photo);

    std::string get_color() const { return this->color; }

    std::string get_photo() const { return this->photo; }

    float get_price() const { return this->price; }

    int get_size() const { return this->size; }

    int get_quantity() const { return this->quantity; }

    void update(int size, const std::string &color, float price, int quantity, const std::string &photo);

    std::string to_string();

    static bool compare_coats(Coat c1, Coat c2);

    friend std::ostream &operator<<(std::ostream &out, const Coat &c);

    friend std::istream &operator>>(std::istream &in, Coat &c);

private:
    int size;
    std::string color;
    float price;
    int quantity;
    std::string photo;
};