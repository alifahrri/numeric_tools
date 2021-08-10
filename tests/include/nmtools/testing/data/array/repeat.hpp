#ifndef NMTOOLS_TESTING_DATA_ARRAY_REPEAT_HPP
#define NMTOOLS_TESTING_DATA_ARRAY_REPEAT_HPP

#include "nmtools/array/ndarray/dynamic.hpp"
#include "nmtools/array/ndarray/hybrid.hpp"
#include "nmtools/array/ndarray/fixed.hpp"

#include "nmtools/constants.hpp"
#include "testing/doctest.hpp"

#include <vector>
#include <array>
#include <tuple>

namespace nm = nmtools;
namespace na = nm::array;
namespace view = nm::view;
namespace kind = na::kind;

NMTOOLS_TESTING_DECLARE_CASE(array, repeat)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        inline int array[2][2] = {{1,2},{3,4}};
        inline int repeats = 3;
        inline auto axis = None;
        inline auto array_a = cast<int>(array);
        inline auto array_v = cast(array,kind::nested_vec);
        inline auto array_d = cast(array,kind::dynamic);
        inline auto array_f = cast(array,kind::fixed);
        inline auto array_h = cast(array,kind::hybrid);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        inline int shape[1] = {12};
        inline int dim = 1;
        inline int result[12] = {1,1,1,2,2,2,3,3,3,4,4,4};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        inline int array[2][2] = {{1,2},{3,4}};
        inline int repeats = 2;
        inline auto axis = 0;
        inline auto array_a = cast<int>(array);
        inline auto array_v = cast(array,kind::nested_vec);
        inline auto array_d = cast(array,kind::dynamic);
        inline auto array_f = cast(array,kind::fixed);
        inline auto array_h = cast(array,kind::hybrid);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        inline int shape[2] = {4,2};
        inline int dim = 2;
        inline int result[4][2] = {
            {1,2},
            {1,2},
            {3,4},
            {3,4}
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        inline int array[2][2] = {{1,2},{3,4}};
        inline int repeats = 2;
        inline auto axis = 1;
        inline auto array_a = cast<int>(array);
        inline auto array_v = cast(array,kind::nested_vec);
        inline auto array_d = cast(array,kind::dynamic);
        inline auto array_f = cast(array,kind::fixed);
        inline auto array_h = cast(array,kind::hybrid);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        inline int shape[2] = {2,4};
        inline int dim = 2;
        inline int result[2][4] = {
            {1,1,2,2},
            {3,3,4,4}
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4)
    {
        inline int array[2][2] = {{1,2},{3,4}};
        inline auto repeats = std::array{1,2};
        inline auto axis = 0;
        inline auto array_a = cast<int>(array);
        inline auto array_v = cast(array,kind::nested_vec);
        inline auto array_d = cast(array,kind::dynamic);
        inline auto array_f = cast(array,kind::fixed);
        inline auto array_h = cast(array,kind::hybrid);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        inline int shape[2] = {3,2};
        inline int dim = 2;
        inline int result[3][2] = {
            {1,2},
            {3,4},
            {3,4},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case5)
    {
        inline int array[2][2] = {{1,2},{3,4}};
        inline auto repeats = std::array{1,2};
        inline auto axis = 1;
        inline auto array_a = cast<int>(array);
        inline auto array_v = cast(array,kind::nested_vec);
        inline auto array_d = cast(array,kind::dynamic);
        inline auto array_f = cast(array,kind::fixed);
        inline auto array_h = cast(array,kind::hybrid);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case5)
    {
        inline int shape[2] = {2,3};
        inline int dim = 2;
        inline int result[2][3] = {
            {1,2,2},
            {3,4,4}
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case6)
    {
        inline int array[1][2][2] = {{{1,2},{3,4}}};
        inline auto repeats = 2;
        inline auto axis = 0;
        inline auto array_a = cast<int>(array);
        inline auto array_v = cast(array,kind::nested_vec);
        inline auto array_d = cast(array,kind::dynamic);
        inline auto array_f = cast(array,kind::fixed);
        inline auto array_h = cast(array,kind::hybrid);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case6)
    {
        inline int shape[3] = {2,2,2};
        inline int dim = 3;
        inline int result[2][2][2] = {
            {
                {1,2},
                {3,4}
            },
            {
                {1,2},
                {3,4}
            },
        };
    }
}

#endif // NMTOOLS_TESTING_DATA_ARRAY_REPEAT_HPP