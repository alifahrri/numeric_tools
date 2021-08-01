#ifndef NMTOOLS_ARRAY_ARRAY_FLATTEN_HPP
#define NMTOOLS_ARRAY_ARRAY_FLATTEN_HPP

#include "nmtools/array/view/flatten.hpp"
#include "nmtools/array/eval.hpp"

namespace nmtools::array
{
    /**
     * @brief Eagerly evaluate flatten.
     * 
     * @tparam output_t 
     * @tparam context_t 
     * @tparam array_t 
     * @param array     array to be flattened
     * @param context   evalutation context
     * @param output
     * @return constexpr auto 
     */
    template <typename output_t=none_t, typename context_t=none_t,
        typename array_t>
    constexpr auto flatten(const array_t& array,
        context_t&& context=context_t{}, output_t&& output=output_t{})
    {
        auto flattened = view::flatten(array);
        return eval(flattened,context,output);
    } // flatten
} // namespace nmtools::array

#endif // NMTOOLS_ARRAY_ARRAY_FLATTEN_HPP