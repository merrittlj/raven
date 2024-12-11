/*******************************************************************************
 * Size: 18 px
 * Bpp: 1
 * Opts: --bpp 1 --size 18 --font Lato-Regular.ttf --symbols ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz!@#$%^&*()_+-={}|;:"'<>,.?/ --format lvgl -o lato_18.c
 ******************************************************************************/

#ifdef LV_LVGL_H_INCLUDE_SIMPLE
#include "lvgl.h"
#else
#include "lvgl/lvgl.h"
#endif

#ifndef LATO_18
#define LATO_18 1
#endif

#if LATO_18

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+0021 "!" */
    0xff, 0xff, 0x3, 0xc0,

    /* U+0022 "\"" */
    0xde, 0xf7, 0xb0,

    /* U+0023 "#" */
    0x9, 0x82, 0x61, 0x90, 0x64, 0x7f, 0xc4, 0xc1,
    0x30, 0xc8, 0xff, 0x88, 0x82, 0x60, 0x98, 0x24,
    0x0,

    /* U+0024 "$" */
    0x4, 0x2, 0x7, 0x86, 0xf6, 0x43, 0x21, 0x90,
    0x78, 0x1f, 0x5, 0xc2, 0x61, 0x34, 0x9b, 0x58,
    0xf8, 0x10, 0x8, 0x0,

    /* U+0025 "%" */
    0x78, 0x37, 0x61, 0x31, 0x11, 0x89, 0x8c, 0x48,
    0x74, 0x81, 0xec, 0x0, 0xde, 0x5, 0x88, 0x4c,
    0x46, 0x62, 0x63, 0x12, 0xf, 0x0,

    /* U+0026 "&" */
    0xe, 0x1, 0x30, 0x21, 0x2, 0x0, 0x20, 0x3,
    0x0, 0x38, 0x6, 0xc4, 0xc6, 0x4c, 0x3c, 0xc1,
    0x86, 0x3c, 0x3e, 0x60,

    /* U+0027 "'" */
    0xff,

    /* U+0028 "(" */
    0x3, 0x26, 0x6c, 0xcc, 0xcc, 0xcc, 0x66, 0x23,
    0x0,

    /* U+0029 ")" */
    0xc, 0x46, 0x63, 0x33, 0x33, 0x33, 0x66, 0x4c,
    0x0,

    /* U+002A "*" */
    0x25, 0x5d, 0xf2, 0x0,

    /* U+002B "+" */
    0x18, 0xc, 0x6, 0x1f, 0xf1, 0x80, 0xc0, 0x60,
    0x30,

    /* U+002C "," */
    0xf6,

    /* U+002D "-" */
    0xf0,

    /* U+002E "." */
    0xf0,

    /* U+002F "/" */
    0x6, 0x8, 0x30, 0x40, 0x83, 0x4, 0x18, 0x20,
    0x41, 0x2, 0xc, 0x10, 0x0,

    /* U+003A ":" */
    0xf0, 0x3, 0xc0,

    /* U+003B ";" */
    0xf0, 0x3, 0xd8,

    /* U+003C "<" */
    0x0, 0xc, 0x63, 0xe, 0x7, 0x3, 0x81,

    /* U+003D "=" */
    0xff, 0x0, 0x0, 0xff,

    /* U+003E ">" */
    0x1, 0x80, 0xc0, 0x60, 0xe7, 0x38, 0x40,

    /* U+003F "?" */
    0x79, 0x1c, 0x18, 0x30, 0xe3, 0xc, 0x10, 0x20,
    0x0, 0x1, 0x83, 0x0,

    /* U+0040 "@" */
    0xf, 0x80, 0x83, 0x8, 0x4, 0x80, 0x18, 0x3c,
    0xc2, 0x66, 0x22, 0x31, 0x11, 0x89, 0x94, 0x37,
    0x10, 0x0, 0xc0, 0x3, 0x83, 0x7, 0xe0,

    /* U+0041 "A" */
    0x6, 0x0, 0x70, 0xf, 0x0, 0x90, 0x19, 0x81,
    0x88, 0x10, 0xc3, 0xc, 0x3f, 0xc6, 0x6, 0x60,
    0x24, 0x3, 0xc0, 0x30,

    /* U+0042 "B" */
    0xfe, 0x61, 0xb0, 0x78, 0x3c, 0x1e, 0x1b, 0xf9,
    0x86, 0xc1, 0xe0, 0xf0, 0x78, 0x6f, 0xe0,

    /* U+0043 "C" */
    0xf, 0xc7, 0xd, 0x80, 0x30, 0xc, 0x1, 0x80,
    0x30, 0x6, 0x0, 0xc0, 0xc, 0x1, 0x80, 0x18,
    0x30, 0xf8,

    /* U+0044 "D" */
    0xfe, 0x18, 0x33, 0x3, 0x60, 0x6c, 0x7, 0x80,
    0xf0, 0x1e, 0x3, 0xc0, 0x78, 0x1b, 0x3, 0x60,
    0xcf, 0xe0,

    /* U+0045 "E" */
    0xff, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xfe, 0xc0,
    0xc0, 0xc0, 0xc0, 0xc0, 0xff,

    /* U+0046 "F" */
    0xff, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xfe, 0xc0,
    0xc0, 0xc0, 0xc0, 0xc0, 0xc0,

    /* U+0047 "G" */
    0xf, 0xc6, 0x1d, 0x80, 0x30, 0xc, 0x1, 0x80,
    0x30, 0x6, 0xf, 0xc0, 0x6c, 0xd, 0x81, 0x98,
    0x70, 0xfc,

    /* U+0048 "H" */
    0xc0, 0x78, 0xf, 0x1, 0xe0, 0x3c, 0x7, 0x80,
    0xff, 0xfe, 0x3, 0xc0, 0x78, 0xf, 0x1, 0xe0,
    0x3c, 0x6,

    /* U+0049 "I" */
    0xff, 0xff, 0xff, 0xc0,

    /* U+004A "J" */
    0xc, 0x30, 0xc3, 0xc, 0x30, 0xc3, 0xc, 0x30,
    0xc6, 0xf0,

    /* U+004B "K" */
    0xc0, 0xd8, 0x33, 0xc, 0x63, 0xc, 0xc1, 0x98,
    0x3e, 0x6, 0x60, 0xc6, 0x18, 0x63, 0xc, 0x60,
    0xcc, 0xc,

    /* U+004C "L" */
    0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0,
    0xc0, 0xc0, 0xc0, 0xc0, 0xff,

    /* U+004D "M" */
    0xc0, 0xf, 0x80, 0x7e, 0x1, 0xfc, 0xf, 0xd0,
    0x2f, 0x61, 0xbc, 0xc4, 0xf1, 0x33, 0xc7, 0x8f,
    0xc, 0x3c, 0x30, 0xf0, 0x3, 0xc0, 0xc,

    /* U+004E "N" */
    0xc0, 0x78, 0xf, 0x81, 0xf8, 0x3d, 0x87, 0x98,
    0xf1, 0x1e, 0x33, 0xc3, 0x78, 0x3f, 0x3, 0xe0,
    0x3c, 0x6,

    /* U+004F "O" */
    0xf, 0x81, 0x83, 0x18, 0xc, 0xc0, 0x6c, 0x1,
    0xe0, 0xf, 0x0, 0x78, 0x3, 0xc0, 0x1b, 0x1,
    0x98, 0xc, 0x60, 0xc0, 0xf8, 0x0,

    /* U+0050 "P" */
    0xfe, 0x61, 0xb0, 0x78, 0x3c, 0x1e, 0xf, 0xd,
    0xfc, 0xc0, 0x60, 0x30, 0x18, 0xc, 0x0,

    /* U+0051 "Q" */
    0xf, 0x80, 0xc1, 0x86, 0x3, 0x18, 0xc, 0xc0,
    0x1b, 0x0, 0x6c, 0x1, 0xb0, 0x6, 0xc0, 0x19,
    0x80, 0xc6, 0x3, 0xc, 0x18, 0xf, 0xc0, 0x1,
    0x80, 0x3, 0x0, 0x6,

    /* U+0052 "R" */
    0xfe, 0x30, 0xcc, 0x1b, 0x6, 0xc1, 0xb0, 0x6c,
    0x33, 0xf0, 0xcc, 0x31, 0x8c, 0x33, 0x6, 0xc0,
    0xc0,

    /* U+0053 "S" */
    0x1f, 0x18, 0x98, 0xc, 0x7, 0x3, 0xe0, 0xfc,
    0xf, 0x1, 0x80, 0xc0, 0x6c, 0x63, 0xe0,

    /* U+0054 "T" */
    0xff, 0xc3, 0x0, 0xc0, 0x30, 0xc, 0x3, 0x0,
    0xc0, 0x30, 0xc, 0x3, 0x0, 0xc0, 0x30, 0xc,
    0x0,

    /* U+0055 "U" */
    0xc0, 0xf0, 0x3c, 0xf, 0x3, 0xc0, 0xf0, 0x3c,
    0xf, 0x3, 0xc0, 0xf0, 0x36, 0x19, 0x86, 0x1e,
    0x0,

    /* U+0056 "V" */
    0xc0, 0x34, 0x3, 0x60, 0x66, 0x6, 0x30, 0x43,
    0xc, 0x10, 0xc1, 0x98, 0x9, 0x80, 0xd0, 0xf,
    0x0, 0x70, 0x6, 0x0,

    /* U+0057 "W" */
    0xc0, 0xc0, 0xd0, 0x30, 0x36, 0xe, 0x9, 0x87,
    0x86, 0x21, 0xa1, 0x8c, 0x4c, 0x63, 0x33, 0x30,
    0xcc, 0x4c, 0x1a, 0x1b, 0x7, 0x86, 0x81, 0xe0,
    0xe0, 0x30, 0x38, 0xc, 0xc, 0x0,

    /* U+0058 "X" */
    0x60, 0x6c, 0x18, 0xc3, 0xc, 0xc1, 0xb0, 0x1e,
    0x3, 0x80, 0x78, 0x19, 0x6, 0x30, 0xc3, 0x30,
    0x6c, 0x6,

    /* U+0059 "Y" */
    0x60, 0x66, 0x6, 0x30, 0xc3, 0xc, 0x19, 0x80,
    0xd0, 0xf, 0x0, 0x60, 0x6, 0x0, 0x60, 0x6,
    0x0, 0x60, 0x6, 0x0,

    /* U+005A "Z" */
    0x7f, 0xc0, 0x70, 0x18, 0xc, 0x7, 0x1, 0x80,
    0xc0, 0x70, 0x38, 0xe, 0x7, 0x3, 0x80, 0xff,
    0xc0,

    /* U+005E "^" */
    0x8, 0x18, 0x3c, 0x24, 0x62, 0x43,

    /* U+005F "_" */
    0xfe,

    /* U+0061 "a" */
    0x3c, 0x8c, 0x18, 0x33, 0xfc, 0xf1, 0xe7, 0x76,

    /* U+0062 "b" */
    0xc0, 0xc0, 0xc0, 0xc0, 0xdc, 0xe6, 0xc3, 0xc3,
    0xc3, 0xc3, 0xc3, 0xc6, 0xfc,

    /* U+0063 "c" */
    0x3e, 0x62, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0x63,
    0x3e,

    /* U+0064 "d" */
    0x3, 0x3, 0x3, 0x3, 0x3f, 0x63, 0xc3, 0xc3,
    0xc3, 0xc3, 0xc3, 0x67, 0x3b,

    /* U+0065 "e" */
    0x3c, 0x62, 0xc1, 0xff, 0xc0, 0xc0, 0xc0, 0x63,
    0x3e,

    /* U+0066 "f" */
    0x3b, 0x18, 0xcf, 0xb1, 0x8c, 0x63, 0x18, 0xc6,
    0x0,

    /* U+0067 "g" */
    0x7f, 0xe1, 0xb0, 0xd8, 0x63, 0xe2, 0x1, 0x0,
    0xfe, 0xc1, 0xe0, 0xf8, 0xc7, 0xc0,

    /* U+0068 "h" */
    0xc0, 0xc0, 0xc0, 0xc0, 0xde, 0xe7, 0xc3, 0xc3,
    0xc3, 0xc3, 0xc3, 0xc3, 0xc3,

    /* U+0069 "i" */
    0xd8, 0x6, 0xdb, 0x6d, 0xb6,

    /* U+006A "j" */
    0x66, 0x0, 0x33, 0x33, 0x33, 0x33, 0x33, 0x3e,

    /* U+006B "k" */
    0xc0, 0xc0, 0xc0, 0xc0, 0xc3, 0xc6, 0xcc, 0xd8,
    0xf0, 0xd8, 0xcc, 0xc6, 0xc3,

    /* U+006C "l" */
    0xff, 0xff, 0xff, 0xc0,

    /* U+006D "m" */
    0xdd, 0xee, 0x73, 0xc6, 0x3c, 0x63, 0xc6, 0x3c,
    0x63, 0xc6, 0x3c, 0x63, 0xc6, 0x30,

    /* U+006E "n" */
    0xde, 0xe7, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3,
    0xc3,

    /* U+006F "o" */
    0x3e, 0x31, 0xb0, 0x78, 0x3c, 0x1e, 0xf, 0x6,
    0xc6, 0x3e, 0x0,

    /* U+0070 "p" */
    0xdc, 0xe6, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xe6,
    0xfc, 0xc0, 0xc0, 0xc0,

    /* U+0071 "q" */
    0x3f, 0x67, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0x67,
    0x3b, 0x3, 0x3, 0x3,

    /* U+0072 "r" */
    0xdf, 0x8c, 0x30, 0xc3, 0xc, 0x30, 0xc0,

    /* U+0073 "s" */
    0x7b, 0xc, 0x38, 0x78, 0x70, 0xe3, 0x78,

    /* U+0074 "t" */
    0x23, 0x19, 0xf6, 0x31, 0x8c, 0x63, 0x18, 0x70,

    /* U+0075 "u" */
    0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xe7,
    0x7b,

    /* U+0076 "v" */
    0xc1, 0xa0, 0x98, 0xc4, 0x63, 0x21, 0xb0, 0x50,
    0x38, 0xc, 0x0,

    /* U+0077 "w" */
    0xc3, 0xd, 0xc, 0x26, 0x71, 0x99, 0x66, 0x24,
    0x90, 0xb2, 0xc3, 0x8f, 0x6, 0x18, 0x18, 0x60,

    /* U+0078 "x" */
    0x61, 0x31, 0x8d, 0x83, 0x81, 0xc0, 0xa0, 0xd8,
    0xc6, 0x41, 0x0,

    /* U+0079 "y" */
    0xc1, 0xb0, 0x98, 0xc4, 0x63, 0x20, 0xb0, 0x70,
    0x38, 0x8, 0xc, 0x4, 0x6, 0x0,

    /* U+007A "z" */
    0xfe, 0x18, 0x30, 0xc3, 0x4, 0x18, 0x60, 0xfe,

    /* U+007B "{" */
    0x3b, 0x18, 0xc6, 0x31, 0x8c, 0x83, 0x18, 0xc6,
    0x31, 0x87,

    /* U+007C "|" */
    0xff, 0xff, 0x80,

    /* U+007D "}" */
    0xe1, 0x8c, 0x63, 0x18, 0xc6, 0x9, 0x8c, 0x63,
    0x18, 0xdc
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 99, .box_w = 2, .box_h = 13, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 4, .adv_w = 114, .box_w = 5, .box_h = 4, .ofs_x = 1, .ofs_y = 9},
    {.bitmap_index = 7, .adv_w = 167, .box_w = 10, .box_h = 13, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 24, .adv_w = 167, .box_w = 9, .box_h = 17, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 44, .adv_w = 226, .box_w = 13, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 66, .adv_w = 202, .box_w = 12, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 86, .adv_w = 66, .box_w = 2, .box_h = 4, .ofs_x = 1, .ofs_y = 9},
    {.bitmap_index = 87, .adv_w = 86, .box_w = 4, .box_h = 17, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 96, .adv_w = 86, .box_w = 4, .box_h = 17, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 105, .adv_w = 115, .box_w = 5, .box_h = 5, .ofs_x = 1, .ofs_y = 8},
    {.bitmap_index = 109, .adv_w = 167, .box_w = 9, .box_h = 8, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 118, .adv_w = 61, .box_w = 2, .box_h = 4, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 119, .adv_w = 100, .box_w = 4, .box_h = 1, .ofs_x = 1, .ofs_y = 5},
    {.bitmap_index = 120, .adv_w = 61, .box_w = 2, .box_h = 2, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 121, .adv_w = 107, .box_w = 7, .box_h = 14, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 134, .adv_w = 73, .box_w = 2, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 137, .adv_w = 73, .box_w = 2, .box_h = 11, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 140, .adv_w = 167, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 147, .adv_w = 167, .box_w = 8, .box_h = 4, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 151, .adv_w = 167, .box_w = 7, .box_h = 8, .ofs_x = 2, .ofs_y = 2},
    {.bitmap_index = 158, .adv_w = 115, .box_w = 7, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 170, .adv_w = 237, .box_w = 13, .box_h = 14, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 193, .adv_w = 196, .box_w = 12, .box_h = 13, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 213, .adv_w = 186, .box_w = 9, .box_h = 13, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 228, .adv_w = 197, .box_w = 11, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 246, .adv_w = 217, .box_w = 11, .box_h = 13, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 264, .adv_w = 167, .box_w = 8, .box_h = 13, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 277, .adv_w = 163, .box_w = 8, .box_h = 13, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 290, .adv_w = 211, .box_w = 11, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 308, .adv_w = 218, .box_w = 11, .box_h = 13, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 326, .adv_w = 88, .box_w = 2, .box_h = 13, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 330, .adv_w = 128, .box_w = 6, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 340, .adv_w = 196, .box_w = 11, .box_h = 13, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 358, .adv_w = 148, .box_w = 8, .box_h = 13, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 371, .adv_w = 265, .box_w = 14, .box_h = 13, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 394, .adv_w = 218, .box_w = 11, .box_h = 13, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 412, .adv_w = 230, .box_w = 13, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 434, .adv_w = 176, .box_w = 9, .box_h = 13, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 449, .adv_w = 230, .box_w = 14, .box_h = 16, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 477, .adv_w = 185, .box_w = 10, .box_h = 13, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 494, .adv_w = 153, .box_w = 9, .box_h = 13, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 509, .adv_w = 170, .box_w = 10, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 526, .adv_w = 210, .box_w = 10, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 543, .adv_w = 196, .box_w = 12, .box_h = 13, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 563, .adv_w = 293, .box_w = 18, .box_h = 13, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 593, .adv_w = 185, .box_w = 11, .box_h = 13, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 611, .adv_w = 181, .box_w = 12, .box_h = 13, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 631, .adv_w = 180, .box_w = 10, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 648, .adv_w = 167, .box_w = 8, .box_h = 6, .ofs_x = 1, .ofs_y = 7},
    {.bitmap_index = 654, .adv_w = 113, .box_w = 7, .box_h = 1, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 655, .adv_w = 146, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 663, .adv_w = 161, .box_w = 8, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 676, .adv_w = 134, .box_w = 8, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 685, .adv_w = 161, .box_w = 8, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 698, .adv_w = 151, .box_w = 8, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 707, .adv_w = 97, .box_w = 5, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 716, .adv_w = 147, .box_w = 9, .box_h = 12, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 730, .adv_w = 160, .box_w = 8, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 743, .adv_w = 74, .box_w = 3, .box_h = 13, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 748, .adv_w = 73, .box_w = 4, .box_h = 16, .ofs_x = -1, .ofs_y = -3},
    {.bitmap_index = 756, .adv_w = 151, .box_w = 8, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 769, .adv_w = 74, .box_w = 2, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 773, .adv_w = 236, .box_w = 12, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 787, .adv_w = 160, .box_w = 8, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 796, .adv_w = 160, .box_w = 9, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 807, .adv_w = 159, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 819, .adv_w = 161, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 831, .adv_w = 116, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 838, .adv_w = 125, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 845, .adv_w = 107, .box_w = 5, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 853, .adv_w = 160, .box_w = 8, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 862, .adv_w = 147, .box_w = 9, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 873, .adv_w = 221, .box_w = 14, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 889, .adv_w = 145, .box_w = 9, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 900, .adv_w = 147, .box_w = 9, .box_h = 12, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 914, .adv_w = 133, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 922, .adv_w = 86, .box_w = 5, .box_h = 16, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 932, .adv_w = 86, .box_w = 1, .box_h = 17, .ofs_x = 2, .ofs_y = -3},
    {.bitmap_index = 935, .adv_w = 86, .box_w = 5, .box_h = 16, .ofs_x = 0, .ofs_y = -3}
};

