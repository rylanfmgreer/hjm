#ifndef _HJM_Model_rg_20240608__
#define _HJM_Model_rg_20240608__
#include <vector>

namespace HJM
{
    typedef std::vector<double> DoubVec;
    class HJM_Model
    {
        public:
        HJM_Model();
        HJM_Model(DoubVec p_alphas, DoubVec p_sigmas, std::vector<DoubVec> p_correlations);
        HJM_Model copy() const;

        double get_alpha(int p_index) const { return m_alphas[p_index]; }
        double get_sigma(int p_index) const{ return m_sigmas[p_index]; }
        double get_correlation(int p_row, int p_col) const{ return m_correlations[p_row][p_col];}
        
        private:
        void set_alphas(const DoubVec p_alphas);
        void set_sigmas(const DoubVec p_sigmas);
        void set_correlations(const std::vector<DoubVec> p_correlations);
        void size_check();

        DoubVec m_alphas;
        DoubVec m_sigmas;
        std::vector<DoubVec> m_correlations;
    
    };
};
#endif