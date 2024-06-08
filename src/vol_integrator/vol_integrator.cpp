#include "vol_integrator.hpp"
#include <cmath>

namespace HJM
{

    
    VolIntegrator::VolIntegrator(const HJM_Model p_model)
    {
        set_model(p_model);
        VolIntegrator();
    }

}