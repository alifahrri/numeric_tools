#include "nmtools/array/view/ufuncs/negative.hpp"
#include "nmtools/array/ndarray/dynamic.hpp"
#include "nmtools/array/ndarray/hybrid.hpp"
#include "nmtools/array/ndarray/fixed.hpp"
#include "nmtools/testing/doctest.hpp"

#include <vector>
#include <array>

namespace nm = nmtools;
namespace na = nm::array;
namespace view = nm::view;
namespace kind = na::kind;

#define CAST_ARRAYS(name) \
auto name##_a = cast(name, kind::nested_arr); \
auto name##_v = cast(name, kind::nested_vec); \
auto name##_f = cast(name, kind::fixed); \
auto name##_d = cast(name, kind::dynamic); \
auto name##_h = cast(name, kind::hybrid); \

NMTOOLS_TESTING_DECLARE_CASE(view, negative)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        int a[3][3] = {
            {0,1,2},
            {3,4,5},
            {6,7,8},
        };
        CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        int shape[2] = {3,3};
        int result[3][3] = {
            {-0,-1,-2},
            {-3,-4,-5},
            {-6,-7,-8},
        };
    }
}

#define RUN_negative_impl(...) \
nm::view::negative(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs negative fn to callable lambda
#define RUN_negative(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("negative-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_negative_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_negative(case_name, ...) \
RUN_negative_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define NEGATIVE_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(view, negative, case_name); \
    using namespace args; \
    auto result = RUN_negative(case_name, __VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( result.shape(), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("negative(case1)" * doctest::test_suite("view::negative"))
{
    NEGATIVE_SUBCASE( case1,   a);
    NEGATIVE_SUBCASE( case1, a_a);
    NEGATIVE_SUBCASE( case1, a_v);
    NEGATIVE_SUBCASE( case1, a_f);
    NEGATIVE_SUBCASE( case1, a_d);
    NEGATIVE_SUBCASE( case1, a_h);
}