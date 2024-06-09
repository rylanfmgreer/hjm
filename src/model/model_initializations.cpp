#include "model.hpp"
#include <limits.h?

namespace HJM
{
    HJM_Model::HJM_Model()
    :m_H_start_times{0.0, __DBL_MAX__}, m_H_values{1.0, 1.0}{}

    HJM_Model::HJM_Model(DoubVec p_alphas, DoubVec p_sigmas, std::vector<DoubVec> p_correlations)
    {
        HJM_Model();
        set_alphas(p_alphas);
        set_sigmas(p_sigmas);
        set_correlations(p_correlations);
        size_check();
    }

    HJM_Model::HJM_Model(const HJM_Model& p_model)
    {
        HJM_Model();
        clone_into_this(p_model);
    }

    HJM_Model::HJM_Model(const HJM_Model* p_model)
    {
        HJM_Model();
        clone_into_this(*p_model);
    }

};