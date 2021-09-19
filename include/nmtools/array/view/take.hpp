#ifndef NMTOOLS_ARRAY_VIEW_TAKE_HPP
#define NMTOOLS_ARRAY_VIEW_TAKE_HPP

#include "nmtools/meta.hpp"
#include "nmtools/array/view/decorator.hpp"
#include "nmtools/array/index/take.hpp"
#include "nmtools/array/index/make_array.hpp"
#include "nmtools/array/shape.hpp"

namespace nmtools::view
{
    template <typename array_t, typename indices_t, typename axis_t>
    struct take_t
    {
        using array_type = const array_t&;
        using indices_type = const indices_t&;
        using axis_type = axis_t;

        array_type array;
        indices_type indices;
        axis_type axis;

        constexpr take_t(array_type array, indices_type indices, axis_type axis)
            : array(array), indices(indices), axis(axis) {}
        
        constexpr auto shape() const
        {
            using ::nmtools::index::make_array;
            auto shape_ = ::nmtools::shape(array);
            auto ashape = [&](){
                using shape_t = meta::remove_cvref_t<decltype(shape_)>;
                if constexpr (meta::is_specialization_v<shape_t, std::tuple>)
                    return make_array<std::array>(shape_);
                else return shape_;
            }();
            return ::nmtools::index::shape_take(ashape, indices, axis);
        } // shape

        constexpr auto dim() const
        {
            return len(shape());
        } // dim

        template <typename...size_types>
        constexpr auto index(size_types...indices) const
        {
            using ::nmtools::index::make_array;
            using common_t = std::common_type_t<size_types...>;
            auto indices_ = [&](){
                // handle non-packed indices
                if constexpr (std::is_integral_v<common_t>)
                    return make_array<std::array>(indices...);
                // handle packed indices, number of indices must be 1
                else {
                    static_assert (sizeof...(indices)==1
                        , "unsupported index for compress view"
                    );
                    return std::get<0>(std::tuple{indices...});
                }
            }();

            auto shape_ = ::nmtools::shape(array);
            auto ashape = [&](){
                using shape_t = meta::remove_cvref_t<decltype(shape_)>;
                if constexpr (meta::is_specialization_v<shape_t, std::tuple>)
                    return make_array<std::array>(shape_);
                else return shape_;
            }();
            return ::nmtools::index::take(indices_,ashape,this->indices,axis);
        } // index
    }; // take_t

    /**
     * @brief Take elements from an array along an axis.
     * 
     * @tparam array_t 
     * @tparam indices_t 
     * @tparam axis_t 
     * @param array The source array.
     * @param indices The indices of elements to be extracted.
     * @param axis Which axis to take elements.
     * @return constexpr auto 
     */
    template <typename array_t, typename indices_t, typename axis_t>
    constexpr auto take(const array_t& array, const indices_t& indices, axis_t axis)
    {
        return decorator_t<take_t,array_t,indices_t,axis_t>{{array,indices,axis}};
    } // take
} // namespace nmtools::view


namespace nmtools::meta
{
    /**
     * @brief Infer shape for take view at compile-time.
     * 
     * Only supported if array's shape and indices and axis are known at compile-time.
     * 
     * @tparam array_t 
     * @tparam indices_t 
     * @tparam axis_t 
     */
    template <typename array_t, typename indices_t, typename axis_t>
    struct fixed_ndarray_shape< view::take_t<array_t,indices_t,axis_t> >
    {
        static inline constexpr auto value = [](){
            if constexpr (is_fixed_size_ndarray_v<array_t>
                && is_constant_index_array_v<indices_t>
                && is_constant_index_v<axis_t>)
            {
                constexpr auto shape   = fixed_ndarray_shape_v<array_t>;
                constexpr auto indices = indices_t{};
                constexpr auto axis    = axis_t{};
                return ::nmtools::index::shape_take(shape,indices,axis);
            } else {
                return detail::Fail;
            }
        }();
        using value_type = decltype(value);
    }; // fixed_ndarray_shape

    template <typename array_t, typename indices_t, typename axis_t>
    struct is_ndarray< view::decorator_t< view::take_t, array_t, indices_t, axis_t >>
    {
        static constexpr auto value = is_ndarray_v<array_t>;
    };
} // namespace nmtools::meta

#endif // NMTOOLS_ARRAY_VIEW_TAKE_HPP