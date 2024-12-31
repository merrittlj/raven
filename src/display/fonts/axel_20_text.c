/*******************************************************************************
 * Size: 20 px
 * Bpp: 1
 * Opts: --bpp 1 --size 20 --font AxelBold.TTF --symbols ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789`~!@#$%^&*()-_=+[]{}|;:'",.<>?/\ --format lvgl -o axel_20_text.c
 ******************************************************************************/

#ifdef LV_LVGL_H_INCLUDE_SIMPLE
#include "lvgl.h"
#else
#include "lvgl/lvgl.h"
#endif

#ifndef AXEL_20_TEXT
#define AXEL_20_TEXT 1
#endif

#if AXEL_20_TEXT

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+0021 "!" */
    0x77, 0x77, 0x77, 0x77, 0x70, 0x6, 0xff, 0x60,

    /* U+0022 "\"" */
    0xef, 0xdd, 0xbb, 0x76, 0x6c, 0xc0,

    /* U+0023 "#" */
    0x1c, 0xc1, 0xdc, 0x1d, 0xc7, 0xff, 0x7f, 0xf7,
    0xff, 0x19, 0xc3, 0x9c, 0x39, 0xcf, 0xfe, 0xff,
    0xef, 0xfe, 0x3b, 0x83, 0xb8, 0x33, 0x83, 0x38,

    /* U+0024 "$" */
    0x18, 0x18, 0x7e, 0x7e, 0xe2, 0xe0, 0xe0, 0xf8,
    0x7c, 0x3e, 0x1f, 0x7, 0x7, 0xc7, 0xff, 0xfe,
    0x38, 0x18, 0x18,

    /* U+0025 "%" */
    0x38, 0x70, 0x7c, 0xe0, 0xee, 0xe0, 0xee, 0xe0,
    0xee, 0xc0, 0xef, 0xc0, 0x7d, 0xc0, 0x39, 0x9c,
    0x3, 0xbe, 0x3, 0xf7, 0x3, 0x77, 0x7, 0x77,
    0x7, 0x77, 0x6, 0x3e, 0xe, 0x1c,

    /* U+0026 "&" */
    0x1e, 0x3, 0xf0, 0x73, 0x87, 0x38, 0x73, 0x87,
    0xf0, 0x3e, 0x3, 0xc0, 0x7e, 0xef, 0x7e, 0xe7,
    0xee, 0x3c, 0xe3, 0xe7, 0xfe, 0x3e, 0x40,

    /* U+0027 "'" */
    0xfd, 0xb6, 0xc0,

    /* U+0028 "(" */
    0x18, 0x73, 0x8e, 0x71, 0xc7, 0x38, 0xe3, 0x8e,
    0x38, 0xe3, 0x8e, 0x1c, 0x70, 0xe3, 0x87, 0x1c,
    0x0,

    /* U+0029 ")" */
    0x63, 0x87, 0x1c, 0x38, 0xe3, 0x87, 0x1c, 0x71,
    0xc7, 0x1c, 0x73, 0x8e, 0x39, 0xc7, 0x38, 0xe0,
    0x0,

    /* U+002A "*" */
    0x18, 0xc, 0x36, 0xdf, 0xef, 0xf1, 0xe1, 0xf8,
    0xcc, 0x24, 0x0,

    /* U+002B "+" */
    0x1c, 0xe, 0x7, 0x1f, 0xff, 0xff, 0xfc, 0x70,
    0x38, 0x1c, 0x0,

    /* U+002C "," */
    0x6f, 0xff, 0x76, 0xc4,

    /* U+002D "-" */
    0xff, 0xff, 0xc0,

    /* U+002E "." */
    0x6f, 0xf6,

    /* U+002F "/" */
    0x3, 0x3, 0x7, 0x6, 0x6, 0xe, 0xe, 0xc,
    0x1c, 0x1c, 0x18, 0x38, 0x38, 0x30, 0x30, 0x70,
    0x60, 0x60, 0xe0, 0xe0, 0xc0,

    /* U+0030 "0" */
    0x1e, 0x3f, 0x9d, 0xdc, 0x7e, 0x7f, 0x3f, 0xbf,
    0xf7, 0xf3, 0xf9, 0xf8, 0xee, 0xe7, 0xf1, 0xf0,

    /* U+0031 "1" */
    0x1c, 0x3c, 0x7c, 0xfc, 0x5c, 0x1c, 0x1c, 0x1c,
    0x1c, 0x1c, 0x1c, 0x1c, 0x7f, 0x7f,

    /* U+0032 "2" */
    0x3c, 0x7e, 0xe7, 0xe7, 0x7, 0x7, 0xf, 0x1e,
    0x1c, 0x3c, 0x78, 0xf0, 0xff, 0xff,

    /* U+0033 "3" */
    0x3c, 0xff, 0x67, 0x7, 0x7, 0x3c, 0x3e, 0xf,
    0x7, 0x7, 0x7, 0x4f, 0xfe, 0x7c,

    /* U+0034 "4" */
    0x0, 0x7, 0x7, 0x3, 0x83, 0x81, 0xc1, 0xcc,
    0xe6, 0x67, 0x73, 0xbf, 0xff, 0xf0, 0x70, 0x38,
    0x1c,

    /* U+0035 "5" */
    0xfe, 0xfe, 0xe0, 0xe0, 0xe0, 0xfc, 0xfe, 0x47,
    0x7, 0x7, 0x7, 0x8f, 0xfe, 0xfc,

    /* U+0036 "6" */
    0x1f, 0x3e, 0x70, 0x60, 0xfc, 0xfe, 0xe7, 0xe7,
    0xe7, 0xe7, 0xe7, 0x67, 0x7e, 0x3c,

    /* U+0037 "7" */
    0xff, 0xff, 0xf, 0xe, 0xe, 0x1e, 0x1c, 0x1c,
    0x3c, 0x38, 0x38, 0x70, 0x70,

    /* U+0038 "8" */
    0x3e, 0x3f, 0xb8, 0xfc, 0x7e, 0x3b, 0xb9, 0xfc,
    0x7e, 0x7f, 0x73, 0xf8, 0xfc, 0x7e, 0x3b, 0xf8,
    0xf8,

    /* U+0039 "9" */
    0x3c, 0x7e, 0xe7, 0xe7, 0xe7, 0xe7, 0xe7, 0x7f,
    0x3f, 0x7, 0x6, 0xe, 0x7c, 0x78,

    /* U+003A ":" */
    0x6f, 0xf6, 0x0, 0x6, 0xff, 0x60,

    /* U+003B ";" */
    0x6f, 0xf6, 0x0, 0xf, 0xff, 0x76, 0xec,

    /* U+003C "<" */
    0x0, 0x80, 0xc1, 0xe1, 0xf3, 0xf3, 0xe3, 0xc1,
    0xe0, 0xfc, 0x1f, 0x7, 0xe0, 0xf0, 0x18, 0x4,

    /* U+003D "=" */
    0xff, 0xff, 0xff, 0xe0, 0xf, 0xff, 0xff, 0xfe,

    /* U+003E ">" */
    0x0, 0x60, 0x38, 0x1f, 0x7, 0xc0, 0xf8, 0x3e,
    0xf, 0x1f, 0x3f, 0x3e, 0x1c, 0xc, 0x0, 0x0,

    /* U+003F "?" */
    0x3c, 0xff, 0x7f, 0x47, 0x7, 0xf, 0xe, 0x1c,
    0x1c, 0x1c, 0x0, 0x18, 0x3c, 0x3c, 0x18,

    /* U+0040 "@" */
    0x3, 0xe0, 0x1f, 0xf0, 0x70, 0x71, 0xc0, 0x67,
    0x0, 0x6c, 0x38, 0xd8, 0xf9, 0xe1, 0xb3, 0xc6,
    0x67, 0x8c, 0xcf, 0x19, 0x36, 0x36, 0x6c, 0x7f,
    0x9c, 0x6e, 0x18, 0x0, 0x1c, 0x8, 0x3f, 0xf8,
    0x1f, 0xc0,

    /* U+0041 "A" */
    0xe, 0x1, 0xe0, 0x7c, 0xf, 0x81, 0xb0, 0x37,
    0xe, 0xe1, 0xdc, 0x3b, 0xc7, 0xf9, 0xff, 0x38,
    0xe7, 0x1e, 0xe1, 0xfc, 0x38,

    /* U+0042 "B" */
    0xfc, 0x7f, 0x39, 0xdc, 0xee, 0x77, 0x3b, 0xf9,
    0xfe, 0xe7, 0x71, 0xf8, 0xfc, 0x7e, 0x7f, 0xfb,
    0xf8,

    /* U+0043 "C" */
    0x1e, 0x3f, 0x7f, 0x73, 0xe0, 0xe0, 0xe0, 0xe0,
    0xe0, 0xe0, 0xe0, 0x71, 0x7f, 0x3f, 0x1e,

    /* U+0044 "D" */
    0xfc, 0x7f, 0xb9, 0xdc, 0x7e, 0x3f, 0x1f, 0x8f,
    0xc7, 0xe3, 0xf1, 0xf8, 0xfc, 0xff, 0xf7, 0xf3,
    0xf0,

    /* U+0045 "E" */
    0xff, 0xfe, 0xfe, 0xe0, 0xe0, 0xe0, 0xfe, 0xfe,
    0xe0, 0xe0, 0xe0, 0xe0, 0xff, 0xff, 0xff,

    /* U+0046 "F" */
    0xff, 0xff, 0xff, 0xe, 0x1c, 0x3f, 0xff, 0xff,
    0xc3, 0x87, 0xe, 0x1c, 0x38, 0x0,

    /* U+0047 "G" */
    0x1e, 0x1f, 0xdf, 0xce, 0x2e, 0x7, 0x3, 0x81,
    0xcf, 0xe7, 0xf1, 0xf8, 0xfc, 0x77, 0x39, 0xfc,
    0x7c,

    /* U+0048 "H" */
    0xe3, 0xf1, 0xf8, 0xfc, 0x7e, 0x3f, 0x1f, 0xff,
    0xff, 0xff, 0xf1, 0xf8, 0xfc, 0x7e, 0x3f, 0x1f,
    0x8e,

    /* U+0049 "I" */
    0xff, 0xf7, 0x1c, 0x71, 0xc7, 0x1c, 0x71, 0xc7,
    0x1c, 0x73, 0xff, 0xc0,

    /* U+004A "J" */
    0x3f, 0x3f, 0x7, 0x7, 0x7, 0x7, 0x7, 0x7,
    0x7, 0x7, 0xe7, 0xe7, 0xe7, 0x7e, 0x3c,

    /* U+004B "K" */
    0xe3, 0xb9, 0xee, 0x73, 0xbc, 0xee, 0x3f, 0x8f,
    0xc3, 0xf0, 0xfc, 0x3f, 0x8e, 0xe3, 0xbc, 0xe7,
    0xb9, 0xee, 0x3c,

    /* U+004C "L" */
    0xe1, 0xc3, 0x87, 0xe, 0x1c, 0x38, 0x70, 0xe1,
    0xc3, 0x87, 0xf, 0xff, 0xff, 0x80,

    /* U+004D "M" */
    0xf1, 0xfe, 0x3f, 0xc7, 0xfd, 0xff, 0xbf, 0xf7,
    0xfe, 0xff, 0xff, 0xee, 0xfd, 0xdf, 0xbb, 0xf0,
    0x7e, 0xf, 0xc1, 0xf8, 0x38,

    /* U+004E "N" */
    0xe3, 0xf9, 0xfc, 0xfe, 0x7f, 0xbf, 0xdf, 0xef,
    0xf7, 0xef, 0xf7, 0xfb, 0xfc, 0xfe, 0x7f, 0x3f,
    0x8e,

    /* U+004F "O" */
    0x1e, 0xf, 0xc7, 0x3b, 0x87, 0xe1, 0xf8, 0x7e,
    0x1f, 0x87, 0xe1, 0xf8, 0x7e, 0x1f, 0x86, 0x73,
    0x9f, 0xc1, 0xe0,

    /* U+0050 "P" */
    0xfc, 0xfe, 0xe7, 0xe7, 0xe7, 0xe7, 0xe7, 0xfe,
    0xfc, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0,

    /* U+0051 "Q" */
    0x1e, 0x7, 0xe1, 0xce, 0x70, 0xce, 0x1d, 0xc3,
    0xb8, 0x77, 0xe, 0xe1, 0xdc, 0x3b, 0x87, 0x30,
    0xe7, 0x38, 0x7f, 0x7, 0xf0, 0xe, 0x0, 0x0,

    /* U+0052 "R" */
    0xfc, 0x7f, 0x39, 0xdc, 0xee, 0x77, 0x3b, 0x9d,
    0xfc, 0xfc, 0x77, 0x3b, 0x9d, 0xee, 0x77, 0x3b,
    0x9e,

    /* U+0053 "S" */
    0x3e, 0x7f, 0xfe, 0xe2, 0xe0, 0xf0, 0x78, 0x3e,
    0x1f, 0x7, 0x7, 0x87, 0xff, 0xfe, 0x7c,

    /* U+0054 "T" */
    0xff, 0xff, 0xff, 0xe3, 0x81, 0xc0, 0xe0, 0x70,
    0x38, 0x1c, 0xe, 0x7, 0x3, 0x81, 0xc0, 0xe0,
    0x70,

    /* U+0055 "U" */
    0xe1, 0xf8, 0x7e, 0x1f, 0x87, 0xe1, 0xf8, 0x7e,
    0x1f, 0x87, 0xe1, 0xf8, 0x7e, 0x1f, 0x87, 0xf3,
    0xdf, 0xe3, 0xf0,

    /* U+0056 "V" */
    0xf1, 0xfc, 0x77, 0x1d, 0xc7, 0x73, 0x9c, 0xe3,
    0xb8, 0xee, 0x3b, 0xe, 0xc1, 0xf0, 0x7c, 0x1e,
    0x7, 0x81, 0xe0,

    /* U+0057 "W" */
    0xe3, 0x8f, 0xc7, 0x39, 0xce, 0x73, 0x9c, 0xe7,
    0x7d, 0xce, 0xdb, 0x9d, 0xb7, 0x3b, 0x6c, 0x36,
    0xd8, 0x6d, 0xf0, 0xfb, 0xe1, 0xe7, 0xc3, 0xcf,
    0x7, 0x8e, 0x7, 0x1c, 0x0,

    /* U+0058 "X" */
    0x71, 0xce, 0x79, 0xee, 0x1d, 0xc3, 0xb8, 0x3e,
    0x7, 0xc0, 0xf8, 0x1f, 0x3, 0x60, 0xee, 0x1d,
    0xc7, 0x3c, 0xe3, 0xbc, 0x78,

    /* U+0059 "Y" */
    0xf1, 0xee, 0x39, 0xef, 0x1d, 0xc3, 0xb8, 0x36,
    0x7, 0xc0, 0xf8, 0xe, 0x1, 0xc0, 0x38, 0x7,
    0x0, 0xe0, 0x1c, 0x3, 0x80,

    /* U+005A "Z" */
    0x7f, 0xff, 0xff, 0xe0, 0xe0, 0xf0, 0x70, 0x78,
    0x38, 0x3c, 0x1c, 0x1e, 0xe, 0xf, 0xff, 0xff,
    0xfe,

    /* U+005B "[" */
    0xff, 0xf9, 0xce, 0x73, 0x9c, 0xe7, 0x39, 0xce,
    0x73, 0x9c, 0xe7, 0x39, 0xff, 0x80,

    /* U+005C "\\" */
    0xe0, 0x30, 0x18, 0xe, 0x7, 0x1, 0x80, 0xe0,
    0x70, 0x18, 0xc, 0x7, 0x1, 0x80, 0xc0, 0x70,
    0x38, 0xc, 0x7, 0x3, 0x80, 0xc0, 0x70, 0x38,

    /* U+005D "]" */
    0xff, 0xce, 0x73, 0x9c, 0xe7, 0x39, 0xce, 0x73,
    0x9c, 0xe7, 0x39, 0xcf, 0xff, 0x80,

    /* U+005E "^" */
    0x1c, 0xf, 0xf, 0x87, 0xe7, 0x73, 0x9d, 0x8e,

    /* U+005F "_" */
    0xff, 0xff, 0xfc,

    /* U+0060 "`" */
    0x6, 0x3c, 0xf1, 0x80,

    /* U+0061 "a" */
    0x7e, 0x7f, 0x47, 0x7, 0x3f, 0x7f, 0xe7, 0xe7,
    0xe7, 0xff, 0x7b,

    /* U+0062 "b" */
    0x60, 0xe0, 0xe0, 0xe0, 0xe0, 0xfe, 0xfe, 0xe7,
    0xe7, 0xe7, 0xe7, 0xe7, 0xe7, 0xe7, 0xfe, 0xdc,

    /* U+0063 "c" */
    0x3e, 0x7e, 0x72, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0,
    0xf2, 0x7e, 0x3c,

    /* U+0064 "d" */
    0x3, 0x7, 0x7, 0x7, 0x7, 0x3f, 0x7f, 0xe7,
    0xe7, 0xe7, 0xe7, 0xe7, 0xe7, 0xe7, 0x7f, 0x3b,

    /* U+0065 "e" */
    0x3c, 0x3f, 0x99, 0xdc, 0xef, 0xf7, 0xff, 0x81,
    0xc0, 0x73, 0x3f, 0x8f, 0x80,

    /* U+0066 "f" */
    0x3e, 0xfd, 0xc3, 0x87, 0x1f, 0xbf, 0x38, 0x70,
    0xe1, 0xc3, 0x87, 0xe, 0x1c, 0x38,

    /* U+0067 "g" */
    0x3b, 0x7f, 0xe7, 0xe7, 0xe7, 0xe7, 0xe7, 0xe7,
    0xe7, 0x7f, 0x3f, 0x7, 0x7, 0x47, 0x7e, 0x7c,

    /* U+0068 "h" */
    0x60, 0xe0, 0xe0, 0xe0, 0xe0, 0xee, 0xff, 0xe7,
    0xe7, 0xe7, 0xe7, 0xe7, 0xe7, 0xe7, 0xe7, 0xe7,

    /* U+0069 "i" */
    0x27, 0x76, 0xf, 0xf7, 0x77, 0x77, 0x77, 0x77,

    /* U+006A "j" */
    0x18, 0xf3, 0xc6, 0x0, 0xf3, 0xc7, 0x1c, 0x71,
    0xc7, 0x1c, 0x71, 0xc7, 0x1c, 0x71, 0xfe, 0xf0,

    /* U+006B "k" */
    0x60, 0x70, 0x38, 0x1c, 0xe, 0x7, 0x3b, 0x9d,
    0xdc, 0xfc, 0x7e, 0x3f, 0x1f, 0x8e, 0xe7, 0x73,
    0x9d, 0xcf,

    /* U+006C "l" */
    0xe7, 0x39, 0xce, 0x73, 0x9c, 0xe7, 0x39, 0xce,
    0x7b, 0xef,

    /* U+006D "m" */
    0xce, 0xef, 0xff, 0xe7, 0x7e, 0x77, 0xe7, 0x7e,
    0x77, 0xe7, 0x7e, 0x77, 0xe7, 0x7e, 0x77, 0xe7,
    0x70,

    /* U+006E "n" */
    0xce, 0xff, 0xe7, 0xe7, 0xe7, 0xe7, 0xe7, 0xe7,
    0xe7, 0xe7, 0xe7,

    /* U+006F "o" */
    0x3e, 0x3f, 0x9d, 0xdc, 0x7e, 0x3f, 0x1f, 0x8f,
    0xc7, 0x77, 0x3f, 0x8f, 0x80,

    /* U+0070 "p" */
    0xdc, 0xfe, 0xe7, 0xe7, 0xe7, 0xe7, 0xe7, 0xe7,
    0xe7, 0xfe, 0xfc, 0xe0, 0xe0, 0xe0, 0xe0,

    /* U+0071 "q" */
    0x3b, 0x7f, 0xe7, 0xe7, 0xe7, 0xe7, 0xe7, 0xe7,
    0xe7, 0x7f, 0x3f, 0x7, 0x7, 0x7, 0x7,

    /* U+0072 "r" */
    0xcf, 0xff, 0xf8, 0xe3, 0x8e, 0x38, 0xe3, 0x8e,
    0x0,

    /* U+0073 "s" */
    0x3d, 0xfb, 0x97, 0xf, 0x8f, 0x8f, 0x87, 0x8f,
    0xff, 0xf0,

    /* U+0074 "t" */
    0x38, 0x38, 0x38, 0xfe, 0xfe, 0x38, 0x38, 0x38,
    0x38, 0x38, 0x38, 0x3e, 0x3f, 0x1e,

    /* U+0075 "u" */
    0xe7, 0xe7, 0xe7, 0xe7, 0xe7, 0xe7, 0xe7, 0xe7,
    0xe7, 0xff, 0x7b,

    /* U+0076 "v" */
    0x73, 0x9c, 0xe7, 0x39, 0xce, 0x73, 0xf, 0xc3,
    0xf0, 0xf8, 0x1e, 0x7, 0x81, 0xe0,

    /* U+0077 "w" */
    0xe7, 0x3f, 0x39, 0xdd, 0xcc, 0xee, 0xe7, 0xdf,
    0x3e, 0xf8, 0xf7, 0x87, 0xbc, 0x3d, 0xe1, 0xcf,
    0xe, 0x70,

    /* U+0078 "x" */
    0x73, 0x9c, 0xe7, 0xf8, 0xfc, 0x3e, 0x7, 0x81,
    0xe0, 0xfc, 0x7f, 0x1c, 0xef, 0x3c,

    /* U+0079 "y" */
    0x61, 0x9c, 0xe7, 0x39, 0xce, 0x73, 0x8e, 0xe3,
    0xb0, 0xfc, 0x1f, 0x7, 0xc1, 0xe0, 0x38, 0xe,
    0x13, 0x87, 0xc1, 0xe0,

    /* U+007A "z" */
    0x7f, 0x7f, 0xf, 0xe, 0x1e, 0x1c, 0x38, 0x38,
    0x70, 0xff, 0xff,

    /* U+007B "{" */
    0x1e, 0x7c, 0xe1, 0xc3, 0x87, 0xe, 0x1c, 0x39,
    0xe3, 0x87, 0x83, 0x87, 0xe, 0x1c, 0x38, 0x70,
    0xe1, 0xf1, 0xe0,

    /* U+007C "|" */
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc,

    /* U+007D "}" */
    0xf1, 0xf0, 0xe1, 0xc3, 0x87, 0xe, 0x1c, 0x38,
    0x3c, 0x38, 0xf3, 0x87, 0xe, 0x1c, 0x38, 0x70,
    0xe7, 0xcf, 0x0,

    /* U+007E "~" */
    0x70, 0x3c, 0xd3, 0xe0, 0xe0
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 109, .box_w = 4, .box_h = 15, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 8, .adv_w = 152, .box_w = 7, .box_h = 6, .ofs_x = 1, .ofs_y = 9},
    {.bitmap_index = 14, .adv_w = 212, .box_w = 12, .box_h = 16, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 38, .adv_w = 152, .box_w = 8, .box_h = 19, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 57, .adv_w = 268, .box_w = 16, .box_h = 15, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 87, .adv_w = 198, .box_w = 12, .box_h = 15, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 110, .adv_w = 91, .box_w = 3, .box_h = 6, .ofs_x = 1, .ofs_y = 9},
    {.bitmap_index = 113, .adv_w = 133, .box_w = 6, .box_h = 22, .ofs_x = 1, .ofs_y = -6},
    {.bitmap_index = 130, .adv_w = 133, .box_w = 6, .box_h = 22, .ofs_x = 1, .ofs_y = -6},
    {.bitmap_index = 147, .adv_w = 163, .box_w = 9, .box_h = 9, .ofs_x = 1, .ofs_y = 6},
    {.bitmap_index = 158, .adv_w = 152, .box_w = 9, .box_h = 9, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 169, .adv_w = 94, .box_w = 4, .box_h = 8, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 173, .adv_w = 124, .box_w = 6, .box_h = 3, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 176, .adv_w = 94, .box_w = 4, .box_h = 4, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 178, .adv_w = 137, .box_w = 8, .box_h = 21, .ofs_x = 0, .ofs_y = -5},
    {.bitmap_index = 199, .adv_w = 152, .box_w = 9, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 215, .adv_w = 152, .box_w = 8, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 229, .adv_w = 152, .box_w = 8, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 243, .adv_w = 152, .box_w = 8, .box_h = 14, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 257, .adv_w = 152, .box_w = 9, .box_h = 15, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 274, .adv_w = 152, .box_w = 8, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 288, .adv_w = 152, .box_w = 8, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 302, .adv_w = 152, .box_w = 8, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 315, .adv_w = 152, .box_w = 9, .box_h = 15, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 332, .adv_w = 152, .box_w = 8, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 346, .adv_w = 97, .box_w = 4, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 352, .adv_w = 97, .box_w = 4, .box_h = 14, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 359, .adv_w = 152, .box_w = 9, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 375, .adv_w = 152, .box_w = 9, .box_h = 7, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 383, .adv_w = 152, .box_w = 9, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 399, .adv_w = 154, .box_w = 8, .box_h = 15, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 414, .adv_w = 302, .box_w = 15, .box_h = 18, .ofs_x = 2, .ofs_y = -3},
    {.bitmap_index = 448, .adv_w = 183, .box_w = 11, .box_h = 15, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 469, .adv_w = 172, .box_w = 9, .box_h = 15, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 486, .adv_w = 155, .box_w = 8, .box_h = 15, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 501, .adv_w = 179, .box_w = 9, .box_h = 15, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 518, .adv_w = 149, .box_w = 8, .box_h = 15, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 533, .adv_w = 140, .box_w = 7, .box_h = 15, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 547, .adv_w = 177, .box_w = 9, .box_h = 15, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 564, .adv_w = 183, .box_w = 9, .box_h = 15, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 581, .adv_w = 105, .box_w = 6, .box_h = 15, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 593, .adv_w = 148, .box_w = 8, .box_h = 15, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 608, .adv_w = 179, .box_w = 10, .box_h = 15, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 627, .adv_w = 147, .box_w = 7, .box_h = 15, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 641, .adv_w = 215, .box_w = 11, .box_h = 15, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 662, .adv_w = 184, .box_w = 9, .box_h = 15, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 679, .adv_w = 181, .box_w = 10, .box_h = 15, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 698, .adv_w = 160, .box_w = 8, .box_h = 15, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 713, .adv_w = 181, .box_w = 11, .box_h = 17, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 737, .adv_w = 171, .box_w = 9, .box_h = 15, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 754, .adv_w = 156, .box_w = 8, .box_h = 15, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 769, .adv_w = 146, .box_w = 9, .box_h = 15, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 786, .adv_w = 188, .box_w = 10, .box_h = 15, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 805, .adv_w = 169, .box_w = 10, .box_h = 15, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 824, .adv_w = 237, .box_w = 15, .box_h = 15, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 853, .adv_w = 175, .box_w = 11, .box_h = 15, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 874, .adv_w = 164, .box_w = 11, .box_h = 15, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 895, .adv_w = 161, .box_w = 9, .box_h = 15, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 912, .adv_w = 138, .box_w = 5, .box_h = 21, .ofs_x = 2, .ofs_y = -5},
    {.bitmap_index = 926, .adv_w = 137, .box_w = 9, .box_h = 21, .ofs_x = 0, .ofs_y = -5},
    {.bitmap_index = 950, .adv_w = 138, .box_w = 5, .box_h = 21, .ofs_x = 1, .ofs_y = -5},
    {.bitmap_index = 964, .adv_w = 152, .box_w = 9, .box_h = 7, .ofs_x = 0, .ofs_y = 8},
    {.bitmap_index = 972, .adv_w = 173, .box_w = 11, .box_h = 2, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 975, .adv_w = 152, .box_w = 5, .box_h = 5, .ofs_x = 2, .ofs_y = 12},
    {.bitmap_index = 979, .adv_w = 149, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 990, .adv_w = 160, .box_w = 8, .box_h = 16, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1006, .adv_w = 135, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1017, .adv_w = 160, .box_w = 8, .box_h = 16, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1033, .adv_w = 154, .box_w = 9, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1046, .adv_w = 111, .box_w = 7, .box_h = 16, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1060, .adv_w = 160, .box_w = 8, .box_h = 16, .ofs_x = 1, .ofs_y = -5},
    {.bitmap_index = 1076, .adv_w = 161, .box_w = 8, .box_h = 16, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1092, .adv_w = 92, .box_w = 4, .box_h = 16, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1100, .adv_w = 92, .box_w = 6, .box_h = 21, .ofs_x = -1, .ofs_y = -5},
    {.bitmap_index = 1116, .adv_w = 156, .box_w = 9, .box_h = 16, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1134, .adv_w = 93, .box_w = 5, .box_h = 16, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1144, .adv_w = 231, .box_w = 12, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1161, .adv_w = 163, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1172, .adv_w = 161, .box_w = 9, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1185, .adv_w = 160, .box_w = 8, .box_h = 15, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 1200, .adv_w = 160, .box_w = 8, .box_h = 15, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 1215, .adv_w = 116, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1224, .adv_w = 133, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1234, .adv_w = 122, .box_w = 8, .box_h = 14, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1248, .adv_w = 160, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1259, .adv_w = 158, .box_w = 10, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1273, .adv_w = 207, .box_w = 13, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1291, .adv_w = 159, .box_w = 10, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1305, .adv_w = 159, .box_w = 10, .box_h = 16, .ofs_x = 0, .ofs_y = -5},
    {.bitmap_index = 1325, .adv_w = 143, .box_w = 8, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1336, .adv_w = 153, .box_w = 7, .box_h = 21, .ofs_x = 1, .ofs_y = -5},
    {.bitmap_index = 1355, .adv_w = 115, .box_w = 3, .box_h = 18, .ofs_x = 2, .ofs_y = -3},
    {.bitmap_index = 1362, .adv_w = 153, .box_w = 7, .box_h = 21, .ofs_x = 1, .ofs_y = -5},
    {.bitmap_index = 1381, .adv_w = 152, .box_w = 9, .box_h = 4, .ofs_x = 0, .ofs_y = 5}
};

