#ifndef NMTOOLS_ARRAY_VIEW_DECORATOR_HPP
#define NMTOOLS_ARRAY_VIEW_DECORATOR_HPP

#include "nmtools/traits.hpp"
#include "nmtools/meta.hpp"
#include "nmtools/array/meta.hpp" // is_fixed_shape_v
#include "nmtools/array/utility/at.hpp"
#include "nmtools/array/utility/shape.hpp"

#include <cassert>

namespace nmtools::view
{
    using traits::is_fixed_shape_v;

    /**
     * @addtogroup view
     * Collections of functions/class for view objects
     * @{
     */

    namespace detail
    {
        /**
         * @brief return the dimensionality of the referred array
         * 
         * @tparam array_t the type of array
         * @param array 
         * @return constexpr auto 
         * @note marked as static fn here to properly handle fixed_size array
         * @see nmtools::traits::has_dim
         * @see nmtools::traits::is_array2d
         * @see nmtools::traits::is_array1d
         * @see nmtools::array_dim
         */
        template <typename array_t>
        constexpr auto dim(const array_t& array)
        {
            // @note somehow array cant be universal ref
            if constexpr (traits::has_dim_v<array_t>)
                return array.dim();
            // @note since is_array2d_v and is_array1d_v may not be mutually exclusive prefer array2d first
            else if constexpr (traits::is_array2d_v<array_t>)
                return 2;
            else if constexpr (traits::is_array1d_v<array_t>)
                return 1;
            else
                return array_dim(array);
        } // dim()

        /**
         * @brief call at given packed indices
         * 
         * @tparam array_t array type to be accessed
         * @tparam indices_t packed indices type
         * @tparam I compile-time index sequence to access indices
         * @param array array to be accessed
         * @param indices packed indices
         * @return constexpr decltype(auto) 
         */
        template <typename array_t, typename indices_t, size_t...I>
        constexpr decltype(auto) unpack_at(array_t&& array, const indices_t& indices, std::index_sequence<I...>)
        {
            return at(array, std::get<I>(indices)...);
        } // unpack_at
    } // namespace detail

    /**
     * @brief provide generic common implementation for view objects. 
     * 
     * @note implemented as decorator/mixin instead of 'interface'
     * @tparam view_t template template parameter
     * @tparam Ts arbitrary number of tparams for view_t
     */
    template <template<typename...> typename view_t, typename...Ts>
    struct decorator_t : view_t<Ts...>
    {
        using view_type = view_t<Ts...>;
        // @note possibly const
        using array_type = typename view_type::array_type;

        /**
         * @todo
         *  - static assert if view_type array exists
         *  - has index member function that transform indices
         */

        /**
         * @brief return the dimensionality of the referred array
         * 
         * @return constexpr auto 
         */
        template <typename=std::enable_if_t<!traits::has_dim_v<traits::remove_cvref_t<view_type>>>>
        constexpr auto dim() const noexcept
        {
            // @note `this` must be constexpr when constexpr return value is desired
            return detail::dim(view_type::array);
        } // dim()

        /**
         * @brief return the shape of this array
         * 
         * @return constexpr auto 
         * @see nmtools::vector_size
         * @see nmtools::matrix_size
         * @see nmtools::array_shape
         */
        constexpr auto shape() const noexcept
        {
            using array_t = traits::remove_cvref_t<array_type>;
            if constexpr (traits::has_shape_v<traits::remove_cvref_t<view_type>>)
                return view_type::shape();
            else if constexpr (traits::has_shape_v<array_t>)
                return view_type::array.shape();
            // @note since is_array2d_v and is_array1d_v may not be mutually exclusive, check for array2d first
            else if constexpr (traits::is_array2d_v<array_t>)
                return matrix_size(view_type::array);
            // @note for 1d array, wrap return value in array for generalization
            else if constexpr (traits::is_array1d_v<array_t> && traits::has_size_v<array_t>)
                return std::array{view_type::array.size()};
            else if constexpr (traits::is_array1d_v<array_t>)
                return std::array{vector_size(view_type::array)};
            else
                return array_shape(view_type::array);
        } // shape

