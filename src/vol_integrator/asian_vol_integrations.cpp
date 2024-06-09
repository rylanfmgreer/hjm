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
                + log(p_these_params.alpha_a_i + p_these_params.alpha_b_j) + 2 * log(integration_period));
            double log_scalar = log_scalar_numerator - log_scalar_denominator;
            return log_scalar;
        }
    
    double VolIntegrator::exponential_integral_for_asian_covariance(
            int p_index_1, int p_index_2,
            double p_delivery_start_time, double p_delivery_end_time,
            double p_observation_start_time, double p_observation_end_time) const
            {
                ParamSet these_params(unpack_these_params(p_index_1, p_index_2));

                // create the time differences -- cleaner to read this way
                double Ts_minus_ts = p_delivery_start_time - p_observation_start_time;
                double Te_minus_ts = p_delivery_end_time - p_observation_start_time;
                double Ts_minus_te = p_delivery_start_time - p_observation_end_time;
                double Te_minus_te = p_delivery_end_time - p_observation_end_time;

                // We work in log space for the rest of the computation, 
                // as otherwise there are big numerical instabilities
                // for small values of alpha.
                double term_Ts_Ts = Utils::improved_diff_of_exponentials(
                    -(these_params.alpha_a_i + these_params.alpha_b_j) * Ts_minus_te,
                    -(these_params.alpha_a_i + these_params.alpha_b_j) * Ts_minus_ts);

                double term_Te_Ts = Utils::improved_diff_of_exponentials(
                   -these_params.alpha_a_i * Te_minus_te - these_params.alpha_b_j * Ts_minus_te,
                   -these_params.alpha_a_i * Te_minus_ts - these_params.alpha_b_j * Ts_minus_ts);

                double term_Ts_Te = Utils::improved_diff_of_exponentials(
                   -these_params.alpha_a_i * Ts_minus_te - these_params.alpha_b_j * Te_minus_te,
                   -these_params.alpha_a_i * Ts_minus_ts - these_params.alpha_b_j * Te_minus_ts);

                double term_Te_Te = Utils::improved_diff_of_exponentials(
                    -(these_params.alpha_a_i + these_params.alpha_b_j) * Te_minus_te,
                    -(these_params.alpha_a_i + these_params.alpha_b_j) * Te_minus_ts);
                
                double tmp_TsTs_TeTs = Utils::improved_diff_of_exponentials(
                    log(term_Ts_Ts), log(term_Te_Ts));
                double tmp_TsTe_TeTe = Utils::improved_diff_of_exponentials(
                    log(term_Ts_Te), log(term_Te_Te));
                double sum_all_terms = Utils::improved_diff_of_exponentials(
                    log(tmp_TsTs_TeTs), log(tmp_TsTe_TeTe));

                
                double log_scalar = get_log_scalar_for_asian_cov_integration(
                    these_params, p_observation_start_time, p_observation_end_time);
                double log_all = log(sum_all_terms);
                double final_term = exp(log_all + log_scalar);
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