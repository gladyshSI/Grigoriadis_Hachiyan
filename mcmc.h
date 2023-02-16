#pragma once
#include<vector>
using namespace std;

typedef std::vector <std::pair <size_t, double>> adjlst;
typedef std::vector <std::vector <std::pair <size_t, double>>> adjlsts;

/// @brief MCMC algorithm for finding PageRank vector (see https://www.mathnet.ru/links/2d46d176f79b3a4d43b6cfcb7f994656/zvmmf10164.pdf)
/// @param gr -- our web-graph
/// @param get_norm -- if it true than we safe statistics every @param each_time to @param file_name file.
/// @param truePRV -- theoretical PageRank vector (if it is known)
/// @return PageRank vector
vector<double> mcmc(const adjlsts& gr, int t_start, int t_end, bool get_norm = false, const vector<double>& truePRV = {}, int each_time = 100, const string& file_name = "../mcmcOut.csv");
