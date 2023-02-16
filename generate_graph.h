#pragma once
#include <iostream>
#include <vector>
#include <random>
#include <map>
#include <set>
#include <fstream>
#include <chrono>

typedef std::vector <std::pair <size_t, double>> adjlst;
typedef std::vector <std::vector <std::pair <size_t, double>>> adjlsts;

adjlsts transpose(const adjlsts& P);
adjlsts generate_cycle(size_t n);
adjlsts generate_chain(size_t n);

/// @return @param d demensional cube 
adjlsts generate_cube(size_t d); 