/**
 * @file index.cpp
 * @author your name (you@domain.com)
 * @brief test file for indices_pack
 * @version 0.1
 * @date 2020-11-11
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#include "nmtools/array/detail.hpp"
#include "nmtools/utils/isequal.hpp"
#include "testing/doctest.hpp"
#include <array>
#include <tuple>

namespace nm = nmtools;
using nmtools::utils::isequal;
using std::tuple;

TEST_CASE("indices_pack({3,2})" * doctest::test_suite("index"))
{
    auto indices = nm::indices_pack(tuple{3,2});
    REQUIRE( indices.size() == 6 );
    {
        auto i = indices[0];
        CHECK(( isequal(i,tuple{0,0}) ));
    }
    {
        auto i = indices[1];
        CHECK(( isequal(i,tuple{0,1}) ));
    }
    {
        auto i = indices[2];
        CHECK(( isequal(i,tuple{1,0}) ));
    }
    {
        auto i = indices[3];
        CHECK(( isequal(i,tuple{1,1}) ));
    }
    {
        auto i = indices[4];
        CHECK(( isequal(i,tuple{2,0}) ));
    }
    {
        auto i = indices[5];
        CHECK(( isequal(i,tuple{2,1}) ));
    }
}

TEST_CASE("indices_pack({3,2,3})" * doctest::test_suite("index"))
{
    auto indices = nm::indices_pack(tuple{3,2,3});
    REQUIRE( indices.size() == 18 );
    {
        auto i = indices[0];
        CHECK(( isequal(i,tuple{0,0,0}) ));
    }
    {
        auto i = indices[1];
        CHECK(( isequal(i,tuple{0,0,1}) ));
    }
    {
        auto i = indices[2];
        CHECK(( isequal(i,tuple{0,0,2}) ));
    }
    {
        auto i = indices[3];
        CHECK(( isequal(i,tuple{0,1,0}) ));
    }
    {
        auto i = indices[4];
        CHECK(( isequal(i,tuple{0,1,1}) ));
    }
    {
        auto i = indices[5];
        CHECK(( isequal(i,tuple{0,1,2}) ));
    }
    {
        auto i = indices[6];
        CHECK(( isequal(i,tuple{1,0,0}) ));
    }
    {
        auto i = indices[7];
        CHECK(( isequal(i,tuple{1,0,1}) ));
    }
    {
        auto i = indices[8];
        CHECK(( isequal(i,tuple{1,0,2}) ));
    }
    {
        auto i = indices[9];
        CHECK(( isequal(i,tuple{1,1,0}) ));
    }
    {
        auto i = indices[10];
        CHECK(( isequal(i,tuple{1,1,1}) ));
    }
    {
        auto i = indices[11];
        CHECK(( isequal(i,tuple{1,1,2}) ));
    }
    {
        auto i = indices[12];
        CHECK(( isequal(i,tuple{2,0,0}) ));
    }
    {
        auto i = indices[13];
        CHECK(( isequal(i,tuple{2,0,1}) ));
    }
    {
        auto i = indices[14];
        CHECK(( isequal(i,tuple{2,0,2}) ));
    }
    {
        auto i = indices[15];
        CHECK(( isequal(i,tuple{2,1,0}) ));
    }
    {
        auto i = indices[16];
        CHECK(( isequal(i,tuple{2,1,1}) ));
    }
    {
        auto i = indices[17];
        CHECK(( isequal(i,tuple{2,1,2}) ));
    }
}

TEST_CASE("indices_pack({3,2,3,1})" * doctest::test_suite("index"))
{
    auto indices = nm::indices_pack(tuple{3,2,3,1});
    REQUIRE( indices.size() == 18 );
    {
        auto i = indices[0];
        CHECK(( isequal(i,tuple{0,0,0,0}) ));
    }
    {
        auto i = indices[1];
        CHECK(( isequal(i,tuple{0,0,1,0}) ));
    }
    {
        auto i = indices[2];
        CHECK(( isequal(i,tuple{0,0,2,0}) ));
    }
    {
        auto i = indices[3];
        CHECK(( isequal(i,tuple{0,1,0,0}) ));
    }
    {
        auto i = indices[4];
        CHECK(( isequal(i,tuple{0,1,1,0}) ));
    }
    {
        auto i = indices[5];
        CHECK(( isequal(i,tuple{0,1,2,0}) ));
    }
    {
        auto i = indices[6];
        CHECK(( isequal(i,tuple{1,0,0,0}) ));
    }
    {
        auto i = indices[7];
        CHECK(( isequal(i,tuple{1,0,1,0}) ));
    }
    {
        auto i = indices[8];
        CHECK(( isequal(i,tuple{1,0,2,0}) ));
    }
    {
        auto i = indices[9];
        CHECK(( isequal(i,tuple{1,1,0,0}) ));
    }
    {
        auto i = indices[10];
        CHECK(( isequal(i,tuple{1,1,1,0}) ));
    }
    {
        auto i = indices[11];
        CHECK(( isequal(i,tuple{1,1,2,0}) ));
    }
    {
        auto i = indices[12];
        CHECK(( isequal(i,tuple{2,0,0,0}) ));
    }
    {
        auto i = indices[13];
        CHECK(( isequal(i,tuple{2,0,1,0}) ));
    }
    {
        auto i = indices[14];
        CHECK(( isequal(i,tuple{2,0,2,0}) ));
    }
    {
        auto i = indices[15];
        CHECK(( isequal(i,tuple{2,1,0,0}) ));
    }
    {
        auto i = indices[16];
        CHECK(( isequal(i,tuple{2,1,1,0}) ));
    }
    {
        auto i = indices[17];
        CHECK(( isequal(i,tuple{2,1,2,0}) ));
    }
}

TEST_CASE("indices_pack({3,2,3,1})" * doctest::test_suite("index"))
{
    auto indices = nm::indices_pack(tuple{2,3,1,3,1});
    REQUIRE( indices.size() == 18 );
    {
        auto i = indices[0];
        CHECK(( isequal(i,tuple{0,0,0,0,0}) ));
    }
    {
        auto i = indices[1];
        CHECK(( isequal(i,tuple{0,0,0,1,0}) ));
    }
    {
        auto i = indices[2];
        CHECK(( isequal(i,tuple{0,0,0,2,0}) ));
    }
    {
        auto i = indices[3];
        CHECK(( isequal(i,tuple{0,1,0,0,0}) ));
    }
    {
        auto i = indices[4];
        CHECK(( isequal(i,tuple{0,1,0,1,0}) ));
    }
    {
        auto i = indices[5];
        CHECK(( isequal(i,tuple{0,1,0,2,0}) ));
    }
    {
        auto i = indices[6];
        CHECK(( isequal(i,tuple{0,2,0,0,0}) ));
    }
    {
        auto i = indices[7];
        CHECK(( isequal(i,tuple{0,2,0,1,0}) ));
    }
    {
        auto i = indices[8];
        CHECK(( isequal(i,tuple{0,2,0,2,0}) ));
    }
    {
        auto i = indices[9];
        CHECK(( isequal(i,tuple{1,0,0,0,0}) ));
    }
    {
        auto i = indices[10];
        CHECK(( isequal(i,tuple{1,0,0,1,0}) ));
    }
    {
        auto i = indices[11];
        CHECK(( isequal(i,tuple{1,0,0,2,0}) ));
    }
    {
        auto i = indices[12];
        CHECK(( isequal(i,tuple{1,1,0,0,0}) ));
    }
    {
        auto i = indices[13];
        CHECK(( isequal(i,tuple{1,1,0,1,0}) ));
    }
    {
        auto i = indices[14];
        CHECK(( isequal(i,tuple{1,1,0,2,0}) ));
    }
    {
        auto i = indices[15];
        CHECK(( isequal(i,tuple{1,2,0,0,0}) ));
    }
    {
        auto i = indices[16];
        CHECK(( isequal(i,tuple{1,2,0,1,0}) ));
    }
    {
        auto i = indices[17];
        CHECK(( isequal(i,tuple{1,2,0,2,0}) ));
    }
}