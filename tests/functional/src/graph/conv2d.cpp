#include "nmtools/array/array/arange.hpp"
#include "nmtools/array/array/reshape.hpp"
#include "nmtools/array/array/random.hpp"
#include "nmtools/array/view/conv2d.hpp"
#include "nmtools/array/functional/functor.hpp"
#include "nmtools/array/functional/conv2d.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace na = nmtools::array;
namespace ix = nmtools::index;
namespace fn = nmtools::functional;
namespace meta = nmtools::meta;
namespace view = nmtools::view;
namespace utils = nmtools::utils;

using namespace nmtools::literals;
using nmtools::unwrap, nmtools::None;

TEST_CASE("conv2d" * doctest::test_suite("functional::get_compute_graph"))
{
    auto input_shape  = nmtools_array{1,1,4,4};
    auto weight_shape = nmtools_array{1,1,3,3};

    auto input  = na::reshape(na::arange(ix::product(input_shape)),input_shape);
    auto weight = na::reshape(na::arange(ix::product(weight_shape)),weight_shape);

    auto result = view::conv2dv2(unwrap(input),unwrap(weight));
    auto graph  = fn::get_compute_graph(unwrap(result));

    CHECK_MESSAGE( true, utils::to_string(graph,utils::Graphviz) );
}

TEST_CASE("conv2d" * doctest::test_suite("functional::get_compute_graph"))
{
    auto input_shape  = nmtools_array{1,1,5,5};
    auto weight_shape = nmtools_array{1,1,3,3};

    auto input  = na::reshape(na::arange(ix::product(input_shape)),input_shape);
    auto weight = na::reshape(na::arange(ix::product(weight_shape)),weight_shape);

    auto stride = nmtools_array{2,2};

    auto result = view::conv2dv2(unwrap(input),unwrap(weight),None,stride);
    auto graph  = fn::get_compute_graph(unwrap(result));

    CHECK_MESSAGE( true, utils::to_string(graph,utils::Graphviz) );
}

TEST_CASE("conv2d" * doctest::test_suite("functional::get_compute_graph"))
{
    auto input_shape  = nmtools_array{1,1,5,5};
    auto weight_shape = nmtools_array{2,1,3,3};

    auto input  = na::reshape(na::arange(ix::product(input_shape)),input_shape);
    auto weight = na::reshape(na::arange(ix::product(weight_shape)),weight_shape);

    auto stride = nmtools_array{2,2};

    auto result = view::conv2dv2(unwrap(input),unwrap(weight),None,stride);
    auto graph  = fn::get_compute_graph(unwrap(result));

    CHECK_MESSAGE( true, utils::to_string(graph,utils::Graphviz) );
}

TEST_CASE("conv2d" * doctest::test_suite("functional::get_compute_graph"))
{
    auto input_shape  = nmtools_array{1,4,5,5};
    auto weight_shape = nmtools_array{2,4,3,3};

    auto input  = na::reshape(na::arange(ix::product(input_shape)),input_shape);
    auto weight = na::reshape(na::arange(ix::product(weight_shape)),weight_shape);

    auto stride = nmtools_array{2,2};

    auto result = view::conv2dv2(unwrap(input),unwrap(weight),None,stride);
    auto graph  = fn::get_compute_graph(unwrap(result));

    CHECK_MESSAGE( true, utils::to_string(graph,utils::Graphviz) );
}

#if 0
TEST_CASE("conv2d" * doctest::test_suite("functional::get_compute_graph"))
{
    auto input_shape  = nmtools_array{6,4,5,5};
    auto weight_shape = nmtools_array{2,4,3,3};

    auto input  = na::reshape(na::arange(ix::product(input_shape)),input_shape);
    auto weight = na::reshape(na::arange(ix::product(weight_shape)),weight_shape);

    auto stride = nmtools_array{2,2};

    auto result = view::conv2dv2(unwrap(input),unwrap(weight),None,stride);
    auto graph  = fn::get_compute_graph(unwrap(result));

    CHECK_MESSAGE( true, utils::to_string(graph,utils::Graphviz) );
}
#endif

#if 0
TEST_CASE("conv2d" * doctest::test_suite("functional::get_compute_graph"))
{
    auto input_shape  = nmtools_array{1,3,5,5};
    auto weight_shape = nmtools_array{2,3,3,3};

    auto input  = na::reshape(na::arange(ix::product(input_shape)),input_shape);
    auto weight = na::reshape(na::arange(ix::product(weight_shape)),weight_shape);

    auto stride  = nmtools_array{2,2};
    auto padding = nmtools_array{1,1};

    auto result = view::conv2dv2(unwrap(input),unwrap(weight),None,stride,padding);
    auto graph  = fn::get_compute_graph(unwrap(result));

    CHECK_MESSAGE( true, utils::to_string(graph,utils::Graphviz) );
}
#endif