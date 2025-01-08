/*******************************************************************************
 * Size: 18 px
 * Bpp: 1
 * Opts: --bpp 1 --size 18 --font Gloock-Regular.ttf --symbols 0123456789abcdefghijlmnoprstuvyJFMASOND --format lvgl -o gloock_date.c
 ******************************************************************************/

#ifdef LV_LVGL_H_INCLUDE_SIMPLE
#include "lvgl.h"
#else
#include "lvgl/lvgl.h"
#endif

#ifndef GLOOCK_DATE
#define GLOOCK_DATE 1
#endif

#if GLOOCK_DATE

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+0030 "0" */
    0x1f, 0x6, 0x31, 0xc7, 0x30, 0x6e, 0xf, 0xc1,
    0xf8, 0x3f, 0x7, 0xe0, 0xfc, 0x1d, 0x83, 0x38,
    0xe3, 0x18, 0x3e, 0x0,

    /* U+0031 "1" */
    0x0, 0x23, 0x9e, 0x38, 0xe3, 0x8e, 0x38, 0xe3,
    0x8e, 0x38, 0xe7, 0xc0,

    /* U+0032 "2" */
    0x3e, 0x21, 0x90, 0xe0, 0x70, 0x38, 0x38, 0x18,
    0x1c, 0xc, 0x8, 0x8, 0x8, 0x37, 0xfb, 0xfc,

    /* U+0033 "3" */
    0x7e, 0x23, 0xa1, 0xc0, 0xc0, 0xc0, 0xf0, 0x1c,
    0x7, 0x3, 0x81, 0xe0, 0xf0, 0x68, 0x73, 0xe0,

    /* U+0034 "4" */
    0x1, 0x0, 0x40, 0x30, 0x1c, 0x7, 0x7, 0xc1,
    0x70, 0x9c, 0x47, 0x11, 0xc7, 0xff, 0xff, 0x7,
    0x1, 0xc0, 0xf8,

    /* U+0035 "5" */
    0x61, 0x3f, 0x1f, 0x10, 0x8, 0x4, 0xe3, 0x9c,
    0x6, 0x3, 0x81, 0xc0, 0xf0, 0x78, 0x34, 0x39,
    0xf0,

    /* U+0036 "6" */
    0x1f, 0x8c, 0x26, 0x1, 0x80, 0xef, 0x3c, 0xee,
    0x1f, 0x87, 0xe1, 0xf8, 0x76, 0x1d, 0x86, 0x33,
    0x87, 0xc0,

    /* U+0037 "7" */
    0xff, 0xff, 0xb0, 0x40, 0x40, 0x60, 0x20, 0x30,
    0x18, 0x1c, 0xc, 0xe, 0x7, 0x3, 0x81, 0xc0,

    /* U+0038 "8" */
    0x3f, 0x1c, 0xe7, 0x38, 0xcc, 0x1e, 0x1c, 0xe6,
    0x1b, 0x87, 0xe1, 0xf8, 0x7e, 0x1d, 0x86, 0x73,
    0x87, 0x80,

    /* U+0039 "9" */
    0x3e, 0x18, 0xce, 0x1b, 0x87, 0xe1, 0xf8, 0x7e,
    0x1d, 0xc7, 0x3f, 0xc0, 0x70, 0x1a, 0xe, 0x43,
    0x1f, 0x80,

    /* U+0041 "A" */
    0x2, 0x0, 0x10, 0x1, 0x80, 0xe, 0x1, 0xf0,
    0x9, 0x80, 0x4e, 0x4, 0x30, 0x1f, 0xc3, 0xe,
    0x10, 0x30, 0x81, 0xc4, 0xe, 0x60, 0x78,

    /* U+0044 "D" */
    0xff, 0x81, 0xc1, 0x87, 0x3, 0x1c, 0xe, 0x70,
    0x1d, 0xc0, 0x77, 0x1, 0xdc, 0x7, 0x70, 0x1d,
    0xc0, 0x77, 0x3, 0x9c, 0xc, 0x70, 0x63, 0xfe,
    0x0,

    /* U+0046 "F" */
    0x7f, 0xe7, 0x4, 0xe0, 0x1c, 0x43, 0x88, 0x7f,
    0xe, 0x21, 0xc4, 0x38, 0x7, 0x0, 0xe0, 0x1c,
    0x3, 0x80, 0xf8, 0x0,

    /* U+004A "J" */
    0x7c, 0xe3, 0x8e, 0x38, 0xe3, 0x8e, 0x38, 0xe3,
    0x8e, 0x38, 0xe3, 0x8c, 0x31, 0x0,

    /* U+004D "M" */
    0x38, 0x3, 0x83, 0x80, 0xe0, 0x70, 0x1c, 0x17,
    0x3, 0x82, 0xe1, 0xb0, 0x4c, 0x26, 0x9, 0xc4,
    0xc1, 0x39, 0x1c, 0x23, 0xa3, 0x84, 0x78, 0x70,
    0x87, 0xe, 0x10, 0xe1, 0xc4, 0x18, 0x38, 0xc1,
    0x7, 0x80, 0x0, 0x0,

    /* U+004E "N" */
    0x7c, 0x1c, 0x78, 0x10, 0xb8, 0x21, 0x38, 0x42,
    0x38, 0x84, 0x71, 0x8, 0x72, 0x10, 0x74, 0x20,
    0x68, 0x40, 0xf0, 0x80, 0xe1, 0x0, 0xc2, 0x0,
    0x8e, 0x1, 0x0,

    /* U+004F "O" */
    0xf, 0xc0, 0xe1, 0xc7, 0x3, 0x9c, 0x6, 0xe0,
    0x1f, 0x80, 0x7e, 0x1, 0xf8, 0x7, 0xe0, 0x1f,
    0x80, 0x76, 0x3, 0x9c, 0xe, 0x38, 0x70, 0x3f,
    0x0,

    /* U+0053 "S" */
    0x3e, 0x62, 0xe2, 0xe0, 0xf0, 0x78, 0x3c, 0x1e,
    0xf, 0x7, 0x83, 0x83, 0x82, 0xfc,

    /* U+0061 "a" */
    0x1e, 0x19, 0xc6, 0x70, 0x9c, 0xf, 0xd, 0xce,
    0x73, 0x9c, 0xe7, 0x5e, 0xe0,

    /* U+0062 "b" */
    0x10, 0x3c, 0x7, 0x1, 0xc0, 0x70, 0x1d, 0xc7,
    0x99, 0xc7, 0x71, 0xdc, 0x77, 0x1d, 0xc7, 0x71,
    0xdc, 0x64, 0xf0,

    /* U+0063 "c" */
    0x3c, 0x31, 0x98, 0xdc, 0x6e, 0x7, 0x3, 0xc1,
    0xe2, 0x7e, 0x1e, 0x0,

    /* U+0064 "d" */
    0x0, 0x81, 0xe0, 0x38, 0xe, 0x3, 0x8f, 0xe6,
    0x3b, 0x8e, 0xe3, 0xb8, 0xee, 0x3b, 0x8e, 0xe3,
    0x99, 0xe3, 0xbc, 0x0,

    /* U+0065 "e" */
    0x1e, 0x31, 0x98, 0xff, 0xfe, 0x7, 0x3, 0xc0,
    0xe1, 0x7f, 0x1f, 0x0,

    /* U+0066 "f" */
    0xf, 0xc, 0xce, 0x47, 0x3, 0x83, 0xe0, 0xe0,
    0x70, 0x38, 0x1c, 0xe, 0x7, 0x3, 0x81, 0xc1,
    0xf0,

    /* U+0067 "g" */
    0x3f, 0x73, 0x39, 0xdc, 0xee, 0x73, 0x31, 0x21,
    0x80, 0xff, 0x3f, 0xd0, 0xf8, 0x3c, 0x13, 0xf0,

    /* U+0068 "h" */
    0x10, 0x1e, 0x1, 0xc0, 0x38, 0x7, 0x0, 0xe7,
    0x1f, 0x73, 0x8e, 0x71, 0xce, 0x39, 0xc7, 0x38,
    0xe7, 0x1c, 0xe3, 0x9c, 0xf8,

    /* U+0069 "i" */
    0x73, 0x9c, 0x0, 0x79, 0xce, 0x73, 0x9c, 0xe7,
    0x3b, 0xe0,

    /* U+006A "j" */
    0x77, 0x70, 0x7, 0x77, 0x77, 0x77, 0x77, 0x77,
    0x76, 0xc0,

    /* U+006C "l" */
    0x17, 0x9c, 0xe7, 0x39, 0xce, 0x73, 0x9c, 0xe7,
    0x3b, 0xe0,

    /* U+006D "m" */
    0x0, 0x0, 0x79, 0xc7, 0x1f, 0x7d, 0xce, 0x38,
    0xe7, 0x1c, 0x73, 0x8e, 0x39, 0xc7, 0x1c, 0xe3,
    0x8e, 0x71, 0xc7, 0x38, 0xe3, 0xbe, 0xfb, 0xe0,

    /* U+006E "n" */
    0x0, 0x1e, 0x71, 0xf7, 0x38, 0xe7, 0x1c, 0xe3,
    0x9c, 0x73, 0x8e, 0x71, 0xce, 0x3b, 0xef, 0x80,

    /* U+006F "o" */
    0x1e, 0x1c, 0xe6, 0x1b, 0x87, 0xe1, 0xf8, 0x7e,
    0x1d, 0x86, 0x73, 0x87, 0x80,

    /* U+0070 "p" */
    0x0, 0x1d, 0xc7, 0x19, 0xc7, 0x71, 0xdc, 0x77,
    0x1d, 0xc7, 0x71, 0xdc, 0x67, 0xb1, 0xd0, 0x70,
    0x1c, 0xf, 0x80,

    /* U+0072 "r" */
    0xf7, 0x77, 0x78, 0x70, 0x70, 0x70, 0x70, 0x70,
    0x70, 0xf8,

    /* U+0073 "s" */
    0x7d, 0x8b, 0x7, 0x87, 0xc7, 0xc7, 0xc3, 0x87,
    0xf8,

    /* U+0074 "t" */
    0x8, 0x8, 0x38, 0x7c, 0x38, 0x38, 0x38, 0x38,
    0x38, 0x38, 0x38, 0x38, 0x1e,

    /* U+0075 "u" */
    0x0, 0x1e, 0x79, 0xc7, 0x38, 0xe7, 0x1c, 0xe3,
    0x9c, 0x73, 0x8e, 0x71, 0xce, 0x78, 0xf7, 0x80,

    /* U+0076 "v" */
    0x70, 0x9c, 0x43, 0x10, 0xe4, 0x3a, 0x7, 0x81,
    0xc0, 0x30, 0x8, 0x2, 0x0,

    /* U+0079 "y" */
    0x70, 0xb8, 0x8c, 0x47, 0x23, 0xa0, 0xf0, 0x70,
    0x18, 0xc, 0x4, 0x2, 0x2, 0xf, 0x7, 0x0
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 189, .box_w = 11, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 20, .adv_w = 94, .box_w = 6, .box_h = 15, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 32, .adv_w = 145, .box_w = 9, .box_h = 14, .ofs_x = -1, .ofs_y = 0},
    {.bitmap_index = 48, .adv_w = 154, .box_w = 9, .box_h = 14, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 64, .adv_w = 173, .box_w = 10, .box_h = 15, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 83, .adv_w = 158, .box_w = 9, .box_h = 15, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 100, .adv_w = 179, .box_w = 10, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 118, .adv_w = 145, .box_w = 9, .box_h = 14, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 134, .adv_w = 179, .box_w = 10, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 152, .adv_w = 179, .box_w = 10, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 170, .adv_w = 197, .box_w = 13, .box_h = 14, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 193, .adv_w = 238, .box_w = 14, .box_h = 14, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 218, .adv_w = 164, .box_w = 11, .box_h = 14, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 238, .adv_w = 90, .box_w = 6, .box_h = 18, .ofs_x = -1, .ofs_y = -4},
    {.bitmap_index = 252, .adv_w = 274, .box_w = 19, .box_h = 15, .ofs_x = -1, .ofs_y = -1},
    {.bitmap_index = 288, .adv_w = 216, .box_w = 15, .box_h = 14, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 315, .adv_w = 253, .box_w = 14, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 340, .adv_w = 147, .box_w = 8, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 354, .adv_w = 159, .box_w = 10, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 367, .adv_w = 168, .box_w = 10, .box_h = 15, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 386, .adv_w = 154, .box_w = 9, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 398, .adv_w = 174, .box_w = 10, .box_h = 16, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 418, .adv_w = 155, .box_w = 9, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 430, .adv_w = 90, .box_w = 9, .box_h = 15, .ofs_x = -1, .ofs_y = 0},
    {.bitmap_index = 447, .adv_w = 156, .box_w = 9, .box_h = 14, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 463, .adv_w = 182, .box_w = 11, .box_h = 15, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 484, .adv_w = 86, .box_w = 5, .box_h = 15, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 494, .adv_w = 81, .box_w = 4, .box_h = 19, .ofs_x = 0, .ofs_y = -4},
    {.bitmap_index = 504, .adv_w = 83, .box_w = 5, .box_h = 15, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 514, .adv_w = 281, .box_w = 17, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 538, .adv_w = 183, .box_w = 11, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 554, .adv_w = 176, .box_w = 10, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 567, .adv_w = 173, .box_w = 10, .box_h = 15, .ofs_x = 0, .ofs_y = -4},
    {.bitmap_index = 586, .adv_w = 130, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 596, .adv_w = 120, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 605, .adv_w = 114, .box_w = 8, .box_h = 13, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 618, .adv_w = 176, .box_w = 11, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 634, .adv_w = 137, .box_w = 10, .box_h = 10, .ofs_x = -1, .ofs_y = 0},
    {.bitmap_index = 647, .adv_w = 128, .box_w = 9, .box_h = 14, .ofs_x = -1, .ofs_y = -4}
};

