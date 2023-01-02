//
// Created by Robert Haranguș on 18/04/2022.
//
#pragma once
#include "coat.h"

class Handler {
public:
    virtual void save(std::vector<Coat> v) = 0;
};