        /**
         * @brief immutable element acces to the referenced array
         * 
         * @tparam size_types size type(s) to array
         * @param indices 
         * @return constexpr auto
         * @todo make error handling configurable, e.g. throw/assert/optional
         * @note for fixed size, it is necessary to pass Array{} (value initialization) to dim since `this` may not be constant exprression
         * @see https://en.cppreference.com/w/cpp/language/value_initialization
         * @see nmtools::at
         */
        template <typename...size_types>
        constexpr decltype(auto) operator()(size_types...indices)
        {
            // @note either using auto& or decltype(auto) for return type
            // since at(...) return auto&

            auto transformed_indices = view_type::index(indices...);
            static_assert (traits::has_tuple_size_v<decltype(transformed_indices)>,
                "return value from view_type::index(...) must have compile time size"
            );

            using array_t = traits::remove_cvref_t<array_type>;
            constexpr auto n = sizeof...(size_types);

            // @note needs to initialize array_t since view_type::array may not be constant expression
            if constexpr (is_fixed_shape_v<array_t>)
                static_assert (detail::dim(array_t{})==n);
            else
                assert (dim()==n);
            // call at to referred object, not to this
            // return at(view_type::array, indices...);
            using indices_sequence_t = std::make_index_sequence<std::tuple_size_v<decltype(transformed_indices)>>;
            return detail::unpack_at(view_type::array, transformed_indices, indices_sequence_t{});
        } // operator()

    }; // decorator_t

    /**
     * @brief make view given parameters arrays
     * 
     * @tparam view_t template template parameter
     * @tparam Ts tparams for view_t, should be deducible from template argument deduction
     * @param arrays array to be viewed
     * @return constexpr auto 
     */
    template <template<typename...> typename view_t, typename...Ts>
    constexpr auto make_view(Ts&&...arrays)
    {
        // @note using aggregate initialization 
        // since decorator_t doesn't provide constructor
        // @note requires nested brace so that view_t that takes
        // multiple value at instantiation can be instantiated
        return decorator_t<view_t,Ts...>{{arrays...}};
    } // make_view

    /** @} */ // end group view
} // namespace nmtools::view

namespace nmtools
{
    /**
     * @brief specialization of fixed_array_shape for view decorator
     * 
     * @tparam view_t template template parameter corresponding to the underlying view
     * @tparam Ts template parameter(s) to the underlying view
     */
    template <template<typename...> typename view_t, typename...Ts>
    struct fixed_array_shape<view::decorator_t<view_t,Ts...>>
        : fixed_array_shape<traits::remove_cvref_t<typename view::decorator_t<view_t,Ts...>::array_type>> {};
} // namespace nmtools

namespace nmtools::traits
{
    /**
     * @brief specialization of is_fixed_size_vector for view type
     * 
     * @tparam view_t template template parameter corresponding to the underlying view
     * @tparam Ts template parameter(s) to the underlying view
     */
    template <template<typename...> typename view_t, typename...Ts>
    struct is_fixed_size_vector<view::decorator_t<view_t,Ts...>>
        : is_fixed_size_vector<traits::remove_cvref_t<typename view::decorator_t<view_t,Ts...>::array_type>> {};

    /**
     * @brief specialization of is_fixed_size_matrix for view type
     * 
     * @tparam view_t template template parameter corresponding to the underlying view
     * @tparam Ts template parameter(s) to the underlying view
     */
    template <template<typename...> typename view_t, typename...Ts>
    struct is_fixed_size_matrix<view::decorator_t<view_t,Ts...>>
        : is_fixed_size_matrix<traits::remove_cvref_t<typename view::decorator_t<view_t,Ts...>::array_type>> {};
    
