#include "model.hpp"
#include <cassert>
#include <algorithm>
namespace HJM
{

    void HJM_Model::scale_vols(double p_scalar)
    {
        std::transform(m_sigmas.begin(), m_sigmas.end(), m_sigmas.begin(),
            [p_scalar](double p_x){ return p_x * p_scalar; }
        );
    }

    double HJM_Model::get_sigma_with_specific_times(
        int p_index, double p_start_time, double p_end_time)
    {
        return 0.0;
    }
}