#include "nmtools/array/functional/ufuncs/arctanh.hpp"
#include "nmtools/testing/data/array/arctanh.hpp"
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

TEST_CASE("arctanh(case1)" * doctest::test_suite("functional::arctanh"))
{
    NMTOOLS_TESTING_DECLARE_NS(view, arctanh, case1);
    using namespace args;

    FUNCTIONAL_SUBCASE( "case1", fn::arctanh, a );
    FUNCTIONAL_SUBCASE( "case1", fn::arctanh, a_a );
    FUNCTIONAL_SUBCASE( "case1", fn::arctanh, a_f );
    FUNCTIONAL_SUBCASE( "case1", fn::arctanh, a_h );
    FUNCTIONAL_SUBCASE( "case1", fn::arctanh, a_d );
}