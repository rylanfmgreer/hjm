#include "vol_integrator.hpp"
#include <cmath>

namespace HJM
{
    double VolIntegrator::exponential_integral_for_covariance(int p_index_1, int p_index_2, 
            double p_delivery_time,
            double p_observation_start_time, double p_observation_end_time) const
    {
                // unpack the model params
                double sigma_a_i = m_model.get_sigma(p_index_1);
                double sigma_b_j = m_model.get_sigma(p_index_2);
                double alpha_a_i = m_model.get_alpha(p_index_1);
                double alpha_b_j = m_model.get_alpha(p_index_2);
                double rho_ai_bj = m_model.get_correlation(p_index_1, p_index_2);

                double sum_alpha = alpha_a_i + alpha_b_j;
                double t_long = exp(-sum_alpha * (p_delivery_time - p_observation_end_time));
                double t_short = exp(-sum_alpha * (p_delivery_time - p_observation_start_time));
                double scalar = (rho_ai_bj * sigma_a_i * sigma_b_j) / (sum_alpha);
                return scalar * (t_long - t_short);
    }

    double VolIntegrator::covariance(IdxVec p_indices_1, IdxVec p_indices_2,
            double p_delivery_time, double p_observation_start_time,
            double p_observation_end_time) const
    {
        double accumulator(0);
        for( int idx_1(0); idx_1 < p_indices_1.size(); ++idx_1)
        {
            for( int idx_2(0); idx_2 < p_indices_2.size(); ++idx_2)
            {
                accumulator += exponential_integral_for_covariance(
                    p_indices_1[idx_1], p_indices_2[idx_2],
                    p_delivery_time,p_observation_start_time, p_observation_end_time);           
            }   
        }
        return accumulator / (p_observation_end_time - p_observation_start_time);
    }

    double VolIntegrator::variance(IdxVec p_indices,
            double p_delivery_time,
            double p_observation_start_time, double p_observation_end_time) const
        {
            // could be better optimized by taking into account 
            // the fact that we compute all off-diagonals twice, 
            // when we could just compute them once.
            return covariance(p_indices, p_indices,
                p_delivery_time, 
                p_observation_start_time, p_observation_end_time);
        }

    double VolIntegrator::volatility(IdxVec p_indices,
            double p_delivery_time,
            double p_observation_start_time, double p_observation_end_time) const
        {
            double var = variance(p_indices, p_delivery_time, p_observation_start_time, p_observation_end_time);
            return sqrt(var);
        }

    double VolIntegrator::correlation(IdxVec p_indices_1, IdxVec p_indices_2,
            double p_delivery_time,
            double p_observation_start_time, double p_observation_end_time) const
        {
            double cov = covariance(p_indices_1, p_indices_2,
                p_delivery_time, p_observation_start_time, p_observation_end_time);
            double std_a = volatility(p_indices_1,
                p_delivery_time, p_observation_start_time, p_observation_end_time);
            double std_b = volatility(p_indices_2,
                p_delivery_time, p_observation_start_time, p_observation_end_time);
            return cov / (std_a * std_b);
        }
}