    /**
     * @brief specialization of is_fixed_ndarray for view type
     * 
     * @tparam view_t template template parameter corresponding to the underlying view
     * @tparam Ts template parameter(s) to the underlying view
     */
    template <template<typename...> typename view_t, typename...Ts>
    struct is_fixed_ndarray<view::decorator_t<view_t,Ts...>>
        : is_fixed_ndarray<traits::remove_cvref_t<typename view::decorator_t<view_t,Ts...>::array_type>> {};
    
    /**
     * @brief specialization of is_array1d for view type
     * 
     * @tparam view_t template template parameter corresponding to the underlying view
     * @tparam Ts template parameter(s) to the underlying view
     */
    template <template<typename...> typename view_t, typename...Ts>
    struct is_array1d<view::decorator_t<view_t,Ts...>>
        : is_array1d<traits::remove_cvref_t<typename view::decorator_t<view_t,Ts...>::array_type>> {};
    
    /**
     * @brief specialization of is_array2d for view type
     * 
     * @tparam view_t template template parameter corresponding to the underlying view
     * @tparam Ts template parameter(s) to the underlying view
     */
    template <template<typename...> typename view_t, typename...Ts>
    struct is_array2d<view::decorator_t<view_t,Ts...>>
        : is_array2d<traits::remove_cvref_t<typename view::decorator_t<view_t,Ts...>::array_type>> {};
    
    /**
     * @brief specialization of is_array3d for view type
     * 
     * @tparam view_t template template parameter corresponding to the underlying view
     * @tparam Ts template parameter(s) to the underlying view
     */
    template <template<typename...> typename view_t, typename...Ts>
    struct is_array3d<view::decorator_t<view_t,Ts...>>
        : is_array3d<traits::remove_cvref_t<typename view::decorator_t<view_t,Ts...>::array_type>> {};
    
    /**
     * @brief specialization of is_ndarray for view type
     * 
     * @tparam view_t template template parameter corresponding to the underlying view
     * @tparam Ts template parameter(s) to the underlying view
     */
    template <template<typename...> typename view_t, typename...Ts>
    struct is_ndarray<view::decorator_t<view_t,Ts...>>
        : is_ndarray<traits::remove_cvref_t<typename view::decorator_t<view_t,Ts...>::array_type>> {};
} // namespace nmtools::traits

namespace nmtools::meta
{
    /**
     * @brief specializtion of metafunction get_vector_value_type for view type
     * 
     * @tparam view_t template template parameter corresponding to the underlying view
     * @tparam Ts template parameter(s) to the underlying view
     */
    template <template<typename...> typename view_t, typename...Ts>
    struct get_vector_value_type<view::decorator_t<view_t,Ts...>>
        : get_vector_value_type<traits::remove_cvref_t<typename view::decorator_t<view_t,Ts...>::array_type>> {};
    
    /**
     * @brief specialization of metafunction get_matrix_value_type for view type
     * 
     * @tparam view_t template template parameter corresponding to the underlying view
     * @tparam Ts template parameter(s) to the underlying view
     */
    template <template<typename...> typename view_t, typename...Ts>
    struct get_matrix_value_type<view::decorator_t<view_t,Ts...>>
        : get_matrix_value_type<traits::remove_cvref_t<typename view::decorator_t<view_t,Ts...>::array_type>> {};

    /**
     * @brief specialization of metafunction get_ndarray_value_type for view type
     * 
     * @tparam view_t template template parameter corresponding to the underlying view
     * @tparam Ts template parameter(s) to the underlying view
     */
    template <template<typename...> typename view_t, typename...Ts>
    struct get_ndarray_value_type<view::decorator_t<view_t,Ts...>>
        : get_ndarray_value_type<traits::remove_cvref_t<typename view::decorator_t<view_t,Ts...>::array_type>> {};
} // namespace nmtools::meta

#endif // NMTOOLS_ARRAY_VIEW_DECORATOR_HPP