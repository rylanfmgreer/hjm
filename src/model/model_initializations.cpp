#include "model.hpp"

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

    HJM_Model::HJM_Model(const HJM_Model& p_model)
    {
        clone_into_this(p_model);
    }

    HJM_Model::HJM_Model(const HJM_Model* p_model)
    {
        clone_into_this(*p_model);
    }

};