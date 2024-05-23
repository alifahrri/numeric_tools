#ifndef NMTOOLS_ARRAY_VIEW_UFUNCS_HYPOT_HPP
#define NMTOOLS_ARRAY_VIEW_UFUNCS_HYPOT_HPP

#include "nmtools/array/view/ufunc.hpp"
#include "nmtools/math.hpp"

namespace nmtools::view::fun
{
    struct hypot
    {
        template <typename T, typename U>
        NMTOOLS_UFUNC_CONSTEXPR
        auto operator()(const T& t, const U& u) const
        {
            return math::hypot(t,u);
        } // operator()
    }; // hypot
}

namespace nmtools::view
{
    using hypot_t = fun::hypot;

    template <typename left_t, typename right_t>
    NMTOOLS_UFUNC_CONSTEXPR
    auto hypot(const left_t& a, const right_t& b)
    {
        return broadcast_binary_ufunc(hypot_t{},a,b);
    } // hypot
}

#if NMTOOLS_HAS_STRING

namespace nmtools::utils::impl
{
    template <auto...fmt_args>
    struct to_string_t<view::fun::hypot,fmt_string_t<fmt_args...>>
    {
        using result_type = nmtools_string;

        auto operator()(view::fun::hypot) const
        {
            auto str = nmtools_string();

            str += "hypot";

            return str;
        }
    };
}

#endif // NMTOOLS_HAS_STRING

#endif // NMTOOLS_ARRAY_VIEW_UFUNCS_HYPOT_HPP