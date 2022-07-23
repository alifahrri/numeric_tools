#if defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
#define NMTOOLS_CAST_ARRAYS_EXTRA(name) \
inline auto name##_cs_fb = nmtools::cast(name, nmtools::array::kind::ndarray_cs_fb); \
inline auto name##_cs_hb = nmtools::cast(name, nmtools::array::kind::ndarray_cs_hb); \
inline auto name##_cs_db = nmtools::cast(name, nmtools::array::kind::ndarray_cs_db); \
inline auto name##_fs_fb = nmtools::cast(name, nmtools::array::kind::ndarray_fs_fb); \
inline auto name##_fs_hb = nmtools::cast(name, nmtools::array::kind::ndarray_fs_hb); \
inline auto name##_fs_db = nmtools::cast(name, nmtools::array::kind::ndarray_fs_db); \
inline auto name##_hs_fb = nmtools::cast(name, nmtools::array::kind::ndarray_hs_fb); \
inline auto name##_hs_hb = nmtools::cast(name, nmtools::array::kind::ndarray_hs_hb); \
inline auto name##_hs_db = nmtools::cast(name, nmtools::array::kind::ndarray_hs_db); \
inline auto name##_ds_fb = nmtools::cast(name, nmtools::array::kind::ndarray_ds_fb); \
inline auto name##_ds_hb = nmtools::cast(name, nmtools::array::kind::ndarray_ds_hb); \
inline auto name##_ds_db = nmtools::cast(name, nmtools::array::kind::ndarray_ds_db);
#endif

#include "nmtools/array/view/flatten.hpp"
#include "nmtools/testing/data/array/flatten.hpp"
#include "nmtools/testing/doctest.hpp"

#include <array>
#include <vector>

namespace nm = nmtools;
namespace na = nm::array;
namespace view = nm::view;
namespace meta = nm::meta;

