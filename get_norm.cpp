#include "get_norm.h"
#include<stdexcept>
#include<cmath>
using namespace std;



/// @return $\|param \cdot \Vec{a} - \Vec{b}\|_infty$
double get_inftyNormOfDifference(const vector<double>& a, const vector<double>& b, double param)
{
    double answer = -1.;
    if(a.size() != b.size())
    {
        throw std::invalid_argument( "a.size() != b.size()" );
    }

    for(int i = 0; i < a.size(); ++i)
    {
        double delta = abs(a[i] * param - b[i]);
        if( delta > answer) answer = delta; 
    }
    return answer;
}


/// @return $\|param \cdot \Vec{a} - \Vec{b}\|_2$
double get_secondNormOfDifference(const vector<double>& a, const vector<double>& b, double param)
{
    double answer = 0.;
    if(a.size() != b.size())
    {
        throw std::invalid_argument( "a.size() != b.size()" );
    }

    for(int i = 0; i < a.size(); ++i)
    {
        double delta = param * a[i] - b[i];
        answer += delta * delta; 
    }
    return sqrt(answer);
}