/*---------------------
 *  CHARACTER MAPPING
 *--------------------*/



/*Collect the unicode lists and glyph_id offsets*/
static const lv_font_fmt_txt_cmap_t cmaps[] =
{
    {
        .range_start = 33, .range_length = 94, .glyph_id_start = 1,
        .unicode_list = NULL, .glyph_id_ofs_list = NULL, .list_length = 0, .type = LV_FONT_FMT_TXT_CMAP_FORMAT0_TINY
    }
};

/*-----------------
 *    KERNING
 *----------------*/


/*Map glyph_ids to kern left classes*/
static const uint8_t kern_left_class_mapping[] =
{
    0, 0, 1, 0, 0, 0, 0, 1,
    2, 0, 0, 3, 4, 5, 4, 6,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 7, 7, 3, 3, 3, 0,
    0, 8, 9, 10, 11, 0, 12, 13,
    0, 0, 14, 15, 16, 0, 0, 11,
    17, 11, 18, 19, 20, 14, 21, 22,
    23, 24, 25, 0, 0, 0, 0, 4,
    0, 26, 27, 28, 0, 29, 30, 0,
    0, 0, 0, 31, 0, 0, 0, 27,
    27, 0, 32, 33, 34, 0, 35, 36,
    37, 35, 28, 0, 0, 0, 5
};

