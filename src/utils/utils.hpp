#ifndef _hjm_utils_hpp_9328402
#define _hjm_utils_hpp_9328402
#include <vector>

namespace HJM
{
    namespace Utils
    {
        // self explanatory
        std::vector<double> copy(const std::vector<double> p_v);
        std::vector< std::vector<double> > copy(const std::vector< std::vector<double>> p_mat);
    };
    
}; 


#endif