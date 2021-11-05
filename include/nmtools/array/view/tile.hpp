#ifndef NMTOOLS_ARRAY_VIEW_TILE_HPP
#define NMTOOLS_ARRAY_VIEW_TILE_HPP

#include "nmtools/meta.hpp"
#include "nmtools/array/view/decorator.hpp"
#include "nmtools/array/index/tile.hpp"
#include "nmtools/array/index/shape_tile.hpp"
#include "nmtools/array/shape.hpp"

namespace nmtools::view
{
    /**
     * @brief Type constructor for tile view.
     * 
     * @tparam array_t array type to be referenced.
     * @tparam reps_t  reps type
     */
    template <typename array_t, typename reps_t>
    struct tile_t
    {
        using value_type = meta::get_element_type_t<array_t>;
        using const_reference = const value_type&;
        using array_type = resolve_array_type_t<array_t>;
        using reps_type  = resolve_attribute_type_t<reps_t>;
        
        array_type array;
        reps_type  reps;

        constexpr tile_t(const array_t& array, const reps_t& reps)
            : array(initialize(array, meta::as_value_v<array_type>))
            , reps(init_attribute(reps, meta::as_value_v<reps_type>)) {}
        
        constexpr decltype(auto) shape() const
        {
            auto shape_ = detail::shape(array);
            return index::shape_tile(shape_,reps);
        } // shape

        constexpr decltype(auto) dim() const
        {
            return len(shape());
        } // dim

        template <typename...size_types>
        constexpr auto index(size_types...indices) const
        {
            // tile view is just indexing view, no value transform
            auto indices_ = pack_indices(indices...);
            auto shape_   = detail::shape(array);
            return index::tile(shape_,reps,indices_);
        } // index
    }; // tile_t

    /**
     * @brief Construct a view by repeating array the number of times given by reps.
     * 
     * This follow numpy's tile, that is, if reps has length d, the result will have dimension of max(d, dim(array)).
     * 
     * @tparam array_t 
     * @tparam reps_t 
     * @param array The input array
     * @param reps The number of repetitions of array along each axis.
     * @return constexpr auto 
     */
    template <typename array_t, typename reps_t>
    constexpr auto tile(const array_t& array, const reps_t& reps)
    {
        return decorator_t<tile_t,array_t,reps_t>{{array,reps}};
    } // tile
} // namespace nmtools::view

namespace nmtools::meta
{
    /**
     * @brief Infer the shape of tile view at compile-time.
     * 
     * @tparam array_t 
     * @tparam reps_t 
     */
    template <typename array_t, typename reps_t>
    struct fixed_ndarray_shape< view::tile_t<array_t,reps_t> >
    {
        static inline constexpr auto value = [](){
            // we can only know the shape at compile time if both array and reps are compile-time constant
            // note that shape_tile will "repeat elements" or multiply size between array's shape and reps
            if constexpr (is_fixed_size_ndarray_v<array_t> && is_constant_index_array_v<reps_t>) {
                constexpr auto shape_ = fixed_ndarray_shape_v<array_t>;
                constexpr auto reps   = reps_t{};
                return index::shape_tile(shape_,reps);
            } else {
                return detail::Fail;
            }
        }();
        using value_type = decltype(value);
    }; // fixed_ndarray_shape

    /**
     * @brief Infer dimension of tile view at compile-time.
     * 
     * @tparam array_t 
     * @tparam reps_t 
     */
    template <typename array_t, typename reps_t>
    struct fixed_dim< view::decorator_t<view::tile_t, array_t, reps_t> >
    {
        static inline constexpr auto value = [](){
            if constexpr (is_fixed_index_array_v<reps_t>) {
                return fixed_index_array_size_v<reps_t>;
            } else {
                return detail::Fail;
            }
        }();
        using value_type = decltype(value);
    }; // fixed_dim

    template <typename array_t, typename reps_t>
    struct is_ndarray< view::decorator_t< view::tile_t, array_t, reps_t >>
        : is_ndarray<array_t> {};
} // namespace nmtools::meta

#endif // NMTOOLS_ARRAY_VIEW_TILE_HPP