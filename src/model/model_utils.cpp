#include "model.hpp"
#include "../utils/utils.hpp"
#include <cassert>
#include <algorithm>
#include <cmath>
#include <iostream>

namespace HJM
{
    HJM_Model HJM_Model::copy() const
    {
        return HJM_Model(m_alphas, m_sigmas, m_correlations);
    }

    void HJM_Model::size_check() const
    {
        int m = m_alphas.size();
        int n = m_sigmas.size();
        assert(m == n);
        int nr = m_correlations.size();
        assert(nr == m);
        for(int i(0); i < nr; ++i) assert(m_correlations[i].size() == m);
    }

    void HJM_Model::sanity_check_alphas() const
    {
        double smallest_alpha = *std::min_element(
            m_alphas.begin(), m_alphas.end());
        double largest_alpha = *std::max_element(
            m_alphas.begin(), m_alphas.end());
        if(smallest_alpha < 0.) throw("Alphas must be all non-negative");
        if(smallest_alpha * 10e12 < largest_alpha)
        {
            std::cout << "Alphas are very different sizes; numerical issues are likely to occur." << '\n';
        }
    }

    void HJM_Model::sanity_check_sigmas() const
    {
        double smallest_sigma = *std::min_element(
            m_sigmas.begin(), m_sigmas.end());
        assert((smallest_sigma >= 0));
    }
    void HJM_Model::clone_into_this(const HJM_Model& p_other_model)
    {
        set_alphas(p_other_model.m_alphas);
        set_sigmas(p_other_model.m_sigmas);
        set_correlations(p_other_model.m_correlations);
        m_H_start_times = Utils::copy(p_other_model.m_H_start_times);
        m_H_values = Utils::copy(p_other_model.m_H_values);
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