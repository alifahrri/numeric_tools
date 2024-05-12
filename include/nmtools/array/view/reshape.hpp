#ifndef NMTOOLS_ARRAY_VIEW_RESHAPE_HPP
#define NMTOOLS_ARRAY_VIEW_RESHAPE_HPP

#include "nmtools/meta.hpp"

#include "nmtools/array/utility/at.hpp"
#include "nmtools/array/shape.hpp"
#include "nmtools/array/view/indexing.hpp"
#include "nmtools/array/as_static.hpp"

#include "nmtools/array/index/reshape.hpp"
#include "nmtools/array/index/compute_indices.hpp"
#include "nmtools/array/index/compute_offset.hpp"
#include "nmtools/array/index/compute_strides.hpp"

#include "nmtools/utils/isequal/isequal.hpp"
#include "nmtools/utils/to_string/to_string.hpp"
#include "nmtools/utility/unwrap.hpp"

namespace nmtools::view
{
    template <typename src_shape_t, typename dst_shape_t, typename src_size_t>
    struct reshape_t
        : base_indexer_t<reshape_t<src_shape_t,dst_shape_t,src_size_t>>
    {
        using src_shape_type = meta::fwd_attribute_t<decltype(unwrap(meta::declval<src_shape_t>()))>;
        using src_size_type  = meta::fwd_attribute_t<decltype(unwrap(meta::declval<src_size_t>()))>;

        // TODO: refactor index::shape_reshape so that the result can be easily deduced
        // using dst_shape_type = meta::resolve_optype_t<
        //     index::shape_reshape_t, src_shape_type, dst_shape_t
        // >;
        // avoid storing maybe type here since it is not constexpr-friendly (at least for maybe static_vector)
        using dst_shape_type   = decltype(unwrap(index::shape_reshape(meta::declval<src_shape_type>(),meta::declval<dst_shape_t>())));
        using dst_strides_type = meta::resolve_optype_t<unwrap_t,meta::resolve_optype_t<
            index::compute_strides_t, dst_shape_type
        >>;
        // reshape doesn't change the number of elements
        using dst_size_type = src_size_type;

        static constexpr auto n_inputs  = 1;
        static constexpr auto n_outputs = 1;

        const src_shape_type   src_shape;
        const dst_shape_type   dst_shape;
        const src_size_type    src_size;
        const dst_size_type    dst_size;
        const dst_strides_type dst_strides;

        constexpr reshape_t(const src_shape_t& src_shape_
            , const dst_shape_t& dst_shape_
            , src_size_t src_size_
        )
            : src_shape(fwd_attribute(unwrap(src_shape_)))
            , dst_shape(unwrap(index::shape_reshape(src_shape,dst_shape_)))
            , src_size(fwd_attribute(unwrap(src_size_)))
            , dst_size(fwd_attribute(unwrap(src_size_)))
            , dst_strides(unwrap(index::compute_strides(dst_shape)))
        {}

        template <typename indices_t>
        constexpr auto indices(const indices_t& indices) const
        {
            if constexpr (is_none_v<src_shape_type>) {
                return None;
            } else {
                auto dst_offset  = index::compute_offset(indices,unwrap(dst_strides));
                auto src_indices = index::compute_indices(dst_offset,src_shape);
                return unwrap(src_indices);
            }
        }

        template <typename...args_t>
        constexpr auto operator==(reshape_t<args_t...> other) const
        {
            return utils::isequal(src_shape,other.src_shape)
                && utils::isequal(dst_shape,other.dst_shape)
            ;
        }
    };

    template <typename array_t, typename dst_shape_t>
    constexpr auto make_reshaper(const array_t& array, const dst_shape_t& dst_shape)
    {
        static_assert( !meta::is_maybe_v<array_t> && !meta::is_maybe_v<dst_shape_t>, "invalid type for array" );
        auto src_shape   = shape<true>(array);
        auto src_size    = size<true>(array);
        auto m_dst_shape = index::shape_reshape(src_shape,dst_shape);
        if constexpr (meta::is_maybe_v<decltype(m_dst_shape)>) {
            using result_t = reshape_t<decltype(src_shape),dst_shape_t,decltype(src_size)>;
            using return_t = nmtools_maybe<result_t>;
            if (static_cast<bool>(m_dst_shape)) {
                return return_t{result_t{src_shape,dst_shape,src_size}};
            } else {
                return return_t{meta::Nothing};
            }
        } else {
            return reshape_t{src_shape,dst_shape,src_size};
        }
    }

    template <typename array_t, typename dst_shape_t>
    constexpr auto make_reshape(const array_t& array, const dst_shape_t& dst_shape)
    {
        auto indexer = make_reshaper(array,dst_shape);
        return indexing(array,indexer);
    }

    template <typename array_t, typename dst_shape_t>
    constexpr auto reshape(const array_t& array, const dst_shape_t& dst_shape)
    {
        auto f = [](const auto&...args){
            return make_reshape(args...);
        };
        return lift_indexing(f,array,dst_shape);
    }

} // namespace nmtools::view

namespace nmtools::array
{
    template <typename...args_t, auto max_dim>
    struct as_static_t<
        view::reshape_t<args_t...>, max_dim
    > {
        using attribute_type = view::reshape_t<args_t...>;

        attribute_type attribute;

        auto operator()() const
        {
            auto src_shape = as_static<max_dim>(attribute.src_shape);
            auto dst_shape = as_static<max_dim>(attribute.dst_shape);
            auto src_size  = as_static<max_dim>(attribute.src_size);
            return view::reshape_t{src_shape,dst_shape,src_size};
        }
    };
}

#if NMTOOLS_HAS_STRING

namespace nmtools::utils::impl
{
    template <typename...args_t, auto...fmt_args>
    struct to_string_t<
        view::reshape_t<args_t...>, fmt_string_t<fmt_args...>
    > {
        using result_type = nmtools_string;

        auto operator()(const view::reshape_t<args_t...>& kwargs) const noexcept
        {
            nmtools_string str;
            str += "reshape{";
            str += ".src_shape=";
            str += to_string(kwargs.src_shape,Compact);
            str += ".dst_shape=";
            str += to_string(kwargs.dst_shape,Compact);
            str += ".src_size=";
            str += to_string(kwargs.src_size,Compact);
            str += "}";
            return str;
        }
    };
} // namespace nmtools::utils::impl

#endif // NMTOOLS_HAS_STRING

#endif // NMTOOLS_ARRAY_VIEW_RESHAPE_HPP