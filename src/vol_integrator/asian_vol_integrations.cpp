#include "vol_integrator.hpp"
#include <cmath>

namespace HJM
{
    double VolIntegrator::exponential_integral_for_asian_covariance(
            int p_index_1, int p_index_2,
            double p_delivery_start_time, double p_delivery_end_time,
            double p_observation_start_time, double p_observation_end_time) const
            {
                // unpack the model params
                double sigma_a_i = m_model.get_sigma(p_index_1);
                double sigma_b_j = m_model.get_sigma(p_index_2);
                double alpha_a_i = m_model.get_alpha(p_index_1);
                double alpha_b_j = m_model.get_alpha(p_index_2);
                double rho_ai_bj = m_model.get_correlation(p_index_1, p_index_2);

                // create the time differences -- cleaner to read this way
                double Ts_minus_ts = p_delivery_start_time - p_observation_start_time;
                double Te_minus_ts = p_delivery_end_time - p_observation_start_time;
                double Ts_minus_te = p_delivery_start_time - p_observation_end_time;
                double Te_minus_te = p_delivery_end_time - p_observation_end_time;

                // create the terms we add together
                double term_Ts_Ts = (exp( -(alpha_a_i + alpha_b_j) * Ts_minus_te)
                    - exp( -(alpha_a_i + alpha_b_j) * Ts_minus_ts));
                double term_Te_Ts = (exp( -alpha_a_i * Te_minus_te - alpha_b_j * Ts_minus_te)
                    - exp(alpha_a_i * Te_minus_ts - alpha_b_j * Ts_minus_ts));
                double term_Ts_Te = (exp( -alpha_a_i * Ts_minus_te - alpha_b_j * Te_minus_te)
                    - exp(alpha_a_i * Ts_minus_ts - alpha_b_j * Te_minus_ts));
                double term_Te_Te = (exp( -(alpha_a_i + alpha_b_j) * Te_minus_te)
                    - exp( -(alpha_a_i + alpha_b_j) * Te_minus_ts));

                double all_terms = term_Ts_Ts - term_Te_Ts - term_Ts_Te + term_Ts_Ts;
                double scalar = rho_ai_bj * sigma_a_i * sigma_b_j / (alpha_a_i * alpha_b_j * (alpha_a_i + alpha_b_j));
                return all_terms * scalar;
            }

    double VolIntegrator::asian_covariance(IdxVec p_indices_1, IdxVec p_indices_2,
                double p_delivery_start_time, double p_delivery_end_time,
                double p_observation_start_time, double p_observation_end_time) const
            {
                double accumulator(0);
                for( int idx_1(0); idx_1 < p_indices_1.size(); ++idx_1)
                {
                    for( int idx_2(0); idx_2 < p_indices_2.size(); ++idx_2)
                    {
                        accumulator += exponential_integral_for_asian_covariance(
                            p_indices_1[idx_1], p_indices_2[idx_2], 
                            p_delivery_start_time, p_delivery_end_time,
                            p_observation_start_time, p_observation_end_time);
                    }
                }
                return accumulator;
            }
    double VolIntegrator::asian_variance(IdxVec p_indices,
            double p_delivery_start_time, double p_delivery_end_time,
            double p_observation_start_time, double p_observation_end_time) const
        {
            // could be better optimized by taking into account 
            // the fact that we compute all off-diagonals twice, 
            // when we could just compute them once.
            return asian_covariance(p_indices, p_indices,
                p_delivery_start_time, p_delivery_end_time,
                p_observation_start_time, p_observation_end_time);
        }

    double VolIntegrator::asian_volatility(IdxVec p_indices,
            double p_delivery_start_time, double p_delivery_end_time,
            double p_observation_start_time, double p_observation_end_time) const
        {
            double var = asian_variance(p_indices,
                p_delivery_start_time, p_delivery_end_time,
                p_observation_start_time, p_observation_end_time);
            return sqrt(var);
        }

    double VolIntegrator::asian_correlation(IdxVec p_indices_1, IdxVec p_indices_2,
            double p_delivery_start_time, double p_delivery_end_time,
            double p_observation_start_time, double p_observation_end_time) const
        {
            double cov = asian_covariance(p_indices_1, p_indices_2,
                p_delivery_start_time, p_delivery_end_time,
                p_observation_start_time, p_observation_end_time);
            double std_a = asian_volatility(p_indices_1, p_delivery_start_time, p_delivery_end_time,
                p_observation_start_time, p_observation_end_time);
            double std_b = asian_volatility(p_indices_2, p_delivery_start_time, p_delivery_end_time,
                p_observation_start_time, p_observation_end_time);
            return cov / (std_a * std_b);
        }
}