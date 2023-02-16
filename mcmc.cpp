#include<iostream>
#include<fstream>
#include "mcmc.h"
#include "gen_random_value.h"
#include "get_norm.h"
#include "map_heap.h"

using namespace std;

vector<vector<double>> make_cumulative_weights(const adjlsts& P)
{
    vector<vector<double>> cumulative_weights;
    for(const auto& row : P)
    {
        double sum = 0.;
        cumulative_weights.push_back({sum});
        for(const auto& [column_id, p] : row)
        {
            sum += p;
            cumulative_weights.back().push_back(sum);
        }
    }
    return cumulative_weights;
}

vector<double> PTdot(const adjlsts& P, const vector<double>& v)
{
    if(v.size() != P.size()) 
    {
        throw std::invalid_argument( "v.size() != P.size()" );
    }
    size_t n = v.size();
    vector<double> answer(n);

    for(int i = 0; i < n; ++i)
    {
        const auto& row = P.at(i);
        for(int j = 0; j < row.size(); ++j)
        {
            double pij = row.at(j).second;
            answer[j] += v[i] * pij;
        }
    }

    return answer;
}


/// @brief MCMC algorithm for finding PageRank vector (see https://www.mathnet.ru/links/2d46d176f79b3a4d43b6cfcb7f994656/zvmmf10164.pdf)
/// @param gr -- our web-graph
/// @param get_norm -- if it true than we safe statistics every @param each_time to @param file_name file.
/// @param truePRV -- theoretical PageRank vector (if it is known)
/// @return PageRank vector
vector<double> mcmc(const adjlsts& gr, int t_start, int t_end, bool get_norm, const vector<double>& truePRV, int each_time, const string& file_name)
{
    ofstream file;
    file.open(file_name);

    size_t n = gr.size();
    vector<vector<double>> cumulative_weights = make_cumulative_weights(gr);

    vector<double> answer(n);
    double delta  = 1. / (t_end - t_start);
    int from = 0;

    for(int t = 1; t <= t_end; ++t)
    {
        if( t % 100000 == 0) cout << "t(%) = " << 100. * (t + 0.) / t_end << " % " << endl;

        int to_id = random_choice_id(cumulative_weights[from]);
        from = gr.at(from).at(to_id).first;

        if(t >= t_start)
        {
            answer[from] += delta;
        }

        if(get_norm && t % each_time == 0 && t > t_start)
        {
            double param = (t_end - t_start) / (t - t_start);
            double norm = get_inftyNormOfDifference(PTdot(gr, answer), answer, param);
            double secondNorm = get_secondNormOfDifference(answer, truePRV, param);
            file << t << "," << norm << "," << secondNorm << endl;
        }
    }
    return answer;
}
