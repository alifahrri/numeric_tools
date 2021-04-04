#include "nmtools/array/array/ufuncs/logical_and.hpp"
#include "nmtools/testing/data/array/logical_and.hpp"
#include "nmtools/testing/doctest.hpp"

#include <vector>
#include <array>
#include <algorithm> // std::max

namespace nm = nmtools;
namespace na = nm::array;

#define RUN_logical_and_impl(...) \
nm::array::logical_and(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs logical_and fn to callable lambda
#define RUN_logical_and(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("logical_and-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_logical_and_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_logical_and(case_name, ...) \
RUN_logical_and_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define LOGICAL_AND_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(view, logical_and, case_name); \
    using namespace args; \
    auto result = RUN_logical_and(case_name, __VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( result.shape(), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("logical_and(case1)" * doctest::test_suite("array::logical_and"))
{
    LOGICAL_AND_SUBCASE( case1,   a,   b );
    LOGICAL_AND_SUBCASE( case1, a_a, b_a );
    LOGICAL_AND_SUBCASE( case1, a_v, b_v );
    LOGICAL_AND_SUBCASE( case1, a_f, b_f );
    LOGICAL_AND_SUBCASE( case1, a_d, b_d );
    LOGICAL_AND_SUBCASE( case1, a_h, b_h );
}