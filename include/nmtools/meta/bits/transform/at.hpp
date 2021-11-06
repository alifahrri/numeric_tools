#ifndef NMTOOLS_META_BITS_TRANSFORM_AT_HPP
#define NMTOOLS_META_BITS_TRANSFORM_AT_HPP

#include "nmtools/meta/common.hpp"

namespace nmtools::meta
{
    /**
     * @brief Helper metafunction to get type at index I from type list T.
     * 
     * @tparam T type list
     * @tparam I index to get the type
     */
    template <typename T, size_t I>
    struct type_at
    {
        using type = detail::fail_t;
    }; // at

    /**
     * @brief Helper alias template to type_at.
     * 
     * @tparam T type list
     * @tparam I index to get the type
     */
    template <typename T, size_t I>
    using at_t = type_t<type_at<T,I>>;
} // namespace nmtools::meta

#endif // NMTOOLS_META_BITS_TRANSFORM_AT_HPP