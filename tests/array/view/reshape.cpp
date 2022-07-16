#if 1
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

#include "nmtools/array/view/reshape.hpp"
#include "nmtools/testing/data/array/reshape.hpp"
#include "nmtools/testing/doctest.hpp"

#include <array>
#include <tuple>
#include <vector>

namespace nm = nmtools;
namespace na = nm::array;
namespace view = nm::view;
namespace meta = nm::meta;

#define RUN_impl(...) \
nm::view::reshape(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs reshape fn to callable lambda
#define RUN_reshape(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("reshape-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_reshape(case_name, ...) \
RUN_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define RESHAPE_SUBCASE(case_name, array, newshape) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(reshape, case_name) \
    auto array_ref = RUN_reshape(case_name, args::array, args::newshape); \
    NMTOOLS_ASSERT_CLOSE( array_ref, expect::expected ); \
}

TEST_CASE("reshape(case1)" * doctest::test_suite("view::reshape"))
{
    RESHAPE_SUBCASE(case1, array, newshape );
    RESHAPE_SUBCASE(case1, array_a, newshape_a );
    RESHAPE_SUBCASE(case1, array_f, newshape_a );
    RESHAPE_SUBCASE(case1, array_d, newshape_v );
    RESHAPE_SUBCASE(case1, array_h, newshape_h );

    RESHAPE_SUBCASE(case1, array, newshape_ct );
    RESHAPE_SUBCASE(case1, array_a, newshape_ct );
    RESHAPE_SUBCASE(case1, array_f, newshape_ct );
    RESHAPE_SUBCASE(case1, array_d, newshape_ct );
    RESHAPE_SUBCASE(case1, array_h, newshape_ct );

    RESHAPE_SUBCASE(case1, array_cs_fb, newshape_ct );
    RESHAPE_SUBCASE(case1, array_cs_hb, newshape_ct );
    RESHAPE_SUBCASE(case1, array_cs_db, newshape_ct );

    RESHAPE_SUBCASE(case1, array_fs_fb, newshape_ct );
    RESHAPE_SUBCASE(case1, array_fs_hb, newshape_ct );
    RESHAPE_SUBCASE(case1, array_fs_db, newshape_ct );

    RESHAPE_SUBCASE(case1, array_hs_fb, newshape_ct );
    RESHAPE_SUBCASE(case1, array_hs_hb, newshape_ct );
    RESHAPE_SUBCASE(case1, array_hs_db, newshape_ct );

    RESHAPE_SUBCASE(case1, array_ds_fb, newshape_ct );
    RESHAPE_SUBCASE(case1, array_ds_hb, newshape_ct );
    RESHAPE_SUBCASE(case1, array_ds_db, newshape_ct );

    RESHAPE_SUBCASE(case1, array_cs_fb, newshape_a );
    RESHAPE_SUBCASE(case1, array_cs_hb, newshape_a );
    RESHAPE_SUBCASE(case1, array_cs_db, newshape_a );

    RESHAPE_SUBCASE(case1, array_fs_fb, newshape_a );
    RESHAPE_SUBCASE(case1, array_fs_hb, newshape_a );
    RESHAPE_SUBCASE(case1, array_fs_db, newshape_a );

    RESHAPE_SUBCASE(case1, array_hs_fb, newshape_a );
    RESHAPE_SUBCASE(case1, array_hs_hb, newshape_a );
    RESHAPE_SUBCASE(case1, array_hs_db, newshape_a );

    RESHAPE_SUBCASE(case1, array_ds_fb, newshape_a );
    RESHAPE_SUBCASE(case1, array_ds_hb, newshape_a );
    RESHAPE_SUBCASE(case1, array_ds_db, newshape_a );
}

