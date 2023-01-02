//
// Created by Robert Haranguș on 19/04/2022.
//

#include "../Headers/CSVHandler.h"
#include "../Headers/HTMLHandler.h"
#include <fstream>

void HTMLHandler::save(const std::vector<Coat> v) {
    std::ofstream out("basket_list.html");
    out << "<!DOCTYPE html><html><head><title>Shopping basket_list</title><style>table, th, td {\n"
           "  border: 1px solid;\n"
           "}</style></head><body><table>";
    out << "        <tr>\n"
           "            <td>Size</td>\n"
           "            <td>Color</td>\n"
           "            <td>Price</td>\n"
           "            <td>Quantity</td>\n"
           "            <td>Photo</td>\n"
           "        </tr>";
    for (const Coat &c: v) {
        out << "<tr>";

        out << "<td>" << c.get_size() << "</td>";
        out << "<td>" << c.get_color() << "</td>";
        out << "<td>" << c.get_price() << "</td>";
        out << "<td>" << c.get_quantity() << "</td>";
        out << "<td><a href=\"" << c.get_photo() << "\">PHOTO</a></td>";

        out << "</tr>";
    }
    out << "</table></body></html>";
    out.close();
}
