//
// Created by Robert Haranguș on 18/04/2022.
//
#pragma once
#include <vector>
#include "Handler.h"
#include "coat.h"

class CSVHandler : public Handler {
public:
    void save(std::vector<Coat> v) override;
};