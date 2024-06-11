#include "simulator.hpp"
#include <algorithm>
#include <iterator>

namespace HJM
{
    Simulator::Simulator()
    :m_random_device{},
    m_random_gen{m_random_device()},
    m_normal{0.0, 1.0},
    m_model_ptr(nullptr),
    m_sims_ptr(nullptr, &gsl_matrix_free),
    m_cholesky_ptr(nullptr, &gsl_matrix_free)
    {}

    Simulator::Simulator(int p_n_factors, int p_n_sims, double p_dt)
    :Simulator()
    {
        m_n_factors = p_n_factors;
        m_n_sims = p_n_sims;
        m_dt = p_dt;
    }

    void Simulator::allocate_memory()
    {
        m_sims_ptr.reset( gsl_matrix_alloc(m_n_sims, m_n_factors));
        m_cholesky_ptr.reset(gsl_matrix_alloc(m_model_ptr->n_factors(), m_model_ptr->n_factors()));
    }

    void Simulator::create_sims()
    {
        allocate_memory();
        create_rands();

        copy_correlation_matrix_into_cholesky_ptr();
        apply_cholesky_decomposition_to_correlation_matrix();
        apply_choleskied_corr_mat_to_rands();

    }

    void Simulator::apply_cholesky_decomposition_to_correlation_matrix()
    {

    }

    void Simulator::apply_choleskied_corr_mat_to_rands()
    {

    }

    void Simulator::copy_correlation_matrix_into_cholesky_ptr()
    {
        for( int r(0); r < m_model_ptr->n_factors(); ++r)    
            for( int c(0); c < m_model_ptr->n_factors(); ++c)
                gsl_matrix_set(m_cholesky_ptr.get(),
                    r, c, m_model_ptr->get_correlation(r, c));
    }
        
    void Simulator::create_rands()
    {
        
        for( int r(0); r < m_n_sims; ++r)
            for( int c(0); c < m_n_factors; ++c)
                gsl_matrix_set(m_sims_ptr.get(), r, c, create_rand() * m_dt);           
   
    }

    

};