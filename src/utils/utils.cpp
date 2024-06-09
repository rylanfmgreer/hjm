#include "utils.hpp"
#include <algorithm>
#include <cmath>

namespace HJM
{
    std::vector<double> Utils::copy(const std::vector<double> p_v)
    {
        std::vector<double> new_vector(p_v.size());
        std::copy(p_v.begin(), p_v.end(), new_vector.begin());
        return new_vector;
    }

    std::vector< std::vector<double> > Utils::copy(
        const std::vector< std::vector<double>> p_mat)
    {
        std::vector< std::vector<double >> new_matrix(p_mat.size());
        std::transform(p_mat.begin(), p_mat.end(), new_matrix.begin(), [](const std::vector<double> x){ return copy(x); });
        return new_matrix;
    }
    double Utils::numerically_stable_exponential_diff(
        double p_positive_exp_arg, double p_negative_exp_arg)
    {
        double e_a = exp(p_positive_exp_arg);
        double e_b_minus_a = exp(p_negative_exp_arg - p_positive_exp_arg);
        return e_a * (1.0 - e_b_minus_a);
    }

       
} 
