#ifndef NMTOOLS_TESTING_DATA_ARRAY_LOG2_HPP
#define NMTOOLS_TESTING_DATA_ARRAY_LOG2_HPP

#include "nmtools/array/ndarray/dynamic.hpp"
#include "nmtools/array/ndarray/hybrid.hpp"
#include "nmtools/array/ndarray/fixed.hpp"
#include "nmtools/testing/testing.hpp"

#include <vector>
#include <array>

namespace nm = nmtools;
namespace na = nm::array;
namespace kind = na::kind;

NMTOOLS_TESTING_DECLARE_CASE(view, log2)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        inline float a[3][3] = {
            {1,1,2},
            {3,4,5},
            {6,7,8},
        };
        NMTOOLS_CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        inline int shape[2] = {3,3};
        inline float result[3][3] = {
            {std::log2(1.f),std::log2(1.f),std::log2(2.f)},
            {std::log2(3.f),std::log2(4.f),std::log2(5.f)},
            {std::log2(6.f),std::log2(7.f),std::log2(8.f)},
        };
    }
}

#endif // NMTOOLS_TESTING_DATA_ARRAY_LOG2_HPP