#ifndef NMTOOLS_ARRAY_VIEW_COMPRESS_HPP
#define NMTOOLS_ARRAY_VIEW_COMPRESS_HPP

#include "nmtools/meta.hpp"
#include "nmtools/array/index/compress.hpp"
#include "nmtools/array/index/product.hpp"
#include "nmtools/array/view/decorator.hpp"

namespace nmtools::view
{

    template <typename condition_t, typename array_t, typename axis_t>
    struct compress_t
    {
        using condition_type = resolve_attribute_type_t<condition_t>;
        using array_type = resolve_array_type_t<array_t>;
        using axis_type  = resolve_attribute_type_t<axis_t>;

        condition_type condition;
        array_type array;
        axis_type axis;

        constexpr compress_t(const condition_t& condition, const array_t& array, const axis_t& axis)
            : condition(init_attribute<condition_type>(condition))
            , array(initialize<array_type>(array))
            , axis(init_attribute<axis_type>(axis))
        {}
        
        constexpr auto shape() const
        {
            auto shape_ = detail::shape(array);
            return ::nmtools::index::shape_compress(condition, shape_, axis);
        } // shape

        constexpr auto dim() const
        {
            return len(shape());
        } // dim

        template <typename...size_types>
        constexpr auto index(size_types...indices) const
        {
            auto indices_ = pack_indices(indices...);

            auto shape_ = detail::shape(array);
            return ::nmtools::index::compress(indices_,condition,shape_,axis);
        } // index
    }; // compress_t

    /**
     * @brief View selected slices of an array along given axis.
     * 
     * @tparam condition_t 1-D array of booleans
     * @tparam array_t 
     * @tparam axis_t 
     * @param condition array that selects which entries to return 
     * @param array array from which to extract
     * @param axis axis to take slices
     * @return constexpr auto 
     */
    template <typename condition_t, typename array_t, typename axis_t>
    constexpr auto compress(const condition_t& condition, const array_t& array, axis_t axis)
    {
        return decorator_t<compress_t,condition_t,array_t,axis_t>{{condition,array,axis}};
    } // compress
} // namespace nmtools::view

namespace nmtools::meta
{
    /**
     * @brief Infer the shape of compress view at compile-time.
     * 
     * @tparam condition_t 
     * @tparam array_t 
     * @tparam axis_t 
     */
    template <typename condition_t, typename array_t, typename axis_t>
    struct fixed_ndarray_shape< view::compress_t<condition_t,array_t,axis_t> >
    {
        static inline constexpr auto value = [](){
            if constexpr (
                    is_fixed_size_ndarray_v<array_t>
                &&  is_constant_index_array_v<condition_t>
                && (is_none_v<axis_t> || is_constant_index_v<axis_t>)
            ) {
                constexpr auto ashape    = fixed_ndarray_shape_v<array_t>;
                constexpr auto condition = condition_t{};
                constexpr auto axis      = axis_t{};
                return index::shape_compress(condition,ashape,axis);
            } else {
                return detail::Fail;
            }
        }();
        using value_type = detail::fail_to_void_t<remove_cvref_t<decltype(value)>>;
    }; // fixed_ndarray_shape

    /**
     * @brief Infer the maximum size of compress view at compile-time.
     * Successful call will make the view considered hybrid_ndarray.
     * 
     * @tparam condition_t 
     * @tparam array_t 
     * @tparam axis_t 
     */
    template <typename condition_t, typename array_t, typename axis_t>
    struct hybrid_ndarray_max_size<
        view::decorator_t<view::compress_t,condition_t,array_t,axis_t>
    >
    {
        static inline constexpr auto value = [](){
            if constexpr (
                     is_fixed_size_ndarray_v<array_t>
                &&  !is_constant_index_array_v<condition_t>
                && !(is_none_v<axis_t> || is_constant_index_v<axis_t>)
            ) {
                constexpr auto shape = fixed_ndarray_shape_v<array_t>;
                return index::product(shape);
            } else if constexpr (is_hybrid_ndarray_v<array_t>) {
                return hybrid_ndarray_max_size_v<array_t>;
            } else {
                return detail::Fail;
            }
        }();
        // TODO: fix either use value_type or type for deducing a valid value
        using value_type = detail::fail_to_void_t<remove_cvref_t<decltype(value)>>;
        using type = remove_cvref_t<decltype(value)>;
    }; // hybrid_ndarray_max_size

    /**
     * @brief Infer the fixed dimension of compress view at compile-time.
     * 
     * @tparam condition_t 
     * @tparam array_t 
     * @tparam axis_t 
     */
    template <typename condition_t, typename array_t, typename axis_t>
    struct fixed_dim<
        view::decorator_t<view::compress_t,condition_t,array_t,axis_t>
    >
    {
        // compress view doesn't change the resulting dimension,
        // except for None axis
        static constexpr auto value = [](){
            if constexpr (is_none_v<axis_t>) {
                // None axis means compress on flattened array
                return 1;
            } else if constexpr (is_fixed_dim_ndarray_v<array_t>) {
                return fixed_dim_v<array_t>;
            } else {
                return detail::Fail;
            }
        }();
        // TODO: fix either use value_type or type for deducing a valid value
        using value_type = detail::fail_to_void_t<remove_cvref_t<decltype(value)>>;
        using type = remove_cvref_t<decltype(value)>;
    }; // fixed_dim

    template <typename condition_t, typename array_t, typename axis_t>
    struct is_ndarray< view::decorator_t< view::compress_t, condition_t, array_t, axis_t >>
    {
        static constexpr auto value = (is_ndarray_v<condition_t> || is_index_array_v<condition_t>) && is_ndarray_v<array_t>;
    };
} // namespace nmtools::meta

#endif // NMTOOLS_ARRAY_VIEW_COMPRESS_HPP