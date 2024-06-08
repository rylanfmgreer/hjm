    #include "test_objects.hpp"
    namespace HJM
    {
        namespace TestObjects
        {
            std::vector<DoubVec> make_correlation_matrix()
            {
                std::vector<DoubVec> corrs(4);
                for(int i(0); i < 4; ++i)
                {   corrs[i] = DoubVec(4);
                    corrs[i][i] = 1.0;
                }
                corrs[1][0] = corrs[0][1] = corrs[2][3] = corrs[3][2] = rho;
                corrs[0][2] = corrs[2][0] = corrs[1][3] = corrs[3][1] = c;
                corrs[0][3] = corrs[3][0] = corrs[1][2] = corrs[2][1] = c * rho;
                return corrs;
            }
        }
    }