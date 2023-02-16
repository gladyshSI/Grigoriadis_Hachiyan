#include<iostream>
#include<cmath>
#include"gen_random_value.h"

int random_choice_id(const vector<double>& cumulative_probabilities, double norm)
{
    std::random_device rd;  
    std::mt19937 gen(rd()); 
    std::uniform_real_distribution<> dis(0.0, norm);
    double alpha = dis(gen);

    // Bin search
    int left = 0;
    int right = cumulative_probabilities.size() - 1;
    while(right - left >= 2)
    {
        int mid = (left + right) / 2;
        (cumulative_probabilities[mid] <= alpha) ? left = mid : right = mid;
    }
    return right - 1;
}

int uniform_random_choice(const vector<int>& values)
{
    std::random_device rd;  
    std::mt19937 gen(rd()); 
    std::uniform_real_distribution<> dis(0.0, values.size() + 0.);
    double alpha = dis(gen);

    return values[(int)floor(alpha)];
}

RandomGenerator::RandomGenerator(const std::vector <double> &weights): n(weights.size())
{
    _nodes.resize(2*n);

    for(int i = 0; i < n; ++i)
    {
        _nodes.at(n + i) = weights.at(i);
    }

    for(int i = n - 1; i >= 1; --i)
    {
        int i1 = 2*i;
        int i2 = i1 + 1;
        _nodes.at(i) = _nodes.at(i1) + _nodes.at(i2);
    }
}

int RandomGenerator::generate() const
{
    int cur_node = 1;
    while(cur_node < n)
    {
        int child1 = cur_node * 2;
        int child2 = child1 + 1;
        double w = _nodes.at(cur_node);
        double w1 = _nodes.at(child1);
        double r = 1.0 * rand() / RAND_MAX;
        if(r < w1/w)
        {
            cur_node = child1;
        }
        else
        {
            cur_node = child2;
        }
    }
    return cur_node - n;
}

void RandomGenerator::set_weight(int id, double new_weight)
{
    _nodes[n + id] = new_weight;
    int cur_node = n + id;
    while(cur_node > 1)
    {
        cur_node /= 2;
        int child1 = 2 * cur_node;
        int child2 = child1 + 1;
        _nodes.at(cur_node) = _nodes.at(child1) + _nodes.at(child2);
    }
}

double RandomGenerator::get_weight(int id) const
{
    return _nodes.at(n + id);
}