/*---------------------
 *  CHARACTER MAPPING
 *--------------------*/

static const uint8_t glyph_id_ofs_list_1[] = {
    0, 0, 0, 1, 0, 2, 0, 0,
    0, 3, 0, 0, 4, 5, 6, 0,
    0, 0, 7, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    8, 9, 10, 11, 12, 13, 14, 15,
    16, 17, 0, 18, 19, 20, 21, 22,
    0, 23, 24, 25, 26, 27, 0, 0,
    28
};

/*Collect the unicode lists and glyph_id offsets*/
static const lv_font_fmt_txt_cmap_t cmaps[] =
{
    {
        .range_start = 48, .range_length = 10, .glyph_id_start = 1,
        .unicode_list = NULL, .glyph_id_ofs_list = NULL, .list_length = 0, .type = LV_FONT_FMT_TXT_CMAP_FORMAT0_TINY
    },
    {
        .range_start = 65, .range_length = 57, .glyph_id_start = 11,
        .unicode_list = NULL, .glyph_id_ofs_list = glyph_id_ofs_list_1, .list_length = 57, .type = LV_FONT_FMT_TXT_CMAP_FORMAT0_FULL
    }
};

/*-----------------
 *    KERNING
 *----------------*/


/*Map glyph_ids to kern left classes*/
static const uint8_t kern_left_class_mapping[] =
{
    0, 1, 2, 3, 4, 5, 6, 7,
    8, 9, 10, 11, 12, 13, 14, 15,
    16, 12, 17, 18, 19, 20, 21, 22,
    23, 24, 25, 26, 27, 28, 25, 29,
    19, 30, 31, 32, 33, 21, 34, 35
};

