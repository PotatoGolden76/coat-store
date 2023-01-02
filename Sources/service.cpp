#include "../Headers/service.h"

Service::Service(Repo &rep) : r{rep}{}

void Service::add(int size, const std::string &color, float price, int quantity, const std::string &photo) {
    Coat c = Coat(size, color, price, quantity, photo);
    this->r.add(c);
}

void Service::update(int size, const std::string &color, float price, int quantity, const std::string &photo) {
    this->r.get_at(this->r.get_index(size, color)).update(size, color, price, quantity, photo);
}

void Service::remove(int size, const std::string &color) {
    Coat c = Coat(size, color, 0.0f, 0, "");
    this->r.remove(c);
}

void Service::save(std::vector<Coat> v) {
    this->h->save(v);
}

Service::~Service() {
    delete this->h;
}
