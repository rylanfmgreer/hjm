#ifndef _tests_9348028930482903
#define _tests_9348028930482903
#pragma once

#include "../model/model.hpp"
#include "../vol_integrator/vol_integrator.hpp"
#include "test_objects.hpp"
#include <memory>
#include "../simulator/simulator.hpp"

namespace HJM
{
    class TestSuite
    {
        public:
        TestSuite();
        ~TestSuite(){}
        void run_tests() const;


        private:
        bool test_correlation() const;
        bool test_asian_correlation() const;
        bool test_volatility() const;
        bool test_asian_volatility() const;
        bool test_simulations_generate() const;
        std::shared_ptr<HJM_Model> m_model;
        VolIntegrator m_integrator;
        bool close(double x, double y, double tol=1e-10) const;

    };

    void test();
}

#endif