/*Map glyph_ids to kern right classes*/
static const uint8_t kern_right_class_mapping[] =
{
    0, 1, 0, 2, 3, 4, 5, 6,
    7, 8, 9, 10, 11, 11, 12, 13,
    14, 15, 16, 17, 18, 19, 20, 20,
    21, 22, 23, 24, 24, 23, 24, 24,
    25, 24, 24, 26, 27, 28, 29, 30
};

/*Kern values between classes*/
static const int8_t kern_class_values[] =
{
    0, -5, -1, 0, 0, 0, -3, 0,
    -1, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, -4, 0,
    -1, -6, -2, -6, -6, -6, -6, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    -8, -8, 0, 0, 0, 0, -8, 0,
    0, 0, 0, 0, 0, 0, 0, -3,
    0, -3, 0, -3, -3, 0, 0, 0,
    0, 0, 0, 0, 0, 0, -2, -2,
    0, 0, 0, 0, -2, 0, 0, 0,
    0, 0, -1, -6, 0, 0, -3, 0,
    -13, -5, -5, 0, 0, 0, 0, 0,
    0, 0, 0, 0, -3, -3, 0, 0,
    0, 0, -3, 0, 0, 0, 0, 0,
    0, -5, 0, 0, -2, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, -5,
    0, 0, 0, 0, 0, 0, -7, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    -3, -3, 0, 0, 0, 0, -3, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, -7, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, -3, -3,
    0, 0, 0, 0, -3, 0, 0, 0,
    0, 0, -10, 0, 0, -30, -4, -11,
    0, -10, -7, 0, 0, 0, 0, 0,
    0, 0, 0, 0, -36, -36, 0, 0,
    0, 0, -36, 0, 0, 0, 0, 0,
    0, -7, 0, 0, 0, 0, -11, 0,
    -4, 0, 0, 0, 0, 0, 0, 0,
    0, 0, -3, -3, 0, 0, 0, 0,
    -3, 0, 0, 0, 0, 0, 0, -6,
    -1, -2, 0, 0, -5, 0, -3, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    -3, -3, 0, 0, 0, 0, -3, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, -2, -4,
    0, -5, -21, 0, -3, 0, -10, -10,
    0, -3, -4, -3, -10, 0, 0, -10,
    -25, -24, 0, 0, 0, 0, 0, 0,
    0, 0, 0, -17, -7, -6, -9, -9,
    0, 0, -8, -1, -4, -4, -3, -9,
    -11, -5, -4, -4, -6, -7, 4, 4,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, -31, 0, 0, 0, 0, -7, 0,
    -29, 0, -27, -27, 0, 0, -1, -5,
    -27, -17, -13, -14, 0, -8, 0, 0,
    0, 0, 0, 0, 0, 0, 0, -6,
    -6, 0, 0, 0, -5, 0, -5, 0,
    -10, -10, 0, 0, -3, -7, -10, 0,
    0, -6, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, -7, 0, 0, 0, -7, -7,
    0, 0, 0, -3, -7, 0, -11, -5,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, -2, -7, 0, 0, -7,
    -10, -5, -10, 0, -14, -14, 0, 0,
    0, -5, -14, 0, 0, -10, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, -1, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, -2, -1, -1,
    0, 0, -7, -1, -5, -4, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    -7, -7, 0, 0, 0, -3, -6, 0,
    -12, -7, -11, -10, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, -6, -1, -4, -4,
    -3, -6, -7, -7, -4, -4, -13, -7,
    -9, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, -7, -3, -7, -7, -6, -7,
    -10, -7, -7, -4, -9, -2, -7, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    -3, 3, -4, -4, 3, -1, 1, 0,
    -4, 0, -10, -1, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, -7, -3,
    -7, -7, -6, -6, -10, -7, -7, -4,
    0, -2, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, -1, 0, 0, -3, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, -3, 0, -14, -14, 0, 0,
    0, 0, -14, -3, -7, -9, -14, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    -4, 1, -9, -4, 0, -4, 0, -1,
    -4, 0, -13, -7, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 6,
    -4, -4, 0, 0, 0, 0, -3, 0,
    -4, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, -6, 3, -3, -3,
    0, 0, -4, -1, -4, -1, 0, -4,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, -3, 0, -4, -4, 3, -1,
    1, 0, -4, 0, -10, -1, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    -4, 1, -9, -7, 0, -4, 0, -1,
    -4, -3, -13, -7, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, -4, 0,
    0, 0, -4, -6, -6, -7, 0, 0,
    -9, -1, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, -6, 0, -6, -10,
    0, 0, -7, 0, -10, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, -3, -3, 0, -3,
    -6, -4, -3, 0, -10, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    -7, -6, -16, -16, 0, 0, -7, -9,
    -16, -4, -23, -12, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, -9, 0,
    -4, -10, 0, 0, 0, 0, -10, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, -9, 0, -10, -10,
    0, 0, 0, 0, -10, 0, 0, 0,
    0, 0
};


/*Collect the kern class' data in one place*/
static const lv_font_fmt_txt_kern_classes_t kern_classes =
{
    .class_pair_values   = kern_class_values,
    .left_class_mapping  = kern_left_class_mapping,
    .right_class_mapping = kern_right_class_mapping,
    .left_class_cnt      = 35,
    .right_class_cnt     = 30,
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
    .cmap_num = 2,
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
const lv_font_t gloock_date = {
#else
lv_font_t gloock_date = {
#endif
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,    /*Function pointer to get glyph's data*/
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,    /*Function pointer to get glyph's bitmap*/
    .line_height = 19,          /*The maximum line height required by the font*/
    .base_line = 4,             /*Baseline measured from the bottom of the line*/
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



#endif /*#if GLOOCK_DATE*/

