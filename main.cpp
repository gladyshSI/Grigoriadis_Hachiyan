#include<iostream>
#include "mcmc.h"
#include "get_norm.h"
#include "generate_graph.h"
#include "gk1_algorithm.h"
#include "gk2_algorithm.h"


void test_chain_graphs(int n, int Tmax, double eps, int delta_t = 1000, string dir_to_save = "../")
{
    auto P = generate_chain(n);
    auto P_T = transpose(P);

    vector<double> truePRV(n);
    for(int i = 0; i < n; ++i)
    {
        if(i == 0 || i == n-1)
        {
            truePRV[i] = 1. / (2 * (n-1));
        }
        else
        {
            truePRV[i] = 1./ (n-1);
        }
    }

    string prefix = dir_to_save+"chain_"+to_string(n);
    cout << "..... GK1 STARTED ......" << endl;
    auto pgv1 = GK1(P, P_T, truePRV, eps, Tmax, delta_t, prefix+"_GK1.csv");
    cout << "..... (results saved in " + prefix + "_GK1.csv) ......" << endl;

    cout << "..... GK2 STARTED ......" << endl;
    auto pgv2 = GK2(P, P_T, truePRV, Tmax, delta_t, prefix+"_GK2.csv");
    cout << "..... (results saved in " + prefix + "_GK2.csv) ......" << endl;

    cout << "..... MCMC STARTED ......" << endl;
    auto pgv3 = mcmc(P, Tmax /  5, Tmax, true, truePRV, delta_t, prefix+"_MCMC.csv");
    cout << "..... (results saved in " + prefix + "_MCMC.csv) ......" << endl;
}

void test_cycle_graphs(int n, int Tmax, double eps, int delta_t = 1000, string dir_to_save = "../")
{
    auto P = generate_cycle(n);
    auto P_T = transpose(P);

    vector<double> truePRV(n);
    for(int i = 0; i < n; ++i)
    {
        truePRV[i] = 1. / n;
    }

    string prefix = dir_to_save+"cycle_"+to_string(n);
    cout << "..... GK1 STARTED ......" << endl;
    auto pgv1 = GK1(P, P_T, truePRV, eps, Tmax, delta_t, prefix+"_GK1.csv");
    cout << "..... (results saved in " + prefix + "_GK1.csv) ......" << endl;

    cout << "..... GK2 STARTED ......" << endl;
    auto pgv2 = GK2(P, P_T, truePRV, Tmax, delta_t, prefix+"_GK2.csv");
    cout << "..... (results saved in " + prefix + "_GK2.csv) ......" << endl;

    cout << "..... MCMC STARTED ......" << endl;
    auto pgv3 = mcmc(P, Tmax /  5, Tmax, true, truePRV, delta_t, prefix+"_MCMC.csv");
    cout << "..... (results saved in " + prefix + "_GK1.csv) ......" << endl;
}

void test_cube_graphs(int d, int Tmax, double eps, int delta_t = 1000, string dir_to_save = "../")
{
    auto P = generate_cube(d);
    auto P_T = transpose(P);

    int n = pow(2, d);
    vector<double> truePRV(n);
    for(int i = 0; i < n; ++i)
    {
        truePRV[i] = 1. / n;
    }

    string prefix = dir_to_save+"cube_"+to_string(d);
    cout << "..... GK1 STARTED ......" << endl;
    auto pgv1 = GK1(P, P_T, truePRV, eps, Tmax, delta_t, prefix+"_GK1.csv");
    cout << "..... (results saved in " + prefix + "_GK1.csv) ......" << endl;

    cout << "..... GK2 STARTED ......" << endl;
    auto pgv2 = GK2(P, P_T, truePRV, Tmax, delta_t, prefix+"_GK2.csv");
    cout << "..... (results saved in " + prefix + "_GK2.csv) ......" << endl;

    cout << "..... MCMC STARTED ......" << endl;
    auto pgv3 = mcmc(P, Tmax /  5, Tmax, true, truePRV, delta_t, prefix+"_MCMC.csv");
    cout << "..... (results saved in " + prefix + "_GK1.csv) ......" << endl;
}


int main()
{
    vector<int> d_list = {1};
    
    // Test algorithms on CHAIN graphs: 
    cout << "Testing CHAIN graphs:" << endl;
    for(int d : d_list)
    {
        int n = pow(2, d);

        double eps = 0.01;
        int Tmax = (n < 1e6) ? 1e6 : 1e7;
        int delta_t = (n < 1e6) ? 1e3 : 1e4;

        cout << "n = " << n << ", Tmax = " << Tmax << ", eps = " << eps << ", delta_t = " << delta_t << endl;
        test_chain_graphs(n, Tmax, eps, delta_t, "../chain/");
    }

    // Test algorithms on CYCLE graphs:
    // cout << "Testing CYCLE graphs:" << endl;
    // for(int d : d_list)
    // {
    //     int n = pow(2, d);

    //     double eps = 0.01;
    //     int Tmax = (n < 1e6) ? 1e6 : 1e7;
    //     int delta_t = (n < 1e6) ? 1e3 : 1e4;

    //     cout << "n = " << n << ", Tmax = " << Tmax << ", eps = " << eps << ", delta_t = " << delta_t << endl;
    //     test_cycle_graphs(n, Tmax, eps, delta_t, "../cycle/");
    // }

    // Test algorithms on CUBE graphs:
    cout << "Testing CUBE graphs:" << endl;
    for(int d : d_list)
    {
        double eps = 0.01;
        int Tmax = (d < 20) ? 1e6 : 1e7;
        int delta_t = (d < 20) ? 1e3 : 1e4;

        cout << "d = " << d << ", Tmax = " << Tmax << ", eps = " << eps << ", delta_t = " << delta_t << endl;
        test_cube_graphs(d, Tmax, eps, delta_t, "../cube/");
    }


    return 0;
}