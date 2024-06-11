#ifndef _SIMULATOR_HPP_890284902
#define _SIMULATOR_HPP_890284902

#include <gsl/gsl_linalg.h>
#include <gsl/gsl_matrix.h>
#include <memory>
#include "../model/model.hpp"
#include <random>

namespace HJM
{
    typedef std::unique_ptr<gsl_matrix, decltype(&gsl_matrix_free)> MatPtr;
        
    class Simulator
    {
        public:
        Simulator();
        Simulator(int p_n_factors, int p_n_sims, double p_dt);
        void set_model(const HJM_Model& p_model){m_model_ptr->clone_into_this(p_model);}
        void create_sims();

        private:
        int m_n_factors;
        int m_n_sims;
        double m_dt;


        void create_rands();
        void copy_correlation_matrix_into_cholesky_ptr();
        void apply_cholesky_decomposition_to_correlation_matrix();
        void apply_choleskied_corr_mat_to_rands();

        void allocate_memory();
        MatPtr m_sims_ptr;
        MatPtr m_cholesky_ptr;

        std::shared_ptr<HJM_Model> m_model_ptr;
        std::random_device m_random_device;
        std::mt19937 m_random_gen;
        std::normal_distribution<double> m_normal{0.0,};
        double create_rand(){ return m_normal(m_random_gen); }

    };
};
#endif