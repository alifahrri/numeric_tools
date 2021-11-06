#ifndef NMTOOLS_META_BITS_TRAITS_IS_NDARRAY_HPP
#define NMTOOLS_META_BITS_TRAITS_IS_NDARRAY_HPP

#include "nmtools/meta/bits/traits/has_at.hpp"
#include "nmtools/meta/bits/traits/has_bracket.hpp"
#include "nmtools/meta/bits/traits/has_square_bracket.hpp"
#include "nmtools/meta/bits/traits/is_fixed_size_ndarray.hpp"
#include "nmtools/meta/bits/array/nested_array_dim.hpp"

namespace nmtools::meta
{
    // TODO: remove
    /**
     * @brief check if T t{} are:
     * - t[0][0][0] is valid
     * 
     * @tparam T 
     * @tparam void 
     */
    template <typename T, typename=void>
    struct is_array3d
    {
        static constexpr inline auto _check()
        {
            if constexpr (has_atnd_v<T,size_t,size_t,size_t>)
                return true;
            else if constexpr (has_funcnd_v<T,size_t,size_t,size_t>)
                return true;
            else if constexpr (has_bracketnd_v<T,size_t,size_t,size_t>)
                return true;
            else if constexpr (std::is_array_v<T> && std::rank_v<T> == 3)
                return true;
            else if constexpr (nested_array_dim_v<T> == 3)
                return true;
            else return false;
        } // _check
        static constexpr inline auto value = _check();
    }; // is_array3d

    template <typename T>
    inline constexpr bool is_array3d_v = is_array3d<T>::value;

    // TODO: remove
    /**
     * @brief check if T t{} are:
     * - t[0][0] is valid
     * 
     * @tparam T 
     * @tparam void 
     */
    template <typename T, typename=void>
    struct is_array2d
    {
        static constexpr inline auto _check()
        {
            if constexpr (has_atnd_v<T,size_t,size_t>)
                return true;
            else if constexpr (has_funcnd_v<T,size_t,size_t>)
                return true;
            else if constexpr (has_bracketnd_v<T,size_t,size_t>)
                return true;
            else if constexpr (std::is_array_v<T> && std::rank_v<T> == 2)
                return true;
            else if constexpr (nested_array_dim_v<T> == 2)
                return true;
            else return false;
        } // _check
        static constexpr inline auto value = _check();
    }; // is_array2d

    template <typename T>
    inline constexpr bool is_array2d_v = is_array2d<T>::value;

    // TODO: remove
    /**
     * @brief check if T t{} are:
     * - t[0] is valid
     * 
     * @tparam T 
     * @tparam void 
     */
    template <typename T, typename=void>
    struct is_array1d
    {
        static constexpr inline auto _check()
        {
            if constexpr (has_atnd_v<T,size_t>)
                return true;
            else if constexpr (has_funcnd_v<T,size_t>)
                return true;
            else if constexpr (has_square_bracket_v<T,size_t>)
                return true;
            else if constexpr (std::is_array_v<T> && std::rank_v<T> == 1)
                return true;
            else if constexpr (nested_array_dim_v<T> == 1)
                return true;
            else return false;
        } // _check
        static constexpr inline auto value = _check();
    }; // is_array1d

    /**
     * @brief helper variable template to check if T is 1d array-like
     * 
     * @tparam T 
     */
    template <typename T>
    inline constexpr bool is_array1d_v = is_array1d<T>::value;
} // namespace nmtools::meta

namespace nmtools::meta
{
    /**
     * @addtogroup traits
     * @{
     */

    /**
     * @brief check if given type T is n-dimensional array
     * 
     * Default implementation check for distjunction of fixed-size ndarray, array1d and array2d.
     *
     * @tparam T type to check
     * @tparam typename customization point
     * @see is_fixed_size_ndarray
     * @see is_array1d
     * @see is_array2d
     */
    template <typename T, typename=void>
    struct is_ndarray
    {
        static constexpr auto value = [](){

            if constexpr (is_fixed_size_ndarray_v<T>)
                return true;
            // TODO: remove
            else if constexpr (is_array2d_v<T>)
                return true;
            // TODO: remove
            else if constexpr (is_array1d_v<T>)
                return true;
            else return false;
        }();
    }; // is_ndarray

    /**
     * @brief helper variable template to check if T is n-dimensional array
     * 
     * @tparam T type to check
     */
    template <typename T>
    inline constexpr bool is_ndarray_v = is_ndarray<T>::value;


    /** @} */ // end group traits

} // namespace nmtools::meta

#endif // NMTOOLS_META_BITS_TRAITS_IS_NDARRAY_HPP