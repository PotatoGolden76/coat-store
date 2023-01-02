#pragma once
#include "repo.h"
#include "Handler.h"
#include <string>

class Service
{
    Repo& r;
public:
    Handler *h = nullptr;

    Service(Repo& rep);
    void add(int size, const std::string &color, float price, int quantity, const std::string &photo);
    void remove(int size, const std::string &color);
    void update(int size, const std::string &color, float price, int quantity, const std::string &photo);
    int get_size() const { return this->r.get_size(); }
    Repo& get_repo(){ return this->r; }
    void save(std::vector<Coat> v);
    Handler* get_handler() {return this->h;}
    ~Service();
};

