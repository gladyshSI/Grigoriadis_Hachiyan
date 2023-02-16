#include<random>
#include<vector>
using namespace std;

int random_choice_id(const vector<double>& cumulative_probabilities, double norm = 1.);

int uniform_random_choice(const vector<int>& values);

class RandomGenerator
{
    int n;
    std::vector <double> _nodes;
 
 public:
    RandomGenerator(const std::vector <double> &weights);
 
    int generate() const;
    void set_weight(int id, double new_weight);
    double get_weight(int id) const;
};
