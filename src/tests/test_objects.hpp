#ifndef _test_objects_hpp_938740289302
#define _test_objects_hpp_938740289302
#include "../model/model.hpp"
#include "../vol_integrator/vol_integrator.hpp"
#pragma once

namespace HJM
{
    namespace TestObjects
    {
        static IdxVec F_idx{0, 1};
        static IdxVec G_idx{2, 3};
        static double rho = 0.7;
        static double c = 0.9;
            
        HJM_Model create_model();
        std::vector<DoubVec> make_correlation_matrix();
        
    };
};

#endif