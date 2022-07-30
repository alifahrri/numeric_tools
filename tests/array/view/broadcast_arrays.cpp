#if defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
#define NMTOOLS_CAST_ARRAYS_EXTRA(name) \
inline auto name##_cs_fb = nmtools::cast(name, nmtools::array::kind::ndarray_cs_fb); \
inline auto name##_cs_hb = nmtools::cast(name, nmtools::array::kind::ndarray_cs_hb); \
inline auto name##_cs_db = nmtools::cast(name, nmtools::array::kind::ndarray_cs_db); \
inline auto name##_fs_fb = nmtools::cast(name, nmtools::array::kind::ndarray_fs_fb); \
inline auto name##_fs_hb = nmtools::cast(name, nmtools::array::kind::ndarray_fs_hb); \
inline auto name##_fs_db = nmtools::cast(name, nmtools::array::kind::ndarray_fs_db); \
inline auto name##_hs_fb = nmtools::cast(name, nmtools::array::kind::ndarray_hs_fb); \
inline auto name##_hs_hb = nmtools::cast(name, nmtools::array::kind::ndarray_hs_hb); \
inline auto name##_hs_db = nmtools::cast(name, nmtools::array::kind::ndarray_hs_db); \
inline auto name##_ds_fb = nmtools::cast(name, nmtools::array::kind::ndarray_ds_fb); \
inline auto name##_ds_hb = nmtools::cast(name, nmtools::array::kind::ndarray_ds_hb); \
inline auto name##_ds_db = nmtools::cast(name, nmtools::array::kind::ndarray_ds_db);
#endif

#include "nmtools/array/view/broadcast_arrays.hpp"
#include "nmtools/array/ndarray.hpp"

#include "nmtools/testing/doctest.hpp"

#include <vector>
#include <array>

namespace nm = nmtools;
namespace na = nm::array;
namespace view = nm::view;
namespace kind = na::kind;

NMTOOLS_TESTING_DECLARE_CASE(broadcast_arrays)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        int lhs[1][3] = {
            {1,2,3}
        };
        int rhs[2][1] = {
            {4},
            {5}
        };
        NMTOOLS_CAST_ARRAYS(lhs)
        NMTOOLS_CAST_ARRAYS(rhs)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        int lhs[2][3] = {
            {1,2,3},
            {1,2,3},
        };
        int rhs[2][3] = {
            {4,4,4},
            {5,5,5},
        };
        auto shape = nmtools_array{2,3};
        auto expected = nmtools_tuple{cast<int>(lhs),cast<int>(rhs)};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        int lhs[3] = {1,2,3};
        int rhs[2][1] = {
            {4},
            {5}
        };
        NMTOOLS_CAST_ARRAYS(lhs)
        NMTOOLS_CAST_ARRAYS(rhs)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        int lhs[2][3] = {
            {1,2,3},
            {1,2,3},
        };
        int rhs[2][3] = {
            {4,4,4},
            {5,5,5},
        };
        auto shape = nmtools_array{2,3};
        auto expected = nmtools_tuple{cast<int>(lhs),cast<int>(rhs)};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        int lhs[1][3] = {
            {1,2,3}
        };
        int rhs[1][2][1] = {
            {
                {4},
                {5}
            }
        };
        NMTOOLS_CAST_ARRAYS(lhs)
        NMTOOLS_CAST_ARRAYS(rhs)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        int lhs[1][2][3] = {
            {
                {1,2,3},
                {1,2,3},
            }
        };
        int rhs[1][2][3] = {
            {
                {4,4,4},
                {5,5,5},
            }
        };
        auto shape = nmtools_array{1,2,3};
        auto expected = nmtools_tuple{cast<int>(lhs),cast<int>(rhs)};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4)
    {
        int lhs[1][3] = {
            {1,2,3}
        };
        int rhs[2][2][1] = {
            {
                {4},
                {5},
            },
            {
                {6},
                {7},
            },
        };
        NMTOOLS_CAST_ARRAYS(lhs)
        NMTOOLS_CAST_ARRAYS(rhs)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        int lhs[2][2][3] = {
            {
                {1,2,3},
                {1,2,3},
            },
            {
                {1,2,3},
                {1,2,3},
            },
        };
        int rhs[2][2][3] = {
            {
                {4,4,4},
                {5,5,5},
            },
            {
                {6,6,6},
                {7,7,7},
            }
        };
        auto shape = nmtools_array{2,2,3};
        auto expected = nmtools_tuple{cast<int>(lhs),cast<int>(rhs)};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case5)
    {
        int A[1][3] = {
            {1,2,3}
        };
        int B[2][2][1] = {
            {
                {4},
                {5},
            },
            {
                {6},
                {7},
            },
        };
        int C[1][2][3] = {
            {
                { 8, 9,10},
                {11,12,13},
            }
        };
        NMTOOLS_CAST_ARRAYS(A)
        NMTOOLS_CAST_ARRAYS(B)
        NMTOOLS_CAST_ARRAYS(C)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case5)
    {
        int A[2][2][3] = {
            {
                {1,2,3},
                {1,2,3},
            },
            {
                {1,2,3},
                {1,2,3},
            },
        };
        int B[2][2][3] = {
            {
                {4,4,4},
                {5,5,5},
            },
            {
                {6,6,6},
                {7,7,7},
            }
        };
        int C[2][2][3] = {
            {
                { 8, 9,10},
                {11,12,13},
            },
            {
                { 8, 9,10},
                {11,12,13},
            }
        };
        auto shape = nmtools_array{2,2,3};
        auto expected = nmtools_tuple{cast<int>(A),cast<int>(B),cast<int>(C)};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case6)
    {
        int lhs[1][3] = {
            {1,2,3}
        };
        int rhs = 6;
        NMTOOLS_CAST_ARRAYS(lhs)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case6)
    {
        int lhs[1][3] = {
            {1,2,3}
        };
        int rhs[1][3] = {
            {6,6,6}
        };
        auto shape = nmtools_array{1,3};
        auto expected = nmtools_tuple{cast<int>(lhs),cast<int>(rhs)};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case7)
    {
        int lhs = 6;
        int rhs[1][3] = {
            {1,2,3}
        };
        NMTOOLS_CAST_ARRAYS(rhs)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case7)
    {
        int lhs[1][3] = {
            {6,6,6}
        };
        int rhs[1][3] = {
            {1,2,3}
        };
        auto shape = nmtools_array{1,3};
        auto expected = nmtools_tuple{cast<int>(lhs),cast<int>(rhs)};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case8)
    {
        int lhs = 6;
        int rhs = 1;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case8)
    {
        int lhs = 6;
        int rhs = 1;
        auto shape = None;
        auto expected = nmtools_tuple{lhs,rhs};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case9)
    {
        int A = 6;
        int B[2][2][1] = {
            {
                {4},
                {5},
            },
            {
                {6},
                {7},
            },
        };
        int C[1][2][3] = {
            {
                { 8, 9,10},
                {11,12,13},
            }
        };
        NMTOOLS_CAST_ARRAYS(B)
        NMTOOLS_CAST_ARRAYS(C)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case9)
    {
        int A[2][2][3] = {
            {
                {6,6,6},
                {6,6,6},
            },
            {
                {6,6,6},
                {6,6,6},
            },
        };
        int B[2][2][3] = {
            {
                {4,4,4},
                {5,5,5},
            },
            {
                {6,6,6},
                {7,7,7},
            }
        };
        int C[2][2][3] = {
            {
                { 8, 9,10},
                {11,12,13},
            },
            {
                { 8, 9,10},
                {11,12,13},
            }
        };
        auto shape = nmtools_array{2,2,3};
        auto expected = nmtools_tuple{cast<int>(A),cast<int>(B),cast<int>(C)};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case10)
    {
        int A = 1;
        int B = 2;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case10)
    {
        auto shape = None;
        auto expected = nmtools_tuple{1,2};
    }
}

