#include "gk2_algorithm.h"
#include "map_heap.h"
#include "gen_random_value.h"

 
adjlst GK_get_row(const adjlsts &P, size_t row_id)
{
    size_t n = P.size();
    
    adjlst res;
    
    bool diag = false;
    
    for(const auto &[column_id, p]: P.at(row_id))
    {
        if(row_id != column_id)
        {
            res.emplace_back(column_id, p);
            res.emplace_back(n + column_id, -p);
        }
        else
        {
            res.emplace_back(column_id, p - 1);
            res.emplace_back(n + column_id, 1 - p);
            diag = true;
        }
    }
    
    if(!diag)
    {
        res.emplace_back(row_id, -1);
        res.emplace_back(n + row_id, 1);
    }
    
    return res;
}
 
 
adjlst GK_get_column(const adjlsts &P_T, size_t column_id)
{
    size_t n = P_T.size();
    
    adjlst res;
    
    bool diag = false;
    
    for(const auto &[row_id, p]: P_T.at(column_id % n))
    {
        if(row_id != column_id)
        {
            res.emplace_back(row_id, column_id < n ? p : -p);
        }
        else
        {
            res.emplace_back(row_id, column_id < n ? p - 1 : 1 - p);
            diag = true;
        }
    }
    
    if(!diag)
    {
        res.emplace_back(column_id % n, column_id < n ? -1 : 1);
    }
    
    return res;
}
 
 
std::vector <double> GK2(const adjlsts &P, const adjlsts &P_T, const std::vector <double> &true_pgv, long long T, long long delta_t, const std::string &path_to_file)
{
    auto start = std::chrono::high_resolution_clock::now();
 
    srand(time(nullptr));
 
    std::ofstream of(path_to_file);
    
    MapHeap mh;
    
    size_t n = P.size();
    
    double lr_A = std::sqrt(2*std::log(2*n)/T);
    double lr_B = std::sqrt(2*std::log(n)/T);
    
    std::vector <double> initial_weights_A(2*n, 1);
    std::vector <double> initial_weights_B(n, 1);
    RandomGenerator gen_A(initial_weights_A);
    RandomGenerator gen_B(initial_weights_B);
    initial_weights_A.clear();
    initial_weights_B.clear();
    
    std::vector <int> x(n, 0);
    std::vector <int> y(2*n, 0);
    
    for(long long t = 1; t <= T; ++t)
    {
        if( t % 100000 == 0) cout << "t(%) = " << 100. * (t + 0.) / T << " % " << endl;

        auto column_id = gen_A.generate();
        auto row_id = gen_B.generate();
        ++x.at(row_id);
        ++y.at(column_id);
        auto row = GK_get_row(P, row_id);
        auto column = GK_get_column(P_T, column_id);
        for(const auto &[j, a]: row)
        {
            gen_A.set_weight(j, gen_A.get_weight(j) * std::exp(lr_A * a));
        }
        for(const auto &[i, a]: column)
        {
            gen_B.set_weight(i, gen_B.get_weight(i) * std::exp(-lr_B * a));
        }
        
        auto col = GK_get_column(P_T, row_id);
        for(const auto &[i, a]: col)
        {
            mh.add(i, a);
        }
        
        if(t % delta_t == 0)
        {
            double error_inf = mh.max()/t;
            double error2 = -1;
            if(!true_pgv.empty())
            {
                error2 = 0.0;
                for(auto i = 0; i < n; ++i)
                {
                    auto tmp = 1.0*x.at(i)/t - true_pgv.at(i);
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
    
    std::vector <double> pgv(n);
    
    for(auto i = 0; i < n; ++i)
    {
        pgv.at(i) = 1.0*x.at(i)/T;
    }
    
    of.close();
    
    return pgv;
}