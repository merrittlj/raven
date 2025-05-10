/*******************************************************************************
 * Size: 22 px
 * Bpp: 1
 * Opts: --bpp 1 --size 22 --font AxelBold.TTF --symbols JanFebMrApyulgSOctNovD1234567890: --format lvgl -o axel_time_date.c
 ******************************************************************************/

#ifdef LV_LVGL_H_INCLUDE_SIMPLE
#include "lvgl.h"
#else
#include "lvgl/lvgl.h"
#endif

#ifndef AXEL_TIME_DATE
#define AXEL_TIME_DATE 1
#endif

#if AXEL_TIME_DATE

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+0030 "0" */
    0x1e, 0xf, 0xc7, 0x39, 0x8e, 0xe3, 0xf9, 0xfe,
    0x7f, 0xbf, 0xfd, 0xfe, 0x7f, 0x9f, 0xc7, 0x71,
    0x9c, 0xe3, 0xf0, 0x78,

    /* U+0031 "1" */
    0x1c, 0x3c, 0x7c, 0xfc, 0xfc, 0x1c, 0x1c, 0x1c,
    0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0x7f, 0x7f,

    /* U+0032 "2" */
    0x3c, 0xfe, 0xe7, 0xe7, 0x7, 0x7, 0xe, 0x1e,
    0x1c, 0x3c, 0x78, 0xf0, 0xff, 0xff, 0xff,

    /* U+0033 "3" */
    0x3c, 0xfe, 0x67, 0x7, 0x7, 0x7, 0x3e, 0x3c,
    0x3e, 0x7, 0x7, 0x7, 0x8f, 0xff, 0xfe, 0x7c,

    /* U+0034 "4" */
    0xc, 0x3, 0x81, 0xc0, 0x70, 0x38, 0xe, 0x7,
    0x31, 0xcc, 0x67, 0x39, 0xcf, 0xff, 0xff, 0xff,
    0xc1, 0xc0, 0x70, 0x1c,

    /* U+0035 "5" */
    0x7f, 0x3f, 0x9f, 0xce, 0x7, 0x7, 0x83, 0xf9,
    0xfe, 0x23, 0x81, 0xc0, 0xe0, 0x70, 0x7f, 0xfb,
    0xfc, 0xf8,

    /* U+0036 "6" */
    0xf, 0x9f, 0x8e, 0xe, 0x6, 0x7, 0xf3, 0xfd,
    0xee, 0xe3, 0xf1, 0xf8, 0xfc, 0x7e, 0x3b, 0xb9,
    0xfc, 0x3c,

    /* U+0037 "7" */
    0xff, 0xff, 0xff, 0xe0, 0xf0, 0x70, 0x78, 0x38,
    0x1c, 0x1e, 0xe, 0xf, 0x7, 0x83, 0x83, 0xc1,
    0xe0, 0x0,

    /* U+0038 "8" */
    0x1e, 0x1f, 0x9c, 0xee, 0x77, 0x3b, 0xfc, 0xfc,
    0x7c, 0x7f, 0x7b, 0xf8, 0xfc, 0x7e, 0x3f, 0x9d,
    0xfc, 0x7c,

    /* U+0039 "9" */
    0x3e, 0x3f, 0x9d, 0xdc, 0x7e, 0x3f, 0x1f, 0x8f,
    0xef, 0x7f, 0x9f, 0xc0, 0xe0, 0xe0, 0x73, 0xf9,
    0xf8, 0xf8,

    /* U+003A ":" */
    0x77, 0xff, 0xf7, 0x0, 0xe, 0xff, 0xfe, 0xe0,

    /* U+0041 "A" */
    0xf, 0x0, 0xf0, 0xf, 0x81, 0xf8, 0x1f, 0x81,
    0xdc, 0x1d, 0xc3, 0x9c, 0x39, 0xc3, 0xfe, 0x3f,
    0xe7, 0x8e, 0x70, 0xe7, 0xf, 0x70, 0xff, 0xf,

    /* U+0044 "D" */
    0xfe, 0x3f, 0xcf, 0xfb, 0x8e, 0xe1, 0xf8, 0x7e,
    0x1f, 0x87, 0xe1, 0xf8, 0x7e, 0x1f, 0x87, 0xe3,
    0xbf, 0xef, 0xf3, 0xf8,

    /* U+0046 "F" */
    0xff, 0x7f, 0xbf, 0xdc, 0xe, 0x7, 0x3, 0xfd,
    0xfe, 0xff, 0x70, 0x38, 0x1c, 0xe, 0x7, 0x3,
    0x81, 0xc0,

    /* U+004A "J" */
    0x3f, 0x3f, 0x3f, 0x7, 0x7, 0x7, 0x7, 0x7,
    0x7, 0x7, 0x7, 0xe7, 0xe7, 0xff, 0x7e, 0x3c,

    /* U+004D "M" */
    0xf0, 0xff, 0xf, 0xf9, 0xff, 0x9f, 0xf9, 0xff,
    0xdf, 0xff, 0xff, 0xff, 0xef, 0x7e, 0xf7, 0xef,
    0x7e, 0x67, 0xe0, 0x7e, 0x7, 0xe0, 0x7e, 0x7,

    /* U+004E "N" */
    0xe1, 0xfc, 0x7f, 0x1f, 0xe7, 0xf9, 0xfe, 0x7f,
    0xdf, 0xb7, 0xed, 0xfb, 0xfe, 0x7f, 0x9f, 0xe7,
    0xf8, 0xfe, 0x3f, 0x87,

    /* U+004F "O" */
    0x1f, 0x7, 0xf1, 0xff, 0x38, 0xee, 0xf, 0xc1,
    0xf8, 0x3f, 0x7, 0xe0, 0xfc, 0x1f, 0x83, 0xf0,
    0x77, 0x1c, 0xff, 0x8f, 0xe0, 0xf8,

    /* U+0053 "S" */
    0x3e, 0x3f, 0xff, 0xdc, 0x2e, 0x7, 0x81, 0xe0,
    0xfc, 0x1f, 0x3, 0xc0, 0xe0, 0x7c, 0x3f, 0xff,
    0xfc, 0xfc,

    /* U+0061 "a" */
    0x7e, 0x3f, 0x90, 0xe0, 0x71, 0xfb, 0xff, 0xcf,
    0xc7, 0xe3, 0xf3, 0xdf, 0xe7, 0xb0,

    /* U+0062 "b" */
    0xe0, 0x70, 0x38, 0x1c, 0xe, 0x7, 0xf3, 0xfd,
    0xcf, 0xe3, 0xf1, 0xf8, 0xfc, 0x7e, 0x3f, 0x1f,
    0x9d, 0xfe, 0xde, 0x0,

    /* U+0063 "c" */
    0x1e, 0x7f, 0x72, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0,
    0xe0, 0x72, 0x7f, 0x3e,

    /* U+0065 "e" */
    0x1e, 0x3f, 0x98, 0xfc, 0x7f, 0xff, 0xff, 0x81,
    0xc0, 0xe0, 0x38, 0x9f, 0xe3, 0xe0,

    /* U+0067 "g" */
    0x3d, 0xbf, 0xdc, 0xfc, 0x7e, 0x3f, 0x1f, 0x8f,
    0xc7, 0xe3, 0xf9, 0xdf, 0xe7, 0xf0, 0x38, 0x1d,
    0xe, 0xfe, 0x7e, 0x0,

    /* U+006C "l" */
    0x27, 0x39, 0xce, 0x73, 0x9c, 0xe7, 0x39, 0xce,
    0x73, 0x9f, 0xfb, 0xc0,

    /* U+006E "n" */
    0xcf, 0x7f, 0xfc, 0xfc, 0x7e, 0x3f, 0x1f, 0x8f,
    0xc7, 0xe3, 0xf1, 0xf8, 0xfc, 0x70,

    /* U+006F "o" */
    0x3e, 0x3f, 0x9d, 0xdc, 0x7e, 0x3f, 0x1f, 0x8f,
    0xc7, 0xe3, 0xbb, 0x9f, 0xc7, 0xc0,

    /* U+0070 "p" */
    0xde, 0x7f, 0xb9, 0xfc, 0x7e, 0x3f, 0x1f, 0x8f,
    0xc7, 0xe3, 0xf3, 0xbf, 0xdf, 0xce, 0x7, 0x3,
    0x81, 0xc0, 0x0, 0x0,

    /* U+0072 "r" */
    0xcf, 0xfb, 0xf7, 0x8e, 0x1c, 0x38, 0x70, 0xe1,
    0xc3, 0x87, 0x0,

    /* U+0074 "t" */
    0x18, 0x38, 0x38, 0x38, 0xff, 0xfe, 0x38, 0x38,
    0x38, 0x38, 0x38, 0x38, 0x38, 0x3f, 0x3f, 0x1e,

    /* U+0075 "u" */
    0x20, 0xf1, 0xf8, 0xfc, 0x7e, 0x3f, 0x1f, 0x8f,
    0xc7, 0xe3, 0xf1, 0xff, 0xef, 0xb0,

    /* U+0076 "v" */
    0x71, 0xce, 0x39, 0xc7, 0x3d, 0xe3, 0xb8, 0x77,
    0xe, 0xe1, 0xd8, 0x1b, 0x3, 0xe0, 0x78, 0x7,
    0x0,

    /* U+0079 "y" */
    0x71, 0xce, 0x39, 0xc7, 0x38, 0xe7, 0x9c, 0x77,
    0xe, 0xe1, 0xdc, 0x1b, 0x83, 0xf0, 0x7c, 0x7,
    0x80, 0x70, 0x1e, 0x1f, 0x83, 0xf0, 0x7c, 0x0
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 168, .box_w = 10, .box_h = 16, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 20, .adv_w = 168, .box_w = 8, .box_h = 15, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 35, .adv_w = 168, .box_w = 8, .box_h = 15, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 50, .adv_w = 168, .box_w = 8, .box_h = 16, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 66, .adv_w = 168, .box_w = 10, .box_h = 16, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 86, .adv_w = 168, .box_w = 9, .box_h = 16, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 104, .adv_w = 168, .box_w = 9, .box_h = 16, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 122, .adv_w = 168, .box_w = 9, .box_h = 16, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 140, .adv_w = 168, .box_w = 9, .box_h = 16, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 158, .adv_w = 168, .box_w = 9, .box_h = 16, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 176, .adv_w = 107, .box_w = 5, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 184, .adv_w = 201, .box_w = 12, .box_h = 16, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 208, .adv_w = 197, .box_w = 10, .box_h = 16, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 228, .adv_w = 154, .box_w = 9, .box_h = 16, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 246, .adv_w = 162, .box_w = 8, .box_h = 16, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 262, .adv_w = 237, .box_w = 12, .box_h = 16, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 286, .adv_w = 202, .box_w = 10, .box_h = 16, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 306, .adv_w = 199, .box_w = 11, .box_h = 16, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 328, .adv_w = 172, .box_w = 9, .box_h = 16, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 346, .adv_w = 164, .box_w = 9, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 360, .adv_w = 176, .box_w = 9, .box_h = 17, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 380, .adv_w = 149, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 392, .adv_w = 169, .box_w = 9, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 406, .adv_w = 176, .box_w = 9, .box_h = 17, .ofs_x = 1, .ofs_y = -5},
    {.bitmap_index = 426, .adv_w = 103, .box_w = 5, .box_h = 18, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 438, .adv_w = 179, .box_w = 9, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 452, .adv_w = 177, .box_w = 9, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 466, .adv_w = 176, .box_w = 9, .box_h = 17, .ofs_x = 1, .ofs_y = -5},
    {.bitmap_index = 486, .adv_w = 127, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 497, .adv_w = 134, .box_w = 8, .box_h = 16, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 513, .adv_w = 176, .box_w = 9, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 527, .adv_w = 174, .box_w = 11, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 544, .adv_w = 175, .box_w = 11, .box_h = 17, .ofs_x = 0, .ofs_y = -5}
};

