#ifndef _HJM_Model_rg_20240608__
#define _HJM_Model_rg_20240608__
#include <vector>

namespace HJM
{
    struct ParamSet
    {
        double sigma_a_i;
        double sigma_b_j;
        double alpha_a_i;
        double alpha_b_j;
        double rho_ai_bj;
    };

    typedef std::vector<double> DoubVec;
    class HJM_Model
    {
        /*
            We assume W(t) is an N-dimensional Brownian motion with correlation matrix S.
            Let f(t, T) be the price of a contract for instantaneous delivery at time T,
            observed at time t.


        */
        public:
        HJM_Model();
        HJM_Model(DoubVec p_alphas, DoubVec p_sigmas, std::vector<DoubVec> p_correlations);
        HJM_Model(const HJM_Model& p_model);
        HJM_Model(const HJM_Model* p_model);

        HJM_Model copy() const;

        ~HJM_Model(){}

        double get_alpha(int p_index) const { return m_alphas[p_index]; }
        double get_sigma(int p_index) const{ return m_sigmas[p_index]; }
        double get_sigma_with_specific_times(int p_index, double p_start_time, double p_end_time);
        double get_correlation(int p_row, int p_col) const{ return m_correlations[p_row][p_col];}
        void scale_vols(double p_scalar);
        void clone_into_this(const HJM_Model& p_model);
        ParamSet unpack(int p_index_1, int p_index_2) const;

        private:
        void set_alphas(const DoubVec& p_alphas);
        void set_sigmas(const DoubVec& p_sigmas);
        void set_correlations(const std::vector<DoubVec>& p_correlations);
        void size_check();

        DoubVec m_alphas; // a_1, ..., a_n
        DoubVec m_sigmas;
        std::vector<DoubVec> m_correlations;

        DoubVec m_H_start_times;
        DoubVec m_H_values;
    
    };

};
#endif