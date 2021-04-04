#ifndef NMTOOLS_ARRAY_ARRAY_LESS_EQUAL_HPP
#define NMTOOLS_ARRAY_ARRAY_LESS_EQUAL_HPP

#include "nmtools/array/eval.hpp"
#include "nmtools/array/view/ufuncs/less_equal.hpp"
#include "nmtools/constants.hpp"

namespace nmtools::array
{
    namespace fn
    {
        struct less_equal
        {
            template <typename output_t=none_t, typename context_t=none_t, typename left_t, typename right_t>
            inline constexpr auto operator()(const left_t& a, const right_t& b,
                context_t&& context=context_t{}, output_t&& output=output_t{}) const
            {
                auto less_equal = view::less_equal(a,b);
                return eval(less_equal,context,output);
            } // operator()
        }; // less_equal
    } // namespace fn

    constexpr inline auto less_equal = fn::less_equal{};
} // nmtools::array

#endif // NMTOOLS_ARRAY_ARRAY_LESS_EQUAL_HPP