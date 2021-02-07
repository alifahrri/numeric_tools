#include "nmtools/array/view/concatenate.hpp"
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
using namespace nm::literals;

NMTOOLS_TESTING_DECLARE_CASE(view, concatenate)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        int lhs[2][2] = {{1,2},{3,4}};
        int rhs[1][2] = {{5,6}};
        int axis = 0;
        auto lhs_a = cast<int>(lhs);
        auto rhs_a = cast<int>(rhs);
        auto lhs_v = cast(lhs,kind::nested_vec);
        auto rhs_v = cast(rhs,kind::nested_vec);
        auto lhs_d = cast(lhs,kind::dynamic);
        auto rhs_d = cast(rhs,kind::dynamic);
        auto lhs_h = cast(lhs,kind::hybrid);
        auto rhs_h = cast(rhs,kind::hybrid);
        auto lhs_f = cast(lhs,kind::fixed);
        auto rhs_f = cast(rhs,kind::fixed);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        int shape[2] = {3,2};
        int expected[3][2] = {
            {1,2},
            {3,4},
            {5,6},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        int lhs[2][2] = {{1,2},{3,4}};
        int rhs[2][1] = {{5},{6}};
        int axis = 1;
        auto lhs_a = cast<int>(lhs);
        auto rhs_a = cast<int>(rhs);
        auto lhs_v = cast(lhs,kind::nested_vec);
        auto rhs_v = cast(rhs,kind::nested_vec);
        auto lhs_d = cast(lhs,kind::dynamic);
        auto rhs_d = cast(rhs,kind::dynamic);
        auto lhs_h = cast(lhs,kind::hybrid);
        auto rhs_h = cast(rhs,kind::hybrid);
        auto lhs_f = cast(lhs,kind::fixed);
        auto rhs_f = cast(rhs,kind::fixed);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        int shape[2] = {2,3};
        int expected[2][3] = {
            {1,2,5},
            {3,4,6},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        int lhs[2][2] = {{1,2},{3,4}};
        int rhs[2][1] = {{5},{6}};
        auto axis = None;
        auto lhs_a = cast<int>(lhs);
        auto rhs_a = cast<int>(rhs);
        auto lhs_v = cast(lhs,kind::nested_vec);
        auto rhs_v = cast(rhs,kind::nested_vec);
        auto lhs_d = cast(lhs,kind::dynamic);
        auto rhs_d = cast(rhs,kind::dynamic);
        auto lhs_h = cast(lhs,kind::hybrid);
        auto rhs_h = cast(rhs,kind::hybrid);
        auto lhs_f = cast(lhs,kind::fixed);
        auto rhs_f = cast(rhs,kind::fixed);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        int shape[1] = {6};
        int expected[6] = {1,2,3,4,5,6};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4)
    {
        int lhs[2][1][2] = {{{1,2}},{{3,4}}};
        int rhs[2][1][1] = {{{5}},{{6}}};
        int axis = 2;
        auto lhs_a = cast<int>(lhs);
        auto rhs_a = cast<int>(rhs);
        auto lhs_v = cast(lhs,kind::nested_vec);
        auto rhs_v = cast(rhs,kind::nested_vec);
        auto lhs_d = cast(lhs,kind::dynamic);
        auto rhs_d = cast(rhs,kind::dynamic);
        auto lhs_h = cast(lhs,kind::hybrid);
        auto rhs_h = cast(rhs,kind::hybrid);
        auto lhs_f = cast(lhs,kind::fixed);
        auto rhs_f = cast(rhs,kind::fixed);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        int shape[3] = {2,1,3};
        int expected[2][1][3] = {
            {
                {1,2,5}
            },
            {
                {3,4,6},
            }
        };
    }
}

#define CONCATENATE_SUBCASE(case_name, lhs, rhs, axis) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(view, concatenate, case_name); \
    auto array_ref = view::concatenate(args::lhs, args::rhs, args::axis); \
    NMTOOLS_ASSERT_EQUAL( array_ref.shape(), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( array_ref, expect::expected ); \
}


// @note not supported yet
// TEST_CASE("concatenate(raw)" * doctest::test_suite("view::concatenate"))
// {
//     CONCATENATE_SUBCASE(case1, lhs, rhs, axis);
// }

TEST_CASE("concatenate(array)" * doctest::test_suite("view::concatenate"))
{
    CONCATENATE_SUBCASE(case1, lhs_a, rhs_a, axis);
    CONCATENATE_SUBCASE(case2, lhs_a, rhs_a, axis);
    CONCATENATE_SUBCASE(case3, lhs_a, rhs_a, axis);
    CONCATENATE_SUBCASE(case4, lhs_a, rhs_a, axis);
}

TEST_CASE("concatenate(vector)" * doctest::test_suite("view::concatenate"))
{
    CONCATENATE_SUBCASE(case1, lhs_v, rhs_v, axis);
    CONCATENATE_SUBCASE(case2, lhs_v, rhs_v, axis);
    CONCATENATE_SUBCASE(case3, lhs_v, rhs_v, axis);
    CONCATENATE_SUBCASE(case4, lhs_v, rhs_v, axis);
}

TEST_CASE("concatenate(fixed_ndarray)" * doctest::test_suite("view::concatenate"))
{
    CONCATENATE_SUBCASE(case1, lhs_f, rhs_f, axis);
    CONCATENATE_SUBCASE(case2, lhs_f, rhs_f, axis);
    CONCATENATE_SUBCASE(case3, lhs_f, rhs_f, axis);
    CONCATENATE_SUBCASE(case4, lhs_f, rhs_f, axis);
}

TEST_CASE("concatenate(dynamic_ndarray)" * doctest::test_suite("view::concatenate"))
{
    CONCATENATE_SUBCASE(case1, lhs_d, rhs_d, axis);
    CONCATENATE_SUBCASE(case2, lhs_d, rhs_d, axis);
    CONCATENATE_SUBCASE(case3, lhs_d, rhs_d, axis);
    CONCATENATE_SUBCASE(case4, lhs_d, rhs_d, axis);
}

TEST_CASE("concatenate(hybrid_ndarray)" * doctest::test_suite("view::concatenate"))
{
    CONCATENATE_SUBCASE(case1, lhs_h, rhs_h, axis);
    CONCATENATE_SUBCASE(case2, lhs_h, rhs_h, axis);
    CONCATENATE_SUBCASE(case3, lhs_h, rhs_h, axis);
    CONCATENATE_SUBCASE(case4, lhs_h, rhs_h, axis);
}