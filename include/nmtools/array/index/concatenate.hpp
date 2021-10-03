#ifndef NMTOOLS_ARRAY_INDEX_CONCATENATE_HPP
#define NMTOOLS_ARRAY_INDEX_CONCATENATE_HPP

#include "nmtools/constants.hpp"
#include "nmtools/meta.hpp"
#include "nmtools/array/utility/at.hpp"
#include "nmtools/array/index/tuple_at.hpp"
#include "nmtools/array/index/product.hpp"
#include "nmtools/array/index/compute_indices.hpp"
#include "nmtools/array/shape.hpp"

#include <tuple>

namespace nmtools::index
{
    /**
     * @brief specific tag to resolve return type for index::concatenate
     * 
     */
    struct concatenate_t {};

    /**
     * @brief transform indices from concat dst indices to concat src indices
     * 
     * @tparam ashape_t 
     * @tparam bshape_t 
     * @tparam indices_t 
     * @tparam axis_t 
     * @param ashape shape of orignal lhs array
     * @param bshape shape of orignal rhs array
     * @param indices indices of dst (concatenated) array
     * @param axis The axis along which the arrays joined. If axis is None, arrays are flattened before use.
     * @return constexpr auto 
     */
    template <typename ashape_t, typename bshape_t, typename indices_t, typename axis_t>
    constexpr auto concatenate(const ashape_t& ashape, const bshape_t& bshape, const indices_t& indices, [[maybe_unused]] axis_t axis)
    {
        // TODO: allow negative axis
        using a_indices_t = meta::resolve_optype_t<concatenate_t,ashape_t,indices_t,axis_t>;
        using b_indices_t = meta::resolve_optype_t<concatenate_t,bshape_t,indices_t,axis_t>;

        auto a_indices = a_indices_t {};
        auto b_indices = b_indices_t {};

        bool aflag = false;
        bool bflag = false;

        [[maybe_unused]] auto ad = len(ashape);
        [[maybe_unused]] auto bd = len(bshape);

        if constexpr (meta::is_resizeable_v<a_indices_t>)
            a_indices.resize(ad);
        if constexpr (meta::is_resizeable_v<b_indices_t>)
            b_indices.resize(bd);

        // assume len(indices) == len(ashape) == len(bshape)
        // then we can select which indices to be selected from indices[axis]
        // note that ashape should be lhs shape and rhs shape and lhs array corresponds to lower indices,
        // then if indices[axis] < ahape[axis] select a otherwise select b

        // TODO: do not use tuple_at, specialize constant index/shape instead
    
        if constexpr (is_none_v<axis_t>) {
            auto na = product(ashape);
            auto nb = product(bshape);
            // TODO: error handling if len(indices) != 1
            // TODO: do not use tuple_at
            auto i = tuple_at(indices,0);
            if (i<na) {
                aflag = true;
                a_indices = compute_indices(i,ashape);
            }
            else if (i<(na+nb)) {
                bflag = true;
                b_indices = compute_indices(i-na,bshape);
            }
            // not valid
        }
        else {
            // TODO: do not use tuple_at
            auto aa = tuple_at(ashape,axis);
            auto ba = tuple_at(bshape,axis);
            auto ia = tuple_at(indices,axis);
            // todo error handling for other axis
            if (ia<aa) {
                aflag = true;
                // select ashape, no need to offset
                for (size_t i=0; i<ad; i++)
                    at(a_indices,i) = tuple_at(indices,i);
            }
            // also take account for offset
            else if (ia<(ba+aa)) {
                using idx_t = meta::promote_index_t<size_t,axis_t>;
                bflag = true;
                // select ashape, must apply offset from ashape
                for (size_t i=0; i<bd; i++) {
                    // TODO: do not use tuple_at
                    if (static_cast<idx_t>(i)==static_cast<idx_t>(axis))
                        at(b_indices,i) = tuple_at(indices,i) - aa;
                    else at(b_indices,i) = tuple_at(indices,i);
                }
            }
            // not valid
        }

        // TODO: use optional instead
        return std::tuple{aflag,bflag,a_indices,b_indices};
    } // concatenate
} // namespace nmtools::index

namespace nmtools::meta
{
    namespace error
    {
        struct INDEX_CONCATENATE_UNSUPPORTED : detail::fail_t {};
    } // namespace error
    
    /**
     * @brief resolve return type for index::concatenate
     * 
     * @tparam shape_t 
     * @tparam indices_t 
     * @tparam axis_t 
     */
    template <typename shape_t, typename indices_t, typename axis_t>
    struct resolve_optype<
        void, index::concatenate_t, shape_t, indices_t, axis_t
    >
    {
        static constexpr auto vtype = [](){
            if constexpr (is_fixed_index_array_v<shape_t>) {
                // tuple<int,..> is also belong to this category
                constexpr auto N = fixed_index_array_size_v<shape_t>;
                using elem_t = remove_cvref_t<get_element_or_common_type_t<shape_t>>;
                // TODO: create make_array_t metafunction
                return as_value_v<std::array<elem_t,N>>;
            } else if constexpr (is_index_array_v<shape_t>) {
                return as_value_v<shape_t>;
            } else {
                return as_value_v<error::INDEX_CONCATENATE_UNSUPPORTED>;
            }
        }();
        using type = type_t<decltype(vtype)>;
    }; // struct resolve_optype

} // namespace nmtools::meta

