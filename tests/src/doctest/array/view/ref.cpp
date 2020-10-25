// @note need to includ array impl first to make sure overaload/specialization is visible
#include "nmtools/array/fixed.hpp"
#include "nmtools/array/dynamic.hpp"
#include "nmtools/array/view.hpp"
#include "nmtools/utility/helper.hpp"
#include "testing/testing.hpp"

#include "doctest/doctest.h"

#include <array>
#include <vector>

namespace view = nmtools::view;
using nmtools::helper::isclose;
using nmtools::array::fixed_vector;
using nmtools::array::fixed_matrix;
using nmtools::array::fixed_ndarray;
using nmtools::array::dynamic_vector;
using nmtools::array::dynamic_matrix;
using nmtools::array::dynamic_ndarray;

TEST_CASE("view::ref") // ref with 1D std::array
{
    auto array = std::array{1.,2.,3.};
    auto array_ref = view::ref(array);

    CHECK( array_ref.dim()==1 );
    // @todo provide isequal for integer type and use isequal instead of isclose
    CHECK( isclose(array_ref.shape(),std::array{3}) );
    CHECK( array_ref(0)==1 );

    // @note should be compile-error: assignment of read-only location
    // array_ref(0) = 3; 

    array[0] = 3;
    CHECK( array_ref(0)==3 );
    CHECK( nmtools::at(array_ref,0)==3 );

    {
        // view should have fixed_array_shape if its underlying array have too
        constexpr auto shape = nmtools::fixed_array_shape_v<decltype(array_ref)>;
        STATIC_CHECK(( std::get<0>(shape)==3 ));
        STATIC_CHECK(( nmtools::traits::is_array1d_v<decltype(array_ref)> ));
    }
}

TEST_CASE("view::ref") // make_view<ref_t>
{
    using view::ref_t;
    auto array = std::array{1.,2.,3.};
    auto array_ref = view::make_view<ref_t>(array);
    CHECK( array_ref.dim()==1 );
    // @todo provide isequal for integer type and use isequal instead of isclose
    CHECK( isclose(array_ref.shape(),std::array{3}) );
    CHECK( array_ref(0)==1 );

    array[0] = 3;
    CHECK( array_ref(0)==3 );
    CHECK( nmtools::at(array_ref,0)==3 );

    {
        // view::decorator_t should have fixed_array_shape if its underlying view have too
        constexpr auto shape = nmtools::fixed_array_shape_v<decltype(array_ref)>;
        STATIC_CHECK(( std::get<0>(shape)==3 ));
        STATIC_CHECK(( nmtools::traits::is_array1d_v<decltype(array_ref)> ));
        STATIC_CHECK(( std::is_same_v<double,nmtools::meta::get_vector_value_type_t<decltype(array_ref)>> ));
        STATIC_CHECK(( std::is_same_v<double,nmtools::meta::get_element_type_t<decltype(array_ref)>> ));
    }
}

TEST_CASE("view::ref") // ref with 2D std::array
{
    auto array = std::array{
        std::array{1.,2.,3.},
        std::array{3.,4.,5.},
    };
    auto array_ref = view::ref(array);
    CHECK(array_ref.dim()==2);
    // @note that isclose can also handle comparison between pair/tuple with array
    CHECK( isclose(array_ref.shape(),std::array{2,3}) );

    CHECK( array_ref(0,1)==2 );
    CHECK( array_ref(1,0)==3 );

    nmtools::at(array,0,1) = 6;
    nmtools::at(array,1,0) = 7;
    
    CHECK( array_ref(0,1)==6 );
    CHECK( array_ref(1,0)==7 );

    {
        STATIC_CHECK(( nmtools::traits::is_array2d_v<decltype(array_ref)> ));
        STATIC_CHECK(( std::is_same_v<double,nmtools::meta::get_matrix_value_type_t<decltype(array_ref)>> ));
        STATIC_CHECK(( std::is_same_v<double,nmtools::meta::get_element_type_t<decltype(array_ref)>> ));
    }
}

TEST_CASE("view::ref") // ref with 1D std::vector
{
    auto array = std::vector{1.,2.,3.};
    auto array_ref = view::ref(array);
    CHECK( array_ref.dim()==1 );
    CHECK( isclose(array_ref.shape(),std::array{3}) );
    CHECK( array_ref(0)==1 );
    array[0] = 3;
    CHECK( array_ref(0)==3 );
    CHECK( nmtools::at(array_ref,0)==3 );

    {
        STATIC_CHECK(( nmtools::traits::is_array1d_v<decltype(array_ref)> ));
        STATIC_CHECK(( std::is_same_v<double,nmtools::meta::get_vector_value_type_t<decltype(array_ref)>> ));
        STATIC_CHECK(( std::is_same_v<double,nmtools::meta::get_element_type_t<decltype(array_ref)>> ));
    }
}

