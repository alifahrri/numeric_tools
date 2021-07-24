#include "nmtools/array/eval.hpp"
#include "nmtools/array/view/flip.hpp"
#include "nmtools/array/ndarray/fixed.hpp"
#include "nmtools/array/ndarray/hybrid.hpp"
#include "nmtools/array/ndarray/dynamic.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace na = nm::array;
namespace view = nm::view;
namespace meta = nm::meta;

using namespace nm::literals;
using nm::none_t;

TEST_CASE("eval(flip)" * doctest::test_suite("eval"))
{
    {
        using view_t = view::decorator_t< view::flip_t, int[3], none_t >;
        using eval_t = meta::resolve_optype_t< na::eval_t, view_t, none_t >;
        using expected_t = std::array<int,3>;
        NMTOOLS_STATIC_CHECK_IS_SAME( eval_t, expected_t );
        static_assert( meta::is_fixed_size_ndarray_v<view_t> );
    }
    {
        using view_t = view::decorator_t< view::flip_t, na::fixed_ndarray<int,2,2,2>, none_t >;
        using eval_t = meta::resolve_optype_t< na::eval_t, view_t, none_t >;
        using expected_t = na::fixed_ndarray<int,2,2,2>;
        NMTOOLS_STATIC_CHECK_IS_SAME( eval_t, expected_t );
        static_assert( meta::is_fixed_size_ndarray_v<view_t> );
        static_assert( meta::is_fixed_size_ndarray_v<expected_t> );
        static_assert( meta::is_ndarray_v<expected_t> );
    }
}