#ifndef NMTOOLS_TESTING_DATA_ARRAY_FLOOR_HPP
#define NMTOOLS_TESTING_DATA_ARRAY_FLOOR_HPP

#include "nmtools/array/ndarray/dynamic.hpp"
#include "nmtools/array/ndarray/hybrid.hpp"
#include "nmtools/array/ndarray/fixed.hpp"
#include "nmtools/testing/testing.hpp"

#include <vector>
#include <array>

namespace nm = nmtools;
namespace na = nm::array;
namespace kind = na::kind;

NMTOOLS_TESTING_DECLARE_CASE(view, floor)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        inline float a[3][3] = {
            {1.0,2.1,3.2},
            {1.3,2.4,3.5},
            {1.6,2.7,3.8},
        };
        NMTOOLS_CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        inline int shape[2] = {3,3};
        inline float result[3][3] = {
            {std::floor(1.0f),std::floor(2.1f),std::floor(3.2f)},
            {std::floor(1.3f),std::floor(2.4f),std::floor(3.5f)},
            {std::floor(1.6f),std::floor(2.7f),std::floor(3.8f)},
        };
    }
}

#endif // NMTOOLS_TESTING_DATA_ARRAY_FLOOR_HPP