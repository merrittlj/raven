/*******************************************************************************
 * Size: 20 px
 * Bpp: 1
 * Opts: --bpp 1 --size 20 --font AxelRegular.TTF --symbols ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789`~!@#$%^&*()-_=+[]{}|;:'",.<>?/\ --format lvgl -o axel_text.c
 ******************************************************************************/

#ifdef LV_LVGL_H_INCLUDE_SIMPLE
#include "lvgl.h"
#else
#include "lvgl/lvgl.h"
#endif

#ifndef AXEL_TEXT
#define AXEL_TEXT 1
#endif

#if AXEL_TEXT

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+0021 "!" */
    0xdb, 0x6d, 0xb6, 0x0, 0xf, 0xc0,

    /* U+0022 "\"" */
    0x99, 0x99, 0x90,

    /* U+0023 "#" */
    0x33, 0x33, 0x22, 0x22, 0xff, 0x26, 0x66, 0x66,
    0x66, 0x66, 0xff, 0x44, 0x44, 0x44, 0xcc,

    /* U+0024 "$" */
    0x10, 0x21, 0xf7, 0xc, 0x18, 0x30, 0x38, 0x38,
    0x18, 0x18, 0x30, 0x71, 0xbe, 0x8, 0x10,

    /* U+0025 "%" */
    0x70, 0x84, 0x44, 0x22, 0x61, 0x12, 0x8, 0x90,
    0x39, 0x80, 0x9, 0xc0, 0xd9, 0x4, 0x88, 0x24,
    0x43, 0x22, 0x11, 0x30, 0x87, 0x0,

    /* U+0026 "&" */
    0x3c, 0x19, 0x86, 0x61, 0x98, 0x66, 0xf, 0x1,
    0x80, 0xa0, 0x6c, 0xf1, 0xbc, 0x2b, 0xe, 0x63,
    0x8f, 0x30,

    /* U+0027 "'" */
    0xf8,

    /* U+0028 "(" */
    0x0, 0xcc, 0x46, 0x33, 0x18, 0xc6, 0x31, 0x8c,
    0x61, 0x8c, 0x21, 0x86, 0x0,

    /* U+0029 ")" */
    0x6, 0x18, 0x43, 0x18, 0x63, 0x18, 0xc6, 0x31,
    0x8c, 0xc6, 0x23, 0x30, 0x0,

    /* U+002A "*" */
    0x10, 0x21, 0xd8, 0xc3, 0x8c, 0x80,

    /* U+002B "+" */
    0x18, 0xc, 0x6, 0x3, 0xf, 0xf8, 0xc0, 0x60,
    0x30, 0x18, 0x0,

    /* U+002C "," */
    0xf7, 0x80,

    /* U+002D "-" */
    0xf8,

    /* U+002E "." */
    0xfc,

    /* U+002F "/" */
    0x0, 0x80, 0xc0, 0x40, 0x60, 0x20, 0x10, 0x18,
    0x8, 0xc, 0x4, 0x2, 0x3, 0x1, 0x0, 0x80,
    0x80, 0x40, 0x60, 0x20, 0x10, 0x0,

    /* U+0030 "0" */
    0x3c, 0x62, 0x62, 0xc3, 0xc7, 0xcb, 0xcb, 0xd3,
    0xe3, 0xe3, 0x42, 0x66, 0x3c,

    /* U+0031 "1" */
    0x18, 0xf3, 0x60, 0xc1, 0x83, 0x6, 0xc, 0x18,
    0x30, 0x60, 0xc7, 0xe0,

    /* U+0032 "2" */
    0x3c, 0x9e, 0x18, 0x30, 0x61, 0xc3, 0xe, 0x18,
    0x61, 0x86, 0xf, 0xe0,

    /* U+0033 "3" */
    0x7d, 0x1c, 0x18, 0x30, 0xcf, 0x3, 0x3, 0x6,
    0xc, 0x1c, 0x6f, 0x80,

    /* U+0034 "4" */
    0xc, 0x6, 0x6, 0x3, 0x3, 0x1, 0x31, 0x98,
    0x8c, 0xc6, 0x7f, 0xc1, 0x80, 0xc0, 0x60,

    /* U+0035 "5" */
    0xfd, 0x2, 0x4, 0x8, 0x1f, 0x23, 0x3, 0x6,
    0xc, 0x18, 0x6f, 0x80,

    /* U+0036 "6" */
    0x1c, 0x61, 0x82, 0xd, 0xdd, 0xb1, 0xe3, 0xc7,
    0x8f, 0x1b, 0x63, 0x80,

    /* U+0037 "7" */
    0xfe, 0xc, 0x10, 0x60, 0xc1, 0x6, 0x8, 0x10,
    0x60, 0x83, 0x6, 0x0,

    /* U+0038 "8" */
    0x3c, 0xe7, 0xc3, 0xc3, 0xe7, 0x7c, 0x3c, 0x66,
    0xc3, 0xc3, 0xc3, 0x66, 0x3c,

    /* U+0039 "9" */
    0x38, 0xdb, 0x1e, 0x3c, 0x78, 0xfb, 0xbb, 0x6,
    0x18, 0x30, 0xc7, 0x0,

    /* U+003A ":" */
    0xf0, 0x0, 0xf0,

    /* U+003B ";" */
    0xf0, 0x3, 0xda,

    /* U+003C "<" */
    0x1, 0x83, 0x87, 0xe, 0xc, 0x3, 0x80, 0x70,
    0xe, 0x1, 0x80,

    /* U+003D "=" */
    0xff, 0x80, 0x0, 0x0, 0xf, 0xf8,

    /* U+003E ">" */
    0xc0, 0x38, 0x7, 0x0, 0xe0, 0x18, 0x38, 0x70,
    0xe0, 0xc0, 0x0,

    /* U+003F "?" */
    0xf8, 0x30, 0xc3, 0x1c, 0xe3, 0x18, 0x61, 0x80,
    0x0, 0x61, 0x80,

    /* U+0040 "@" */
    0x3, 0xf0, 0x1c, 0x10, 0x60, 0x11, 0x80, 0x16,
    0x0, 0x2c, 0x7c, 0x71, 0x98, 0xe6, 0x31, 0xcc,
    0x47, 0x99, 0x8b, 0x33, 0x26, 0x3b, 0x8c, 0x0,
    0xc, 0x0, 0x1c, 0x2, 0x1c, 0xc, 0xf, 0xe0,

    /* U+0041 "A" */
    0xc, 0x3, 0x0, 0xe0, 0x78, 0x1a, 0x4, 0x83,
    0x30, 0xcc, 0x31, 0xf, 0xe6, 0x19, 0x86, 0x40,
    0xb0, 0x30,

    /* U+0042 "B" */
    0xfc, 0xc6, 0xc6, 0xc6, 0xc6, 0xcc, 0xf8, 0xc6,
    0xc3, 0xc3, 0xc3, 0xc3, 0xc6, 0xfc,

    /* U+0043 "C" */
    0x3e, 0x62, 0x60, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0,
    0xc0, 0xc0, 0xc0, 0x60, 0x63, 0x3e,

    /* U+0044 "D" */
    0xf8, 0xc6, 0xc6, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3,
    0xc3, 0xc3, 0xc2, 0xc6, 0xc4, 0xf8,

    /* U+0045 "E" */
    0xff, 0x83, 0x6, 0xc, 0x18, 0x3f, 0x60, 0xc1,
    0x83, 0x6, 0xc, 0x1f, 0xc0,

    /* U+0046 "F" */
    0xff, 0x83, 0x6, 0xc, 0x18, 0x3f, 0x60, 0xc1,
    0x83, 0x6, 0xc, 0x18, 0x0,

    /* U+0047 "G" */
    0x1e, 0x62, 0x60, 0xc0, 0xc0, 0xc0, 0xc0, 0xcf,
    0xc3, 0xc3, 0xc3, 0x63, 0x63, 0x3f,

    /* U+0048 "H" */
    0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xff, 0xc3,
    0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3,

    /* U+0049 "I" */
    0xfb, 0x18, 0xc6, 0x31, 0x8c, 0x63, 0x18, 0xc6,
    0x7c,

    /* U+004A "J" */
    0x3e, 0xc, 0x18, 0x30, 0x60, 0xc1, 0x83, 0x6,
    0xf, 0x1e, 0x3e, 0x4f, 0x80,

    /* U+004B "K" */
    0xc3, 0xc2, 0xc6, 0xcc, 0xc8, 0xd8, 0xf0, 0xf0,
    0xd8, 0xc8, 0xcc, 0xc6, 0xc2, 0xc3,

    /* U+004C "L" */
    0xc1, 0x83, 0x6, 0xc, 0x18, 0x30, 0x60, 0xc1,
    0x83, 0x6, 0xc, 0x1f, 0xc0,

    /* U+004D "M" */
    0xe3, 0xf1, 0xf8, 0xfc, 0x7d, 0x5e, 0xaf, 0x57,
    0xab, 0xd9, 0xe4, 0xf2, 0x78, 0x3c, 0x1e, 0xc,

    /* U+004E "N" */
    0xc3, 0xe3, 0xe3, 0xe3, 0xd3, 0xd3, 0xd3, 0xcb,
    0xcb, 0xcb, 0xc7, 0xc7, 0xc7, 0xc3,

    /* U+004F "O" */
    0x3e, 0x31, 0x98, 0xd8, 0x3c, 0x1e, 0xf, 0x7,
    0x83, 0xc1, 0xe0, 0xf0, 0x6c, 0x66, 0x31, 0xf0,

    /* U+0050 "P" */
    0xfd, 0x9f, 0x1e, 0x3c, 0x78, 0xf3, 0x7c, 0xc1,
    0x83, 0x6, 0xc, 0x18, 0x0,

    /* U+0051 "Q" */
    0x3e, 0x18, 0xc6, 0x33, 0x6, 0xc1, 0xb0, 0x6c,
    0x1b, 0x6, 0xc1, 0xb0, 0x6c, 0x19, 0x8c, 0x63,
    0xf, 0xc0, 0x18,

    /* U+0052 "R" */
    0xfc, 0xce, 0xc6, 0xc6, 0xc6, 0xc6, 0xcc, 0xf8,
    0xd8, 0xc8, 0xcc, 0xc4, 0xc6, 0xc3,

    /* U+0053 "S" */
    0x3c, 0xc3, 0x6, 0xc, 0xe, 0x1e, 0xe, 0xe,
    0xc, 0x18, 0x38, 0xdf, 0x0,

    /* U+0054 "T" */
    0xff, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18,
    0x18, 0x18, 0x18, 0x18, 0x18, 0x18,

    /* U+0055 "U" */
    0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3,
    0xc3, 0xc3, 0xc3, 0xc3, 0x66, 0x3c,

    /* U+0056 "V" */
    0xc1, 0xa0, 0xd0, 0x4c, 0x26, 0x31, 0x18, 0x88,
    0x44, 0x36, 0xb, 0x5, 0x2, 0x81, 0xc0, 0x60,

    /* U+0057 "W" */
    0xc2, 0x1a, 0x18, 0x91, 0x44, 0x8a, 0x26, 0x53,
    0x32, 0x98, 0x94, 0x84, 0xa4, 0x29, 0xa1, 0x45,
    0xe, 0x38, 0x71, 0x81, 0x8c, 0xc, 0x60,

    /* U+0058 "X" */
    0xc1, 0xb1, 0x88, 0xc6, 0xc1, 0x60, 0xe0, 0x20,
    0x38, 0x14, 0x1b, 0x8, 0x8c, 0x64, 0x16, 0xc,

    /* U+0059 "Y" */
    0xc0, 0xd8, 0x66, 0x18, 0xcc, 0x33, 0x4, 0x81,
    0xe0, 0x30, 0xc, 0x3, 0x0, 0xc0, 0x30, 0xc,
    0x3, 0x0,

    /* U+005A "Z" */
    0xfe, 0xc, 0x10, 0x60, 0x83, 0x6, 0x18, 0x30,
    0x41, 0x82, 0xc, 0x1f, 0xc0,

    /* U+005B "[" */
    0xfc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc,
    0xcc, 0xf0,

    /* U+005C "\\" */
    0xc0, 0x20, 0x18, 0x4, 0x2, 0x1, 0x80, 0x40,
    0x30, 0x8, 0x4, 0x3, 0x0, 0x80, 0x40, 0x10,
    0x8, 0x6, 0x1, 0x0, 0x80, 0x20,

    /* U+005D "]" */
    0xf3, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33,
    0x33, 0xf0,

    /* U+005E "^" */
    0xc, 0xa, 0xc, 0x84, 0x66, 0x12, 0xc,

    /* U+005F "_" */
    0xff, 0xc0,

    /* U+0060 "`" */
    0xc6, 0x10,

    /* U+0061 "a" */
    0x7c, 0x8c, 0x18, 0x33, 0xec, 0xf1, 0xe3, 0xce,
    0xe4,

    /* U+0062 "b" */
    0xc1, 0x83, 0x6, 0xc, 0x1f, 0xb9, 0xe3, 0xc7,
    0x8f, 0x1e, 0x3c, 0x79, 0xae, 0x0,

    /* U+0063 "c" */
    0x3c, 0xc7, 0x6, 0xc, 0x18, 0x30, 0x60, 0x62,
    0x78,

    /* U+0064 "d" */
    0x6, 0xc, 0x18, 0x30, 0x67, 0xd9, 0xe3, 0xc7,
    0x8f, 0x1e, 0x3c, 0x6d, 0xde, 0x80,

    /* U+0065 "e" */
    0x38, 0xdb, 0x1e, 0x3f, 0xf8, 0x30, 0x60, 0x64,
    0x78,

    /* U+0066 "f" */
    0x1e, 0x60, 0xc1, 0x83, 0x1f, 0xcc, 0x18, 0x30,
    0x60, 0xc1, 0x83, 0x6, 0xc, 0x0,

    /* U+0067 "g" */
    0x3e, 0xcf, 0x1e, 0x3c, 0x78, 0xf1, 0xe3, 0x6e,
    0xec, 0x18, 0x34, 0x6f, 0x80,

    /* U+0068 "h" */
    0xc1, 0x83, 0x6, 0xc, 0x1b, 0xb9, 0xe3, 0xc7,
    0x8f, 0x1e, 0x3c, 0x78, 0xf1, 0x80,

    /* U+0069 "i" */
    0x6c, 0x1, 0xdb, 0x6d, 0xb6, 0xd8,

    /* U+006A "j" */
    0x18, 0xc0, 0x0, 0x1c, 0x63, 0x18, 0xc6, 0x31,
    0x8c, 0x63, 0x18, 0xfc,

    /* U+006B "k" */
    0xc1, 0x83, 0x6, 0xc, 0x18, 0xf1, 0x66, 0xd9,
    0xe3, 0xc6, 0xcc, 0xd8, 0xb1, 0x80,

    /* U+006C "l" */
    0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0x70,

    /* U+006D "m" */
    0xfb, 0xb3, 0x3c, 0xcf, 0x33, 0xcc, 0xf3, 0x3c,
    0xcf, 0x33, 0xcc, 0xf3, 0x30,

    /* U+006E "n" */
    0xdd, 0xcf, 0x1e, 0x3c, 0x78, 0xf1, 0xe3, 0xc7,
    0x8c,

    /* U+006F "o" */
    0x3c, 0x66, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3,
    0x66, 0x3c,

    /* U+0070 "p" */
    0xfd, 0xcb, 0x1e, 0x3c, 0x78, 0xf1, 0xe3, 0xcd,
    0xf3, 0x6, 0xc, 0x18, 0x0,

    /* U+0071 "q" */
    0x3e, 0xcf, 0x1e, 0x3c, 0x78, 0xf1, 0xe3, 0x6e,
    0xec, 0x18, 0x30, 0x60, 0xc0,

    /* U+0072 "r" */
    0xdf, 0x31, 0x8c, 0x63, 0x18, 0xc6, 0x0,

    /* U+0073 "s" */
    0x7b, 0xc, 0x30, 0x70, 0xe0, 0xc3, 0x8f, 0xe0,

    /* U+0074 "t" */
    0x30, 0x60, 0xc7, 0xf3, 0x6, 0xc, 0x18, 0x30,
    0x60, 0xc1, 0x81, 0xe0,

    /* U+0075 "u" */
    0xc7, 0x8f, 0x1e, 0x3c, 0x78, 0xf1, 0xe3, 0xce,
    0xf4,

    /* U+0076 "v" */
    0xc1, 0x43, 0x42, 0x62, 0x26, 0x24, 0x34, 0x1c,
    0x18, 0x18,

    /* U+0077 "w" */
    0x46, 0x28, 0xc5, 0x19, 0xb7, 0x36, 0xb4, 0x52,
    0x8a, 0x51, 0xce, 0x31, 0x82, 0x30,

    /* U+0078 "x" */
    0x43, 0x62, 0x36, 0x34, 0x18, 0x1c, 0x34, 0x26,
    0x62, 0xc3,

    /* U+0079 "y" */
    0xc1, 0x43, 0x63, 0x62, 0x22, 0x26, 0x36, 0x14,
    0x14, 0x1c, 0x8, 0x8, 0x18, 0xf0,

    /* U+007A "z" */
    0x7e, 0xc, 0x30, 0x41, 0x82, 0xc, 0x30, 0x61,
    0xfc,

    /* U+007B "{" */
    0x1c, 0xc3, 0xc, 0x30, 0xc3, 0xc, 0x33, 0x3,
    0xc, 0x30, 0xc3, 0xc, 0x30, 0xc1, 0xc0,

    /* U+007C "|" */
    0xff, 0xff, 0xff, 0xff, 0xf0,

    /* U+007D "}" */
    0xf0, 0x30, 0x60, 0xc1, 0x83, 0x6, 0xc, 0x18,
    0xc, 0x60, 0xc1, 0x83, 0x6, 0xc, 0x18, 0x33,
    0xc0,

    /* U+007E "~" */
    0x70, 0xa6, 0x61, 0xc0
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 101, .box_w = 3, .box_h = 14, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 6, .adv_w = 152, .box_w = 4, .box_h = 5, .ofs_x = 3, .ofs_y = 9},
    {.bitmap_index = 9, .adv_w = 152, .box_w = 8, .box_h = 15, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 24, .adv_w = 152, .box_w = 7, .box_h = 17, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 39, .adv_w = 230, .box_w = 13, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 61, .adv_w = 186, .box_w = 10, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 79, .adv_w = 102, .box_w = 1, .box_h = 5, .ofs_x = 3, .ofs_y = 9},
    {.bitmap_index = 80, .adv_w = 112, .box_w = 5, .box_h = 20, .ofs_x = 2, .ofs_y = -5},
    {.bitmap_index = 93, .adv_w = 112, .box_w = 5, .box_h = 20, .ofs_x = 1, .ofs_y = -5},
    {.bitmap_index = 106, .adv_w = 152, .box_w = 7, .box_h = 6, .ofs_x = 1, .ofs_y = 8},
    {.bitmap_index = 112, .adv_w = 152, .box_w = 9, .box_h = 9, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 123, .adv_w = 90, .box_w = 2, .box_h = 5, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 125, .adv_w = 107, .box_w = 5, .box_h = 1, .ofs_x = 1, .ofs_y = 5},
    {.bitmap_index = 126, .adv_w = 90, .box_w = 3, .box_h = 2, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 127, .adv_w = 135, .box_w = 9, .box_h = 19, .ofs_x = -1, .ofs_y = -4},
    {.bitmap_index = 149, .adv_w = 152, .box_w = 8, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 162, .adv_w = 152, .box_w = 7, .box_h = 13, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 174, .adv_w = 152, .box_w = 7, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 186, .adv_w = 152, .box_w = 7, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 198, .adv_w = 152, .box_w = 9, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 213, .adv_w = 152, .box_w = 7, .box_h = 13, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 225, .adv_w = 152, .box_w = 7, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 237, .adv_w = 152, .box_w = 7, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 249, .adv_w = 152, .box_w = 8, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 262, .adv_w = 152, .box_w = 7, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 274, .adv_w = 90, .box_w = 2, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 277, .adv_w = 90, .box_w = 2, .box_h = 12, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 280, .adv_w = 152, .box_w = 9, .box_h = 9, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 291, .adv_w = 152, .box_w = 9, .box_h = 5, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 297, .adv_w = 152, .box_w = 9, .box_h = 9, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 308, .adv_w = 129, .box_w = 6, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 319, .adv_w = 287, .box_w = 15, .box_h = 17, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 351, .adv_w = 163, .box_w = 10, .box_h = 14, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 369, .adv_w = 169, .box_w = 8, .box_h = 14, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 383, .adv_w = 140, .box_w = 8, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 397, .adv_w = 169, .box_w = 8, .box_h = 14, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 411, .adv_w = 141, .box_w = 7, .box_h = 14, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 424, .adv_w = 130, .box_w = 7, .box_h = 14, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 437, .adv_w = 162, .box_w = 8, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 451, .adv_w = 186, .box_w = 8, .box_h = 14, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 465, .adv_w = 101, .box_w = 5, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 474, .adv_w = 134, .box_w = 7, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 487, .adv_w = 157, .box_w = 8, .box_h = 14, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 501, .adv_w = 135, .box_w = 7, .box_h = 14, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 514, .adv_w = 203, .box_w = 9, .box_h = 14, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 530, .adv_w = 174, .box_w = 8, .box_h = 14, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 544, .adv_w = 169, .box_w = 9, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 560, .adv_w = 147, .box_w = 7, .box_h = 14, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 573, .adv_w = 169, .box_w = 10, .box_h = 15, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 592, .adv_w = 159, .box_w = 8, .box_h = 14, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 606, .adv_w = 147, .box_w = 7, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 619, .adv_w = 127, .box_w = 8, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 633, .adv_w = 180, .box_w = 8, .box_h = 14, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 647, .adv_w = 146, .box_w = 9, .box_h = 14, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 663, .adv_w = 208, .box_w = 13, .box_h = 14, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 686, .adv_w = 146, .box_w = 9, .box_h = 14, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 702, .adv_w = 144, .box_w = 10, .box_h = 14, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 720, .adv_w = 135, .box_w = 7, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 733, .adv_w = 112, .box_w = 4, .box_h = 19, .ofs_x = 2, .ofs_y = -4},
    {.bitmap_index = 743, .adv_w = 135, .box_w = 9, .box_h = 19, .ofs_x = 0, .ofs_y = -4},
    {.bitmap_index = 765, .adv_w = 112, .box_w = 4, .box_h = 19, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 775, .adv_w = 152, .box_w = 9, .box_h = 6, .ofs_x = 0, .ofs_y = 8},
    {.bitmap_index = 782, .adv_w = 156, .box_w = 10, .box_h = 1, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 784, .adv_w = 152, .box_w = 4, .box_h = 3, .ofs_x = 2, .ofs_y = 11},
    {.bitmap_index = 786, .adv_w = 140, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 795, .adv_w = 152, .box_w = 7, .box_h = 15, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 809, .adv_w = 124, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 818, .adv_w = 150, .box_w = 7, .box_h = 15, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 832, .adv_w = 141, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 841, .adv_w = 92, .box_w = 7, .box_h = 15, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 855, .adv_w = 152, .box_w = 7, .box_h = 14, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 868, .adv_w = 156, .box_w = 7, .box_h = 15, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 882, .adv_w = 79, .box_w = 3, .box_h = 15, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 888, .adv_w = 78, .box_w = 5, .box_h = 19, .ofs_x = -2, .ofs_y = -4},
    {.bitmap_index = 900, .adv_w = 134, .box_w = 7, .box_h = 15, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 914, .adv_w = 85, .box_w = 4, .box_h = 15, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 922, .adv_w = 218, .box_w = 10, .box_h = 10, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 935, .adv_w = 155, .box_w = 7, .box_h = 10, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 944, .adv_w = 152, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 954, .adv_w = 150, .box_w = 7, .box_h = 14, .ofs_x = 2, .ofs_y = -4},
    {.bitmap_index = 967, .adv_w = 149, .box_w = 7, .box_h = 14, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 980, .adv_w = 98, .box_w = 5, .box_h = 10, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 987, .adv_w = 118, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 995, .adv_w = 101, .box_w = 7, .box_h = 13, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1007, .adv_w = 155, .box_w = 7, .box_h = 10, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 1016, .adv_w = 136, .box_w = 8, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1026, .adv_w = 186, .box_w = 11, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1040, .adv_w = 135, .box_w = 8, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1050, .adv_w = 136, .box_w = 8, .box_h = 14, .ofs_x = 0, .ofs_y = -4},
    {.bitmap_index = 1064, .adv_w = 124, .box_w = 7, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1073, .adv_w = 129, .box_w = 6, .box_h = 19, .ofs_x = 2, .ofs_y = -4},
    {.bitmap_index = 1088, .adv_w = 93, .box_w = 2, .box_h = 18, .ofs_x = 2, .ofs_y = -4},
    {.bitmap_index = 1093, .adv_w = 129, .box_w = 7, .box_h = 19, .ofs_x = 0, .ofs_y = -4},
    {.bitmap_index = 1110, .adv_w = 152, .box_w = 9, .box_h = 3, .ofs_x = 0, .ofs_y = 5}
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
const lv_font_t axel_text = {
#else
lv_font_t axel_text = {
#endif
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,    /*Function pointer to get glyph's data*/
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,    /*Function pointer to get glyph's bitmap*/
    .line_height = 20,          /*The maximum line height required by the font*/
    .base_line = 5,             /*Baseline measured from the bottom of the line*/
#if !(LVGL_VERSION_MAJOR == 6 && LVGL_VERSION_MINOR == 0)
    .subpx = LV_FONT_SUBPX_NONE,
#endif
#if LV_VERSION_CHECK(7, 4, 0) || LVGL_VERSION_MAJOR >= 8
    .underline_position = -2,
    .underline_thickness = 1,
#endif
    .dsc = &font_dsc,          /*The custom font data. Will be accessed by `get_glyph_bitmap/dsc` */
#if LV_VERSION_CHECK(8, 2, 0) || LVGL_VERSION_MAJOR >= 9
    .fallback = &lv_font_montserrat_28,
#endif
    .user_data = NULL,
};



#endif /*#if AXEL_TEXT*/

