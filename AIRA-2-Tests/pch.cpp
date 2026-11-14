//
// pch.cpp
//

#include "pch.h"

std::mt19937 generator{ std::random_device{}() };

int getInt(int min, int max) {
    std::uniform_int_distribution<int> dist(min, max);
    return dist(generator);
}