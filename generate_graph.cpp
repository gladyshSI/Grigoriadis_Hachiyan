#include "generate_graph.h"

adjlsts transpose(const adjlsts& P)
{
    size_t n = P.size();
    adjlsts P_T(n);

    for(auto row_id = 0; row_id < n; ++row_id)
    {
        for(const auto &[col_id, a]: P.at(row_id))
        {
            P_T.at(col_id).emplace_back(row_id, a);
        }
    }

    return P_T;
}


adjlsts generate_cycle(size_t n)
{
    adjlsts P(n);
 
    for(size_t i = 0; i < n; ++i)
    {
        size_t next_i = (i + 1)%n;
        size_t prev_i = (i - 1)%n;
        P.at(i) = {{prev_i, 0.5}, {next_i, 0.5}};
    }
    
    return P;
}

adjlsts generate_chain(size_t n)
{
    adjlsts P(n);
 
    P.at(0) = {{1, 1}};
    for(size_t i = 1; i < n - 1; ++i)
    {
        P.at(i) = {{i - 1, 0.5}, {i + 1, 0.5}};
    }
    P.at(n - 1) = {{n - 2, 1}};
 
    return P;
}

adjlsts generate_cube(size_t d)
{
    long long int n = pow(2, d);
    double p = 1.0/d;
    adjlsts P(n);

    for(auto i = 0; i < n; ++i)
    {
        size_t l = 0, r = n;
        for(auto j = 0; j < d; ++j)
        {
            auto m = (l + r)/2;
            if(i < m)
            {
                r = m;
                P.at(i).emplace_back(m + i - l, p);
            }
            else
            {
                l = m;
                P.at(i).emplace_back(m - (r - i), p);
            }
        }
    }

    return P;
}