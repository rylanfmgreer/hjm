#include "model.hpp"
#include "../utils/utils.hpp"
#include <cassert>
#include <algorithm>
namespace HJM
{
    HJM_Model::HJM_Model(){}
    HJM_Model::HJM_Model(DoubVec p_alphas, DoubVec p_sigmas, std::vector<DoubVec> p_correlations)
    {
        set_alphas(p_alphas);
        set_sigmas(p_sigmas);
        set_correlations(p_correlations);
        size_check();
    }

    HJM_Model HJM_Model::copy() const
    {
        return HJM_Model(m_alphas, m_sigmas, m_correlations);
    }

    void HJM_Model::set_alphas(const DoubVec p_alphas)
    {
        m_alphas = Utils::copy(p_alphas);
    }

    void HJM_Model::set_sigmas(const DoubVec p_sigmas)
    {
        m_sigmas = Utils::copy(p_sigmas);
    }

    void HJM_Model::set_correlations(const std::vector<DoubVec> p_correlations)
    {
        m_correlations = Utils::copy(p_correlations);
    }

    void HJM_Model::size_check()
    {
        int m = m_alphas.size();
        int n = m_sigmas.size();
        assert(m == n);
        int nr = m_correlations.size();
        assert(nr == m);
        if(m > 0)
            assert(m_correlations[0].size() == m);
    }

    void HJM_Model::scale_vols(double p_scalar)
    {
        std::transform(m_sigmas.begin(), m_sigmas.end(), m_sigmas.begin(),
            [p_scalar](double p_x){ return p_x * p_scalar; }
        );
    }
}