#ifndef _vol_integrator_hpp_938420839
#define _vol_integrator_hpp_938420839
#include "../model/model.hpp"

namespace HJM
{
    typedef const std::vector<int> IdxVec;
    class VolIntegrator
    {
        public:
        VolIntegrator(const HJM_Model p_model);

        double covariance(IdxVec p_indices_1, IdxVec p_indices_2,
            double p_delivery_time, double p_observation_start_time,
            double p_observation_end_time) const;
        double asian_covariance(IdxVec p_indices_1, IdxVec p_indices_2,
            double p_delivery_start_time, double p_delivery_end_time,
            double p_observation_start_time, double p_observation_end_time) const;

        double variance(IdxVec p_indices,
            double p_delivery_time,
            double p_observation_start_time, double p_observation_end_time) const;
        double asian_variance(IdxVec p_indices,
            double p_delivery_start_time, double p_delivery_end_time,
            double p_observation_start_time, double p_observation_end_time) const;

        double volatility(IdxVec p_indices,
            double p_delivery_time,
            double p_observation_start_time, double p_observation_end_time) const;
        double asian_volatility(IdxVec p_indices,
            double p_delivery_start_time, double p_delivery_end_time,
            double p_observation_start_time, double p_observation_end_time) const;

        double correlation(IdxVec p_indices_1, IdxVec p_indices_2,
            double p_delivery_time,
            double p_observation_start_time, double p_observation_end_time) const;
        double asian_correlation(IdxVec p_indices_1, IdxVec p_indices_2,
            double p_delivery_start_time, double p_delivery_end_time,
            double p_observation_start_time, double p_observation_end_time) const;

        void set_model(const HJM_Model p_model) { m_model = p_model.copy(); }
        HJM_Model get_model() const { return m_model.copy(); }

        private:
        VolIntegrator();
        HJM_Model m_model;
        double exponential_integral_for_asian_covariance(int p_index_1, int p_index_2,
            double p_delivery_start_time, double p_delivery_end_time,
            double p_observation_start_time, double p_observation_end_time) const;
        double exponential_integral_for_covariance(int p_index_1, int p_index_2, 
            double p_delivery_time,
            double p_observation_start_time, double p_observation_end_time) const;



    };
};


#endif