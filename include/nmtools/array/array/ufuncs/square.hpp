#ifndef NMTOOLS_ARRAY_ARRAY_SQUARE_HPP
#define NMTOOLS_ARRAY_ARRAY_SQUARE_HPP

#include "nmtools/array/eval.hpp"
#include "nmtools/array/view/ufuncs/square.hpp"
#include "nmtools/constants.hpp"

namespace nmtools::array
{
    namespace fn
    {
        struct square
        {
            template <typename output_t=none_t, typename context_t=none_t, typename left_t>
            inline constexpr auto operator()(const left_t& a,
                context_t&& context=context_t{}, output_t&& output=output_t{}) const
            {
                auto square = view::square(a);
                return eval(square,context,output);
            } // operator()
        }; // square
    } // namespace fn

    constexpr inline auto square = fn::square{};
} // nmtools::array

#endif // NMTOOLS_ARRAY_ARRAY_SQUARE_HPP