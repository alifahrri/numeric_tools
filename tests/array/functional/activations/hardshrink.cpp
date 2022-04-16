#include "nmtools/array/functional/activations/hardshrink.hpp"
#include "nmtools/testing/data/array/hardshrink.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace fn = nmtools::functional;

#define ACTIVATIONS_SUBCASE(subcase_name, function, operand) \
SUBCASE(subcase_name) \
{ \
    auto result = function (operand); \
    NMTOOLS_REQUIRE_EQUAL( nm::shape(result), nm::shape(expect::result) ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("hardshrink(case1)" * doctest::test_suite("functional::hardshrink"))
{
    NMTOOLS_TESTING_DECLARE_NS(activations,hardshrink,case1);
    using namespace args;

    ACTIVATIONS_SUBCASE( "case1", fn::hardshrink, a );
    ACTIVATIONS_SUBCASE( "case1", fn::hardshrink, a_a );
    ACTIVATIONS_SUBCASE( "case1", fn::hardshrink, a_f );
    ACTIVATIONS_SUBCASE( "case1", fn::hardshrink, a_h );
    ACTIVATIONS_SUBCASE( "case1", fn::hardshrink, a_d );
}

TEST_CASE("hardshrink(case2)" * doctest::test_suite("functional::hardshrink"))
{
    NMTOOLS_TESTING_DECLARE_NS(activations,hardshrink,case2);
    using namespace args;

    ACTIVATIONS_SUBCASE( "case2", fn::hardshrink[lambda], a );
    ACTIVATIONS_SUBCASE( "case2", fn::hardshrink[lambda], a_a );
    ACTIVATIONS_SUBCASE( "case2", fn::hardshrink[lambda], a_f );
    ACTIVATIONS_SUBCASE( "case2", fn::hardshrink[lambda], a_h );
    ACTIVATIONS_SUBCASE( "case2", fn::hardshrink[lambda], a_d );
}