//
// Created by Robert Haranguș on 18/04/2022.
//

#include "../Headers/CSVHandler.h"
#include <fstream>

void CSVHandler::save(const std::vector<Coat> v) {
    std::ofstream out("basket_list.csv");

    for(const Coat& c : v) {
        out << c.get_size() << ",";
        out << c.get_color() << ",";
        out << c.get_price() << ",";
        out << c.get_quantity() << ",";
        out << c.get_photo() << "\n";
    }

    out.close();
}