/*---------------------
 *  CHARACTER MAPPING
 *--------------------*/



/*Collect the unicode lists and glyph_id offsets*/
static const lv_font_fmt_txt_cmap_t cmaps[] =
{
    {
        .range_start = 33, .range_length = 15, .glyph_id_start = 1,
        .unicode_list = NULL, .glyph_id_ofs_list = NULL, .list_length = 0, .type = LV_FONT_FMT_TXT_CMAP_FORMAT0_TINY
    },
    {
        .range_start = 58, .range_length = 33, .glyph_id_start = 16,
        .unicode_list = NULL, .glyph_id_ofs_list = NULL, .list_length = 0, .type = LV_FONT_FMT_TXT_CMAP_FORMAT0_TINY
    },
    {
        .range_start = 94, .range_length = 2, .glyph_id_start = 49,
        .unicode_list = NULL, .glyph_id_ofs_list = NULL, .list_length = 0, .type = LV_FONT_FMT_TXT_CMAP_FORMAT0_TINY
    },
    {
        .range_start = 97, .range_length = 29, .glyph_id_start = 51,
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
    2, 0, 1, 0, 3, 4, 3, 5,
    0, 0, 0, 0, 0, 0, 6, 7,
    0, 8, 6, 0, 9, 0, 0, 0,
    10, 11, 12, 0, 0, 6, 13, 6,
    14, 0, 15, 10, 5, 16, 11, 17,
    18, 0, 0, 19, 20, 0, 0, 20,
    21, 0, 19, 0, 0, 22, 0, 19,
    19, 20, 20, 0, 23, 0, 0, 0,
    24, 25, 22, 24, 0, 2, 0, 0
};

/*Map glyph_ids to kern right classes*/
static const uint8_t kern_right_class_mapping[] =
{
    0, 0, 1, 0, 0, 0, 2, 1,
    0, 3, 1, 0, 4, 5, 4, 2,
    6, 6, 0, 0, 0, 7, 8, 2,
    0, 8, 0, 0, 0, 8, 0, 0,
    9, 0, 0, 0, 0, 8, 0, 8,
    0, 0, 10, 11, 12, 13, 14, 15,
    16, 0, 0, 17, 0, 18, 18, 18,
    19, 20, 0, 0, 0, 0, 0, 6,
    6, 18, 6, 18, 6, 21, 22, 6,
    23, 24, 25, 23, 26, 0, 0, 3
};

/*Kern values between classes*/
static const int8_t kern_class_values[] =
{
    0, -26, 0, -33, -26, 0, 0, -7,
    0, 0, 0, 7, 7, 0, 4, 0,
    -9, -13, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, -6, 0, 0, 0, 0, 0, 0,
    0, 0, 0, -5, 0, 0, 0, 0,
    0, 0, 0, 0, -33, 0, 0, 0,
    -20, 0, 0, -8, 0, -26, 0, -26,
    -18, 0, -22, 0, 0, 0, 0, 0,
    0, 0, -19, -9, 0, 0, -26, -7,
    0, -20, 0, 0, 0, 0, 0, -26,
    0, -16, -5, -9, -23, -7, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    7, -20, 0, -28, -16, -13, 7, -7,
    -22, 0, 0, 0, 0, 0, 0, 0,
    -17, -17, -4, -20, -15, -6, -7, 0,
    -7, -12, -7, -6, -6, -8, 0, 0,
    0, 0, 0, -14, 0, -7, 0, -4,
    -12, -10, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, -26, 0, 0, 0,
    -7, 0, -8, -6, 7, -19, -8, -20,
    -12, 0, -24, 0, 0, 0, 0, 0,
    0, 0, -12, 0, 0, 0, 0, 0,
    0, 0, -22, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, -19, 0, -26, 0, -9, 4, 0,
    -29, 0, 0, 0, 0, 0, 0, 0,
    0, -10, 0, 0, 0, 0, 0, 0,
    0, 0, 0, -8, 0, -7, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    -9, 0, 0, -4, 0, 0, 0, 0,
    0, 0, 0, 0, 0, -5, -7, 0,
    0, -12, -10, -8, 0, 0, -42, 0,
    0, 8, -29, 0, -7, -12, 0, -25,
    0, -26, -22, 0, -31, 0, 0, -5,
    0, 0, 0, 0, -16, -12, 0, 0,
    0, -20, 0, -36, 0, 0, 0, 0,
    -26, 0, 0, 0, 0, 0, 0, 0,
    -7, -4, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, -7, 0, -7, -6, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, -19, 0, -26,
    -26, -23, 0, -14, -29, 0, 0, 0,
    0, 0, 0, 0, -36, -30, 0, -27,
    -23, 0, -26, -20, -21, -17, 7, -14,
    0, -18, -5, 0, 5, 0, -15, 0,
    0, 0, 0, 0, 0, 0, -13, -5,
    0, -14, -7, 0, 0, 0, 0, 0,
    4, -24, 0, -22, -23, -18, 5, -12,
    -29, 0, 0, 0, 0, 0, 0, 0,
    -18, -23, 0, -25, -18, 0, -14, -13,
    -19, 0, 0, 0, 0, 0, -10, 0,
    5, -8, 0, 0, 0, 0, 0, 0,
    0, 0, 0, -5, 0, 0, -4, 0,
    -6, 0, 0, 0, -10, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, -5, -2, 0, 0, -13, 0,
    -5, 0, 0, 0, 0, 0, 0, 0,
    0, -17, -5, 0, 0, 0, 0, 0,
    0, 0, 0, 0, -4, 0, -9, 0,
    10, 0, 0, -19, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, -9, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, -19,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, -5, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, -12,
    0, -19, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, -4,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, -9, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0
};


/*Collect the kern class' data in one place*/
static const lv_font_fmt_txt_kern_classes_t kern_classes =
{
    .class_pair_values   = kern_class_values,
    .left_class_mapping  = kern_left_class_mapping,
    .right_class_mapping = kern_right_class_mapping,
    .left_class_cnt      = 25,
    .right_class_cnt     = 26,
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
    .cmap_num = 4,
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
const lv_font_t lato_18 = {
#else
lv_font_t lato_18 = {
#endif
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,    /*Function pointer to get glyph's data*/
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,    /*Function pointer to get glyph's bitmap*/
    .line_height = 18,          /*The maximum line height required by the font*/
    .base_line = 3,             /*Baseline measured from the bottom of the line*/
#if !(LVGL_VERSION_MAJOR == 6 && LVGL_VERSION_MINOR == 0)
    .subpx = LV_FONT_SUBPX_NONE,
#endif
#if LV_VERSION_CHECK(7, 4, 0) || LVGL_VERSION_MAJOR >= 8
    .underline_position = -1,
    .underline_thickness = 1,
#endif
    .dsc = &font_dsc,          /*The custom font data. Will be accessed by `get_glyph_bitmap/dsc` */
#if LV_VERSION_CHECK(8, 2, 0) || LVGL_VERSION_MAJOR >= 9
    .fallback = &lv_font_montserrat_28,
#endif
    .user_data = NULL,
};



#endif /*#if LATO_18*/