TEST_CASE("reshape(case2)" * doctest::test_suite("view::reshape"))
{
    RESHAPE_SUBCASE(case2, array, newshape );
    RESHAPE_SUBCASE(case2, array_a, newshape_a );
    RESHAPE_SUBCASE(case2, array_f, newshape_a );
    RESHAPE_SUBCASE(case2, array_d, newshape_v );
    RESHAPE_SUBCASE(case2, array_h, newshape_h );

    RESHAPE_SUBCASE(case2, array, newshape_ct );
    RESHAPE_SUBCASE(case2, array_a, newshape_ct );
    RESHAPE_SUBCASE(case2, array_f, newshape_ct );
    RESHAPE_SUBCASE(case2, array_d, newshape_ct );
    RESHAPE_SUBCASE(case2, array_h, newshape_ct );

    RESHAPE_SUBCASE(case2, array_cs_fb, newshape_ct );
    RESHAPE_SUBCASE(case2, array_cs_hb, newshape_ct );
    RESHAPE_SUBCASE(case2, array_cs_db, newshape_ct );

    RESHAPE_SUBCASE(case2, array_fs_fb, newshape_ct );
    RESHAPE_SUBCASE(case2, array_fs_hb, newshape_ct );
    RESHAPE_SUBCASE(case2, array_fs_db, newshape_ct );

    RESHAPE_SUBCASE(case2, array_hs_fb, newshape_ct );
    RESHAPE_SUBCASE(case2, array_hs_hb, newshape_ct );
    RESHAPE_SUBCASE(case2, array_hs_db, newshape_ct );

    RESHAPE_SUBCASE(case2, array_ds_fb, newshape_ct );
    RESHAPE_SUBCASE(case2, array_ds_hb, newshape_ct );
    RESHAPE_SUBCASE(case2, array_ds_db, newshape_ct );

    RESHAPE_SUBCASE(case2, array_cs_fb, newshape_a );
    RESHAPE_SUBCASE(case2, array_cs_hb, newshape_a );
    RESHAPE_SUBCASE(case2, array_cs_db, newshape_a );

    RESHAPE_SUBCASE(case2, array_fs_fb, newshape_a );
    RESHAPE_SUBCASE(case2, array_fs_hb, newshape_a );
    RESHAPE_SUBCASE(case2, array_fs_db, newshape_a );

    RESHAPE_SUBCASE(case2, array_hs_fb, newshape_a );
    RESHAPE_SUBCASE(case2, array_hs_hb, newshape_a );
    RESHAPE_SUBCASE(case2, array_hs_db, newshape_a );

    RESHAPE_SUBCASE(case2, array_ds_fb, newshape_a );
    RESHAPE_SUBCASE(case2, array_ds_hb, newshape_a );
    RESHAPE_SUBCASE(case2, array_ds_db, newshape_a );
}

TEST_CASE("reshape(case3)" * doctest::test_suite("view::reshape"))
{
    RESHAPE_SUBCASE(case3, array, newshape );
    RESHAPE_SUBCASE(case3, array_a, newshape_a );
    RESHAPE_SUBCASE(case3, array_f, newshape_a );
    RESHAPE_SUBCASE(case3, array_d, newshape_v );
    RESHAPE_SUBCASE(case3, array_h, newshape_h );

    RESHAPE_SUBCASE(case3, array, newshape_ct );
    RESHAPE_SUBCASE(case3, array_a, newshape_ct );
    RESHAPE_SUBCASE(case3, array_f, newshape_ct );
    RESHAPE_SUBCASE(case3, array_d, newshape_ct );
    RESHAPE_SUBCASE(case3, array_h, newshape_ct );

    RESHAPE_SUBCASE(case3, array_cs_fb, newshape_ct );
    RESHAPE_SUBCASE(case3, array_cs_hb, newshape_ct );
    RESHAPE_SUBCASE(case3, array_cs_db, newshape_ct );

    RESHAPE_SUBCASE(case3, array_fs_fb, newshape_ct );
    RESHAPE_SUBCASE(case3, array_fs_hb, newshape_ct );
    RESHAPE_SUBCASE(case3, array_fs_db, newshape_ct );

    RESHAPE_SUBCASE(case3, array_hs_fb, newshape_ct );
    RESHAPE_SUBCASE(case3, array_hs_hb, newshape_ct );
    RESHAPE_SUBCASE(case3, array_hs_db, newshape_ct );

    RESHAPE_SUBCASE(case3, array_ds_fb, newshape_ct );
    RESHAPE_SUBCASE(case3, array_ds_hb, newshape_ct );
    RESHAPE_SUBCASE(case3, array_ds_db, newshape_ct );

    RESHAPE_SUBCASE(case3, array_cs_fb, newshape_a );
    RESHAPE_SUBCASE(case3, array_cs_hb, newshape_a );
    RESHAPE_SUBCASE(case3, array_cs_db, newshape_a );

    RESHAPE_SUBCASE(case3, array_fs_fb, newshape_a );
    RESHAPE_SUBCASE(case3, array_fs_hb, newshape_a );
    RESHAPE_SUBCASE(case3, array_fs_db, newshape_a );

    RESHAPE_SUBCASE(case3, array_hs_fb, newshape_a );
    RESHAPE_SUBCASE(case3, array_hs_hb, newshape_a );
    RESHAPE_SUBCASE(case3, array_hs_db, newshape_a );

    RESHAPE_SUBCASE(case3, array_ds_fb, newshape_a );
    RESHAPE_SUBCASE(case3, array_ds_hb, newshape_a );
    RESHAPE_SUBCASE(case3, array_ds_db, newshape_a );
}