#define RUN_impl(...) \
nm::view::broadcast_arrays(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs broadcast_arrays fn to callable lambda
#define RUN_broadcast_arrays(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("broadcast_arrays-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    const auto fn    = [&](){ \
        return RUN_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_broadcast_arrays(case_name, ...) \
RUN_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define BROADCAST_ARRAYS_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(broadcast_arrays, case_name); \
    using namespace args; \
    const auto results = RUN_broadcast_arrays(case_name, __VA_ARGS__); \
    constexpr auto N = std::tuple_size_v<decltype(results)>; \
    nm::meta::template_for<N>([&](auto index){ \
        constexpr auto i = decltype(index)::value; \
        const auto array       = nmtools::get<i>(results); \
        const auto expected    = nmtools::get<i>(expect::expected); \
        NMTOOLS_ASSERT_EQUAL( array.shape(), expect::shape ); \
        NMTOOLS_ASSERT_CLOSE( array, expected ); \
    }); \
}

TEST_CASE("broadcast_arrays(case1)" * doctest::test_suite("view::broadcast_arrays"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    BROADCAST_ARRAYS_SUBCASE(case1, lhs_a, rhs_a );
    BROADCAST_ARRAYS_SUBCASE(case1, lhs_d, rhs_d );
    BROADCAST_ARRAYS_SUBCASE(case1, lhs_f, rhs_f );
    BROADCAST_ARRAYS_SUBCASE(case1, lhs_h, rhs_h );

    #else
    BROADCAST_ARRAYS_SUBCASE(case1, lhs_cs_fb, rhs_cs_fb );
    BROADCAST_ARRAYS_SUBCASE(case1, lhs_cs_hb, rhs_cs_hb );
    BROADCAST_ARRAYS_SUBCASE(case1, lhs_cs_db, rhs_cs_db );

    BROADCAST_ARRAYS_SUBCASE(case1, lhs_fs_fb, rhs_fs_fb );
    BROADCAST_ARRAYS_SUBCASE(case1, lhs_fs_hb, rhs_fs_hb );
    BROADCAST_ARRAYS_SUBCASE(case1, lhs_fs_db, rhs_fs_db );

    BROADCAST_ARRAYS_SUBCASE(case1, lhs_hs_fb, rhs_hs_fb );
    BROADCAST_ARRAYS_SUBCASE(case1, lhs_hs_hb, rhs_hs_hb );
    BROADCAST_ARRAYS_SUBCASE(case1, lhs_hs_db, rhs_hs_db );

    BROADCAST_ARRAYS_SUBCASE(case1, lhs_ds_fb, rhs_ds_fb );
    BROADCAST_ARRAYS_SUBCASE(case1, lhs_ds_hb, rhs_ds_hb );
    BROADCAST_ARRAYS_SUBCASE(case1, lhs_ds_db, rhs_ds_db );



    BROADCAST_ARRAYS_SUBCASE(case1, lhs_fs_fb, rhs_cs_fb );
    BROADCAST_ARRAYS_SUBCASE(case1, lhs_fs_hb, rhs_cs_hb );
    BROADCAST_ARRAYS_SUBCASE(case1, lhs_fs_db, rhs_cs_db );

    BROADCAST_ARRAYS_SUBCASE(case1, lhs_hs_fb, rhs_cs_fb );
    BROADCAST_ARRAYS_SUBCASE(case1, lhs_hs_hb, rhs_cs_hb );
    BROADCAST_ARRAYS_SUBCASE(case1, lhs_hs_db, rhs_cs_db );

    BROADCAST_ARRAYS_SUBCASE(case1, lhs_ds_fb, rhs_cs_fb );
    BROADCAST_ARRAYS_SUBCASE(case1, lhs_ds_hb, rhs_cs_hb );
    BROADCAST_ARRAYS_SUBCASE(case1, lhs_ds_db, rhs_cs_db );


    BROADCAST_ARRAYS_SUBCASE(case1, lhs_cs_fb, rhs_fs_fb );
    BROADCAST_ARRAYS_SUBCASE(case1, lhs_cs_hb, rhs_fs_hb );
    BROADCAST_ARRAYS_SUBCASE(case1, lhs_cs_db, rhs_fs_db );

    BROADCAST_ARRAYS_SUBCASE(case1, lhs_hs_fb, rhs_fs_fb );
    BROADCAST_ARRAYS_SUBCASE(case1, lhs_hs_hb, rhs_fs_hb );
    BROADCAST_ARRAYS_SUBCASE(case1, lhs_hs_db, rhs_fs_db );

    BROADCAST_ARRAYS_SUBCASE(case1, lhs_ds_fb, rhs_fs_fb );
    BROADCAST_ARRAYS_SUBCASE(case1, lhs_ds_hb, rhs_fs_hb );
    BROADCAST_ARRAYS_SUBCASE(case1, lhs_ds_db, rhs_fs_db );


    BROADCAST_ARRAYS_SUBCASE(case1, lhs_cs_fb, rhs_hs_fb );
    BROADCAST_ARRAYS_SUBCASE(case1, lhs_cs_hb, rhs_hs_hb );
    BROADCAST_ARRAYS_SUBCASE(case1, lhs_cs_db, rhs_hs_db );

    BROADCAST_ARRAYS_SUBCASE(case1, lhs_fs_fb, rhs_hs_fb );
    BROADCAST_ARRAYS_SUBCASE(case1, lhs_fs_hb, rhs_hs_hb );
    BROADCAST_ARRAYS_SUBCASE(case1, lhs_fs_db, rhs_hs_db );

    BROADCAST_ARRAYS_SUBCASE(case1, lhs_ds_fb, rhs_hs_fb );
    BROADCAST_ARRAYS_SUBCASE(case1, lhs_ds_hb, rhs_hs_hb );
    BROADCAST_ARRAYS_SUBCASE(case1, lhs_ds_db, rhs_hs_db );


    BROADCAST_ARRAYS_SUBCASE(case1, lhs_cs_fb, rhs_ds_fb );
    BROADCAST_ARRAYS_SUBCASE(case1, lhs_cs_hb, rhs_ds_hb );
    BROADCAST_ARRAYS_SUBCASE(case1, lhs_cs_db, rhs_ds_db );

    BROADCAST_ARRAYS_SUBCASE(case1, lhs_fs_fb, rhs_ds_fb );
    BROADCAST_ARRAYS_SUBCASE(case1, lhs_fs_hb, rhs_ds_hb );
    BROADCAST_ARRAYS_SUBCASE(case1, lhs_fs_db, rhs_ds_db );

    BROADCAST_ARRAYS_SUBCASE(case1, lhs_hs_fb, rhs_ds_fb );
    BROADCAST_ARRAYS_SUBCASE(case1, lhs_hs_hb, rhs_ds_hb );
    BROADCAST_ARRAYS_SUBCASE(case1, lhs_hs_db, rhs_ds_db );
    #endif
}

TEST_CASE("broadcast_arrays(case2)" * doctest::test_suite("view::broadcast_arrays"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    BROADCAST_ARRAYS_SUBCASE(case2, lhs_a, rhs_a );
    BROADCAST_ARRAYS_SUBCASE(case2, lhs_d, rhs_d );
    BROADCAST_ARRAYS_SUBCASE(case2, lhs_f, rhs_f );
    BROADCAST_ARRAYS_SUBCASE(case2, lhs_h, rhs_h );

    #else
    BROADCAST_ARRAYS_SUBCASE(case2, lhs_cs_fb, rhs_cs_fb );
    BROADCAST_ARRAYS_SUBCASE(case2, lhs_cs_hb, rhs_cs_hb );
    BROADCAST_ARRAYS_SUBCASE(case2, lhs_cs_db, rhs_cs_db );

    BROADCAST_ARRAYS_SUBCASE(case2, lhs_fs_fb, rhs_fs_fb );
    BROADCAST_ARRAYS_SUBCASE(case2, lhs_fs_hb, rhs_fs_hb );
    BROADCAST_ARRAYS_SUBCASE(case2, lhs_fs_db, rhs_fs_db );

    BROADCAST_ARRAYS_SUBCASE(case2, lhs_hs_fb, rhs_hs_fb );
    BROADCAST_ARRAYS_SUBCASE(case2, lhs_hs_hb, rhs_hs_hb );
    BROADCAST_ARRAYS_SUBCASE(case2, lhs_hs_db, rhs_hs_db );

    BROADCAST_ARRAYS_SUBCASE(case2, lhs_ds_fb, rhs_ds_fb );
    BROADCAST_ARRAYS_SUBCASE(case2, lhs_ds_hb, rhs_ds_hb );
    BROADCAST_ARRAYS_SUBCASE(case2, lhs_ds_db, rhs_ds_db );



    BROADCAST_ARRAYS_SUBCASE(case2, lhs_fs_fb, rhs_cs_fb );
    BROADCAST_ARRAYS_SUBCASE(case2, lhs_fs_hb, rhs_cs_hb );
    BROADCAST_ARRAYS_SUBCASE(case2, lhs_fs_db, rhs_cs_db );

    BROADCAST_ARRAYS_SUBCASE(case2, lhs_hs_fb, rhs_cs_fb );
    BROADCAST_ARRAYS_SUBCASE(case2, lhs_hs_hb, rhs_cs_hb );
    BROADCAST_ARRAYS_SUBCASE(case2, lhs_hs_db, rhs_cs_db );

    BROADCAST_ARRAYS_SUBCASE(case2, lhs_ds_fb, rhs_cs_fb );
    BROADCAST_ARRAYS_SUBCASE(case2, lhs_ds_hb, rhs_cs_hb );
    BROADCAST_ARRAYS_SUBCASE(case2, lhs_ds_db, rhs_cs_db );


    BROADCAST_ARRAYS_SUBCASE(case2, lhs_cs_fb, rhs_fs_fb );
    BROADCAST_ARRAYS_SUBCASE(case2, lhs_cs_hb, rhs_fs_hb );
    BROADCAST_ARRAYS_SUBCASE(case2, lhs_cs_db, rhs_fs_db );

    BROADCAST_ARRAYS_SUBCASE(case2, lhs_hs_fb, rhs_fs_fb );
    BROADCAST_ARRAYS_SUBCASE(case2, lhs_hs_hb, rhs_fs_hb );
    BROADCAST_ARRAYS_SUBCASE(case2, lhs_hs_db, rhs_fs_db );

    BROADCAST_ARRAYS_SUBCASE(case2, lhs_ds_fb, rhs_fs_fb );
    BROADCAST_ARRAYS_SUBCASE(case2, lhs_ds_hb, rhs_fs_hb );
    BROADCAST_ARRAYS_SUBCASE(case2, lhs_ds_db, rhs_fs_db );


    BROADCAST_ARRAYS_SUBCASE(case2, lhs_cs_fb, rhs_hs_fb );
    BROADCAST_ARRAYS_SUBCASE(case2, lhs_cs_hb, rhs_hs_hb );
    BROADCAST_ARRAYS_SUBCASE(case2, lhs_cs_db, rhs_hs_db );

    BROADCAST_ARRAYS_SUBCASE(case2, lhs_fs_fb, rhs_hs_fb );
    BROADCAST_ARRAYS_SUBCASE(case2, lhs_fs_hb, rhs_hs_hb );
    BROADCAST_ARRAYS_SUBCASE(case2, lhs_fs_db, rhs_hs_db );

    BROADCAST_ARRAYS_SUBCASE(case2, lhs_ds_fb, rhs_hs_fb );
    BROADCAST_ARRAYS_SUBCASE(case2, lhs_ds_hb, rhs_hs_hb );
    BROADCAST_ARRAYS_SUBCASE(case2, lhs_ds_db, rhs_hs_db );


    BROADCAST_ARRAYS_SUBCASE(case2, lhs_cs_fb, rhs_ds_fb );
    BROADCAST_ARRAYS_SUBCASE(case2, lhs_cs_hb, rhs_ds_hb );
    BROADCAST_ARRAYS_SUBCASE(case2, lhs_cs_db, rhs_ds_db );

    BROADCAST_ARRAYS_SUBCASE(case2, lhs_fs_fb, rhs_ds_fb );
    BROADCAST_ARRAYS_SUBCASE(case2, lhs_fs_hb, rhs_ds_hb );
    BROADCAST_ARRAYS_SUBCASE(case2, lhs_fs_db, rhs_ds_db );

    BROADCAST_ARRAYS_SUBCASE(case2, lhs_hs_fb, rhs_ds_fb );
    BROADCAST_ARRAYS_SUBCASE(case2, lhs_hs_hb, rhs_ds_hb );
    BROADCAST_ARRAYS_SUBCASE(case2, lhs_hs_db, rhs_ds_db );
    #endif
}

TEST_CASE("broadcast_arrays(case3)" * doctest::test_suite("view::broadcast_arrays"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    BROADCAST_ARRAYS_SUBCASE(case3, lhs_a, rhs_a );
    BROADCAST_ARRAYS_SUBCASE(case3, lhs_d, rhs_d );
    BROADCAST_ARRAYS_SUBCASE(case3, lhs_f, rhs_f );
    BROADCAST_ARRAYS_SUBCASE(case3, lhs_h, rhs_h );

    #else
    BROADCAST_ARRAYS_SUBCASE(case3, lhs_cs_fb, rhs_cs_fb );
    BROADCAST_ARRAYS_SUBCASE(case3, lhs_cs_hb, rhs_cs_hb );
    BROADCAST_ARRAYS_SUBCASE(case3, lhs_cs_db, rhs_cs_db );

    BROADCAST_ARRAYS_SUBCASE(case3, lhs_fs_fb, rhs_fs_fb );
    BROADCAST_ARRAYS_SUBCASE(case3, lhs_fs_hb, rhs_fs_hb );
    BROADCAST_ARRAYS_SUBCASE(case3, lhs_fs_db, rhs_fs_db );

    BROADCAST_ARRAYS_SUBCASE(case3, lhs_hs_fb, rhs_hs_fb );
    BROADCAST_ARRAYS_SUBCASE(case3, lhs_hs_hb, rhs_hs_hb );
    BROADCAST_ARRAYS_SUBCASE(case3, lhs_hs_db, rhs_hs_db );

    BROADCAST_ARRAYS_SUBCASE(case3, lhs_ds_fb, rhs_ds_fb );
    BROADCAST_ARRAYS_SUBCASE(case3, lhs_ds_hb, rhs_ds_hb );
    BROADCAST_ARRAYS_SUBCASE(case3, lhs_ds_db, rhs_ds_db );



    BROADCAST_ARRAYS_SUBCASE(case3, lhs_fs_fb, rhs_cs_fb );
    BROADCAST_ARRAYS_SUBCASE(case3, lhs_fs_hb, rhs_cs_hb );
    BROADCAST_ARRAYS_SUBCASE(case3, lhs_fs_db, rhs_cs_db );

    BROADCAST_ARRAYS_SUBCASE(case3, lhs_hs_fb, rhs_cs_fb );
    BROADCAST_ARRAYS_SUBCASE(case3, lhs_hs_hb, rhs_cs_hb );
    BROADCAST_ARRAYS_SUBCASE(case3, lhs_hs_db, rhs_cs_db );

    BROADCAST_ARRAYS_SUBCASE(case3, lhs_ds_fb, rhs_cs_fb );
    BROADCAST_ARRAYS_SUBCASE(case3, lhs_ds_hb, rhs_cs_hb );
    BROADCAST_ARRAYS_SUBCASE(case3, lhs_ds_db, rhs_cs_db );


    BROADCAST_ARRAYS_SUBCASE(case3, lhs_cs_fb, rhs_fs_fb );
    BROADCAST_ARRAYS_SUBCASE(case3, lhs_cs_hb, rhs_fs_hb );
    BROADCAST_ARRAYS_SUBCASE(case3, lhs_cs_db, rhs_fs_db );

    BROADCAST_ARRAYS_SUBCASE(case3, lhs_hs_fb, rhs_fs_fb );
    BROADCAST_ARRAYS_SUBCASE(case3, lhs_hs_hb, rhs_fs_hb );
    BROADCAST_ARRAYS_SUBCASE(case3, lhs_hs_db, rhs_fs_db );

    BROADCAST_ARRAYS_SUBCASE(case3, lhs_ds_fb, rhs_fs_fb );
    BROADCAST_ARRAYS_SUBCASE(case3, lhs_ds_hb, rhs_fs_hb );
    BROADCAST_ARRAYS_SUBCASE(case3, lhs_ds_db, rhs_fs_db );


    BROADCAST_ARRAYS_SUBCASE(case3, lhs_cs_fb, rhs_hs_fb );
    BROADCAST_ARRAYS_SUBCASE(case3, lhs_cs_hb, rhs_hs_hb );
    BROADCAST_ARRAYS_SUBCASE(case3, lhs_cs_db, rhs_hs_db );

    BROADCAST_ARRAYS_SUBCASE(case3, lhs_fs_fb, rhs_hs_fb );
    BROADCAST_ARRAYS_SUBCASE(case3, lhs_fs_hb, rhs_hs_hb );
    BROADCAST_ARRAYS_SUBCASE(case3, lhs_fs_db, rhs_hs_db );

    BROADCAST_ARRAYS_SUBCASE(case3, lhs_ds_fb, rhs_hs_fb );
    BROADCAST_ARRAYS_SUBCASE(case3, lhs_ds_hb, rhs_hs_hb );
    BROADCAST_ARRAYS_SUBCASE(case3, lhs_ds_db, rhs_hs_db );


    BROADCAST_ARRAYS_SUBCASE(case3, lhs_cs_fb, rhs_ds_fb );
    BROADCAST_ARRAYS_SUBCASE(case3, lhs_cs_hb, rhs_ds_hb );
    BROADCAST_ARRAYS_SUBCASE(case3, lhs_cs_db, rhs_ds_db );

    BROADCAST_ARRAYS_SUBCASE(case3, lhs_fs_fb, rhs_ds_fb );
    BROADCAST_ARRAYS_SUBCASE(case3, lhs_fs_hb, rhs_ds_hb );
    BROADCAST_ARRAYS_SUBCASE(case3, lhs_fs_db, rhs_ds_db );

    BROADCAST_ARRAYS_SUBCASE(case3, lhs_hs_fb, rhs_ds_fb );
    BROADCAST_ARRAYS_SUBCASE(case3, lhs_hs_hb, rhs_ds_hb );
    BROADCAST_ARRAYS_SUBCASE(case3, lhs_hs_db, rhs_ds_db );
    #endif
}

TEST_CASE("broadcast_arrays(case4)" * doctest::test_suite("view::broadcast_arrays"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    BROADCAST_ARRAYS_SUBCASE(case4, lhs_a, rhs_a );
    BROADCAST_ARRAYS_SUBCASE(case4, lhs_d, rhs_d );
    BROADCAST_ARRAYS_SUBCASE(case4, lhs_f, rhs_f );
    BROADCAST_ARRAYS_SUBCASE(case4, lhs_h, rhs_h );

    #else
    BROADCAST_ARRAYS_SUBCASE(case4, lhs_cs_fb, rhs_cs_fb );
    BROADCAST_ARRAYS_SUBCASE(case4, lhs_cs_hb, rhs_cs_hb );
    BROADCAST_ARRAYS_SUBCASE(case4, lhs_cs_db, rhs_cs_db );

    BROADCAST_ARRAYS_SUBCASE(case4, lhs_fs_fb, rhs_fs_fb );
    BROADCAST_ARRAYS_SUBCASE(case4, lhs_fs_hb, rhs_fs_hb );
    BROADCAST_ARRAYS_SUBCASE(case4, lhs_fs_db, rhs_fs_db );

    BROADCAST_ARRAYS_SUBCASE(case4, lhs_hs_fb, rhs_hs_fb );
    BROADCAST_ARRAYS_SUBCASE(case4, lhs_hs_hb, rhs_hs_hb );
    BROADCAST_ARRAYS_SUBCASE(case4, lhs_hs_db, rhs_hs_db );

    BROADCAST_ARRAYS_SUBCASE(case4, lhs_ds_fb, rhs_ds_fb );
    BROADCAST_ARRAYS_SUBCASE(case4, lhs_ds_hb, rhs_ds_hb );
    BROADCAST_ARRAYS_SUBCASE(case4, lhs_ds_db, rhs_ds_db );



    BROADCAST_ARRAYS_SUBCASE(case4, lhs_fs_fb, rhs_cs_fb );
    BROADCAST_ARRAYS_SUBCASE(case4, lhs_fs_hb, rhs_cs_hb );
    BROADCAST_ARRAYS_SUBCASE(case4, lhs_fs_db, rhs_cs_db );

    BROADCAST_ARRAYS_SUBCASE(case4, lhs_hs_fb, rhs_cs_fb );
    BROADCAST_ARRAYS_SUBCASE(case4, lhs_hs_hb, rhs_cs_hb );
    BROADCAST_ARRAYS_SUBCASE(case4, lhs_hs_db, rhs_cs_db );

    BROADCAST_ARRAYS_SUBCASE(case4, lhs_ds_fb, rhs_cs_fb );
    BROADCAST_ARRAYS_SUBCASE(case4, lhs_ds_hb, rhs_cs_hb );
    BROADCAST_ARRAYS_SUBCASE(case4, lhs_ds_db, rhs_cs_db );


    BROADCAST_ARRAYS_SUBCASE(case4, lhs_cs_fb, rhs_fs_fb );
    BROADCAST_ARRAYS_SUBCASE(case4, lhs_cs_hb, rhs_fs_hb );
    BROADCAST_ARRAYS_SUBCASE(case4, lhs_cs_db, rhs_fs_db );

    BROADCAST_ARRAYS_SUBCASE(case4, lhs_hs_fb, rhs_fs_fb );
    BROADCAST_ARRAYS_SUBCASE(case4, lhs_hs_hb, rhs_fs_hb );
    BROADCAST_ARRAYS_SUBCASE(case4, lhs_hs_db, rhs_fs_db );

    BROADCAST_ARRAYS_SUBCASE(case4, lhs_ds_fb, rhs_fs_fb );
    BROADCAST_ARRAYS_SUBCASE(case4, lhs_ds_hb, rhs_fs_hb );
    BROADCAST_ARRAYS_SUBCASE(case4, lhs_ds_db, rhs_fs_db );


    BROADCAST_ARRAYS_SUBCASE(case4, lhs_cs_fb, rhs_hs_fb );
    BROADCAST_ARRAYS_SUBCASE(case4, lhs_cs_hb, rhs_hs_hb );
    BROADCAST_ARRAYS_SUBCASE(case4, lhs_cs_db, rhs_hs_db );

    BROADCAST_ARRAYS_SUBCASE(case4, lhs_fs_fb, rhs_hs_fb );
    BROADCAST_ARRAYS_SUBCASE(case4, lhs_fs_hb, rhs_hs_hb );
    BROADCAST_ARRAYS_SUBCASE(case4, lhs_fs_db, rhs_hs_db );

    BROADCAST_ARRAYS_SUBCASE(case4, lhs_ds_fb, rhs_hs_fb );
    BROADCAST_ARRAYS_SUBCASE(case4, lhs_ds_hb, rhs_hs_hb );
    BROADCAST_ARRAYS_SUBCASE(case4, lhs_ds_db, rhs_hs_db );


    BROADCAST_ARRAYS_SUBCASE(case4, lhs_cs_fb, rhs_ds_fb );
    BROADCAST_ARRAYS_SUBCASE(case4, lhs_cs_hb, rhs_ds_hb );
    BROADCAST_ARRAYS_SUBCASE(case4, lhs_cs_db, rhs_ds_db );

    BROADCAST_ARRAYS_SUBCASE(case4, lhs_fs_fb, rhs_ds_fb );
    BROADCAST_ARRAYS_SUBCASE(case4, lhs_fs_hb, rhs_ds_hb );
    BROADCAST_ARRAYS_SUBCASE(case4, lhs_fs_db, rhs_ds_db );

    BROADCAST_ARRAYS_SUBCASE(case4, lhs_hs_fb, rhs_ds_fb );
    BROADCAST_ARRAYS_SUBCASE(case4, lhs_hs_hb, rhs_ds_hb );
    BROADCAST_ARRAYS_SUBCASE(case4, lhs_hs_db, rhs_ds_db );
    #endif
}

TEST_CASE("broadcast_arrays(case5)" * doctest::test_suite("view::broadcast_arrays"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    BROADCAST_ARRAYS_SUBCASE(case5, A_a, B_a, C_a );
    BROADCAST_ARRAYS_SUBCASE(case5, A_d, B_d, C_d );
    BROADCAST_ARRAYS_SUBCASE(case5, A_f, B_f, C_f );
    BROADCAST_ARRAYS_SUBCASE(case5, A_h, B_h, C_h );

    #else
    BROADCAST_ARRAYS_SUBCASE(case5, A_cs_fb, B_cs_fb, C_cs_fb );
    BROADCAST_ARRAYS_SUBCASE(case5, A_cs_hb, B_cs_hb, C_cs_hb );
    BROADCAST_ARRAYS_SUBCASE(case5, A_cs_db, B_cs_db, C_cs_db );

    BROADCAST_ARRAYS_SUBCASE(case5, A_fs_fb, B_fs_fb, C_fs_fb );
    BROADCAST_ARRAYS_SUBCASE(case5, A_fs_hb, B_fs_hb, C_fs_hb );
    BROADCAST_ARRAYS_SUBCASE(case5, A_fs_db, B_fs_db, C_fs_db );

    BROADCAST_ARRAYS_SUBCASE(case5, A_hs_fb, B_hs_fb, C_hs_fb );
    BROADCAST_ARRAYS_SUBCASE(case5, A_hs_hb, B_hs_hb, C_hs_hb );
    BROADCAST_ARRAYS_SUBCASE(case5, A_hs_db, B_hs_db, C_hs_db );

    BROADCAST_ARRAYS_SUBCASE(case5, A_ds_fb, B_ds_fb, C_ds_fb );
    BROADCAST_ARRAYS_SUBCASE(case5, A_ds_hb, B_ds_hb, C_ds_hb );
    BROADCAST_ARRAYS_SUBCASE(case5, A_ds_db, B_ds_db, C_ds_db );

    BROADCAST_ARRAYS_SUBCASE(case5, A_fs_fb, B_cs_fb, C_cs_fb );
    BROADCAST_ARRAYS_SUBCASE(case5, A_fs_hb, B_cs_hb, C_cs_hb );
    BROADCAST_ARRAYS_SUBCASE(case5, A_fs_db, B_cs_db, C_cs_db );

    BROADCAST_ARRAYS_SUBCASE(case5, A_hs_fb, B_cs_fb, C_cs_fb );
    BROADCAST_ARRAYS_SUBCASE(case5, A_hs_hb, B_cs_hb, C_cs_hb );
    BROADCAST_ARRAYS_SUBCASE(case5, A_hs_db, B_cs_db, C_cs_db );

    BROADCAST_ARRAYS_SUBCASE(case5, A_ds_fb, B_cs_fb, C_cs_fb );
    BROADCAST_ARRAYS_SUBCASE(case5, A_ds_hb, B_cs_hb, C_cs_hb );
    BROADCAST_ARRAYS_SUBCASE(case5, A_ds_db, B_cs_db, C_cs_db );

    BROADCAST_ARRAYS_SUBCASE(case5, A_cs_fb, B_fs_fb, C_cs_fb );
    BROADCAST_ARRAYS_SUBCASE(case5, A_cs_hb, B_fs_hb, C_cs_hb );
    BROADCAST_ARRAYS_SUBCASE(case5, A_cs_db, B_fs_db, C_cs_db );

    BROADCAST_ARRAYS_SUBCASE(case5, A_cs_fb, B_hs_fb, C_cs_fb );
    BROADCAST_ARRAYS_SUBCASE(case5, A_cs_hb, B_hs_hb, C_cs_hb );
    BROADCAST_ARRAYS_SUBCASE(case5, A_cs_db, B_hs_db, C_cs_db );

    BROADCAST_ARRAYS_SUBCASE(case5, A_cs_fb, B_ds_fb, C_cs_fb );
    BROADCAST_ARRAYS_SUBCASE(case5, A_cs_hb, B_ds_hb, C_cs_hb );
    BROADCAST_ARRAYS_SUBCASE(case5, A_cs_db, B_ds_db, C_cs_db );

    BROADCAST_ARRAYS_SUBCASE(case5, A_cs_fb, B_cs_fb, C_fs_fb );
    BROADCAST_ARRAYS_SUBCASE(case5, A_cs_hb, B_cs_hb, C_fs_hb );
    BROADCAST_ARRAYS_SUBCASE(case5, A_cs_db, B_cs_db, C_fs_db );

    BROADCAST_ARRAYS_SUBCASE(case5, A_fs_fb, B_fs_fb, C_cs_fb );
    BROADCAST_ARRAYS_SUBCASE(case5, A_fs_hb, B_fs_hb, C_cs_hb );
    BROADCAST_ARRAYS_SUBCASE(case5, A_fs_db, B_fs_db, C_cs_db );

    BROADCAST_ARRAYS_SUBCASE(case5, A_hs_fb, B_hs_fb, C_cs_fb );
    BROADCAST_ARRAYS_SUBCASE(case5, A_hs_hb, B_hs_hb, C_cs_hb );
    BROADCAST_ARRAYS_SUBCASE(case5, A_hs_db, B_hs_db, C_cs_db );

    BROADCAST_ARRAYS_SUBCASE(case5, A_ds_fb, B_ds_fb, C_cs_fb );
    BROADCAST_ARRAYS_SUBCASE(case5, A_ds_hb, B_ds_hb, C_cs_hb );
    BROADCAST_ARRAYS_SUBCASE(case5, A_ds_db, B_ds_db, C_cs_db );
    #endif
}

TEST_CASE("broadcast_arrays(case6)" * doctest::test_suite("view::broadcast_arrays"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    BROADCAST_ARRAYS_SUBCASE(case6, lhs_a, rhs );
    BROADCAST_ARRAYS_SUBCASE(case6, lhs_d, rhs );
    BROADCAST_ARRAYS_SUBCASE(case6, lhs_f, rhs );
    BROADCAST_ARRAYS_SUBCASE(case6, lhs_h, rhs );

    #else
    BROADCAST_ARRAYS_SUBCASE(case6, lhs_cs_fb, rhs );
    BROADCAST_ARRAYS_SUBCASE(case6, lhs_cs_hb, rhs );
    BROADCAST_ARRAYS_SUBCASE(case6, lhs_cs_db, rhs );

    BROADCAST_ARRAYS_SUBCASE(case6, lhs_fs_fb, rhs );
    BROADCAST_ARRAYS_SUBCASE(case6, lhs_fs_hb, rhs );
    BROADCAST_ARRAYS_SUBCASE(case6, lhs_fs_db, rhs );

    BROADCAST_ARRAYS_SUBCASE(case6, lhs_hs_fb, rhs );
    BROADCAST_ARRAYS_SUBCASE(case6, lhs_hs_hb, rhs );
    BROADCAST_ARRAYS_SUBCASE(case6, lhs_hs_db, rhs );

    BROADCAST_ARRAYS_SUBCASE(case6, lhs_ds_fb, rhs );
    BROADCAST_ARRAYS_SUBCASE(case6, lhs_ds_hb, rhs );
    BROADCAST_ARRAYS_SUBCASE(case6, lhs_ds_db, rhs );
    #endif
}

TEST_CASE("broadcast_arrays(case7)" * doctest::test_suite("view::broadcast_arrays"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    BROADCAST_ARRAYS_SUBCASE(case7, lhs, rhs_a );
    BROADCAST_ARRAYS_SUBCASE(case7, lhs, rhs_d );
    BROADCAST_ARRAYS_SUBCASE(case7, lhs, rhs_f );
    BROADCAST_ARRAYS_SUBCASE(case7, lhs, rhs_h );

    #else
    BROADCAST_ARRAYS_SUBCASE(case7, lhs, rhs_cs_fb );
    BROADCAST_ARRAYS_SUBCASE(case7, lhs, rhs_cs_hb );
    BROADCAST_ARRAYS_SUBCASE(case7, lhs, rhs_cs_db );

    BROADCAST_ARRAYS_SUBCASE(case7, lhs, rhs_fs_fb );
    BROADCAST_ARRAYS_SUBCASE(case7, lhs, rhs_fs_hb );
    BROADCAST_ARRAYS_SUBCASE(case7, lhs, rhs_fs_db );

    BROADCAST_ARRAYS_SUBCASE(case7, lhs, rhs_hs_fb );
    BROADCAST_ARRAYS_SUBCASE(case7, lhs, rhs_hs_hb );
    BROADCAST_ARRAYS_SUBCASE(case7, lhs, rhs_hs_db );

    BROADCAST_ARRAYS_SUBCASE(case7, lhs, rhs_ds_fb );
    BROADCAST_ARRAYS_SUBCASE(case7, lhs, rhs_ds_hb );
    BROADCAST_ARRAYS_SUBCASE(case7, lhs, rhs_ds_db );
    #endif
}

TEST_CASE("broadcast_arrays(case8)" * doctest::test_suite("view::broadcast_arrays"))
{
    BROADCAST_ARRAYS_SUBCASE(case8, lhs, rhs);
}

TEST_CASE("broadcast_arrays(case9)" * doctest::test_suite("view::broadcast_arrays"))
{
    BROADCAST_ARRAYS_SUBCASE(case9, A, B_a, C_a );
    BROADCAST_ARRAYS_SUBCASE(case9, A, B_d, C_d );
    BROADCAST_ARRAYS_SUBCASE(case9, A, B_f, C_f );
    BROADCAST_ARRAYS_SUBCASE(case9, A, B_h, C_h );
}

TEST_CASE("broadcast_arrays(case10)" * doctest::test_suite("view::broadcast_arrays"))
{
    BROADCAST_ARRAYS_SUBCASE(case10, A, B);
}

TEST_CASE("broadcast_arrays(fixed_shape)" * doctest::test_suite("view::broadcast_arrays"))
{
    namespace meta = nmtools::meta;
    SUBCASE("raw")
    {
        int A[1][3] = {{1,2,3}};
        int B[3][1] = {{4},{5},{6}};
        const auto [bA, bB] = RUN_broadcast_arrays(fixed_shape, A, B);
        using bA_t = decltype(bA);
        using bB_t = decltype(bB);
        NMTOOLS_STATIC_CHECK( meta::is_fixed_shape_v<bA_t> );
        NMTOOLS_STATIC_CHECK( meta::is_fixed_shape_v<bB_t> );
        constexpr auto expected_shape = nmtools_array{3,3};
        NMTOOLS_STATIC_CHECK(( isequal(meta::fixed_shape_v<bA_t>, expected_shape) ));
        NMTOOLS_STATIC_CHECK(( isequal(meta::fixed_shape_v<bB_t>, expected_shape) ));
    }
    SUBCASE("array")
    {
        auto A = nmtools_array{1,2,3};
        auto B = nmtools_array{nmtools_array{4,5,6}};
        const auto [bA, bB] = RUN_broadcast_arrays(fixed_shape, A, B);
        using bA_t = decltype(bA);
        using bB_t = decltype(bB);
        NMTOOLS_STATIC_CHECK( meta::is_fixed_shape_v<bA_t> );
        NMTOOLS_STATIC_CHECK( meta::is_fixed_shape_v<bB_t> );
        constexpr auto expected_shape = nmtools_array{3};
        NMTOOLS_STATIC_CHECK(( isequal(meta::fixed_shape_v<bA_t>, expected_shape) ));
        NMTOOLS_STATIC_CHECK(( isequal(meta::fixed_shape_v<bB_t>, expected_shape) ));
    }
    SUBCASE("fixed_ndarray")
    {
        auto A = na::fixed_ndarray{{1,2,3}};
        auto B = na::fixed_ndarray{{{1,2,3},{4,5,6}}};
        const auto [bA, bB] = RUN_broadcast_arrays(fixed_shape, A, B);
        using bA_t = decltype(bA);
        using bB_t = decltype(bB);
        NMTOOLS_STATIC_CHECK( meta::is_fixed_shape_v<bA_t> );
        NMTOOLS_STATIC_CHECK( meta::is_fixed_shape_v<bB_t> );
        constexpr auto expected_shape = nmtools_array{2,3};
        NMTOOLS_STATIC_CHECK(( isequal(meta::fixed_shape_v<bA_t>, expected_shape) ));
        NMTOOLS_STATIC_CHECK(( isequal(meta::fixed_shape_v<bB_t>, expected_shape) ));
    }
}

NMTOOLS_TESTING_DECLARE_CASE(broadcast_arrays_constexpr)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        constexpr int A[1][3] = {
            {1,2,3}
        };
        constexpr int B[2][2][1] = {
            {
                {4},
                {5},
            },
            {
                {6},
                {7},
            },
        };
        constexpr int C[1][2][3] = {
            {
                { 8, 9,10},
                {11,12,13},
            }
        };
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        constexpr int A[2][2][3] = {
            {
                {1,2,3},
                {1,2,3},
            },
            {
                {1,2,3},
                {1,2,3},
            },
        };
        constexpr int B[2][2][3] = {
            {
                {4,4,4},
                {5,5,5},
            },
            {
                {6,6,6},
                {7,7,7},
            }
        };
        constexpr int C[2][2][3] = {
            {
                { 8, 9,10},
                {11,12,13},
            },
            {
                { 8, 9,10},
                {11,12,13},
            }
        };
    }
}

#include "nmtools/array/eval.hpp"

template <typename output_t, typename first_t, typename second_t, typename third_t>
constexpr auto eval_broadcast_arrays(const first_t& A, const second_t& B, const third_t& C)
{
    const auto [a,b,c] = view::broadcast_arrays(A,B,C);

    auto out_t = nm::meta::as_value<output_t>{};
    auto aout = na::eval(a,nm::None,out_t);
    auto bout = na::eval(b,nm::None,out_t);
    auto cout = na::eval(c,nm::None,out_t);

    return nmtools_tuple{aout,bout,cout};
} // eval_broadcast_arrays

// skip constexpr test for emscripten for now, works for gcc & clang
#if NMTOOLS_TESTING_HAS_CONSTEXPR_MATH
TEST_CASE("broadcast_arrays(constexpr)" * doctest::test_suite("view::broadcast_arrays"))
{
    NMTOOLS_TESTING_DECLARE_NS(broadcast_arrays_constexpr, case1);
    using output_t = int[2][2][3];
    constexpr auto broadcasted = eval_broadcast_arrays<output_t>(args::A,args::B,args::C);
    constexpr auto A = nmtools::get<0>(broadcasted);
    constexpr auto B = nmtools::get<1>(broadcasted);
    constexpr auto C = nmtools::get<2>(broadcasted);
    NMTOOLS_STATIC_ASSERT_CLOSE( A, expect::A );
    NMTOOLS_STATIC_ASSERT_CLOSE( B, expect::B );
    NMTOOLS_STATIC_ASSERT_CLOSE( C, expect::C );
}
#endif