TEST_CASE("view::ref") // ref with 2D std::vector
{
    auto array = std::vector{
        std::vector{1.,2.,3.},
        std::vector{3.,4.,5.},
    };
    auto array_ref = view::ref(array);

    CHECK( array_ref.dim()==2 );
    CHECK( isclose(array_ref.shape(),std::array{2,3}) );

    CHECK( array_ref(0,1)==2 );
    CHECK( array_ref(1,0)==3 );

    nmtools::at(array,0,1) = 6;
    nmtools::at(array,1,0) = 7;
    
    CHECK( array_ref(0,1)==6 );
    CHECK( array_ref(1,0)==7 );

    {
        STATIC_CHECK(( nmtools::traits::is_array2d_v<decltype(array_ref)> ));
        STATIC_CHECK(( std::is_same_v<double,nmtools::meta::get_matrix_value_type_t<decltype(array_ref)>> ));
        STATIC_CHECK(( std::is_same_v<double,nmtools::meta::get_element_type_t<decltype(array_ref)>> ));
    }
}

TEST_CASE("view::ref") // ref with fixed_vector
{
    auto array = fixed_vector<double,3>{1.,2.,3.};
    auto array_ref = view::ref(array);

    CHECK( array_ref.dim()==1 );
    CHECK( isclose(array_ref.shape(),std::array{3}) );

    CHECK( array_ref(0)==1 );
    CHECK( nmtools::at(array_ref,0)==1 );

    nmtools::at(array,0) = 3;

    CHECK( array_ref(0)==3 );
    CHECK( nmtools::at(array_ref,0)==3 );

    {
        STATIC_CHECK(( nmtools::traits::is_array1d_v<decltype(array_ref)> ));
        STATIC_CHECK(( std::is_same_v<double,nmtools::meta::get_vector_value_type_t<decltype(array_ref)>> ));
        STATIC_CHECK(( std::is_same_v<double,nmtools::meta::get_element_type_t<decltype(array_ref)>> ));
    }
}

TEST_CASE("view::ref") // ref with fixed_matrix
{
    auto array = fixed_matrix<double,3,2>{};
    auto array_ref = view::ref(array);

    CHECK( array_ref.dim()==2 );
    CHECK( isclose(array_ref.shape(), std::array{3,2}) );

    {
        STATIC_CHECK(( nmtools::traits::is_array2d_v<decltype(array_ref)> ));
        STATIC_CHECK(( std::is_same_v<double,nmtools::meta::get_matrix_value_type_t<decltype(array_ref)>> ));
        STATIC_CHECK(( std::is_same_v<double,nmtools::meta::get_element_type_t<decltype(array_ref)>> ));
    }
}

TEST_CASE("view::ref") // ref with dynamic_vector
{
    auto array = dynamic_vector{1.,2.,3.};
    auto array_ref = view::ref(array);

    CHECK( array_ref.dim()==1 );
    CHECK( isclose(array_ref.shape(),std::array{3}) );
    CHECK( nmtools::at(array_ref,0)==1 );

    nmtools::at(array,0) = 3;
    CHECK( array_ref(0)==3 );
    CHECK( nmtools::at(array_ref,0)==3 );

    {
        STATIC_CHECK(( nmtools::traits::is_array1d_v<decltype(array_ref)> ));
        STATIC_CHECK(( std::is_same_v<double,nmtools::meta::get_vector_value_type_t<decltype(array_ref)>> ));
        STATIC_CHECK(( std::is_same_v<double,nmtools::meta::get_element_type_t<decltype(array_ref)>> ));
    }
}

TEST_CASE("view::ref") // ref with dynamic_matrix
{
    auto array = dynamic_matrix{
        {1.,2.,3.},
        {3.,4.,5.},
    };
    auto array_ref = view::ref(array);

    CHECK( array_ref.dim()==2 );
    CHECK( isclose(array_ref.shape(), std::array{2,3}) );

    {
        STATIC_CHECK(( nmtools::traits::is_array2d_v<decltype(array_ref)> ));
        STATIC_CHECK(( std::is_same_v<double,nmtools::meta::get_matrix_value_type_t<decltype(array_ref)>> ));
        STATIC_CHECK(( std::is_same_v<double,nmtools::meta::get_element_type_t<decltype(array_ref)>> ));
    }
}