TEST_CASE("reshape(case4)" * doctest::test_suite("view::reshape"))
{
    RESHAPE_SUBCASE(case4, array, newshape );
    RESHAPE_SUBCASE(case4, array_a, newshape_a );
    RESHAPE_SUBCASE(case4, array_f, newshape_a );
    RESHAPE_SUBCASE(case4, array_d, newshape_v );
    RESHAPE_SUBCASE(case4, array_h, newshape_h );

    RESHAPE_SUBCASE(case4, array, newshape_ct );
    RESHAPE_SUBCASE(case4, array_a, newshape_ct );
    RESHAPE_SUBCASE(case4, array_f, newshape_ct );
    RESHAPE_SUBCASE(case4, array_d, newshape_ct );
    RESHAPE_SUBCASE(case4, array_h, newshape_ct );

    RESHAPE_SUBCASE(case4, array_cs_fb, newshape_ct );
    RESHAPE_SUBCASE(case4, array_cs_hb, newshape_ct );
    RESHAPE_SUBCASE(case4, array_cs_db, newshape_ct );

    RESHAPE_SUBCASE(case4, array_fs_fb, newshape_ct );
    RESHAPE_SUBCASE(case4, array_fs_hb, newshape_ct );
    RESHAPE_SUBCASE(case4, array_fs_db, newshape_ct );

    RESHAPE_SUBCASE(case4, array_hs_fb, newshape_ct );
    RESHAPE_SUBCASE(case4, array_hs_hb, newshape_ct );
    RESHAPE_SUBCASE(case4, array_hs_db, newshape_ct );

    RESHAPE_SUBCASE(case4, array_ds_fb, newshape_ct );
    RESHAPE_SUBCASE(case4, array_ds_hb, newshape_ct );
    RESHAPE_SUBCASE(case4, array_ds_db, newshape_ct );

    RESHAPE_SUBCASE(case4, array_cs_fb, newshape_a );
    RESHAPE_SUBCASE(case4, array_cs_hb, newshape_a );
    RESHAPE_SUBCASE(case4, array_cs_db, newshape_a );

    RESHAPE_SUBCASE(case4, array_fs_fb, newshape_a );
    RESHAPE_SUBCASE(case4, array_fs_hb, newshape_a );
    RESHAPE_SUBCASE(case4, array_fs_db, newshape_a );

    RESHAPE_SUBCASE(case5, array_hs_fb, newshape_a );
    RESHAPE_SUBCASE(case5, array_hs_hb, newshape_a );
    RESHAPE_SUBCASE(case5, array_hs_db, newshape_a );

    RESHAPE_SUBCASE(case5, array_ds_fb, newshape_a );
    RESHAPE_SUBCASE(case5, array_ds_hb, newshape_a );
    RESHAPE_SUBCASE(case5, array_ds_db, newshape_a );
}

