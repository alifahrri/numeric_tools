#ifndef NMTOOLS_ARRAY_ARRAY_BITWISE_AND_HPP
#define NMTOOLS_ARRAY_ARRAY_BITWISE_AND_HPP

#include "nmtools/array/eval.hpp"
#include "nmtools/array/view/ufuncs/bitwise_and.hpp"
#include "nmtools/constants.hpp"

namespace nmtools::array
{
    namespace fn
    {
        struct bitwise_and
        {
            template <typename output_t=none_t, typename context_t=none_t, typename left_t, typename right_t>
            inline constexpr auto operator()(const left_t& a, const right_t& b,
                context_t&& context=context_t{}, output_t&& output=output_t{}) const
            {
                auto bitwise_and = view::bitwise_and(a,b);
                return eval(bitwise_and,context,output);
            } // operator()
        }; // bitwise_and
    } // namespace fn

    constexpr inline auto bitwise_and = fn::bitwise_and{};
} // nmtools::array

#endif // NMTOOLS_ARRAY_ARRAY_BITWISE_AND_HPP