#include "tests.hpp"
#include <cmath>
#include <iostream>
#include <iomanip>

namespace HJM
{
    bool TestSuite::close(double x, double y, double tol) const
    {
        return abs(x - y) < tol;
    }
    TestSuite::TestSuite()
    {
        HJM_Model base_model = TestObjects::create_model();
        m_model = std::shared_ptr<HJM_Model>(new HJM_Model);
        m_model->clone_into_this(base_model);
        m_integrator.set_model(base_model);
    }

    bool TestSuite::test_asian_correlation() const
    {
        double desired_correlation = TestObjects::c;
        double calculated_correlation = m_integrator.asian_correlation(
            TestObjects::F_idx, TestObjects::G_idx, 
            1.0, 1.08, 0.0, 0.1);
        return close(desired_correlation, calculated_correlation);
    }

    bool TestSuite::test_correlation() const
    {
        double desired_correlation = TestObjects::c;
        double calculated_correlation = m_integrator.correlation(
            TestObjects::F_idx, TestObjects::G_idx, 1.0, 0.0, 0.1);
        return close(desired_correlation, calculated_correlation);
    }

    bool TestSuite::test_volatility() const
    {
        // TODO: get correct vol values
        double desired_volatility = 0.68295921453362607;
        double calculated_volatiltiy = m_integrator.volatility(
            TestObjects::F_idx, 1.0, 0.0, 0.1);
        return close(desired_volatility, calculated_volatiltiy);
    }

    bool TestSuite::test_asian_volatility() const
    {
        // TODO: get correct vol values
        double desired_volatility = 0.54017402899413525;
        double calculated_volatiltiy = m_integrator.asian_volatility(
            TestObjects::F_idx, 1.0, 1.08, 0.0, 0.1);
        return close(desired_volatility, calculated_volatiltiy);
    }


    void TestSuite::run_tests() const
    {
        std::cout << std::boolalpha;
        std::cout << test_asian_correlation() << std::endl;
        std::cout << test_correlation() << std::endl;
        std::cout << test_volatility() << std::endl;
        std::cout << test_asian_volatility() << std::endl;

    }
}