/*Map glyph_ids to kern right classes*/
static const uint8_t kern_right_class_mapping[] =
{
    0, 0, 1, 0, 0, 0, 0, 1,
    0, 0, 0, 2, 3, 4, 3, 5,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 6, 6, 2, 2, 2, 0,
    0, 7, 0, 8, 0, 0, 0, 8,
    0, 0, 9, 0, 0, 0, 0, 8,
    0, 8, 0, 10, 11, 12, 13, 14,
    15, 16, 17, 0, 0, 0, 0, 3,
    0, 18, 0, 19, 19, 19, 0, 20,
    0, 0, 21, 0, 0, 22, 22, 19,
    22, 19, 22, 23, 24, 22, 25, 26,
    27, 25, 28, 0, 0, 0, 4
};

/*Kern values between classes*/
static const int8_t kern_class_values[] =
{
    0, 0, -62, 0, 0, 0, -22, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    16, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, -5, 0,
    -6, 0, -16, 0, -10, -2, -6, -16,
    -5, 0, 0, 0, 0, 0, 0, 0,
    0, 0, -5, 0, -62, 0, 0, 0,
    0, 0, 0, -6, 0, 0, -26, 0,
    -21, -18, 0, -26, 0, 0, -5, 0,
    0, 0, 0, -6, -16, -13, 0, 0,
    0, 0, 0, 0, 0, 0, -5, 0,
    -3, -6, -19, 0, -8, -6, -16, -19,
    -13, -3, 0, 0, 0, 0, 0, 0,
    -3, -3, -14, -10, 0, 0, 0, 0,
    -22, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, -16, 0, -5, -2, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, -22, 0, 0, 0,
    0, 0, 0, -6, 0, 0, -16, -3,
    -14, -8, 0, -19, 0, 0, 0, 0,
    0, 0, 0, -6, -11, -6, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, -3, 0, -5, 0, -5, -8,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, -6, 0, -13,
    0, 0, 0, -6, -3, 0, 0, 0,
    -3, -2, -5, -3, -2, 0, 0, 0,
    0, 0, 0, 0, -5, 0, 0, 0,
    0, 0, -8, 0, 0, -3, -6, 0,
    -10, -2, -8, 0, -6, 0, -13, -14,
    -3, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, -32, 0,
    0, 0, -11, -3, -8, -2, 0, 0,
    0, 0, -2, 0, 0, -6, -6, 0,
    0, -2, -2, 0, 0, 0, -6, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, -3, 0, -4, -2, -6, -5,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, -3, 0, -3, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, -10, 0, -18, 0, 0, 0, -14,
    0, -5, 0, 0, 0, 0, 0, 0,
    0, -3, -8, 0, 0, 0, 0, 0,
    -11, -8, 0, 0, -19, -13, 0, -22,
    0, 0, 0, -10, 0, -2, -21, -5,
    -14, -11, 0, -21, 0, 0, -5, 0,
    0, 0, 0, 0, -6, -3, 0, 0,
    0, 0, -42, 0, -16, 0, -11, 0,
    -10, 0, -2, 0, 0, 0, -8, -4,
    -5, -6, -8, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, -3,
    0, 0, 0, -3, 0, -2, -6, 0,
    -3, 0, 0, -10, 0, -3, -5, 0,
    0, 0, 0, 0, -5, 0, 0, 0,
    0, 0, -3, 0, 0, 0, -2, -2,
    -3, -3, -3, 0, -2, -3, -6, -3,
    -2, 0, 0, 0, 0, 0, 0, 0,
    -6, -2, -3, 0, 0, -16, -26, -19,
    0, -16, -16, -8, -14, 0, -10, 0,
    6, 5, 0, 10, 0, -16, -19, -11,
    0, -14, -16, 0, -11, 0, 0, 0,
    0, -10, -21, -8, -10, -5, -14, -5,
    -8, -2, 2, 0, 0, 0, 0, 0,
    0, -13, -11, -13, 0, -6, 0, 0,
    0, 0, 0, -10, 0, -2, -18, -6,
    0, -2, -8, -4, -3, -1, 0, 0,
    0, 0, 0, 0, 0, -3, -6, 0,
    0, -2, 0, 0, -3, 0, 0, 0,
    0, -6, 0, -16, 0, 0, 0, -13,
    0, -6, 0, 0, 0, 0, 0, 0,
    0, -5, -10, 0, 0, 0, -4, 0,
    -6, -5, 0, 0, 0, -16, -26, -19,
    0, -10, -19, -13, -11, -6, 3, 0,
    0, 0, 0, 0, 0, -19, -21, -22,
    0, -10, -13, 0, 0, 0, 0, -13,
    0, -5, 0, -16, 0, 0, 0, -3,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, -6, 0, 0, 0, 0, 0,
    -3, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, -3, 0, 0, 0,
    0, 0, -5, 0, 0, -5, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    -4, -2, -7, 0, 0, 0, 0, -6,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    -2, 0, 0, 0, 16, 0, -10, -10,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, -6, 0, -16, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, -6, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 6, -6, -19, -16,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, -2, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, -3, -6, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, -2, 0,
    0, 0, 0, 0, 0, 0, 0, -8,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, -2, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, -16, -4, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, -5, -4, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, -13, -3,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, -3, -2, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, -5, 0, -14, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, -6, 0, 0, 0, 0, 0,
    0, 0, 0, 0
};


