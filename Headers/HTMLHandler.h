//
// Created by Robert Haranguș on 19/04/2022.
//

#pragma once
#include <vector>
#include "Handler.h"
#include "coat.h"

class HTMLHandler : public Handler {
public:
    void save(std::vector<Coat> v) override;
};