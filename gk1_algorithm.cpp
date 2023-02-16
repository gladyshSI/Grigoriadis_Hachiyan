#include "gk1_algorithm.h"
#include "map_heap.h"
#include "gen_random_value.h"

adjlst subtract_id(const adjlsts &A, size_t row_id, size_t gap, bool negative)
{
    auto n = A.size();
    adjlst res;
    
    bool diag = false;
 
    for(const auto &[column_id, a]: A.at(row_id))
    {
        if(row_id != column_id)
        {
            if(a != 0)
            {
                res.emplace_back(column_id + gap, negative ? -a : a);
            }
        }
        else
        {
            if(a - 1 != 0)
            {
                res.emplace_back(column_id + gap, negative ? 1 - a : a - 1);
            }
            diag = true;
        }
    }
    if(!diag)
    {
        res.emplace_back(row_id + gap, negative ? 1 : -1);
    }
    
    return res;
}
 
 
adjlst GH_get_column(const adjlsts &P, const adjlsts &P_T, size_t column_id)
{
    size_t n = P.size();
    size_t N = 2*n;
    
    adjlst res;
    
    if(column_id < n)
    {
        res = subtract_id(P_T, column_id, n, true);
        res.emplace_back(N, 1);
    }
    else if(column_id < N)
    {
        res = subtract_id(P, column_id - n, 0, false);
        res.emplace_back(N, -1);
    }
    else
    {
        for(auto i = 0; i < N; ++i)
        {
            res.emplace_back(i, (i < n) ? -1 : 1);
        }
    }
    
    return res;
}
 
 
std::vector <double> GK1(const adjlsts &P, const adjlsts &P_T, const std::vector <double> &true_pgv, double eps, long long T, long long delta_t, const std::string &path_to_file)
{
    //auto start = std::chrono::high_resolution_clock::now();
 
    srand(time(nullptr));
 
    std::ofstream of(path_to_file);
    
    MapHeap mh;
    
    size_t n = P.size();
    size_t N = 2*n + 1;
    
    std::vector <double> initial_weights(N, 1);
    RandomGenerator generator(initial_weights);
    initial_weights.clear();
    std::vector <int> counter(N, 0);
    
    for(long long t = 1; t <= T; ++t)
    {
        if( t % 100000 == 0) cout << "t(%) = " << 100. * (t + 0.) / T << " % " << endl;

        int k = generator.generate();
        auto column = GH_get_column(P, P_T, k);
        for(const auto &[i, val]: column)
        {
            double w = generator.get_weight(i);
            generator.set_weight(i, w * std::exp(eps * val / 2.0));
            mh.add(i, val);
        }
        ++counter.at(k);
        
        if(t % delta_t == 0)
        {
            double error_inf = mh.max()/t;
            double error2 = -1;
            if(!true_pgv.empty())
            {
                error2 = 0.0;
                for(auto i = 0; i < n; ++i)
                {
                    auto tmp = 1.0*counter.at(i + n)/t - true_pgv.at(i);
                    error2 += tmp * tmp;
                }
                error2 = std::sqrt(error2);
            }
            //auto cur_time = std::chrono::high_resolution_clock::now();
            //auto passed_time = std::chrono::duration_cast<std::chrono::milliseconds>(cur_time - start).count();
            of << t << ',' << error_inf;
            if(error2 >= -0.01)
            {
                of << ',' << error2;
            }
            of << '\n';
        }
    }
    
    long long sum = 0;
    for(int i = n; i < 2*n; ++i)
    {
        sum += counter.at(i);
    }
 
    std::vector <double> pgv(n);
    for(int i = 0; i < n; ++i)
    {
        pgv.at(i) = 1.0*counter.at(i + n)/sum;
    }
    
    of.close();
    
    return pgv;
}