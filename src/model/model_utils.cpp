#include "model.hpp"
#include <cassert>
#include <algorithm>
namespace HJM
{
    HJM_Model HJM_Model::copy() const
    {
        return HJM_Model(m_alphas, m_sigmas, m_correlations);
    }

    void HJM_Model::size_check()
    {
        int m = m_alphas.size();
        int n = m_sigmas.size();
        assert(m == n);
        int nr = m_correlations.size();
        assert(nr == m);
        for(int i(0); i < nr; ++i) assert(m_correlations[i].size() == m);
    }

    void HJM_Model::clone_into_this(const HJM_Model& p_other_model)
    {
        set_alphas(p_other_model.m_alphas);
        set_sigmas(p_other_model.m_sigmas);
        set_correlations(p_other_model.m_correlations);
        size_check();
    }

    ParamSet HJM_Model::unpack(int p_index_1, int p_index_2) const
    {
        return ParamSet{
            get_sigma(p_index_1),
            get_sigma(p_index_2), 
            get_alpha(p_index_1),
            get_alpha(p_index_2), 
            get_correlation(p_index_1, p_index_2)
        };
    }

};