#include "tests.hpp"
#include "test_objects.hpp"
#include <cmath>
namespace HJM
{
    TestSuite::TestSuite()
    :m_model(TestObjects::create_model()),
    m_integrator(VolIntegrator(TestObjects::create_model()))
    {}

    bool TestSuite::test_asian_correlation() const
    {
        double desired_correlation = TestObjects::c;
        double calculated_correlation = m_integrator.asian_correlation(
            TestObjects::F_idx, TestObjects::G_idx, 
            1.0, 1.08, 0.0, 0.1);
        return abs(desired_correlation - calculated_correlation) < 1e-10;
    }

    bool TestSuite::test_correlation() const
    {
        double desired_correlation = TestObjects::c;
        double calculated_correlation = m_integrator.correlation(
            TestObjects::F_idx, TestObjects::G_idx, 1.0, 0.0, 0.1);
        return abs(desired_correlation - calculated_correlation) < 1e-10;
    }

    void TestSuite::run_tests() const
    {
        test_asian_correlation();
        test_correlation();
    }
}