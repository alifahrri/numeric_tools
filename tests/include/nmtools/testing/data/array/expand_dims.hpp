#ifndef NMTOOLS_TESTING_DATA_ARRAY_EXPAND_DIMS_HPP
#define NMTOOLS_TESTING_DATA_ARRAY_EXPAND_DIMS_HPP

#include "nmtools/array/fixed.hpp"
#include "nmtools/array/dynamic.hpp"
#include "nmtools/testing/testing.hpp"

#include <array>
#include <tuple>
#include <vector>

namespace nm = nmtools;
namespace na = nm::array;
namespace meta = nm::meta;
namespace kind = na::kind;

#ifndef PLATFORMIO
#define CAST_ARRAYS(name) \
inline auto name##_a = cast(name, kind::nested_arr); \
inline auto name##_v = cast(name, kind::nested_vec); \
inline auto name##_f = cast(name, kind::fixed); \
inline auto name##_d = cast(name, kind::dynamic); \
inline auto name##_h = cast(name, kind::hybrid);
#else
#define CAST_ARRAYS(name) \
inline auto name##_a = cast(name, kind::nested_arr); \
inline auto name##_f = cast(name, kind::fixed); \
inline auto name##_h = cast(name, kind::hybrid);
#endif // PLATFORMIO

NMTOOLS_TESTING_DECLARE_CASE(expand_dims)
{
    // (6) -> (1x6)
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        inline double array[6] = {1,2,3,4,5,6};
        inline int axis[1]  = {0};
        CAST_ARRAYS(array);
        CAST_ARRAYS(axis);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        inline int shape[2] = {1,6};
        inline double expected[1][6] = {{1,2,3,4,5,6}};
    }

    // (6) -> (1x6)
    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        inline double array[6] = {1,2,3,4,5,6};
        inline int axis     = 0;
        CAST_ARRAYS(array);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        inline int shape[2] = {1,6};
        inline double expected[1][6] = {{1,2,3,4,5,6}};
    }

    // (6) -> (6x1)
    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        inline double array[6] = {1,2,3,4,5,6};
        inline int axis     = 1;
        CAST_ARRAYS(array);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        inline int shape[2] = {6,1};
        inline double expected[6][1] = {{1},{2},{3},{4},{5},{6}};
    }

    // (6) -> (1x1x6)
    NMTOOLS_TESTING_DECLARE_ARGS(case4)
    {
        inline double array[6] = {1,2,3,4,5,6};
        inline int axis[2]  = {0,1};
        CAST_ARRAYS(array);
        CAST_ARRAYS(axis);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        inline int shape[3] = {1,1,6};
        inline double expected[1][1][6] = {
            {
                {1,2,3,4,5,6}
            }
        };
    }

    // (6) -> (1x6x1)
    NMTOOLS_TESTING_DECLARE_ARGS(case5)
    {
        inline double array[6] = {1,2,3,4,5,6};
        inline int axis[2]  = {0,2};
        CAST_ARRAYS(array);
        CAST_ARRAYS(axis);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case5)
    {
        inline int shape[3] = {1,6,1};
        inline double expected[1][6][1] = {
            {
                {1},{2},{3},{4},{5},{6}
            }
        };
    }

    // (3x2) -> (1x3x2)
    NMTOOLS_TESTING_DECLARE_ARGS(case6)
    {
        inline double array[3][2] = {
            {1,2},
            {3,4},
            {5,6}
        };
        inline int axis = 0;
        CAST_ARRAYS(array);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case6)
    {
        inline int shape[3] = {1,3,2};
        inline double expected[1][3][2] = {
            {
                {1,2},
                {3,4},
                {5,6}
            }
        };
    }

    // (3x2) -> (3x1x2)
    NMTOOLS_TESTING_DECLARE_ARGS(case7)
    {
        inline double array[3][2] = {
            {1,2},
            {3,4},
            {5,6}
        };
        inline int axis = 1;
        CAST_ARRAYS(array);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case7)
    {
        inline int shape[3] = {3,1,2};
        inline double expected[3][1][2] = {
            {
                {1,2},
            },
            {
                {3,4},
            },
            {
                {5,6}
            }
        };
    }

    // (3x2) -> (3x2x1)
    NMTOOLS_TESTING_DECLARE_ARGS(case8)
    {
        inline double array[3][2] = {
            {1,2},
            {3,4},
            {5,6}
        };
        inline int axis = 2;
        CAST_ARRAYS(array);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case8)
    {
        inline int shape[3] = {3,2,1};
        inline double expected[3][2][1] = {
            {
                {1},
                {2}
            },
            {
                {3},
                {4}
            },
            {
                {5},
                {6}
            }
        };
    }

    // (3x1x2) -> (1x3x1x2)
    NMTOOLS_TESTING_DECLARE_ARGS(case9)
    {
        inline double array[3][1][2] = {
            {
                {1,2},
            },
            {
                {3,4},
            },
            {
                {5,6}
            }
        };
        inline int axis = 0;
        CAST_ARRAYS(array);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case9)
    {
        inline int shape[4] = {1,3,1,2};
        inline double expected[1][3][1][2] = {{
            {
                {1,2},
            },
            {
                {3,4},
            },
            {
                {5,6}
            }
        }};
    }

    // (3x1x1x2) -> (1x3x1x1x2x1)
    NMTOOLS_TESTING_DECLARE_ARGS(case10)
    {
        inline double array[3][1][1][2] = {
            {
                {
                    {1,2},
                }
            },
            {
                {
                    {3,4},
                }
            },
            {
                {
                    {5,6}
                }
            }
        };
        inline int axis[2] = {0,5};
        CAST_ARRAYS(array);
        CAST_ARRAYS(axis);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case10)
    {
        inline int shape[6] = {1,3,1,1,2,1};
        inline double expected[1][3][1][1][2][1] = {{
            {
                {
                    {{1},{2}},
                }
            },
            {
                {
                    {{3},{4}},
                }
            },
            {
                {
                    {{5},{6}}
                }
            }
        }};
    }
}

#undef CAST_ARRAYS

#endif // NMTOOLS_TESTING_DATA_ARRAY_EXPAND_DIMS_HPP