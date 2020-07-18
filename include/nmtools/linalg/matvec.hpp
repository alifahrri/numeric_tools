#ifndef NMTOOLS_LINALG_MATVEC_HPP
#define NMTOOLS_LINALG_MATVEC_HPP

#include "nmtools/traits.hpp"
#include "nmtools/meta.hpp"
#include <type_traits>
#include <cmath>
#include <cassert>

namespace nmtools::linalg {

    using std::size;

    namespace detail {

        /**
         * @brief vector-scalar multiplication
         * 
         * @tparam V vector-like 
         * @tparam S scalar 
         * @param v left-hand-side vector
         * @param s right-hand-side scalar
         * @return constexpr auto vector-like
         */
        template <typename V, typename S>
        constexpr auto vsmul(const V& v, const S& s)
        {
            auto ret = v;
            for (auto& e : ret)
                e *= s;
            return ret;
        }

        /**
         * @brief matrix-scalar multiplication
         * 
         * @tparam M matrix-like
         * @tparam S scalar 
         * @param m left-hand-side matrix
         * @param s right-hand-side scalar
         * @return constexpr auto matrix-like
         */
        template <typename M, typename S>
        constexpr auto msmul(const M& m, const S& s)
        {
            auto ret = zeros_like(m);
            for (auto& e : ret)
                e = vsmul(e,s);
            return ret;
        }

        /**
         * @brief dot product of v1 & v2
         * 
         * @tparam V1 vector-like
         * @tparam V2 vector-like
         * @param v1 left-hand-side vector
         * @param v2 right-hand-side vector
         * @return constexpr auto scalar, common type of element v1 & v2
         */
        template <typename V1, typename V2>
        constexpr auto dot(const V1& v1, const V2& v2)
        {
            using std::remove_cv_t;
            using std::remove_reference_t;

            using e1_t = remove_cv_t<remove_reference_t<decltype(v1[0])>>;
            using e2_t = remove_cv_t<remove_reference_t<decltype(v2[0])>>;
            using value_t = std::common_type_t<e1_t,e2_t>;

            value_t ret{0};

            auto n1 = size(v1);
            auto n2 = size(v2);
            /* TODO: make assertio optional (?) */
            assert(n1==n2);
            
            for (size_t i = 0; i < n1; i++)
                ret += v1[i] * v2[i];
            return ret;
        }

        /**
         * @brief matrix-vector multiplication
         * 
         * @tparam M matrix-like
         * @tparam V vector-like
         * @param m left-hand-side matrix
         * @param v right-hand-side vector
         * @return constexpr auto vector-like
         */
        template <typename M, typename V>
        constexpr auto mvmul(const M& m, const V& v)
        {
            auto ret = zeros_like(v);

            auto n1 = size(m);
            auto n2 = size(v);
            /* TODO: make assertion optional (?) */
            assert(n1==n2);

            for (size_t i=0; i<n1; i++)
                ret[i] = dot(m[i], v);
            return ret;
        }

    } // namespace detail

    using detail::msmul;
    using detail::mvmul;
    using detail::vsmul;
    using detail::dot;
    using std::fabs;

    /**
     * @brief create zero matrix/vector 
     * 
     * @tparam Array 
     * @param a matrix/vector/arithmetic
     * @return constexpr auto 
     */
    template <typename Array>
    constexpr auto zeros_like(const Array& a)
    {
        /** TODO: proper constraints **/
        static_assert(
            traits::is_array1d_v<Array> ||
            traits::is_array2d_v<Array> ||
            std::is_arithmetic_v<Array>,
            "unsupported type for zeros_like"
        );
        using traits::remove_cvref_t;
        using meta::transform_bounded_array_t;
        using return_t = transform_bounded_array_t<remove_cvref_t<Array>>;
        auto ret = return_t{};
        /* ret is aritmethic type (scalr), return as it is */
        if constexpr (std::is_arithmetic_v<Array>)
            return ret;
        /* ret is conteiner, for each elements call zeros_like */
        else {
            if constexpr (traits::is_resizeable_v<Array>) {
                ret.resize(size(a));
            }
            for (size_t i=0; i<size(a); i++)
                ret[i] = zeros_like(a[i]);
            return ret;
        }
    }

    /**
     * @brief clone matrix/vector 
     * 
     * @tparam Array 
     * @param a matrix/vector/arithmetic
     * @return constexpr auto 
     */
    template <typename Array>
    constexpr auto clone(const Array& a)
    {
        /** TODO: proper constraints **/
        static_assert(
            traits::is_array1d_v<Array> ||
            traits::is_array2d_v<Array> ||
            std::is_arithmetic_v<Array>,
            "unsupported type for zeros_like"
        );
        using traits::remove_cvref_t;
        using meta::transform_bounded_array_t;
        using return_t = transform_bounded_array_t<remove_cvref_t<Array>>;
        auto ret = return_t{};
        /* ret is aritmethic type (scalr), return as it is */
        if constexpr (std::is_arithmetic_v<Array>)
            return a;
        /* ret is conteiner, for each elements call zeros_like */
        else {
            if constexpr (traits::is_resizeable_v<Array>) {
                ret.resize(size(a));
            }
            for (size_t i=0; i<size(a); i++)
                ret[i] = clone(a[i]);
            return ret;
        }
    }

