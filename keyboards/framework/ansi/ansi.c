// Copyright 2022 Framework Computer
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

#if defined(RGB_MATRIX_ENABLE)
const is31fl3743a_led_t PROGMEM g_is31fl3743a_leds[IS31FL3743A_LED_COUNT] = {
    /* Refer to IS31 manual for these locations
     *   driver
     *   |    R location
     *   |    |          G location
     *   |    |          |          B location
     *   |    |          |          | */
    // Re-arranged in LED ID order so it matches with the physical location array
    {0, SW6_CS3, SW6_CS2, SW6_CS1}, // LED 1
    {0, SW8_CS3, SW8_CS2, SW8_CS1}, // LED 2
    {0, SW1_CS3, SW1_CS2, SW1_CS1}, // LED 3
    {0, SW2_CS3, SW2_CS2, SW2_CS1}, // LED 4
    {0, SW3_CS3, SW3_CS2, SW3_CS1}, // LED 5
    {0, SW4_CS3, SW4_CS2, SW4_CS1}, // LED 6
    {0, SW9_CS3, SW9_CS2, SW9_CS1}, // LED 7
    {0, SW5_CS3, SW5_CS2, SW5_CS1}, // LED 8
    {0, SW7_CS3, SW7_CS2, SW7_CS1}, // LED 9

    {0, SW3_CS6, SW3_CS5, SW3_CS4}, // LED 10
    {0, SW7_CS6, SW7_CS5, SW7_CS4}, // LED 11
    {0, SW1_CS6, SW1_CS5, SW1_CS4}, // LED 12
    {0, SW2_CS6, SW2_CS5, SW2_CS4}, // LED 13
    {0, SW4_CS6, SW4_CS5, SW4_CS4}, // LED 14
    {0, SW5_CS6, SW5_CS5, SW5_CS4}, // LED 15
    {0, SW6_CS6, SW6_CS5, SW6_CS4}, // LED 16
    {0, SW8_CS6, SW8_CS5, SW8_CS4}, // LED 17
    {0, SW9_CS6, SW9_CS5, SW9_CS4}, // LED 18

    {0, SW1_CS9, SW1_CS8, SW1_CS7}, // LED 19
    {0, SW2_CS9, SW2_CS8, SW2_CS7}, // LED 20
    {0, SW3_CS9, SW3_CS8, SW3_CS7}, // LED 21
    {0, SW4_CS9, SW4_CS8, SW4_CS7}, // LED 22
    {0, SW5_CS9, SW5_CS8, SW5_CS7}, // LED 23
    {0, SW6_CS9, SW6_CS8, SW6_CS7}, // LED 24
    {0, SW7_CS9, SW7_CS8, SW7_CS7}, // LED 25
    {0, SW8_CS9, SW8_CS8, SW8_CS7}, // LED 26
    {0, SW9_CS9, SW9_CS8, SW9_CS7}, // LED 27

    {0, SW1_CS12, SW1_CS11, SW1_CS10}, // LED 28
    {0, SW2_CS12, SW2_CS11, SW2_CS10}, // LED 29
    {0, SW3_CS12, SW3_CS11, SW3_CS10}, // LED 30
    {0, SW4_CS12, SW4_CS11, SW4_CS10}, // LED 31
    {0, SW5_CS12, SW5_CS11, SW5_CS10}, // LED 32
    {0, SW6_CS12, SW6_CS11, SW6_CS10}, // LED 33
    {0, SW7_CS12, SW7_CS11, SW7_CS10}, // LED 34
    {0, SW8_CS12, SW8_CS11, SW8_CS10}, // LED 35
    {0, SW9_CS12, SW9_CS11, SW9_CS10}, // LED 36

    {0, SW2_CS15, SW2_CS14, SW2_CS13}, // LED 37
    {0, SW3_CS15, SW3_CS14, SW3_CS13}, // LED 38
    {0, SW6_CS15, SW6_CS14, SW6_CS13}, // LED 39
    {0, SW7_CS15, SW7_CS14, SW7_CS13}, // LED 40
    {0, SW9_CS15, SW9_CS14, SW9_CS13}, // LED 41
    {0, SW1_CS15, SW1_CS14, SW1_CS13}, // LED 42
    {0, SW4_CS15, SW4_CS14, SW4_CS13}, // LED 43
    {0, SW5_CS15, SW5_CS14, SW5_CS13}, // LED 44
    {0, SW8_CS15, SW8_CS14, SW8_CS13}, // LED 45

    {0, SW1_CS18, SW1_CS17, SW1_CS16}, // LED 46
    {0, SW2_CS18, SW2_CS17, SW2_CS16}, // LED 47
    {0, SW3_CS18, SW3_CS17, SW3_CS16}, // LED 48

    {1, SW1_CS3, SW1_CS2, SW1_CS1}, // LED 49
    {1, SW2_CS3, SW2_CS2, SW2_CS1}, // LED 50
    {1, SW3_CS3, SW3_CS2, SW3_CS1}, // LED 51
    {1, SW4_CS3, SW4_CS2, SW4_CS1}, // LED 52
    {1, SW5_CS3, SW5_CS2, SW5_CS1}, // LED 53
    {1, SW6_CS3, SW6_CS2, SW6_CS1}, // LED 54
    {1, SW7_CS3, SW7_CS2, SW7_CS1}, // LED 55
    {1, SW8_CS3, SW8_CS2, SW8_CS1}, // LED 56
    {1, SW9_CS3, SW9_CS2, SW9_CS1}, // LED 57

    {1, SW1_CS6, SW1_CS5, SW1_CS4}, // LED 58
    {1, SW2_CS6, SW2_CS5, SW2_CS4}, // LED 59
    {1, SW3_CS6, SW3_CS5, SW3_CS4}, // LED 60
    {1, SW4_CS6, SW4_CS5, SW4_CS4}, // LED 61
    {1, SW5_CS6, SW5_CS5, SW5_CS4}, // LED 62
    {1, SW6_CS6, SW6_CS5, SW6_CS4}, // LED 63
    {1, SW7_CS6, SW7_CS5, SW7_CS4}, // LED 64
    {1, SW8_CS6, SW8_CS5, SW8_CS4}, // LED 65
    {1, SW9_CS6, SW9_CS5, SW9_CS4}, // LED 66

    {1, SW1_CS9, SW1_CS8, SW1_CS7}, // LED 67
    {1, SW2_CS9, SW2_CS8, SW2_CS7}, // LED 68
    {1, SW4_CS9, SW4_CS8, SW4_CS7}, // LED 69
    {1, SW5_CS9, SW5_CS8, SW5_CS7}, // LED 70
    {1, SW6_CS9, SW6_CS8, SW6_CS7}, // LED 71
    {1, SW7_CS9, SW7_CS8, SW7_CS7}, // LED 72
    {1, SW8_CS9, SW8_CS8, SW8_CS7}, // LED 73
    {1, SW9_CS9, SW9_CS8, SW9_CS7}, // LED 74
    {1, SW3_CS9, SW3_CS8, SW3_CS7}, // LED 75

    {1, SW1_CS12, SW1_CS11, SW1_CS10}, // LED 76
    {1, SW2_CS12, SW2_CS11, SW2_CS10}, // LED 77
    {1, SW3_CS12, SW3_CS11, SW3_CS10}, // LED 78
    {1, SW4_CS12, SW4_CS11, SW4_CS10}, // LED 79
    {1, SW5_CS12, SW5_CS11, SW5_CS10}, // LED 80
    {1, SW6_CS12, SW6_CS11, SW6_CS10}, // LED 81
    {1, SW7_CS12, SW7_CS11, SW7_CS10}, // LED 82
    {1, SW8_CS12, SW8_CS11, SW8_CS10}, // LED 83
    {1, SW9_CS12, SW9_CS11, SW9_CS10}, // LED 84

    {1, SW1_CS15, SW1_CS14, SW1_CS13}, // LED 85
    {1, SW2_CS15, SW2_CS14, SW2_CS13}, // LED 86
    {1, SW3_CS15, SW3_CS14, SW3_CS13}, // LED 87
    {1, SW4_CS15, SW4_CS14, SW4_CS13}, // LED 88
    {1, SW5_CS15, SW5_CS14, SW5_CS13}, // LED 89
    {1, SW6_CS15, SW6_CS14, SW6_CS13}, // LED 90
    {1, SW7_CS15, SW7_CS14, SW7_CS13}, // LED 91
    {1, SW8_CS15, SW8_CS14, SW8_CS13}, // LED 92
    {1, SW9_CS15, SW9_CS14, SW9_CS13}, // LED 93

    {1, SW1_CS18, SW1_CS17, SW1_CS16}, // LED 94
    {1, SW2_CS18, SW2_CS17, SW2_CS16}, // LED 95
    {1, SW3_CS18, SW3_CS17, SW3_CS16}, // LED 96
    {1, SW4_CS18, SW4_CS17, SW4_CS16}, // LED 97
};

