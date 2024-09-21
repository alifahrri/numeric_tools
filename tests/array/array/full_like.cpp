#include "nmtools/array/array/full_like.hpp"
#include "nmtools/testing/data/array/full_like.hpp"
#include "nmtools/testing/doctest.hpp"

#define FULL_LIKE_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE( array, full_like, case_name ); \
    using namespace args; \
    auto result = nmtools::array::full_like(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( nmtools::shape(result), nmtools::shape(expect::result) ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("full_like(case1)" * doctest::test_suite("array::full_like"))
{
    FULL_LIKE_SUBCASE( case1, a, fill_value );
    FULL_LIKE_SUBCASE( case1, a_a, fill_value );
    FULL_LIKE_SUBCASE( case1, a_f, fill_value );
    FULL_LIKE_SUBCASE( case1, a_h, fill_value );
    FULL_LIKE_SUBCASE( case1, a_d, fill_value );
}

TEST_CASE("full_like(case2)" * doctest::test_suite("array::full_like"))
{
    FULL_LIKE_SUBCASE( case2, a, fill_value );
    FULL_LIKE_SUBCASE( case2, a_a, fill_value );
    FULL_LIKE_SUBCASE( case2, a_f, fill_value );
    FULL_LIKE_SUBCASE( case2, a_h, fill_value );
    FULL_LIKE_SUBCASE( case2, a_d, fill_value );
}

TEST_CASE("full_like(case3)" * doctest::test_suite("array::full_like"))
{
    FULL_LIKE_SUBCASE( case3, a, fill_value, dtype );
    FULL_LIKE_SUBCASE( case3, a_a, fill_value, dtype );
    FULL_LIKE_SUBCASE( case3, a_f, fill_value, dtype );
    FULL_LIKE_SUBCASE( case3, a_h, fill_value, dtype );
    FULL_LIKE_SUBCASE( case3, a_d, fill_value, dtype );
}