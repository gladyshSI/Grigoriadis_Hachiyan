#pragma once
#include <iostream>
#include <vector>
#include <random>
#include <map>
#include <set>
#include <fstream>
#include <chrono>

class MapHeap
{
    std::map <size_t, double> _mp;
    std::set <std::pair <double, size_t>> _set;
    
public:
    MapHeap() = default;
    void add(size_t id, double val);
    double max() const;
};