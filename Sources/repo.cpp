#include "../Headers/repo.h"
#include "../Headers/validator.h"

bool Repo::has(const Coat &c) {
    for (const Coat &i: this->data) {
        if (Coat::compare_coats(c, i)) {
            return true;
        }
    }
    return false;
}

void Repo::add(const Coat &c) {
    if(!Validator::validate_price(c.get_price()))
        throw repo_exception("Invalid price");
    this->data.push_back(c);
}

void Repo::remove(const Coat &c) {
    auto it = std::find_if(this->data.begin(), this->data.end(), [&c](const Coat c2) { return Coat::compare_coats(c, c2); });
    this->data.erase(it);
}

Coat &Repo::get_at(int index) {
    return this->data[index];
}

int Repo::get_index(int size, const std::string &color) {
    Coat c = Coat(size, color, 0, 0, "");
    auto it = std::find_if(this->data.begin(), this->data.end(), [&c](const Coat c2) { return Coat::compare_coats(c, c2); });
    return it - this->data.begin();
}

bool Repo::has(int size, const std::string &color) {
    Coat c = Coat(size, color, 0.0f, 0, "");
    for (const Coat &i: this->data) {
        if (Coat::compare_coats(c, i)) {
            return true;
        }
    }
    return false;
}
