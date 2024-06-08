#ifndef _test_objects_hpp_938740289302
#define _test_objects_hpp_938740289302

#include "model/model.hpp"
#include "vol_integrator/vol_integrator.hpp"

namespace HJM
{
    namespace TestObjects
    {
        IdxVec F_idx{0, 1,};
        IdxVec G_idx{2, 3};

        DoubVec alphas{0.0001, 1., 0.0001, 1. };
        DoubVec sigmas{0.5, 0.6, 0.5, 0.6 };
        double rho = 0.7;
        double c = 0.9;

        std::vector<DoubVec> make_correlation_matrix();
        HJM_Model create_model(){ return HJM_Model(alphas, sigmas, make_correlation_matrix()); }
    };
};

#endif