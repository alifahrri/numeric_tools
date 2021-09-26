#include "nmtools/array/view/var.hpp"
#include "nmtools/testing/data/array/var.hpp"
#include "nmtools/testing/doctest.hpp"

#define RUN_var_impl(...) \
nmtools::view::var(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs var fn to callable lambda
#define RUN_var(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("view::var-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_var_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_var(case_name, ...) \
RUN_var_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define VAR_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(array, var, case_name); \
    using namespace args; \
    auto result = RUN_var(case_name, __VA_ARGS__); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("var(case1)" * doctest::test_suite("view::var"))
{
    VAR_SUBCASE( case1, array, axis );
    VAR_SUBCASE( case1, array_a, axis_a );
    VAR_SUBCASE( case1, array_f, axis_f );
    VAR_SUBCASE( case1, array_h, axis );
    // not supported yet,
    // TODO: support slicing for dynamic dim
    // VAR_SUBCASE( case1, array_d, axis );
}

TEST_CASE("var(case2)" * doctest::test_suite("view::var"))
{
    VAR_SUBCASE( case2, array, axis );
    VAR_SUBCASE( case2, array_a, axis_a );
    VAR_SUBCASE( case2, array_f, axis_f );
    VAR_SUBCASE( case2, array_h, axis );
    // not supported yet,
    // TODO: support slicing for dynamic dim
    // VAR_SUBCASE( case2, array_d, axis );
}

TEST_CASE("var(case3)" * doctest::test_suite("view::var"))
{
    VAR_SUBCASE( case3, array, axis );
    VAR_SUBCASE( case3, array_a, axis );
    VAR_SUBCASE( case3, array_f, axis );
    VAR_SUBCASE( case3, array_h, axis );
    // not supported yet,
    // TODO: support slicing for dynamic dim
    // VAR_SUBCASE( case3, array_d, axis );
}

TEST_CASE("var(case4)" * doctest::test_suite("view::var"))
{
    VAR_SUBCASE( case4, array, axis );
    VAR_SUBCASE( case4, array_a, axis );
    VAR_SUBCASE( case4, array_f, axis );
    VAR_SUBCASE( case4, array_h, axis );
    // not supported yet,
    // TODO: support slicing for dynamic dim
    // VAR_SUBCASE( case4, array_d, axis );
}

TEST_CASE("var(case5)" * doctest::test_suite("view::var"))
{
    VAR_SUBCASE( case5, array, axis );
    VAR_SUBCASE( case5, array_a, axis );
    VAR_SUBCASE( case5, array_f, axis );
    VAR_SUBCASE( case5, array_h, axis );
    // not supported yet,
    // TODO: support slicing for dynamic dim
    // VAR_SUBCASE( case5, array_d, axis );
}

TEST_CASE("var(case6)" * doctest::test_suite("view::var"))
{
    VAR_SUBCASE( case6,   array, axis, nm::None, ddof, keepdims );
    VAR_SUBCASE( case6, array_a, axis, nm::None, ddof, keepdims );
    VAR_SUBCASE( case6, array_f, axis, nm::None, ddof, keepdims );
    VAR_SUBCASE( case6, array_h, axis, nm::None, ddof, keepdims );
    // not supported yet,
    // TODO: support slicing for dynamic dim
    // VAR_SUBCASE( case6, array_d, axis, nm::None, ddof, keepdims );
}

TEST_CASE("var(case7)" * doctest::test_suite("view::var"))
{
    VAR_SUBCASE( case7,   array, axis, nm::None, ddof, keepdims );
    VAR_SUBCASE( case7, array_a, axis, nm::None, ddof, keepdims );
    VAR_SUBCASE( case7, array_f, axis, nm::None, ddof, keepdims );
    VAR_SUBCASE( case7, array_h, axis, nm::None, ddof, keepdims );
    // not supported yet,
    // TODO: support slicing for dynamic dim
    // VAR_SUBCASE( case7, array_d, axis, nm::None, ddof, keepdims );
}

TEST_CASE("var(case8)" * doctest::test_suite("view::var"))
{
    VAR_SUBCASE( case8,   array, axis, nm::None, ddof, keepdims );
    VAR_SUBCASE( case8, array_a, axis, nm::None, ddof, keepdims );
    VAR_SUBCASE( case8, array_f, axis, nm::None, ddof, keepdims );
    VAR_SUBCASE( case8, array_h, axis, nm::None, ddof, keepdims );
    // not supported yet,
    // TODO: support slicing for dynamic dim
    // VAR_SUBCASE( case7, array_d, axis, nm::None, ddof, keepdims );
}

TEST_CASE("var(case9)" * doctest::test_suite("view::var"))
{
    VAR_SUBCASE( case9,   array, axis, nm::None, ddof, keepdims );
    VAR_SUBCASE( case9, array_a, axis, nm::None, ddof, keepdims );
    VAR_SUBCASE( case9, array_f, axis, nm::None, ddof, keepdims );
    VAR_SUBCASE( case9, array_h, axis, nm::None, ddof, keepdims );
    // not supported yet,
    // TODO: support slicing for dynamic dim
    // VAR_SUBCASE( case9, array_d, axis, nm::None, ddof, keepdims );
}

namespace view = nm::view;
namespace meta = nm::meta;

TEST_CASE("var(case10)" * doctest::test_suite("view::var"))
{
    {
        NMTOOLS_TESTING_DECLARE_NS(array, var, case10);
        using namespace args;

        auto var = view::var(array, axis, nm::None, ddof, keepdims );
        using var_t = decltype(var);
        static_assert( meta::is_either_v<var_t> );

        using left_t  = meta::get_either_left_t<var_t>;
        using right_t = meta::get_either_right_t<var_t>;
        static_assert( meta::is_num_v<left_t> );
        static_assert( meta::is_ndarray_v<right_t> );

        auto value = std::get_if<left_t>(&var);
        NMTOOLS_ASSERT_CLOSE( *value, expect::result );
    }

    VAR_SUBCASE( case10,   array, axis, nm::None, ddof, keepdims );
    VAR_SUBCASE( case10, array_a, axis, nm::None, ddof, keepdims );
    VAR_SUBCASE( case10, array_f, axis, nm::None, ddof, keepdims );
    VAR_SUBCASE( case10, array_h, axis, nm::None, ddof, keepdims );
    // not supported yet,
    // TODO: support slicing for dynamic dim
    // VAR_SUBCASE( case10, array_d, axis, nm::None, ddof, keepdims );
}

TEST_CASE("var(case11)" * doctest::test_suite("view::var"))
{
    VAR_SUBCASE( case11,   array, axis, nm::None, ddof, keepdims );
    VAR_SUBCASE( case11, array_a, axis, nm::None, ddof, keepdims );
    VAR_SUBCASE( case11, array_f, axis, nm::None, ddof, keepdims );
    VAR_SUBCASE( case11, array_h, axis, nm::None, ddof, keepdims );
    // not supported yet,
    // TODO: support slicing for dynamic dim
    // VAR_SUBCASE( case11, array_d, axis, nm::None, ddof, keepdims );
}

TEST_CASE("var(case12)" * doctest::test_suite("view::var"))
{
    VAR_SUBCASE( case12,   array, axis, nm::None, ddof, keepdims );
    VAR_SUBCASE( case12, array_a, axis, nm::None, ddof, keepdims );
    VAR_SUBCASE( case12, array_f, axis, nm::None, ddof, keepdims );
    VAR_SUBCASE( case12, array_h, axis, nm::None, ddof, keepdims );
    // not supported yet,
    // TODO: support slicing for dynamic dim
    // VAR_SUBCASE( case12, array_d, axis, nm::None, ddof, keepdims );
}

TEST_CASE("var(case13)" * doctest::test_suite("view::var"))
{
    VAR_SUBCASE( case13,   array, axis, nm::None, ddof, keepdims );
    VAR_SUBCASE( case13, array_a, axis, nm::None, ddof, keepdims );
    VAR_SUBCASE( case13, array_f, axis, nm::None, ddof, keepdims );
    VAR_SUBCASE( case13, array_h, axis, nm::None, ddof, keepdims );
    // not supported yet,
    // TODO: support slicing for dynamic dim
    // VAR_SUBCASE( case13, array_d, axis, nm::None, ddof, keepdims );
}

TEST_CASE("var(case14)" * doctest::test_suite("view::var"))
{
    VAR_SUBCASE( case14,   array, axis, nm::None, ddof, keepdims );
    VAR_SUBCASE( case14, array_a, axis, nm::None, ddof, keepdims );
    VAR_SUBCASE( case14, array_f, axis, nm::None, ddof, keepdims );
    VAR_SUBCASE( case14, array_h, axis, nm::None, ddof, keepdims );
    // not supported yet,
    // TODO: support slicing for dynamic dim
    // VAR_SUBCASE( case14, array_d, axis, nm::None, ddof, keepdims );
}