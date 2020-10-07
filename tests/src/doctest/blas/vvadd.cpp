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
 * @test test cases for vvadd
 * 
 */
TEST_CASE("blas::vvadd")
{
    NMTOOLS_TESTING_DECLARE_SUBCASES2(case1, blas::vvadd, expect::x, args::x, args::y);
    NMTOOLS_TESTING_DEC_RAW_SUBCASES2(case1, blas::vvadd, expect::x, args::v10, args::v10);
    NMTOOLS_TESTING_DECLARE_SUBCASES2(case2, blas::vvadd, expect::x, args::x, args::y);
    NMTOOLS_TESTING_DEC_RAW_SUBCASES2(case2, blas::vvadd, expect::x, args::v20, args::v20);
} // TEST_CASE("blas::vvadd")