#include "model.hpp"
#include "../utils/utils.hpp"

namespace HJM
{
    HJM_Model::HJM_Model(DoubVec p_alphas, DoubVec p_sigmas, std::vector<DoubVec> p_correlations)
    {
        set_alphas(p_alphas);
        set_sigmas(p_sigmas);
        set_correlations(p_correlations);
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
}