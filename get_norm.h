#pragma once
#include<vector>

using namespace std;

/// @return $\|param \cdot \Vec{a} - \Vec{b}\|_infty$
double get_inftyNormOfDifference(const vector<double>& a, const vector<double>& b, double param);

/// @return $\|param \cdot \Vec{a} - \Vec{b}\|_2$
double get_secondNormOfDifference(const vector<double>& a, const vector<double>& b, double param);