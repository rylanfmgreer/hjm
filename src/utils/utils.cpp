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
    double Utils::improved_diff_of_exponentials(
        double p_positive_exp_arg, double p_negative_exp_arg)
    {
        double a_plus_b_over_2 = 0.5 * (p_positive_exp_arg + p_negative_exp_arg);
        double a_minus_b_over_2 = 0.5 * (p_positive_exp_arg - p_negative_exp_arg);
        double scalar = exp(a_plus_b_over_2);
        double diff = (exp(a_minus_b_over_2) - exp(-a_minus_b_over_2));
        return scalar * diff;
    }

       
} 
