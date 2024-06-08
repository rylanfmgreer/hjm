#include "utils.hpp"
#include <algorithm>
namespace HJM
{
    std::vector<double> Utils::copy(const std::vector<double> p_v)
    {
        std::vector<double> new_vector(p_v.size());
        std::copy(p_v.begin(), p_v.end(), new_vector.begin());
        return new_vector;
    }

    std::vector< std::vector<double> > Utils::copy(const std::vector< std::vector<double>> p_mat)
    {
        std::vector< std::vector<double >> new_matrix(p_mat.size());
        std::transform(p_mat.begin(), p_mat.end(), new_matrix.begin(), [](const std::vector<double> x){ return copy(x); });
        return new_matrix;
    }
       
} 
