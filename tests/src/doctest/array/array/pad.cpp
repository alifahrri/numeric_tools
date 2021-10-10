#include "nmtools/array/array/pad.hpp"
#include "nmtools/testing/data/array/pad.hpp"
#include "nmtools/testing/doctest.hpp"

#define RUN_pad_impl(...) \
nmtools::array::pad(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs pad fn to callable lambda
#define RUN_pad(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("array::pad-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_pad_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_pad(case_name, ...) \
RUN_pad_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define PAD_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(array, pad, case_name); \
    using namespace args; \
    auto result = RUN_pad(case_name, __VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( result, expect::result ); \
}

TEST_CASE("pad(case1)" * doctest::test_suite("array::pad"))
{
    PAD_SUBCASE( case1, array, pad_width );
    PAD_SUBCASE( case1, array_a, pad_width_a );
    PAD_SUBCASE( case1, array_f, pad_width_f );
    PAD_SUBCASE( case1, array_h, pad_width_h );
    PAD_SUBCASE( case1, array_d, pad_width_a );
}

TEST_CASE("pad(case2)" * doctest::test_suite("array::pad"))
{
    PAD_SUBCASE( case2, array, pad_width );
    PAD_SUBCASE( case2, array_a, pad_width_a );
    PAD_SUBCASE( case2, array_f, pad_width_f );
    PAD_SUBCASE( case2, array_h, pad_width_h );
    PAD_SUBCASE( case2, array_d, pad_width_a );
}

TEST_CASE("pad(case3)" * doctest::test_suite("array::pad"))
{
    PAD_SUBCASE( case3, array, pad_width );
    PAD_SUBCASE( case3, array_a, pad_width_a );
    PAD_SUBCASE( case3, array_f, pad_width_f );
    PAD_SUBCASE( case3, array_h, pad_width_h );
    PAD_SUBCASE( case3, array_d, pad_width_a );
}

TEST_CASE("pad(case4)" * doctest::test_suite("array::pad"))
{
    PAD_SUBCASE( case4, array, pad_width );
    PAD_SUBCASE( case4, array_a, pad_width_a );
    PAD_SUBCASE( case4, array_f, pad_width_f );
    PAD_SUBCASE( case4, array_h, pad_width_h );
    PAD_SUBCASE( case4, array_d, pad_width_a );
}

TEST_CASE("pad(case5)" * doctest::test_suite("array::pad"))
{
    PAD_SUBCASE( case5, array, pad_width );
    PAD_SUBCASE( case5, array_a, pad_width_a );
    PAD_SUBCASE( case5, array_f, pad_width_f );
    PAD_SUBCASE( case5, array_h, pad_width_h );
    PAD_SUBCASE( case5, array_d, pad_width_a );
}