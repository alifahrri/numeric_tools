#ifndef NMTOOLS_LINALG_DECOMPOSITION_HPP
#define NMTOOLS_LINALG_DECOMPOSITION_HPP

#include "nmtools/traits.hpp"
#include "nmtools/linalg/elimination.hpp"

namespace nmtools::linalg
{
    using std::size;

    /**
     * @brief perform LU decomposition on matrix A
     * 
     * @tparam Matrix matrix-like
     * @param A matrix to decompose
     * @return constexpr auto [L,U]
     * @cite chapra2014numerical_lu_decomposition
     */
    template <typename Matrix>
    constexpr auto lu_decomposition(const Matrix& A)
    {
        static_assert(
            traits::is_array2d_v<Matrix>,
            "unsupported type for Matrix"
        );

        using elim_t = elimination_tag::elimination_keep_lower_mat_t;

        /* TODO : check if matrix A is square */
        auto n = size(A);

        /* TODO: make forward elimination skip rhs computation */
        auto b = zeros_like(A[0]);
        auto [U,_] = forward_elimination<elim_t>(A,b);

        /* placeholder for L */
        auto L = identity(A);

        /* for each lower matrix entry (1,0), (2,0), (2,1) ... 
            swap elemnts between L and U */
        for (size_t i=0; i<(n-1); i++) {
            for (size_t j=i+1; j<n; j++) {
                L[j][i] = U[j][i];
                U[j][i] = 0;
            }
        }
        return std::make_tuple(L,U);
    }

    /**
     * @brief perform forward substitution
     * given matrix L and vector b, calculate augmented vector d
     * to compute backward substitution
     * 
     * @tparam Matrix matrix-like
     * @tparam Vector vector-like
     * @param L lower tridiagonal matrix
     * @param b right hand side
     * @return constexpr auto augmented vector d
     * @cite chapra2014numerical_lu_decomposition
     */
    template <typename Matrix, typename Vector>
    constexpr auto substitution(const Matrix &L, const Vector& b)
    {
        static_assert(
            traits::is_array2d_v<Matrix>,
            "unsupported type for Matrix L"
        );
        static_assert(
            traits::is_array1d_v<Vector>,
            "unsupported type for Vector b"
        );

        /* placeholder for results */
        auto d = zeros_like(b);

        /* TODO: check if matrix L is square and is indeed lower triangular */
        auto n = size(b);

        /* perform forward substitution */
        d[0] = b[0];
        for (size_t i=1; i<n; i++) {
            auto sum = b[i];
            for (size_t j=0; j<i; j++)
                sum -= L[i][j] * b[j];
            d[i] = sum;
        }

        return d;
    }

    /**
     * @brief calculate inverse of matrix A
     * 
     * @tparam Matrix matrix-like
     * @param A 
     * @return constexpr auto inverse of A
     * @cite chapra2014numerical_matrix_inverse
     */
    template <typename Matrix>
    constexpr auto inverse(const Matrix& A)
    {
        static_assert(
            traits::is_array2d_v<Matrix>,
            "unsupported type of Matrix A"
        );
        
        auto [L,U] = lu_decomposition(A);

        /* TODO: check if matrix A is square */
        auto n = size(A);

        /* placeholder for results */
        auto I = zeros_like(A);

        /* for each column, solve corresponding column in identity matrix
            using forward and backward substitution */
        for (size_t i=0; i<n; i++) {

            /* create corresponding column in identity matrix */
            auto b = zeros_like(A[0]);
            b[i] = 1;

            /* forward substitution */
            auto d = substitution(L, b);

            /* backward substitution to get column-matrix */
            auto x = backward_substitution(U, d);

            /* fill column of inv placeholder with x */
            for (size_t j=0; j<n; j++)
                I[j][i] = x[j];
        }

        return I;
    }

    template <typename T>
    using get_value_type_t = traits::get_container_value_type_t<T>;

    /**
     * @brief perform cholesky decomposition on symmetric matrix
     * 
     * @tparam Matrix matrix-like
     * @param A symmetric matrix
     * @return constexpr auto matrix L, where A = LL^{T}
     * @cite chapra2014numerical_cholesky_decomposition
     */
    template <typename Matrix>
    constexpr auto cholesky_decomposition(const Matrix& A)
    {
        static_assert(
            traits::is_array2d_v<Matrix>,
            "unsupported type of Matrix A"
        );
        using traits::remove_cvref_t;
        using value_t = remove_cvref_t<get_value_type_t<get_value_type_t<Matrix>>>;

        /* TODO: check if matrix A is symmetric */
        auto n = size(A);

        /* placeholder for results */
        auto L = zeros_like(A);

        /* traverse row */
        for (int k=0; k<n; k++) {
            /* traverse column, note that this doesn't traverse full column */
            for (int i=0; i<k; i++) {
                value_t sum{0};
                for (int j=0; j<i; j++)
                    sum += L[i][j] * L[k][j];
                /* set column i of row k */
                L[k][i] = (A[k][i] - sum) / L[i][i];
            }
            /* sum of squared elements at row k from column 0 to k-1 */
            value_t sum{0};
            for (int j=0; j<k; j++)
                sum += L[k][j] * L[k][j];
            /* compute diagonal entry */
            L[k][k] = sqrt(A[k][k] - sum);
        }

        return L;
    }
} // namespace nmtools::linalg

#endif // NMTOOLS_LINALG_DECOMPOSITION_HPP