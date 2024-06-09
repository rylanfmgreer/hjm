#include "vol_integrator.hpp"
#include <cmath>

namespace HJM
{

    VolIntegrator::VolIntegrator(HJM_Model* p_model)
    {
        set_model(p_model);
        VolIntegrator();
    }

    void VolIntegrator::set_model(HJM_Model* p_ptr_to_model)
    {
        m_model = std::shared_ptr<HJM_Model>(p_ptr_to_model);
    }

    void VolIntegrator::set_model(HJM_Model& p_ref_of_model)
    {
        m_model = std::shared_ptr<HJM_Model>(new HJM_Model);
        m_model->clone_into_this(p_ref_of_model);
    }

    void VolIntegrator::set_model(std::shared_ptr<HJM_Model> p_shared_ptr)
    {
        m_model = p_shared_ptr;
    }

}