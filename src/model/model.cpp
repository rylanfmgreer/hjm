#include "model.hpp"
#include <cassert>
#include <algorithm>
#include <cmath>

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
        // Partition the set of scalars
        double weight_x_sigma_accumulator(0);
        double weight_accumulator(0);
        double last_start_time(0);
        for( int i(0); i < m_H_start_times.size()-1; ++i)
        {
            double start_of_overlap = std::max(m_H_start_times[i], p_start_time);
            double end_of_overlap = std::min(m_H_start_times[i+1], p_end_time);
            double w = std::max((end_of_overlap - start_of_overlap), 0.0);

            // early break, for belt and suspenders approach.
            if(m_H_start_times[i+1] >= p_end_time)
                i += m_H_start_times.size();

            weight_accumulator += w;
            weight_x_sigma_accumulator += w * m_H_values[i];
        }
        return (weight_x_sigma_accumulator * m_sigmas[p_index]) / weight_accumulator;
    }
}