/*---------------------
 *  CHARACTER MAPPING
 *--------------------*/

static const uint16_t unicode_list_1[] = {
    0x0, 0x3, 0x5, 0x9, 0xc, 0xd, 0xe, 0x12,
    0x20, 0x21, 0x22, 0x24, 0x26, 0x2b, 0x2d, 0x2e,
    0x2f, 0x31, 0x33, 0x34, 0x35, 0x38
};

/*Collect the unicode lists and glyph_id offsets*/
static const lv_font_fmt_txt_cmap_t cmaps[] =
{
    {
        .range_start = 48, .range_length = 11, .glyph_id_start = 1,
        .unicode_list = NULL, .glyph_id_ofs_list = NULL, .list_length = 0, .type = LV_FONT_FMT_TXT_CMAP_FORMAT0_TINY
    },
    {
        .range_start = 65, .range_length = 57, .glyph_id_start = 12,
        .unicode_list = unicode_list_1, .glyph_id_ofs_list = NULL, .list_length = 22, .type = LV_FONT_FMT_TXT_CMAP_SPARSE_TINY
    }
};

/*-----------------
 *    KERNING
 *----------------*/


/*Map glyph_ids to kern left classes*/
static const uint8_t kern_left_class_mapping[] =
{
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 1, 2, 3, 4,
    0, 0, 2, 5, 6, 7, 0, 8,
    0, 0, 0, 7, 7, 9, 10, 0,
    11, 11
};

