#ifndef NMTOOLS_TESTING_DATA_BLAS_OUTER_HPP
#define NMTOOLS_TESTING_DATA_BLAS_OUTER_HPP

/* TODO: use __has_include */
#include "nmtools/array/fixed.hpp"
#include "nmtools/blas/blas.hpp"
#include "testing/testing.hpp"
#include <array>
/* TODO: use __has_include */
#include <vector>
#include <valarray>

/* @todo: make simple script to autogenereate test data */

NMTOOLS_TESTING_DECLARE_CASE(blas, outer)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1) {
        using ::nmtools::testing::data::common::v5;
        using ::nmtools::testing::data::common::r5;
        NMTOOLS_TESTING_DATA_DECLARE_ARRAY(x,v5);
        NMTOOLS_TESTING_DATA_DECLARE_ARRAY(y,r5);
        NMTOOLS_TESTING_DATA_DECLARE_VEC(x,5);
        NMTOOLS_TESTING_DATA_DECLARE_VEC(y,5);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1) {
        constexpr auto res = std::array<std::array<double,5>,5>{{
            {17,    34,    51,    68,    85},
            {24,    48,    72,    96,   120},
            { 1,     2,     3,     4,     5},
            { 8,    16,    24,    32,    40},
            {15,    30,    45,    60,    75},
        }};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2) {
        using ::nmtools::testing::data::common::v10;
        using ::nmtools::testing::data::common::r10;
        NMTOOLS_TESTING_DATA_DECLARE_ARRAY(x,v10);
        NMTOOLS_TESTING_DATA_DECLARE_ARRAY(y,r10);
        NMTOOLS_TESTING_DATA_DECLARE_VEC(x,10);
        NMTOOLS_TESTING_DATA_DECLARE_VEC(y,10);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2) {
        constexpr auto res = std::array<std::array<double,10>,10>{{
            {92,   184,   276,   368,   460,   552,   644,   736,   828,   920},
            {99,   198,   297,   396,   495,   594,   693,   792,   891,   990},
            { 1,     2,     3,     4,     5,     6,     7,     8,     9,    10},
            { 8,    16,    24,    32,    40,    48,    56,    64,    72,    80},
            {15,    30,    45,    60,    75,    90,   105,   120,   135,   150},
            {67,   134,   201,   268,   335,   402,   469,   536,   603,   670},
            {74,   148,   222,   296,   370,   444,   518,   592,   666,   740},
            {51,   102,   153,   204,   255,   306,   357,   408,   459,   510},
            {58,   116,   174,   232,   290,   348,   406,   464,   522,   580},
            {40,    80,   120,   160,   200,   240,   280,   320,   360,   400},
        }};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3) {
        using ::nmtools::testing::data::common::v15;
        using ::nmtools::testing::data::common::r15;
        NMTOOLS_TESTING_DATA_DECLARE_ARRAY(x,v15);
        NMTOOLS_TESTING_DATA_DECLARE_ARRAY(y,r15);
        NMTOOLS_TESTING_DATA_DECLARE_VEC(x,15);
        NMTOOLS_TESTING_DATA_DECLARE_VEC(y,15);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3) {
        constexpr auto res = std::array<std::array<double,15>,15>{{
            {122,    244,    366,    488,    610,    732,    854,    976,   1098,   1220,   1342,   1464,   1586,   1708,   1830},
            {139,    278,    417,    556,    695,    834,    973,   1112,   1251,   1390,   1529,   1668,   1807,   1946,   2085},
            {156,    312,    468,    624,    780,    936,   1092,   1248,   1404,   1560,   1716,   1872,   2028,   2184,   2340},
            {173,    346,    519,    692,    865,   1038,   1211,   1384,   1557,   1730,   1903,   2076,   2249,   2422,   2595},
            {190,    380,    570,    760,    950,   1140,   1330,   1520,   1710,   1900,   2090,   2280,   2470,   2660,   2850},
            {207,    414,    621,    828,   1035,   1242,   1449,   1656,   1863,   2070,   2277,   2484,   2691,   2898,   3105},
            {224,    448,    672,    896,   1120,   1344,   1568,   1792,   2016,   2240,   2464,   2688,   2912,   3136,   3360},
            {  1,      2,      3,      4,      5,      6,      7,      8,      9,     10,     11,     12,     13,     14,     15},
            { 18,     36,     54,     72,     90,    108,    126,    144,    162,    180,    198,    216,    234,    252,    270},
            { 35,     70,    105,    140,    175,    210,    245,    280,    315,    350,    385,    420,    455,    490,    525},
            { 52,    104,    156,    208,    260,    312,    364,    416,    468,    520,    572,    624,    676,    728,    780},
            { 69,    138,    207,    276,    345,    414,    483,    552,    621,    690,    759,    828,    897,    966,   1035},
            { 86,    172,    258,    344,    430,    516,    602,    688,    774,    860,    946,   1032,   1118,   1204,   1290},
            {103,    206,    309,    412,    515,    618,    721,    824,    927,   1030,   1133,   1236,   1339,   1442,   1545},
            {120,    240,    360,    480,    600,    720,    840,    960,   1080,   1200,   1320,   1440,   1560,   1680,   1800},
        }};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4) {
        using ::nmtools::testing::data::common::v20;
        using ::nmtools::testing::data::common::r20;
        NMTOOLS_TESTING_DATA_DECLARE_ARRAY(x,v20);
        NMTOOLS_TESTING_DATA_DECLARE_ARRAY(y,r20);
        NMTOOLS_TESTING_DATA_DECLARE_VEC(x,20);
        NMTOOLS_TESTING_DATA_DECLARE_VEC(y,20);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4) {
        constexpr auto res = std::array<std::array<double,20>,20>{{
            {400,    800,   1200,   1600,   2000,   2400,   2800,   3200,   3600,   4000,   4400,   4800,   5200,   5600,   6000,   6400,   6800,   7200,   7600,   8000},
            {  2,      4,      6,      8,     10,     12,     14,     16,     18,     20,     22,     24,     26,     28,     30,     32,     34,     36,     38,     40},
            {  3,      6,      9,     12,     15,     18,     21,     24,     27,     30,     33,     36,     39,     42,     45,     48,     51,     54,     57,     60},
            {397,    794,   1191,   1588,   1985,   2382,   2779,   3176,   3573,   3970,   4367,   4764,   5161,   5558,   5955,   6352,   6749,   7146,   7543,   7940},
            {396,    792,   1188,   1584,   1980,   2376,   2772,   3168,   3564,   3960,   4356,   4752,   5148,   5544,   5940,   6336,   6732,   7128,   7524,   7920},
            {  6,     12,     18,     24,     30,     36,     42,     48,     54,     60,     66,     72,     78,     84,     90,     96,    102,    108,    114,    120},
            {  7,     14,     21,     28,     35,     42,     49,     56,     63,     70,     77,     84,     91,     98,    105,    112,    119,    126,    133,    140},
            {393,    786,   1179,   1572,   1965,   2358,   2751,   3144,   3537,   3930,   4323,   4716,   5109,   5502,   5895,   6288,   6681,   7074,   7467,   7860},
            {392,    784,   1176,   1568,   1960,   2352,   2744,   3136,   3528,   3920,   4312,   4704,   5096,   5488,   5880,   6272,   6664,   7056,   7448,   7840},
            { 10,     20,     30,     40,     50,     60,     70,     80,     90,    100,    110,    120,    130,    140,    150,    160,    170,    180,    190,    200},
            { 11,     22,     33,     44,     55,     66,     77,     88,     99,    110,    121,    132,    143,    154,    165,    176,    187,    198,    209,    220},
            {389,    778,   1167,   1556,   1945,   2334,   2723,   3112,   3501,   3890,   4279,   4668,   5057,   5446,   5835,   6224,   6613,   7002,   7391,   7780},
            {388,    776,   1164,   1552,   1940,   2328,   2716,   3104,   3492,   3880,   4268,   4656,   5044,   5432,   5820,   6208,   6596,   6984,   7372,   7760},
            { 14,     28,     42,     56,     70,     84,     98,    112,    126,    140,    154,    168,    182,    196,    210,    224,    238,    252,    266,    280},
            { 15,     30,     45,     60,     75,     90,    105,    120,    135,    150,    165,    180,    195,    210,    225,    240,    255,    270,    285,    300},
            {385,    770,   1155,   1540,   1925,   2310,   2695,   3080,   3465,   3850,   4235,   4620,   5005,   5390,   5775,   6160,   6545,   6930,   7315,   7700},
            {384,    768,   1152,   1536,   1920,   2304,   2688,   3072,   3456,   3840,   4224,   4608,   4992,   5376,   5760,   6144,   6528,   6912,   7296,   7680},
            { 18,     36,     54,     72,     90,    108,    126,    144,    162,    180,    198,    216,    234,    252,    270,    288,    306,    324,    342,    360},
            { 19,     38,     57,     76,     95,    114,    133,    152,    171,    190,    209,    228,    247,    266,    285,    304,    323,    342,    361,    380},
            {381,    762,   1143,   1524,   1905,   2286,   2667,   3048,   3429,   3810,   4191,   4572,   4953,   5334,   5715,   6096,   6477,   6858,   7239,   7620},
        }};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case5) {
        using ::nmtools::testing::data::common::v25;
        using ::nmtools::testing::data::common::r25;
        NMTOOLS_TESTING_DATA_DECLARE_ARRAY(x,v25);
        NMTOOLS_TESTING_DATA_DECLARE_ARRAY(y,r25);
        NMTOOLS_TESTING_DATA_DECLARE_VEC(x,25);
        NMTOOLS_TESTING_DATA_DECLARE_VEC(y,25);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case5) {
        constexpr auto res = std::array<std::array<double,25>,25>{{
            {327,     654,     981,    1308,    1635,    1962,    2289,    2616,    2943,    3270,    3597,    3924,    4251,    4578,    4905,    5232,    5559,    5886,    6213,    6540,    6867,    7194,    7521,    7848,    8175},
            {354,     708,    1062,    1416,    1770,    2124,    2478,    2832,    3186,    3540,    3894,    4248,    4602,    4956,    5310,    5664,    6018,    6372,    6726,    7080,    7434,    7788,    8142,    8496,    8850},
            {381,     762,    1143,    1524,    1905,    2286,    2667,    3048,    3429,    3810,    4191,    4572,    4953,    5334,    5715,    6096,    6477,    6858,    7239,    7620,    8001,    8382,    8763,    9144,    9525},
            {408,     816,    1224,    1632,    2040,    2448,    2856,    3264,    3672,    4080,    4488,    4896,    5304,    5712,    6120,    6528,    6936,    7344,    7752,    8160,    8568,    8976,    9384,    9792,   10200},
            {435,     870,    1305,    1740,    2175,    2610,    3045,    3480,    3915,    4350,    4785,    5220,    5655,    6090,    6525,    6960,    7395,    7830,    8265,    8700,    9135,    9570,   10005,   10440,   10875},
            {462,     924,    1386,    1848,    2310,    2772,    3234,    3696,    4158,    4620,    5082,    5544,    6006,    6468,    6930,    7392,    7854,    8316,    8778,    9240,    9702,   10164,   10626,   11088,   11550},
            {489,     978,    1467,    1956,    2445,    2934,    3423,    3912,    4401,    4890,    5379,    5868,    6357,    6846,    7335,    7824,    8313,    8802,    9291,    9780,   10269,   10758,   11247,   11736,   12225},
            {516,    1032,    1548,    2064,    2580,    3096,    3612,    4128,    4644,    5160,    5676,    6192,    6708,    7224,    7740,    8256,    8772,    9288,    9804,   10320,   10836,   11352,   11868,   12384,   12900},
            {543,    1086,    1629,    2172,    2715,    3258,    3801,    4344,    4887,    5430,    5973,    6516,    7059,    7602,    8145,    8688,    9231,    9774,   10317,   10860,   11403,   11946,   12489,   13032,   13575},
            {570,    1140,    1710,    2280,    2850,    3420,    3990,    4560,    5130,    5700,    6270,    6840,    7410,    7980,    8550,    9120,    9690,   10260,   10830,   11400,   11970,   12540,   13110,   13680,   14250},
            {597,    1194,    1791,    2388,    2985,    3582,    4179,    4776,    5373,    5970,    6567,    7164,    7761,    8358,    8955,    9552,   10149,   10746,   11343,   11940,   12537,   13134,   13731,   14328,   14925},
            {624,    1248,    1872,    2496,    3120,    3744,    4368,    4992,    5616,    6240,    6864,    7488,    8112,    8736,    9360,    9984,   10608,   11232,   11856,   12480,   13104,   13728,   14352,   14976,   15600},
            {  1,       2,       3,       4,       5,       6,       7,       8,       9,      10,      11,      12,      13,      14,      15,      16,      17,      18,      19,      20,      21,      22,      23,      24,      25},
            { 28,      56,      84,     112,     140,     168,     196,     224,     252,     280,     308,     336,     364,     392,     420,     448,     476,     504,     532,     560,     588,     616,     644,     672,     700},
            { 55,     110,     165,     220,     275,     330,     385,     440,     495,     550,     605,     660,     715,     770,     825,     880,     935,     990,    1045,    1100,    1155,    1210,    1265,    1320,    1375},
            { 82,     164,     246,     328,     410,     492,     574,     656,     738,     820,     902,     984,    1066,    1148,    1230,    1312,    1394,    1476,    1558,    1640,    1722,    1804,    1886,    1968,    2050},
            {109,     218,     327,     436,     545,     654,     763,     872,     981,    1090,    1199,    1308,    1417,    1526,    1635,    1744,    1853,    1962,    2071,    2180,    2289,    2398,    2507,    2616,    2725},
            {136,     272,     408,     544,     680,     816,     952,    1088,    1224,    1360,    1496,    1632,    1768,    1904,    2040,    2176,    2312,    2448,    2584,    2720,    2856,    2992,    3128,    3264,    3400},
            {163,     326,     489,     652,     815,     978,    1141,    1304,    1467,    1630,    1793,    1956,    2119,    2282,    2445,    2608,    2771,    2934,    3097,    3260,    3423,    3586,    3749,    3912,    4075},
            {190,     380,     570,     760,     950,    1140,    1330,    1520,    1710,    1900,    2090,    2280,    2470,    2660,    2850,    3040,    3230,    3420,    3610,    3800,    3990,    4180,    4370,    4560,    4750},
            {217,     434,     651,     868,    1085,    1302,    1519,    1736,    1953,    2170,    2387,    2604,    2821,    3038,    3255,    3472,    3689,    3906,    4123,    4340,    4557,    4774,    4991,    5208,    5425},
            {244,     488,     732,     976,    1220,    1464,    1708,    1952,    2196,    2440,    2684,    2928,    3172,    3416,    3660,    3904,    4148,    4392,    4636,    4880,    5124,    5368,    5612,    5856,    6100},
            {271,     542,     813,    1084,    1355,    1626,    1897,    2168,    2439,    2710,    2981,    3252,    3523,    3794,    4065,    4336,    4607,    4878,    5149,    5420,    5691,    5962,    6233,    6504,    6775},
            {298,     596,     894,    1192,    1490,    1788,    2086,    2384,    2682,    2980,    3278,    3576,    3874,    4172,    4470,    4768,    5066,    5364,    5662,    5960,    6258,    6556,    6854,    7152,    7450},
            {325,     650,     975,    1300,    1625,    1950,    2275,    2600,    2925,    3250,    3575,    3900,    4225,    4550,    4875,    5200,    5525,    5850,    6175,    6500,    6825,    7150,    7475,    7800,    8125},
        }};
    }
}

#endif // NMTOOLS_TESTING_DATA_BLAS_OUTER_HPP