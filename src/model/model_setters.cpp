#include "model.hpp"
#include "../utils/utils.hpp"

namespace HJM
{
    void HJM_Model::set_alphas(const DoubVec& p_alphas)
    {
        m_alphas = Utils::copy(p_alphas);
        sanity_check_alphas();
    }

    void HJM_Model::set_sigmas(const DoubVec& p_sigmas)
    {
        m_sigmas = Utils::copy(p_sigmas);
    }

    void HJM_Model::set_correlations(const std::vector<DoubVec>& p_correlations)
    {
        m_correlations = Utils::copy(p_correlations);
    }
}