/*Map glyph_ids to kern right classes*/
static const uint8_t kern_right_class_mapping[] =
{
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 1, 2, 0, 0, 3,
    0, 0, 4, 5, 6, 0, 7, 7,
    0, 0, 8, 7, 8, 8, 9, 8,
    10, 10
};

/*Kern values between classes*/
static const int8_t kern_class_values[] =
{
    0, 0, 0, -7, 0, 0, 0, 0,
    -7, -12, -4, -7, -11, 0, -2, 0,
    0, 0, 0, 0, 0, -12, -9, -4,
    -2, -7, -6, -2, 0, 0, 0, -3,
    -4, 0, 0, 0, 0, 0, 0, 0,
    0, -2, -4, -2, -4, 0, 0, 0,
    0, -7, 0, 0, 0, 0, 0, 0,
    0, 0, 0, -3, -5, 0, 0, 0,
    0, 0, 0, 0, 0, -5, 0, 0,
    0, 0, 0, 0, 0, 0, 0, -2,
    0, 0, 0, 0, 0, 0, -2, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    -2, 0, 0, 0, 0, 0, 0, 0,
    0, -5, -5, 0, 0, 0
};


/*Collect the kern class' data in one place*/
static const lv_font_fmt_txt_kern_classes_t kern_classes =
{
    .class_pair_values   = kern_class_values,
    .left_class_mapping  = kern_left_class_mapping,
    .right_class_mapping = kern_right_class_mapping,
    .left_class_cnt      = 11,
    .right_class_cnt     = 10,
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
const lv_font_t axel_time_date = {
#else
lv_font_t axel_time_date = {
#endif
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,    /*Function pointer to get glyph's data*/
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,    /*Function pointer to get glyph's bitmap*/
    .line_height = 23,          /*The maximum line height required by the font*/
    .base_line = 5,             /*Baseline measured from the bottom of the line*/
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



#endif /*#if AXEL_TIME_DATE*/

