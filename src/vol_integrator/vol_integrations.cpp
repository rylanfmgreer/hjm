#include "vol_integrator.hpp"
#include <cmath>

namespace HJM
{
    double VolIntegrator::exponential_integral_for_covariance(int p_index_1, int p_index_2, 
            double p_delivery_time,
            double p_observation_start_time, double p_observation_end_time) const
    {
                // unpack the model params
                ParamSet these_params(unpack_these_params(p_index_1, p_index_2));
                double sum_alpha = these_params.alpha_a_i + these_params.alpha_b_j;
                double t_long = exp(-sum_alpha * (p_delivery_time - p_observation_end_time));
                double t_short = exp(-sum_alpha * (p_delivery_time - p_observation_start_time));
                double log_scalar = (
                    log(these_params.rho_ai_bj) + log(these_params.sigma_a_i)
                    + log(these_params.sigma_b_j) - log(sum_alpha));
                return exp(log_scalar) * (t_long - t_short);
    }

    double VolIntegrator::covariance(IdxVec& p_indices_1, IdxVec& p_indices_2,
            double p_delivery_time, double p_observation_start_time,
            double p_observation_end_time) const
    {
        double accumulator(0);
        for( int idx_1(0); idx_1 < p_indices_1.size(); ++idx_1)
            for( int idx_2(0); idx_2 < p_indices_2.size(); ++idx_2)            
                accumulator += exponential_integral_for_covariance(
                    p_indices_1[idx_1], p_indices_2[idx_2],
                    p_delivery_time,p_observation_start_time, p_observation_end_time);           
        return accumulator / (p_observation_end_time - p_observation_start_time);
    }

    double VolIntegrator::variance(IdxVec& p_indices,
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

    double VolIntegrator::volatility(IdxVec& p_indices,
            double p_delivery_time,
            double p_observation_start_time, double p_observation_end_time) const
        {
            double var = variance(p_indices, p_delivery_time, p_observation_start_time, p_observation_end_time);
            return sqrt(var);
        }

    double VolIntegrator::correlation(IdxVec& p_indices_1, IdxVec& p_indices_2,
            double p_delivery_time,
            double p_observation_start_time, double p_observation_end_time) const
        {
            double cov = covariance(p_indices_1, p_indices_2,
                p_delivery_time, p_observation_start_time, p_observation_end_time);
            double std_a = volatility(p_indices_1,
                p_delivery_time, p_observation_start_time, p_observation_end_time);
            double std_b = volatility(p_indices_2,
                p_delivery_time, p_observation_start_time, p_observation_end_time);
            return exp( log(cov) - log(std_a) - log(std_b));
        }
}