TEST_CASE("reshape(case5)" * doctest::test_suite("view::reshape"))
{
    RESHAPE_SUBCASE(case5, array, newshape );
    RESHAPE_SUBCASE(case5, array_a, newshape_a );
    RESHAPE_SUBCASE(case5, array_f, newshape_a );
    RESHAPE_SUBCASE(case5, array_d, newshape_v );
    RESHAPE_SUBCASE(case5, array_h, newshape_h );

    RESHAPE_SUBCASE(case5, array, newshape_ct );
    RESHAPE_SUBCASE(case5, array_a, newshape_ct );
    RESHAPE_SUBCASE(case5, array_f, newshape_ct );
    RESHAPE_SUBCASE(case5, array_d, newshape_ct );
    RESHAPE_SUBCASE(case5, array_h, newshape_ct );


    RESHAPE_SUBCASE(case5, array_cs_fb, newshape_ct );
    RESHAPE_SUBCASE(case5, array_cs_hb, newshape_ct );
    RESHAPE_SUBCASE(case5, array_cs_db, newshape_ct );

    RESHAPE_SUBCASE(case5, array_fs_fb, newshape_ct );
    RESHAPE_SUBCASE(case5, array_fs_hb, newshape_ct );
    RESHAPE_SUBCASE(case5, array_fs_db, newshape_ct );

    RESHAPE_SUBCASE(case5, array_hs_fb, newshape_ct );
    RESHAPE_SUBCASE(case5, array_hs_hb, newshape_ct );
    RESHAPE_SUBCASE(case5, array_hs_db, newshape_ct );

    RESHAPE_SUBCASE(case5, array_ds_fb, newshape_ct );
    RESHAPE_SUBCASE(case5, array_ds_hb, newshape_ct );
    RESHAPE_SUBCASE(case5, array_ds_db, newshape_ct );

    RESHAPE_SUBCASE(case5, array_cs_fb, newshape_a );
    RESHAPE_SUBCASE(case5, array_cs_hb, newshape_a );
    RESHAPE_SUBCASE(case5, array_cs_db, newshape_a );

    RESHAPE_SUBCASE(case5, array_fs_fb, newshape_a );
    RESHAPE_SUBCASE(case5, array_fs_hb, newshape_a );
    RESHAPE_SUBCASE(case5, array_fs_db, newshape_a );

    RESHAPE_SUBCASE(case5, array_hs_fb, newshape_a );
    RESHAPE_SUBCASE(case5, array_hs_hb, newshape_a );
    RESHAPE_SUBCASE(case5, array_hs_db, newshape_a );

    RESHAPE_SUBCASE(case5, array_ds_fb, newshape_a );
    RESHAPE_SUBCASE(case5, array_ds_hb, newshape_a );
    RESHAPE_SUBCASE(case5, array_ds_db, newshape_a );
}

// NOTE: currently reshape is not monadic
// TODO: support monadic error handling for reshape
#if 0
TEST_CASE("reshape(case6)" * doctest::test_suite("view::reshape"))
{
    RESHAPE_SUBCASE(case6, array, newshape );
    RESHAPE_SUBCASE(case6, array_a, newshape_a );
    RESHAPE_SUBCASE(case6, array_f, newshape_a );
    RESHAPE_SUBCASE(case6, array_d, newshape_v );
    RESHAPE_SUBCASE(case6, array_h, newshape_h );

    RESHAPE_SUBCASE(case6, array, newshape_ct );
    RESHAPE_SUBCASE(case6, array_a, newshape_ct );
    RESHAPE_SUBCASE(case6, array_f, newshape_ct );
    RESHAPE_SUBCASE(case6, array_d, newshape_ct );
    RESHAPE_SUBCASE(case6, array_h, newshape_ct );
}
#endif