TEST_CASE("view::ref") // ref with 1D fixed_ndarray
{
    auto array = fixed_ndarray<double,3>{1.,2.,3.};
    auto array_ref = view::ref(array);
    CHECK( array_ref.dim()==1 );
    CHECK( isclose(array_ref.shape(),std::array{3}) );

    array = std::array{1.,2.,3.};

    {
        STATIC_CHECK(( nmtools::traits::is_ndarray_v<decltype(array_ref)> ));
        STATIC_CHECK(( std::is_same_v<double,nmtools::meta::get_ndarray_value_type_t<decltype(array_ref)>> ));
        STATIC_CHECK(( std::is_same_v<double,nmtools::meta::get_element_type_t<decltype(array_ref)>> ));
    }
}

TEST_CASE("view::ref") // ref with 2D fixed_ndarray
{
    auto array = fixed_ndarray<double,3,2>{};
    auto array_ref = view::ref(array);

    array = std::array{
        std::array{1.,2.},
        std::array{3.,4.},
        std::array{4.,5.},
    };

    CHECK( array_ref.dim()==2 );
    CHECK( isclose(array_ref.shape(),std::array{3,2}) );

    CHECK( array_ref(0,1)==2 );
    CHECK( array_ref(1,0)==3 );

    nmtools::at(array,0,1) = 6;
    nmtools::at(array,1,0) = 7;
    
    CHECK( array_ref(0,1)==6 );
    CHECK( array_ref(1,0)==7 );

    {
        STATIC_CHECK(( nmtools::traits::is_ndarray_v<decltype(array_ref)> ));
        STATIC_CHECK(( std::is_same_v<double,nmtools::meta::get_ndarray_value_type_t<decltype(array_ref)>> ));
        STATIC_CHECK(( std::is_same_v<double,nmtools::meta::get_element_type_t<decltype(array_ref)>> ));
    }
}

TEST_CASE("view::ref") // ref with 3D fixed_ndarray
{
    auto array = fixed_ndarray<double,3,2,4>{};
    auto array_ref = view::ref(array);
    CHECK( array_ref.dim()==3 );
    CHECK( isclose(array_ref.shape(),std::array{3,2,4}) );

    // @todo provide constructor/assignment op from 3D array

    nmtools::at(array,0,1,0) = 6;
    CHECK( array_ref(0,1,0)==6 );

    {
        STATIC_CHECK(( nmtools::traits::is_ndarray_v<decltype(array_ref)> ));
        STATIC_CHECK(( std::is_same_v<double,nmtools::meta::get_ndarray_value_type_t<decltype(array_ref)>> ));
        STATIC_CHECK(( std::is_same_v<double,nmtools::meta::get_element_type_t<decltype(array_ref)>> ));
    }
}

TEST_CASE("view::ref") // // ref with 4D fixed_ndarray
{
    auto array = fixed_ndarray<double,3,2,4,1>{};
    auto array_ref = view::ref(array);
    CHECK( array_ref.dim()==4 );
    CHECK( isclose(array_ref.shape(),std::array{3,2,4,1}) );

    // @todo provide constructor/assignment op from 4D array

    nmtools::at(array,0,1,3,0) = 6;
    CHECK( array_ref(0,1,3,0)==6 );
}

TEST_CASE("view::ref") // ref with 1D dynamic_ndarray
{
    auto array = dynamic_ndarray({1.,2.,3.});
    auto array_ref = view::ref(array);
    CHECK( array_ref.dim()==1 );
    CHECK( isclose(array_ref.shape(),std::array{3}) );
}

TEST_CASE("view::ref") // ref with 1D dynamic_ndarray
{
    auto array = dynamic_ndarray({
        {1.,2.,3.},
        {3.,4.,5.}
    });
    auto array_ref = view::ref(array);
    CHECK( array_ref.dim()==2 );
    CHECK( isclose(array_ref.shape(),std::array{2,3}) );
}

TEST_CASE("view::ref") // ref with 3D dynamic_ndarray
{
    // @note initialize 3D ndarray from flat storage with specified shape
    auto array = dynamic_ndarray({1.,2.,3.},{1,3,1});
    auto array_ref = view::ref(array);
    CHECK( array_ref.dim()==3 );
    CHECK( isclose(array_ref.shape(),std::array{1,3,1}) );

    // @todo provide constructor/assignment op from 3D array
}

TEST_CASE("view::ref") // ref with 4D dynamic_ndarray
{
    // @note initialize 3D ndarray from flat storage with specified shape
    auto array = dynamic_ndarray({1.,2.,3.,4.},{1,2,2,1});
    auto array_ref = view::ref(array);
    CHECK( array_ref.dim()==4 );
    CHECK( isclose(array_ref.shape(),std::array{1,2,2,1}) );

    // @todo provide constructor/assignment op from 3D array

    CHECK( array_ref(0,1,1,0)==4 );
    nmtools::at(array,0,1,1,0) = 6;
    CHECK( array_ref(0,1,1,0)==6 );
}