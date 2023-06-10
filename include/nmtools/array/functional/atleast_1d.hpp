#ifndef NMTOOLS_ARRAY_FUNCTIONAL_ATLEAST_1D_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_ATLEAST_1D_HPP

#include "nmtools/array/functional/functor.hpp"
#include "nmtools/array/view/atleast_1d.hpp"

namespace nmtools::functional
{
    namespace fun 
    {
        struct atleast_1d_t
        {
            template <typename...args_t>
            constexpr auto operator()(const args_t&...args) const
            {
                return view::atleast_1d(args...);
            }
        };
    }

    constexpr inline auto atleast_1d = functor_t(unary_fmap_t<fun::atleast_1d_t>{});

    template <typename...args_t>
    struct get_function_t<
        view::decorator_t<
            view::atleast_1d_t, args_t...
        >
    >
    {
        using view_type = view::decorator_t<
            view::atleast_1d_t, args_t...
        >;

        view_type view;

        constexpr auto operator()() const noexcept
        {
            return atleast_1d;
        }
    };
} // namespace nmtools::functional

#endif // NMTOOLS_ARRAY_FUNCTIONAL_ATLEAST_1D_HPP