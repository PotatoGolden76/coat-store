#pragma once
#include "DynamicArray.h"
#include "Coat.h"
#include <vector>
#include <algorithm>

class repo_exception : public std::exception {

public:

    explicit repo_exception(const std::string& msg) : msg_(msg) {}
    ~repo_exception() override = default;

    std::string get_msg() const {return(msg_);}
private:
    std::string msg_;
};

class Repo {
private:
    std::vector<Coat> data;
public:
    void add(const Coat &c);
    void remove(const Coat &c);

    bool has(const Coat &c);
    bool has(int size, const std::string& color);

    int get_size() { return this->data.size(); }
    int get_index(int size, const std::string& color);
    Coat& get_at(int index);

    const std::vector<Coat> get_data() const { return this->data; }
};