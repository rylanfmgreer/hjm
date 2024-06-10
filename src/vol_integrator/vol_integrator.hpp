#ifndef _vol_integrator_hpp_938420839
#define _vol_integrator_hpp_938420839
#include "../model/model.hpp"
#include <memory>

namespace HJM
{
    typedef const std::vector<int> IdxVec;


    class VolIntegrator
    {
        public:
        VolIntegrator(){}
        VolIntegrator(HJM_Model* p_model);

        double covariance(IdxVec& p_indices_1, IdxVec& p_indices_2,
            double p_delivery_time, double p_observation_start_time,
            double p_observation_end_time) const;
        double asian_covariance(IdxVec& p_indices_1, IdxVec& p_indices_2,
            double p_delivery_start_time, double p_delivery_end_time,
            double p_observation_start_time, double p_observation_end_time) const;

        double variance(IdxVec& p_indices,
            double p_delivery_time,
            double p_observation_start_time, double p_observation_end_time) const;
        double asian_variance(IdxVec& p_indices,
            double p_delivery_start_time, double p_delivery_end_time,
            double p_observation_start_time, double p_observation_end_time) const;

        double volatility(IdxVec& p_indices,
            double p_delivery_time,
            double p_observation_start_time, double p_observation_end_time) const;
        double asian_volatility(IdxVec& p_indices,
            double p_delivery_start_time, double p_delivery_end_time,
            double p_observation_start_time, double p_observation_end_time) const;

        double correlation(IdxVec& p_indices_1, IdxVec& p_indices_2,
            double p_delivery_time,
            double p_observation_start_time, double p_observation_end_time) const;
        double asian_correlation(IdxVec& p_indices_1, IdxVec& p_indices_2,
            double p_delivery_start_time, double p_delivery_end_time,
            double p_observation_start_time, double p_observation_end_time) const;

        void set_model(HJM_Model* p_ptr_to_model);
        void set_model(HJM_Model& p_ref_of_model);
        void set_model(std::shared_ptr<HJM_Model> p_shared_ptr);

        HJM_Model get_model() const { return m_model->copy(); }

        private:
        std::shared_ptr<HJM_Model> m_model;
        double exponential_integral_for_asian_covariance(int p_index_1, int p_index_2,
            double p_delivery_start_time, double p_delivery_end_time,
            double p_observation_start_time, double p_observation_end_time) const;
        double exponential_integral_for_covariance(int p_index_1, int p_index_2, 
            double p_delivery_time,
            double p_observation_start_time, double p_observation_end_time) const;

        double get_log_scalar_for_asian_cov_integration(const ParamSet& p,   
         double p_observation_start_time,
         double p_observation_end_time) const;
        
        ParamSet unpack_these_params(int p_index_1, int p_index_2) const;

        double calculate_exponential_integral_in_small_t_for_asian_covariance(
            double sum_of_alphas, double p_observation_start_time, double p_observation_end_time) const;
        double calculate_multiple_exponential_sum_scalar_for_exponential_integral(
            ParamSet& these_params, double p_delivery_start_time, double p_delivery_end_time) const;

    };
};


#endif