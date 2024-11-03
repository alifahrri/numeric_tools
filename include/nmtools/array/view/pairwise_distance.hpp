#ifndef NMTOOLS_ARRAY_VIEW_PAIRWISE_DISTANCE_HPP
#define NMTOOLS_ARRAY_VIEW_PAIRWISE_DISTANCE_HPP

#include "nmtools/meta.hpp"
#include "nmtools/array/view/alias.hpp"
#include "nmtools/array/view/vector_norm.hpp"
#include "nmtools/array/view/ufuncs/subtract.hpp"
#include "nmtools/array/view/ufuncs/add.hpp"

namespace nmtools::view
{
    template <typename lhs_t, typename rhs_t, typename ord_t=meta::ct<2>, typename eps_t=float, typename keepdims_t=meta::false_type>
    constexpr auto pairwise_distance(const lhs_t& lhs, const rhs_t& rhs, ord_t ord=ord_t{}, eps_t eps=eps_t{1e-6}, keepdims_t keepdims=keepdims_t{})
    {
        auto aliased = view::aliased(lhs,rhs,eps);
        auto a_lhs = nmtools::get<0>(aliased);
        auto a_rhs = nmtools::get<1>(aliased);
        auto a_eps = nmtools::get<2>(aliased);
        
        auto d = view::add(
            view::subtract(a_lhs,a_rhs), a_eps
        );

        auto axis = meta::ct_v<-1>;

        return view::vector_norm(d
            , axis
            , keepdims
            , ord
        );
    } // pairwise_distance
} // nmtools::view

#endif // NMTOOLS_ARRAY_VIEW_PAIRWISE_DISTANCE_HPP