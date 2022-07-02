#ifndef NMTOOLS_UTL_MAYBE_HPP
#define NMTOOLS_UTL_MAYBE_HPP

#include "nmtools/utl/either.hpp"

namespace nmtools::utl
{
    struct nothing_t {};

    inline constexpr auto nothing = nothing_t {};

    
    /**
     * @brief Poor man's optional (Maybe type).
     * 
     * This structure doesn't aim to be fully STL-compatible,
     * only subset of that is used in nmtools.
     * 
     * @tparam T 
     */
    template <typename T>
    struct maybe : either<T,nothing_t>
    {
    public:
        using base = either<T,nothing_t>;
        using value_type = T;
        using pointer    = T*;
        using reference  = T&;
        using const_pointer   = const T*;
        using const_reference = const T&;

        constexpr maybe() : base(nothing) {}

        constexpr maybe(nothing_t) : base(nothing) {}

        constexpr maybe(const T& t) : base(t) {}

        constexpr maybe(const maybe& other) = default;

        constexpr bool has_value() const noexcept
        {
            return this->tag == base::LEFT;
        }

        template <typename U>
        /*constexpr*/ maybe& operator=(const U& val)
        {
            // NOTE: using current approach (using either which use union), assignment cant be constexpr
            // since union can't be changed for constexpr call.
            // other approach for example using placement-new doesn't interact well with constexpr
            // 
            base::operator=(val);
            return *this;
        }

        constexpr explicit operator bool() const noexcept
        {
            return has_value();
        }

        constexpr const_reference value() const& noexcept
        {
            return this->left;
        }

        constexpr reference value() & noexcept
        {
            return this->left;
        }

        constexpr const_reference operator*() const& noexcept
        {
            return value();
        }

        constexpr reference operator*() & noexcept
        {
            return value();
        }
    };
    

} // namespace nmtools::utl

#endif // NMTOOLS_UTL_MAYBE_HPP