#define RUN_impl(...) \
nm::view::flatten(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs flatten fn to callable lambda
#define RUN_flatten(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("flatten-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_flatten(case_name, ...) \
RUN_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define FLATTEN_SUBCASE(case_name, array) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(flatten,case_name); \
    auto array_ref = RUN_flatten(case_name, args::array); \
    NMTOOLS_REQUIRE_EQUAL( array_ref.shape(), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( array_ref, expect::expected ); \
}

TEST_CASE("flatten(case1)" * doctest::test_suite("view::flatten"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    FLATTEN_SUBCASE( case1, array );
    FLATTEN_SUBCASE( case1, array_a );
    FLATTEN_SUBCASE( case1, array_f );
    FLATTEN_SUBCASE( case1, array_d );
    FLATTEN_SUBCASE( case1, array_h );

    #else
    FLATTEN_SUBCASE( case1, array_cs_fb );
    FLATTEN_SUBCASE( case1, array_cs_hb );
    FLATTEN_SUBCASE( case1, array_cs_db );

    FLATTEN_SUBCASE( case1, array_fs_fb );
    FLATTEN_SUBCASE( case1, array_fs_hb );
    FLATTEN_SUBCASE( case1, array_fs_db );

    FLATTEN_SUBCASE( case1, array_hs_fb );
    FLATTEN_SUBCASE( case1, array_hs_hb );
    FLATTEN_SUBCASE( case1, array_hs_db );

    FLATTEN_SUBCASE( case1, array_ds_fb );
    FLATTEN_SUBCASE( case1, array_ds_hb );
    FLATTEN_SUBCASE( case1, array_ds_db );
    #endif
}

TEST_CASE("flatten(case2)" * doctest::test_suite("view::flatten"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    FLATTEN_SUBCASE( case2, array );
    FLATTEN_SUBCASE( case2, array_a );
    FLATTEN_SUBCASE( case2, array_f );
    FLATTEN_SUBCASE( case2, array_d );
    FLATTEN_SUBCASE( case2, array_h );

    #else
    FLATTEN_SUBCASE( case2, array_cs_fb );
    FLATTEN_SUBCASE( case2, array_cs_hb );
    FLATTEN_SUBCASE( case2, array_cs_db );

    FLATTEN_SUBCASE( case2, array_fs_fb );
    FLATTEN_SUBCASE( case2, array_fs_hb );
    FLATTEN_SUBCASE( case2, array_fs_db );

    FLATTEN_SUBCASE( case2, array_hs_fb );
    FLATTEN_SUBCASE( case2, array_hs_hb );
    FLATTEN_SUBCASE( case2, array_hs_db );

    FLATTEN_SUBCASE( case2, array_ds_fb );
    FLATTEN_SUBCASE( case2, array_ds_hb );
    FLATTEN_SUBCASE( case2, array_ds_db );
    #endif
}

TEST_CASE("flatten(case3)" * doctest::test_suite("view::flatten"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    FLATTEN_SUBCASE( case3, array );
    FLATTEN_SUBCASE( case3, array_a );
    FLATTEN_SUBCASE( case3, array_f );
    FLATTEN_SUBCASE( case3, array_d );
    FLATTEN_SUBCASE( case3, array_h );

    #else
    FLATTEN_SUBCASE( case3, array_cs_fb );
    FLATTEN_SUBCASE( case3, array_cs_hb );
    FLATTEN_SUBCASE( case3, array_cs_db );

    FLATTEN_SUBCASE( case3, array_fs_fb );
    FLATTEN_SUBCASE( case3, array_fs_hb );
    FLATTEN_SUBCASE( case3, array_fs_db );

    FLATTEN_SUBCASE( case3, array_hs_fb );
    FLATTEN_SUBCASE( case3, array_hs_hb );
    FLATTEN_SUBCASE( case3, array_hs_db );

    FLATTEN_SUBCASE( case3, array_ds_fb );
    FLATTEN_SUBCASE( case3, array_ds_hb );
    FLATTEN_SUBCASE( case3, array_ds_db );
    #endif
}

TEST_CASE("flatten(case4)" * doctest::test_suite("view::flatten"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    FLATTEN_SUBCASE( case4, array );
    FLATTEN_SUBCASE( case4, array_a );
    FLATTEN_SUBCASE( case4, array_f );
    FLATTEN_SUBCASE( case4, array_d );
    FLATTEN_SUBCASE( case4, array_h );

    #else
    FLATTEN_SUBCASE( case4, array_cs_fb );
    FLATTEN_SUBCASE( case4, array_cs_hb );
    FLATTEN_SUBCASE( case4, array_cs_db );

    FLATTEN_SUBCASE( case4, array_fs_fb );
    FLATTEN_SUBCASE( case4, array_fs_hb );
    FLATTEN_SUBCASE( case4, array_fs_db );

    FLATTEN_SUBCASE( case4, array_hs_fb );
    FLATTEN_SUBCASE( case4, array_hs_hb );
    FLATTEN_SUBCASE( case4, array_hs_db );

    FLATTEN_SUBCASE( case4, array_ds_fb );
    FLATTEN_SUBCASE( case4, array_ds_hb );
    FLATTEN_SUBCASE( case4, array_ds_db );
    #endif
}

TEST_CASE("flatten(case5)" * doctest::test_suite("view::flatten"))
{
    FLATTEN_SUBCASE( case5, array );
}

template <typename array_t>
auto f(const array_t& array)
{
    return view::flatten(array);
}

template <typename array_t>
auto g(const array_t& array)
{
    auto flattened = f(array);
    return view::flatten(flattened);
}

TEST_CASE("flatten" * doctest::test_suite("view::flatten"))
{
    {
        int array[2][3] = {
            {1,2,3},
            {4,5,6},
        };
        auto flattened = f(array);
        auto expected  = std::array{1,2,3,4,5,6};
        NMTOOLS_ASSERT_EQUAL( flattened, expected );
    }
    {
        int array[2][3] = {
            {1,2,3},
            {4,5,6},
        };
        auto flattened = g(array);
        auto expected  = std::array{1,2,3,4,5,6};
        NMTOOLS_ASSERT_EQUAL( flattened, expected );
    }
}