led_config_t g_led_config = {{
                                 // Key Matrix to LED Index
                                 {
                                     31,
                                     73,
                                     5,
                                     84,
                                     NO_LED,
                                     29,
                                     33,
                                     77,
                                     75,
                                     92,
                                     78,
                                     NO_LED,
                                     88,
                                     79,
                                     52,
                                     NO_LED,
                                 },
                                 {
                                     NO_LED,
                                     NO_LED,
                                     NO_LED,
                                     47,
                                     94,
                                     27,
                                     35,
                                     76,
                                     90,
                                     32,
                                     NO_LED,
                                     NO_LED,
                                     34,
                                     81,
                                     56,
                                     67,
                                 },
                                 {
                                     NO_LED,
                                     NO_LED,
                                     93,
                                     NO_LED,
                                     2,
                                     19,
                                     39,
                                     40,
                                     55,
                                     NO_LED,
                                     26,
                                     NO_LED,
                                     NO_LED,
                                     63,
                                     NO_LED,
                                     91,
                                 },
                                 {
                                     NO_LED,
                                     46,
                                     1,
                                     NO_LED,
                                     20,
                                     21,
                                     7,
                                     8,
                                     59,
                                     NO_LED,
                                     24,
                                     74,
                                     NO_LED,
                                     70,
                                     NO_LED,
                                     NO_LED,
                                 },
                                 {
                                     NO_LED,
                                     NO_LED,
                                     16,
                                     NO_LED,
                                     44,
                                     41,
                                     9,
                                     14,
                                     68,
                                     NO_LED,
                                     22,
                                     NO_LED,
                                     NO_LED,
                                     61,
                                     62,
                                     NO_LED,
                                 },
                                 {
                                     NO_LED,
                                     NO_LED,
                                     15,
                                     NO_LED,
                                     12,
                                     13,
                                     11,
                                     10,
                                     69,
                                     NO_LED,
                                     17,
                                     NO_LED,
                                     NO_LED,
                                     60,
                                     65,
                                     NO_LED,
                                 },
                                 {
                                     NO_LED,
                                     NO_LED,
                                     NO_LED,
                                     NO_LED,
                                     18,
                                     3,
                                     4,
                                     6,
                                     66,
                                     NO_LED,
                                     58,
                                     89,
                                     NO_LED,
                                     57,
                                     54,
                                     NO_LED,
                                 },
                                 {
                                     NO_LED,
                                     NO_LED,
                                     36,
                                     NO_LED,
                                     NO_LED,
                                     25,
                                     43,
                                     49,
                                     51,
                                     NO_LED,
                                     50,
                                     NO_LED,
                                     NO_LED,
                                     48,
                                     37,
                                     NO_LED,
                                 },
                             },
                             {
                                 // LED Index to Physical Position
                                 {11, 23},  // LED 1
                                 {0, 23},   // LED 2
                                 {57, 22},  // LED 3
                                 {41, 22},  // LED 4
                                 {73, 22},  // LED 5
                                 {25, 22},  // LED 6
                                 {121, 22}, // LED 7
                                 {89, 22},  // LED 8
                                 {105, 22}, // LED 9
                                 {82, 10},  // LED 10
                                 {114, 10}, // LED 11
                                 {66, 10},  // LED 12
                                 {50, 10},  // LED 13
                                 {34, 10},  // LED 14
                                 {98, 10},  // LED 15
                                 {18, 10},  // LED 16
                                 {2, 10},   // LED 17
                                 {130, 10}, // LED 18
                                 {56, 0},   // LED 19
                                 {40, 0},   // LED 20
                                 {72, 0},   // LED 21
                                 {24, 0},   // LED 22
                                 {88, 0},   // LED 23
                                 {10, 0},   // LED 24
                                 {104, 0},  // LED 25
                                 {0, 0},    // LED 26
                                 {120, 0},  // LED 27
                                 {38, 47},  // LED 28
                                 {22, 47},  // LED 29
                                 {54, 47},  // LED 30
                                 {5, 48},   // LED 31
                                 {70, 47},  // LED 32
                                 {1, 48},   // LED 33
                                 {86, 47},  // LED 34
                                 {0, 60},   // LED 35
                                 {102, 47}, // LED 36
                                 {30, 34},  // LED 37
                                 {62, 34},  // LED 38
                                 {7, 35},   // LED 39
                                 {94, 34},  // LED 40
                                 {110, 34}, // LED 41
                                 {46, 34},  // LED 42
                                 {13, 36},  // LED 43
                                 {78, 34},  // LED 44
                                 {1, 36},   // LED 45
                                 {8, 60},   // LED 46
                                 {38, 59},  // LED 47
                                 {54, 59},  // LED 48
                                 {174, 34}, // LED 49
                                 {126, 34}, // LED 50
                                 {142, 34}, // LED 51
                                 {158, 34}, // LED 52
                                 {190, 34}, // LED 53
                                 {205, 34}, // LED 54
                                 {202, 22}, // LED 55
                                 {219, 22}, // LED 56
                                 {223, 36}, // LED 57
                                 {185, 22}, // LED 58
                                 {137, 22}, // LED 59
                                 {153, 22}, // LED 60
                                 {169, 22}, // LED 61
                                 {162, 10}, // LED 62
                                 {194, 10}, // LED 63
                                 {178, 10}, // LED 64
                                 {209, 11}, // LED 65
                                 {222, 11}, // LED 66
                                 {181, 0},  // LED 67
                                 {136, 0},  // LED 68
                                 {168, 0},  // LED 69
                                 {146, 10}, // LED 70
                                 {199, 0},  // LED 71
                                 {186, 0},  // LED 72
                                 {213, 0},  // LED 73
                                 {224, 0},  // LED 74
                                 {152, 0},  // LED 75
                                 {166, 47}, // LED 76
                                 {118, 47}, // LED 77
                                 {134, 47}, // LED 78
                                 {150, 47}, // LED 79
                                 {182, 47}, // LED 80
                                 {197, 48}, // LED 81
                                 {202, 58}, // LED 82
                                 {203, 48}, // LED 83
                                 {217, 48}, // LED 84
                                 {150, 59}, // LED 85
                                 {108, 60}, // LED 86
                                 {121, 60}, // LED 87
                                 {134, 60}, // LED 88
                                 {166, 59}, // LED 89
                                 {183, 64}, // LED 90
                                 {202, 62}, // LED 91
                                 {220, 64}, // LED 92
                                 {222, 48}, // LED 93
                                 {22, 59},  // LED 94
                                 {70, 60},  // LED 95
                                 {83, 60},  // LED 96
                                 {95, 60},  // LED 97
                             },
                             {// LED Index to Flag
                              4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4}};
#endif
