#include "vol_integrator.hpp"
#include <cmath>
#include "../utils/utils.hpp"

namespace HJM
{
     
    double VolIntegrator::get_log_scalar_for_asian_cov_integration(const ParamSet& p_these_params,   
         double p_observation_start_time,
         double p_observation_end_time) const
        {
            double integration_period = p_observation_end_time - p_observation_start_time;
            double log_scalar_numerator = (log(p_these_params.rho_ai_bj)
                + log(p_these_params.sigma_a_i) + log(p_these_params.sigma_b_j));
            double log_scalar_denominator = (log(p_these_params.alpha_a_i) + log(p_these_params.alpha_b_j)
                + log(p_these_params.alpha_a_i + p_these_params.alpha_b_j) + 2. * log(integration_period));
            double log_scalar = log_scalar_numerator - log_scalar_denominator;
            return log_scalar;
        }
    
    double VolIntegrator::calculate_exponential_integral_in_small_t_for_asian_covariance(
        double sum_of_alphas, double p_observation_start_time, double p_observation_end_time) const
    {
                double exponential_integral_pos = expm1(sum_of_alphas * p_observation_end_time) ;
                double exponential_integral_neg = expm1(sum_of_alphas * p_observation_start_time);
                double exponential_integral = (exponential_integral_pos - exponential_integral_neg) / sum_of_alphas;
                return exponential_integral;

    }

    double VolIntegrator::calculate_multiple_exponential_sum_scalar_for_exponential_integral(
        ParamSet& these_params, double p_delivery_start_time, double p_delivery_end_time) const
        {
                double product_of_alphas = (these_params.alpha_a_i * these_params.alpha_b_j);
                double term_Ts_Ts = expm1(-these_params.alpha_a_i * p_delivery_start_time -these_params.alpha_b_j * p_delivery_start_time);
                double Term_Te_Ts = expm1(-these_params.alpha_a_i * p_delivery_end_time -these_params.alpha_b_j * p_delivery_start_time);
                double Term_Ts_Te = expm1(-these_params.alpha_a_i * p_delivery_start_time -these_params.alpha_b_j * p_delivery_end_time);
                double Term_Te_Te = expm1(-these_params.alpha_a_i * p_delivery_end_time -these_params.alpha_b_j * p_delivery_end_time);
                double tmp_Ts_Ts_Te_Ts = term_Ts_Ts - Term_Te_Ts;
                double tmp_Ts_Te_Te_Te = Term_Ts_Te - Term_Te_Te;
                double sum_of_all_terms = (tmp_Ts_Ts_Te_Ts - tmp_Ts_Te_Te_Te) / product_of_alphas;
                return sum_of_all_terms;
        }
    double VolIntegrator::exponential_integral_for_asian_covariance(
            int p_index_1, int p_index_2,
            double p_delivery_start_time, double p_delivery_end_time,
            double p_observation_start_time, double p_observation_end_time) const
            {
                ParamSet these_params(unpack_these_params(p_index_1, p_index_2));

                // create the time differences -- cleaner to read this way
                double delivery_time = p_delivery_start_time - p_delivery_end_time;
                double sum_of_alphas = these_params.alpha_a_i + these_params.alpha_b_j;
                double scalar_outside = (these_params.rho_ai_bj * these_params.sigma_a_i * these_params.sigma_b_j) / (delivery_time * delivery_time);

                double sum_of_integrals_in_observation = calculate_exponential_integral_in_small_t_for_asian_covariance(sum_of_alphas, p_observation_start_time, p_observation_end_time);
                double sum_of_integrals_in_delivery = calculate_multiple_exponential_sum_scalar_for_exponential_integral(these_params, p_delivery_start_time, p_delivery_end_time);
                double final_term = (sum_of_integrals_in_delivery * sum_of_integrals_in_observation) * scalar_outside;
                return final_term;
            }

    double VolIntegrator::asian_covariance(IdxVec& p_indices_1, IdxVec& p_indices_2,
                double p_delivery_start_time, double p_delivery_end_time,
                double p_observation_start_time, double p_observation_end_time) const
            {
                double accumulator(0);
                for( int idx_1(0); idx_1 < p_indices_1.size(); ++idx_1)
                    for( int idx_2(0); idx_2 < p_indices_2.size(); ++idx_2)    
                        accumulator += exponential_integral_for_asian_covariance(
                            p_indices_1[idx_1], p_indices_2[idx_2], 
                            p_delivery_start_time, p_delivery_end_time,
                            p_observation_start_time, p_observation_end_time);
                return accumulator / (p_observation_end_time - p_observation_start_time);
            }

    double VolIntegrator::asian_variance(IdxVec& p_indices,
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

    double VolIntegrator::asian_volatility(IdxVec& p_indices,
            double p_delivery_start_time, double p_delivery_end_time,
            double p_observation_start_time, double p_observation_end_time) const
        {
            double var = asian_variance(p_indices,
                p_delivery_start_time, p_delivery_end_time,
                p_observation_start_time, p_observation_end_time);
            return sqrt(var);
        }

    double VolIntegrator::asian_correlation(IdxVec& p_indices_1, IdxVec& p_indices_2,
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
            return exp( log(cov) - log(std_a) - log(std_b));
        }
}