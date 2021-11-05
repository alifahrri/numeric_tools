#ifndef NMTOOLS_ARRAY_INDEX_SCATTER_HPP
#define NMTOOLS_ARRAY_INDEX_SCATTER_HPP

#include "nmtools/array/meta.hpp"
#include "nmtools/traits.hpp"
#include "nmtools/meta.hpp"

#include "nmtools/array/utility/at.hpp"
#include "nmtools/array/index/tuple_at.hpp"
#include "nmtools/array/shape.hpp"

#include "nmtools/assert.hpp"

#include <array>
#include <tuple>
#include <type_traits>

namespace nmtools::index
{
    // tag to resolve scatter return type
    struct scatter_t {};

    // TODO: cleanup index functions
    /**
     * @brief perform scatter op
     * 
     * perform `ret[idx[i]] = vec[i]` aka reverse of gather
     *
     * @tparam vector_t type of vec
     * @tparam indices_t type of indices
     * @param vec 
     * @param indices 
     * @return constexpr auto 
     * @see gather
     */
    template <typename vector_t, typename indices_t>
    constexpr auto scatter(const vector_t& vec, const indices_t& indices)
    {
        using result_t = meta::resolve_optype_t<scatter_t,vector_t,indices_t>;

        auto ret = result_t{};

        if constexpr (!meta::is_constant_index_array_v<result_t>) {
            // get the size of vec, add namespace to avoid ambiguous call
            auto n = len(vec);
            // get the size of indices
            auto m = len(indices);
            // TODO: support optional
            // TODO: static assert whenever possible
            nmtools_cassert ((size_t)n == (size_t)m
                , "unsupported scatter, mismatched dimension between vec and indices"
            );

            if constexpr (meta::is_resizeable_v<result_t>)
                ret.resize(len(vec)); // assuming indices has size

            auto scatter_impl = [&](auto& ret, const auto& vec, const auto& indices, auto i){
                auto value  = at(vec,i);
                auto idx    = at(indices,i);
                at(ret,idx) = value;
            }; // scatter_impl

            // handle tuple if it has common_type
            if constexpr (meta::is_fixed_index_array_v<vector_t>)
                meta::template_for<meta::len_v<vector_t>>([&](auto i){
                    scatter_impl(ret, vec, indices, i);
                });
            else
                for (size_t i=0; i<m; i++)
                    scatter_impl(ret, vec, indices, i);
        }

        return ret;
    } // scatter
} // namespace nmtools

namespace nmtools::meta
{
    namespace error
    {
        struct INDEX_SCATTER_UNSUPPORTED : detail::fail_t {};
    }

    template <typename vector_t, typename indices_t>
    struct resolve_optype<
        void, index::scatter_t, vector_t, indices_t
    >
    {
        static constexpr auto vtype = [](){
            if constexpr (is_constant_index_array_v<vector_t> && is_constant_index_array_v<indices_t>) {
                constexpr auto vec = to_value_v<vector_t>;
                constexpr auto ind = to_value_v<indices_t>;
                constexpr auto res = index::scatter(vec, ind);
                // convert back to type
                using init_type = make_tuple_type_t<ct<at(res,0)>>;
                return template_reduce<::nmtools::len(res)-1>([&](auto init, auto index){
                    using init_t = type_t<decltype(init)>;
                    using result_t = append_type_t<init_t,ct<at(res,index+1)>>;
                    return as_value_v<result_t>;
                }, as_value_v<init_type>);
            } else if constexpr (is_index_array_v<vector_t> && is_index_array_v<indices_t>) {
                // some fn still allow tuple of (runtime) index
                using type = tuple_to_array_t<transform_bounded_array_t<vector_t>>;
                return as_value_v<type>;
            } else {
                return as_value_v<error::INDEX_SCATTER_UNSUPPORTED>;
            }
        }();
        using type = type_t<decltype(vtype)>;
    };
} // namespace nmtools::meta

#endif // NMTOOLS_ARRAY_INDEX_SCATTER_HPP