/*Collect the kern class' data in one place*/
static const lv_font_fmt_txt_kern_classes_t kern_classes =
{
    .class_pair_values   = kern_class_values,
    .left_class_mapping  = kern_left_class_mapping,
    .right_class_mapping = kern_right_class_mapping,
    .left_class_cnt      = 37,
    .right_class_cnt     = 28,
};

/*--------------------
 *  ALL CUSTOM DATA
 *--------------------*/

#if LVGL_VERSION_MAJOR == 8
/*Store all the custom data of the font*/
static  lv_font_fmt_txt_glyph_cache_t cache;
#endif

#if LVGL_VERSION_MAJOR >= 8
static const lv_font_fmt_txt_dsc_t font_dsc = {
#else
static lv_font_fmt_txt_dsc_t font_dsc = {
#endif
    .glyph_bitmap = glyph_bitmap,
    .glyph_dsc = glyph_dsc,
    .cmaps = cmaps,
    .kern_dsc = &kern_classes,
    .kern_scale = 16,
    .cmap_num = 1,
    .bpp = 1,
    .kern_classes = 1,
    .bitmap_format = 0,
#if LVGL_VERSION_MAJOR == 8
    .cache = &cache
#endif
};

extern const lv_font_t lv_font_montserrat_28;


/*-----------------
 *  PUBLIC FONT
 *----------------*/

/*Initialize a public general font descriptor*/
#if LVGL_VERSION_MAJOR >= 8
const lv_font_t axel_20_text = {
#else
lv_font_t axel_20_text = {
#endif
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,    /*Function pointer to get glyph's data*/
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,    /*Function pointer to get glyph's bitmap*/
    .line_height = 23,          /*The maximum line height required by the font*/
    .base_line = 6,             /*Baseline measured from the bottom of the line*/
#if !(LVGL_VERSION_MAJOR == 6 && LVGL_VERSION_MINOR == 0)
    .subpx = LV_FONT_SUBPX_NONE,
#endif
#if LV_VERSION_CHECK(7, 4, 0) || LVGL_VERSION_MAJOR >= 8
    .underline_position = -1,
    .underline_thickness = 2,
#endif
    .dsc = &font_dsc,          /*The custom font data. Will be accessed by `get_glyph_bitmap/dsc` */
#if LV_VERSION_CHECK(8, 2, 0) || LVGL_VERSION_MAJOR >= 9
    .fallback = &lv_font_montserrat_28,
#endif
    .user_data = NULL,
};



#endif /*#if AXEL_20_TEXT*/