namespace nmtools::index
{
    /**
     * @brief specific tag to resolve return type of index::shape_concatenate
     * 
     */
    struct shape_concatenate_t {};

    /**
     * @brief compute the resulting shape of concatenate op
     * 
     * @tparam ashape_t 
     * @tparam bshape_t 
     * @tparam axis_t 
     * @param ashape lhs array
     * @param bshape rhs array
     * @param axis The axis along which the arrays will be joined. If axis is None, arrays are flattened before use.
     * @return constexpr auto 
     */
    template <typename ashape_t, typename bshape_t, typename axis_t>
    constexpr auto shape_concatenate(const ashape_t& ashape, const bshape_t& bshape, [[maybe_unused]] axis_t axis)
    {
        // TODO: allow negative axis
        using return_t = meta::resolve_optype_t<shape_concatenate_t,ashape_t,bshape_t,axis_t>;

        auto ret = return_t {};
        bool suc = true;

        [[maybe_unused]] auto ad = len(ashape);
        [[maybe_unused]] auto bd = len(bshape);

        if constexpr (meta::is_resizeable_v<return_t>)
            ret.resize(ad); // ad must be == bd

        if constexpr (is_none_v<axis_t>)
        {
            auto na = product(ashape);
            auto nb = product(bshape);
            at(ret,0) = na + nb;
        }
        else if (ad==bd) {
            using idx_t = meta::promote_index_t<size_t,axis_t>;
            // todo: maybe convert ashape & bshape to array first to simplify expression
            for (size_t i=0; i<(size_t)ad; i++) {
                // TODO: do not use tuple_at
                auto ai = tuple_at(ashape,i);
                auto bi = tuple_at(bshape,i);
                if (static_cast<idx_t>(i)==static_cast<idx_t>(axis))
                    at(ret,i) = ai + bi;
                // concat must have same shape except at axis idx
                else if (ai==bi)
                    at(ret,i) = ai;
                else {
                    suc = false;
                    break;
                }
            }
        }
        else suc = false;
        
        // TODO: use optional instead
        return std::tuple{suc,ret};
    } // shape_concatenate
} // namespace nmtools::index

namespace nmtools::meta
{
    namespace error
    {
        struct SHAPE_CONCATENATE_UNSUPPORTED : detail::fail_t {};
    } // namespace error
    
    /**
     * @brief resolve return type for index::shape_concatenate op
     * 
     * @tparam ashape_t 
     * @tparam bshape_t 
     * @tparam axis_t 
     */
    template <typename ashape_t, typename bshape_t, typename axis_t>
    struct resolve_optype<
        void, index::shape_concatenate_t, ashape_t, bshape_t, axis_t
    >
    {
        // @todo enforce same dim
        static constexpr auto vtype = [](){
            if constexpr (is_constant_index_array_v<ashape_t> && is_constant_index_array_v<bshape_t>) {
                return as_value_v<error::SHAPE_CONCATENATE_UNSUPPORTED>;
            } else if constexpr (is_dynamic_index_array_v<ashape_t>) {
                return as_value_v<ashape_t>;
            } else if constexpr (is_dynamic_index_array_v<bshape_t>) {
                return as_value_v<bshape_t>;
            } else if constexpr (is_hybrid_index_array_v<ashape_t>) {
                return as_value_v<ashape_t>;
            } else if constexpr (is_hybrid_index_array_v<bshape_t>) {
                return as_value_v<bshape_t>;
            } else if constexpr (is_fixed_index_array_v<ashape_t>) {
                return as_value_v<transform_bounded_array_t<ashape_t>>;
            } else if constexpr (is_fixed_index_array_v<bshape_t>) {
                return as_value_v<transform_bounded_array_t<bshape_t>>;
            } else {
                return as_value_v<error::SHAPE_CONCATENATE_UNSUPPORTED>;
            }
        }();
        using type = type_t<decltype(vtype)>;
    }; // resolve_optype

    template <typename ashape_t, typename bshape_t>
    struct resolve_optype <
        void, index::shape_concatenate_t, ashape_t, bshape_t, none_t
    >
    {
        // for shape_concatenate, when axis is none, the arrays are flattened before concatenated
        static constexpr auto vtype = [](){
            if constexpr (is_index_array_v<ashape_t> && is_index_array_v<bshape_t>)
                return as_value<std::array<size_t,1>>{};
            else return as_value<void>{};
        }();

        using type = type_t<decltype(vtype)>;
    }; // resolve_optype
} // namespace nmtools::meta

#endif // NMTOOLS_ARRAY_INDEX_CONCATENATE_HPP