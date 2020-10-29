#ifndef NMTOOLS_ARRAY_VIEW_REF_HPP
#define NMTOOLS_ARRAY_VIEW_REF_HPP

#include "nmtools/traits.hpp"
#include "nmtools/meta.hpp"
#include "nmtools/array/meta.hpp"
#include "nmtools/array/utility/at.hpp"
#include "nmtools/array/utility/shape.hpp"
#include "nmtools/array/view/decorator.hpp"

#include <cassert>

namespace nmtools::view
{
    using traits::is_array1d_v;
    using traits::is_array2d_v;
    using traits::is_ndarray_v;
    using traits::is_fixed_size_vector_v;
    using traits::is_fixed_size_matrix_v;
    using traits::is_fixed_size_ndarray_v;
    using traits::has_shape_v;
    using traits::has_size_v;
    using traits::has_dim_v;

    /**
     * @addtogroup view
     * Collections of functions/class for view objects
     * @{
     */

    namespace detail {
        /**
         * @brief identity mapping of indices
         * 
         * @tparam size_types 
         * @param indices 
         * @return constexpr auto 
         */
        template <typename...size_types>
        constexpr auto identity(size_types...indices)
        {
            using common_size_t = std::common_type_t<size_types...>;
            using indices_t = std::array<common_size_t,sizeof...(indices)>;
            auto indices_pack = indices_t{static_cast<common_size_t>(indices)...};
            return indices_pack;
        } // identity
    } // detail

    /**
     * @brief represent constant reference to 1D/2D/ND array.
     * Inspired from <a href="https://llvm.org/doxygen/classllvm_1_1ArrayRef.html">llvm ArrayRef</a>
     * and <a href="https://github.com/tcbrindle/NanoRange/blob/master/include/nanorange/views/ref.hpp">nanorange view ref</a>
     * but specialized for 1D/2D/ND fixed/resizeable array with random access and numpy-like
     * array shape information (dim(), shape())
     * 
     * @tparam Array non-cvref type of array to be referenced, should be deducable via CTAD
     */
    template <typename Array>
    struct ref_t
    {
        static_assert(
            is_array1d_v<Array> || is_array2d_v<Array> || is_ndarray_v<Array>,
            "ref_t only support 1D, 2D, or ndarray for now"
        );
        // get_element_type metafunction should be able to handle
        // ndarray, array2d, array1d etc
        using value_type = meta::get_element_type_t<Array>;
        using const_reference = const value_type&;
        // array type as required by decorator
        using array_type = const Array&;
        static inline constexpr bool is_fixed_size = is_fixed_size_vector_v<Array> || is_fixed_size_matrix_v<Array> || is_fixed_size_ndarray_v<Array>;

        // const reference to actual array type
        array_type array;

        /**
         * @brief construct ref view
         * 
         */
        constexpr ref_t(array_type array) : array(array) {}

        /**
         * @brief identity mapping of indices
         * 
         * @tparam size_types 
         * @param indices 
         * @return constexpr auto 
         */
        template <typename...size_types>
        constexpr auto index(size_types...indices) const
        {
            return detail::identity(indices...);
        } // index
    }; // ref_t

    /**
     * @brief create ref_t object
     * 
     * @tparam array_t type of array
     * @param array array to be referenced
     * @return constexpr auto 
     * @see nmtools::view::ref_t
     */
    template <typename array_t>
    constexpr auto ref(const array_t& array)
    {
        // @note using aggregate initialization 
        // since decorator_t doesn't provide constructor
        return decorator_t<ref_t,array_t>{array};
    } // ref

    /** @} */ // end group view
} // namespace nmtools::view

namespace nmtools
{
    /**
     * @brief specialization of fixed_vector_size for ref view.
     *
     * Only enabled when the referenced array is fixed-size.
     * 
     * @tparam array_t referenced array type
     * @note needs to remove-cvref since the referenced array type returned from make_view may be ref
     * @see nmtools::view::make_view
     */
    template <typename array_t>
    struct fixed_vector_size< view::ref_t<array_t>
        , std::enable_if_t< traits::is_fixed_size_vector_v< traits::remove_cvref_t<array_t> > >
    > : fixed_vector_size< traits::remove_cvref_t<array_t> > {};

    /**
     * @brief specialization of fixed_matrix_size for ref view.
     *
     * Only enabled when the referenced array is fixed-size.
     * 
     * @tparam array_t referenced array type
     * @note needs to remove-cvref since the referenced array type returned from make_view may be ref
     * @see nmtools::view::make_view
     */
    template <typename array_t>
    struct fixed_matrix_size< view::ref_t<array_t>
        , std::enable_if_t< traits::is_fixed_size_matrix_v< traits::remove_cvref_t<array_t> > >
    > : fixed_matrix_size< traits::remove_cvref_t<array_t> > {};
} // namespace nmtools

#endif // NMTOOLS_ARRAY_VIEW_REF_HPP