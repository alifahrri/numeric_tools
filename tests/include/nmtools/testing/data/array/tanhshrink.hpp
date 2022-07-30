#ifndef NMTOOLS_TESTING_DATA_ARRAY_TANHSHRINK_HPP
#define NMTOOLS_TESTING_DATA_ARRAY_TANHSHRINK_HPP

#include "nmtools/array/ndarray/dynamic.hpp"
#include "nmtools/array/ndarray/hybrid.hpp"
#include "nmtools/array/ndarray/fixed.hpp"
#include "nmtools/testing/testing.hpp"

#include <vector>
#include <array>

namespace nm = nmtools;
namespace na = nm::array;
namespace kind = na::kind;

NMTOOLS_TESTING_DECLARE_CASE(activations, tanhshrink)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        inline float a[2][3][2] = {{{-9.000000, -7.363636},
         {-5.727273, -4.090909},
         {-2.454545, -0.818182}},

        {{ 0.818182,  2.454545},
         { 4.090909,  5.727273},
         { 7.363636,  9.000000}}};
        NMTOOLS_CAST_ARRAYS(a);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        inline float result[2][3][2] = {{{-8.000000, -6.363637},
         {-4.727294, -3.091468},
         {-1.469196, -0.144103}},

        {{ 0.144103,  1.469196},
         { 3.091468,  4.727294},
         { 6.363637,  8.000000}}};
    }
}

#endif // NMTOOLS_TESTING_DATA_ARRAY_TANHSHRINK_HPP