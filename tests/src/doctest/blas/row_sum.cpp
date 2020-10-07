// NOTE: seems like it is required to include these headers first
// TODO: fix dependency
#include "nmtools/array/fixed.hpp"
#include "nmtools/array/dynamic.hpp"
#include "testing/data/blas.hpp"
#include "doctest/doctest.h"

/**
 * @brief define testing using doctest
 * 
 */
#define NMTOOLS_ASSERT_CLOSE NMTOOLS_ASSERT_CLOSE_DOCTEST

/**
 * @brief check if we should disable benchmark
 * 
 */
#ifdef NMTOOLS_TESTING_DOCTEST_DISABLE_BENCH
namespace blas = nmtools::blas;
#define NMTOOLS_TEST_SUBCASE NMTOOLS_TESTING_DOCTEST_SUBCASE
#else
// TODO: rename to nmtools/bench/common.hpp or something
#include "common.hpp"
// TODO: rename to nmtools/bench/blas.hpp or something
#include "blas.hpp"
namespace blas = nmtools::bench::nanobench::blas;
#define NMTOOLS_TEST_SUBCASE NMTOOLS_BENCH_DOCTEST_SUBCASE
#endif

/**
 * @test test casses for nmtools::blas::row_sum
 * 
 */
TEST_CASE("blas::row_sum")
{
    NMTOOLS_TESTING_DECLARE_SUBCASES(case1, blas::row_sum, expect::sum, args::x );
    NMTOOLS_TESTING_DEC_RAW_SUBCASES(case1, blas::row_sum, expect::sum, args::x );
    NMTOOLS_TESTING_DECLARE_SUBCASES(case2, blas::row_sum, expect::sum, args::x );
    NMTOOLS_TESTING_DEC_RAW_SUBCASES(case2, blas::row_sum, expect::sum, args::m5x5 );
    NMTOOLS_TESTING_DECLARE_SUBCASES(case3, blas::row_sum, expect::sum, args::x );
    NMTOOLS_TESTING_DEC_RAW_SUBCASES(case3, blas::row_sum, expect::sum, args::m10x10 );
    NMTOOLS_TESTING_DECLARE_SUBCASES(case4, blas::row_sum, expect::sum, args::x );
    NMTOOLS_TESTING_DEC_RAW_SUBCASES(case4, blas::row_sum, expect::sum, args::m15x15 );
    NMTOOLS_TESTING_DECLARE_SUBCASES(case5, blas::row_sum, expect::sum, args::x );
    NMTOOLS_TESTING_DEC_RAW_SUBCASES(case5, blas::row_sum, expect::sum, args::m20x20 );
    NMTOOLS_TESTING_DECLARE_SUBCASES(case6, blas::row_sum, expect::sum, args::x );
    NMTOOLS_TESTING_DEC_RAW_SUBCASES(case6, blas::row_sum, expect::sum, args::m25x25 );
} // TEST_CASE("blas::row_sum")