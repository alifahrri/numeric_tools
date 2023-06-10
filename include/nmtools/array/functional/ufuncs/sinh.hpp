#ifndef NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_SINH_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_SINH_HPP

#include "nmtools/array/functional/functor.hpp"
#include "nmtools/array/view/ufuncs/sinh.hpp"

namespace nmtools::functional
{
    namespace fun
    {
        struct sinh_t
        {
            template <typename...args_t>
            constexpr auto operator()(const args_t&...args) const
            {
                return view::sinh(args...);
            }
        };
    }

    constexpr inline auto sinh = functor_t(unary_fmap_t<fun::sinh_t>{});

    template <typename...arrays_t>
    struct get_function_t<
        view::decorator_t<
            view::ufunc_t, view::sinh_t, arrays_t...
        >
    > {
        using view_type = view::decorator_t<
            view::ufunc_t, view::sinh_t, arrays_t...
        >;

        view_type view;

        constexpr auto operator()() const noexcept
        {
            return sinh;
        }
    };
} // namespace nmtools::functional


#endif // NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_SINH_HPP