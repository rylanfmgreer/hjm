#ifndef _tests_9348028930482903
#define _tests_9348028930482903

#include "../model/model.hpp"
#include "../vol_integrator/vol_integrator.hpp"

namespace HJM
{
    class TestSuite
    {
        public:
        TestSuite();
        void run_tests() const;
        bool test_correlation() const;
        bool test_asian_correlation() const;

        private:
        HJM_Model m_model;
        VolIntegrator m_integrator;

    }
}

#endif