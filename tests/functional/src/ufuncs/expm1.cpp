#include "nmtools/array/functional/ufuncs/expm1.hpp"
#include "nmtools/testing/data/array/expm1.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace fn = nm::functional;

#define FUNCTIONAL_SUBCASE(subcase_name, function, ...) \
SUBCASE(subcase_name) \
{ \
    auto result = function (__VA_ARGS__); \
    NMTOOLS_REQUIRE_EQUAL( nm::shape(result), nm::shape(expect::result) ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("expm1(case1)" * doctest::test_suite("functional::expm1"))
{
    NMTOOLS_TESTING_DECLARE_NS(view, expm1, case1);
    using namespace args;

    FUNCTIONAL_SUBCASE( "case1", fn::expm1, a );
    FUNCTIONAL_SUBCASE( "case1", fn::expm1, a_a );
    FUNCTIONAL_SUBCASE( "case1", fn::expm1, a_f );
    FUNCTIONAL_SUBCASE( "case1", fn::expm1, a_h );
    FUNCTIONAL_SUBCASE( "case1", fn::expm1, a_d );
}