#include "nmtools/array/functional/ufuncs/log1p.hpp"
#include "nmtools/testing/data/array/log1p.hpp"
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

TEST_CASE("log1p(case1)" * doctest::test_suite("functional::log1p"))
{
    NMTOOLS_TESTING_DECLARE_NS(view, log1p, case1);
    using namespace args;

    FUNCTIONAL_SUBCASE( "case1", fn::log1p, a );
    FUNCTIONAL_SUBCASE( "case1", fn::log1p, a_a );
    FUNCTIONAL_SUBCASE( "case1", fn::log1p, a_f );
    FUNCTIONAL_SUBCASE( "case1", fn::log1p, a_h );
    FUNCTIONAL_SUBCASE( "case1", fn::log1p, a_d );
}