#ifndef NMTOOLS_ARRAY_VIEW_FLATTEN_HPP
#define NMTOOLS_ARRAY_VIEW_FLATTEN_HPP

#include "nmtools/traits.hpp"
#include "nmtools/meta.hpp"
#include "nmtools/array/utility/at.hpp"
#include "nmtools/array/utility/shape.hpp"
#include "nmtools/array/view/decorator.hpp"

#include "nmtools/array/meta.hpp"
#include "nmtools/array/detail.hpp"
#include "nmtools/array/index.hpp"

#include <cassert>

namespace nmtools::view
{
    /**
     * @addtogroup view
     * Collections of functions/class for view objects
     * @{
     */
    
    template <typename array_t>
    struct flatten_t
    {
        using value_type = meta::get_element_type_t<array_t>;
        using const_reference = const value_type&;
        // array type as required by decorator
        using array_type = const array_t&;

        array_type array;

        constexpr flatten_t(array_type array) : array(array) {}

        constexpr auto dim() const noexcept
        {
            // flattened array is strictly 1D
            return 1;
        } // dim

        constexpr auto shape() const noexcept
        {
            // assuming fixed dim array
            auto shape_ = detail::shape<std::array>(array);
            // compute product
            auto identity = 1;
            for (size_t i=0; i<shape_.size(); i++)
                identity *= shape_[i];
            // flattened array is strictly 1D
            return std::tuple{identity};
        } // shape

        template <typename size_type>
        constexpr auto index(size_type i) const
        {
            using ::nmtools::array::detail::compute_indices;
            // assuming fixed dim array
            auto shape_  = detail::shape<std::array>(array);
            auto indices = compute_indices(i,shape_);
            return indices;
        } // index
    }; // flatten_t

    template <typename array_t>
    constexpr auto flatten(const array_t& array)
    {
        // @note using aggregate initialization
        // since decorator_t doesn't provide constructor
        return decorator_t<flatten_t,array_t>{array};
    } // flatten

    /** @} */ // end group view
} // namespace nmtools::view

namespace nmtools::traits
{
    /**
     * @brief flatten view is 1D
     * 
     * @tparam array_t 
     */
    template <typename array_t>
    struct is_array1d<view::decorator_t<view::flatten_t,array_t>> : std::true_type {};

    /**
     * @brief flatten view is 1D
     * 
     * @tparam array_t 
     */
    template <typename array_t>
    struct is_array2d<view::decorator_t<view::flatten_t,array_t>> : std::false_type {};

    /**
     * @brief flatten view is 1D
     * 
     * @tparam array_t 
     */
    template <typename array_t>
    struct is_array3d<view::decorator_t<view::flatten_t,array_t>> : std::false_type {};

    /**
     * @brief flatten view is 1D
     * 
     * @tparam array_t 
     */
    template <typename array_t>
    struct is_ndarray<view::decorator_t<view::flatten_t,array_t>> : std::false_type {};
} // namespace nmtools::traits

namespace nmtools
{
    template <typename array_t>
    struct fixed_vector_size< view::flatten_t<array_t>
        , std::enable_if_t<
            traits::is_fixed_size_array_v<traits::remove_cvref_t<array_t>>
        >
    > {
        static constexpr auto _get()
        {
            constexpr auto shape_ = fixed_array_shape_v<traits::remove_cvref_t<array_t>>;
            constexpr auto shape  = detail::make_array<std::array>(shape_);
            // compute product
            auto identity = 1;
            for (size_t i=0; i<shape.size(); i++)
                identity *= shape[i];
            // flattened array is strictly 1D
            return identity;
        } // get

        static constexpr auto value = _get();
        using value_type = decltype(_get());
    };
} // nmtools

#endif // NMTOOLS_ARRAY_VIEW_FLATTEN_HPP