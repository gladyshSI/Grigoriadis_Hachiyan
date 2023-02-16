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

std::vector <double> GK1(const adjlsts &P, const adjlsts &P_T, 
                                            const std::vector <double> &true_pgv, 
                                            double eps, long long T, long long delta_t, 
                                            const std::string &path_to_file);