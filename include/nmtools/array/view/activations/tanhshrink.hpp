#ifndef NMTOOLS_ARRAY_VIEW_ACTIVATIONS_TANHSHRINK_HPP
#define NMTOOLS_ARRAY_VIEW_ACTIVATIONS_TANHSHRINK_HPP

#include "nmtools/array/view/ufunc.hpp"
#include "nmtools/math.hpp"

namespace nmtools::view
{
    /**
     * @brief Function object for tanhshrink ufunc
     * 
     */
    struct tanhshrink_t
    {
        template <typename T>
        NMTOOLS_UFUNC_CONSTEXPR
        nmtools_func_attribute
        auto operator()(const T& x) const
        {
            return x - math::tanh(x);
        } // operator()
    }; // tanhshrink_t

    /**
     * @brief Create element-wise tanhshrink ufunc view
     * 
     * @tparam array_t 
     * @param array     input array
     * @return NMTOOLS_UFUNC_CONSTEXPR 
     */
    template <typename array_t>
    nmtools_func_attribute
    NMTOOLS_UFUNC_CONSTEXPR
    auto tanhshrink(const array_t& array)
    {
        return ufunc(tanhshrink_t{},array);
    } // tanhshrink
} // namespace nmtools::view


#endif // NMTOOLS_ARRAY_VIEW_ACTIVATIONS_TANHSHRINK_HPP