    /**
     * @brief make identity matrix
     * 
     * @tparam Array matrix-like
     * @param a square matrix
     * @return constexpr auto identity matrix
     */
    template <typename Array>
    constexpr auto identity(const Array& a)
    {
        using traits::remove_cvref_t;
        using traits::get_container_value_type_t;
        using traits::is_resizeable_v;
        using traits::is_array2d_v;

        static_assert(
            is_array2d_v<Array>,
            "only support 2D array"
        );

        /* remove cv-ref to make sure we get non const */
        using element_t = remove_cvref_t<get_container_value_type_t<Array>>;
        using value_t = remove_cvref_t<get_container_value_type_t<element_t>>;

        auto ret = zeros_like(a);
        auto n = size(a);
        auto m = size(a[0]);
        assert (m==n);

        if constexpr (is_resizeable_v<Array>)
            ret.resize(n);

        for (size_t i=0; i<n; i++) {
            if constexpr (is_resizeable_v<element_t>)
                ret[i].resize(m);
            ret[i][i] = static_cast<value_t>(1);
        }
        return ret;
    }

    /**
     * @brief max-element
     * 
     * @tparam Array vector-like
     * @param a vector
     * @return constexpr auto 
     */
    template <typename Array>
    constexpr auto max(const Array& a)
    {
        /* only support 1d array for now */
        static_assert(
            traits::is_array1d_v<Array>,
            "unsupported type of array"
        );
        using value_type = typename Array::value_type;
        value_type m = std::numeric_limits<value_type>::min();
        for (const auto e : a)
            if (e > m)
                m = e;
        return m;
    }

    /**
     * @brief elementwise absolute value
     * 
     * @tparam Array matrix-like, vector-like, or arithmetic
     * @param a 
     * @return constexpr auto 
     */
    template <typename Array>
    constexpr auto fabs(const Array& a)
    {
        using traits::is_array1d_v;
        using traits::is_array2d_v;
        using std::is_arithmetic_v;

        static_assert(
            is_array1d_v<Array> ||
            is_array2d_v<Array> ||
            is_arithmetic_v<Array>,
            "unsupported type for fabs"
        );

        /* dispatch if Array is 1d or 2d */
        if constexpr (is_array1d_v<Array> || is_array2d_v<Array>) {
            auto ret = zeros_like(a);
            for (size_t i=0; i<size(a); i++)
                ret[i] = fabs(a[i]);
            return ret;
        }
        /* dispatch if Array is arithmetic type */
        else {
            auto ret = fabs(a);
            return ret;
        }
    }

    /**
     * @brief perform lhs * rhs
     * 
     * @tparam A matrix-like or vector-like
     * @tparam B matrix-like or vector-like or arithmetic type
     * @param lhs 
     * @param rhs 
     * @return constexpr auto 
     */
    template <typename A, typename B>
    constexpr auto mul(const A& lhs, const B& rhs)
    {
        using traits::is_array2d;
        using traits::is_array1d;
        using traits::is_multiplicative_v;
        using std::disjunction_v;
        using std::conjunction_v;
        using std::negation_v;
        using std::is_arithmetic_v;

        static_assert(
            disjunction_v<is_array1d<A>,is_array2d<A>> &&
            disjunction_v<is_array1d<B>,is_array2d<B>,is_arithmetic_v<B>>,
            "unsupported type(s) for mul(lhs,rhs)"
        );

        /* dispatch if A & B is multiplicative */
        if constexpr (is_multiplicative_v<A,B>) {
            return lhs * rhs;
        }
        /* dispatch matrix-matrix multiplication */
        else if (conjunction_v<is_array2d<A>,is_array2d<B>>) {
            /* TODO: implement matmul */
            mmmul(lhs, rhs);
        }
        /* dispatch matrix-vector multiplication */
        else if (conjunction_v<is_array2d<A>,is_array1d<B>>) {
            return mvmul(lhs, rhs);
        }
        /* dispatch matrix-scalar multiplication */
        else if (conjunction_v<is_array2d<A>,is_arithmetic_v<B>>) {
            return msmul(lhs, rhs);
        }
        /* dispatch vector-scalar multiplication */
        else if (conjunction_v<is_array1d<A>,is_arithmetic_v<B>>) {
            return vsmul(lhs, rhs);
        }
        else {
            static_assert(negation_v<std::conjunction<is_array1d<A>,is_array1d<B>>>,
                "vector * vector operation not supported for mul, use dot instead");
        }
    }

} // namespace nmtools::linalg

#endif // NMTOOLS_LINALG_MATVEC_HPP
