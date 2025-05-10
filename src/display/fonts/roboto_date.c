/*******************************************************************************
 * Size: 20 px
 * Bpp: 1
 * Opts: --bpp 1 --size 20 --font RobotoCondensed-Regular.ttf --symbols 1234567890:MondayTuesWhrFiSt --format lvgl -o roboto_date.c
 ******************************************************************************/

#ifdef LV_LVGL_H_INCLUDE_SIMPLE
#include "lvgl.h"
#else
#include "lvgl/lvgl.h"
#endif

#ifndef ROBOTO_DATE
#define ROBOTO_DATE 1
#endif

#if ROBOTO_DATE

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+0030 "0" */
    0x3c, 0x66, 0x42, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3,
    0xc3, 0xc3, 0xc3, 0xc3, 0x42, 0x66, 0x3c,

    /* U+0031 "1" */
    0xb, 0xff, 0x31, 0x8c, 0x63, 0x18, 0xc6, 0x31,
    0x8c, 0x60,

    /* U+0032 "2" */
    0x3c, 0x66, 0xc3, 0xc3, 0x3, 0x3, 0x6, 0x6,
    0xc, 0x1c, 0x18, 0x30, 0x70, 0xe0, 0xff,

    /* U+0033 "3" */
    0x38, 0xdb, 0x1e, 0x30, 0x60, 0xc3, 0x1e, 0xe,
    0xc, 0x1e, 0x3c, 0x6d, 0x8e, 0x0,

    /* U+0034 "4" */
    0x3, 0x1, 0xc0, 0x70, 0x3c, 0xb, 0x6, 0xc3,
    0x30, 0xcc, 0x63, 0x18, 0xcf, 0xfc, 0xc, 0x3,
    0x0, 0xc0, 0x30,

    /* U+0035 "5" */
    0x7f, 0x60, 0x60, 0x40, 0x40, 0x40, 0x7c, 0x46,
    0x3, 0x3, 0x3, 0xc3, 0xc3, 0x66, 0x3c,

    /* U+0036 "6" */
    0x1c, 0x30, 0x60, 0x60, 0xc0, 0xc0, 0xdc, 0xe6,
    0xc3, 0xc3, 0xc3, 0xc3, 0x43, 0x66, 0x3c,

    /* U+0037 "7" */
    0xff, 0x3, 0x2, 0x6, 0x6, 0x4, 0xc, 0xc,
    0x8, 0x18, 0x18, 0x10, 0x30, 0x30, 0x20,

    /* U+0038 "8" */
    0x38, 0x6c, 0xc6, 0xc6, 0xc6, 0xc6, 0x6c, 0x3c,
    0x66, 0xc3, 0xc3, 0xc3, 0xc3, 0x66, 0x3c,

    /* U+0039 "9" */
    0x3c, 0x66, 0xc6, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3,
    0x67, 0x3b, 0x3, 0x2, 0x6, 0xc, 0x38,

    /* U+003A ":" */
    0xc0, 0x0, 0xc,

    /* U+0046 "F" */
    0xff, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xfe,
    0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0,

    /* U+004D "M" */
    0xe0, 0x7e, 0x7, 0xe0, 0x7f, 0xf, 0xf0, 0xff,
    0xf, 0xd0, 0xbd, 0x9b, 0xd9, 0xbc, 0x93, 0xcf,
    0x3c, 0xf3, 0xc6, 0x3c, 0x63, 0xc6, 0x30,

    /* U+0053 "S" */
    0x3e, 0x31, 0xb0, 0x78, 0x3c, 0x7, 0x1, 0xf0,
    0x7c, 0xf, 0x1, 0xc0, 0x78, 0x3c, 0x1b, 0x18,
    0xf8,

    /* U+0054 "T" */
    0xff, 0xc3, 0x0, 0xc0, 0x30, 0xc, 0x3, 0x0,
    0xc0, 0x30, 0xc, 0x3, 0x0, 0xc0, 0x30, 0xc,
    0x3, 0x0, 0xc0,

    /* U+0057 "W" */
    0xc3, 0xf, 0xc, 0x2c, 0x71, 0xb1, 0xc6, 0x47,
    0x19, 0x16, 0x66, 0x59, 0x1b, 0x24, 0x6c, 0xb1,
    0xa2, 0xc2, 0x8f, 0xa, 0x1c, 0x38, 0x60, 0xc1,
    0x83, 0x6, 0x0,

    /* U+0061 "a" */
    0x3d, 0xcf, 0x18, 0x33, 0xec, 0xf1, 0xe3, 0xc7,
    0x9d, 0xd8,

    /* U+0064 "d" */
    0x3, 0x3, 0x3, 0x3, 0x3f, 0x67, 0xc3, 0xc3,
    0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0x67, 0x3f,

    /* U+0065 "e" */
    0x3c, 0x66, 0xc3, 0xc3, 0xc3, 0xff, 0xc0, 0xc0,
    0xc0, 0x63, 0x3e,

    /* U+0068 "h" */
    0xc1, 0x83, 0x6, 0xd, 0xdc, 0xf1, 0xe3, 0xc7,
    0x8f, 0x1e, 0x3c, 0x78, 0xf1, 0x80,

    /* U+0069 "i" */
    0xc0, 0xff, 0xff, 0xfc,

    /* U+006E "n" */
    0xdd, 0xcf, 0x1e, 0x3c, 0x78, 0xf1, 0xe3, 0xc7,
    0x8f, 0x18,

    /* U+006F "o" */
    0x3c, 0x66, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3,
    0xc3, 0x66, 0x3c,

    /* U+0072 "r" */
    0xfe, 0x31, 0x8c, 0x63, 0x18, 0xc6, 0x30,

    /* U+0073 "s" */
    0x3d, 0x9f, 0x1e, 0xf, 0xf, 0x87, 0x83, 0xc7,
    0x8c, 0xf0,

    /* U+0074 "t" */
    0x30, 0xc3, 0x3f, 0x30, 0xc3, 0xc, 0x30, 0xc3,
    0xc, 0x30, 0x70,

    /* U+0075 "u" */
    0xc7, 0x8f, 0x1e, 0x3c, 0x78, 0xf1, 0xe3, 0xc7,
    0x9d, 0xf8,

    /* U+0079 "y" */
    0xc3, 0x63, 0x66, 0x66, 0x26, 0x34, 0x3c, 0x1c,
    0x1c, 0x18, 0x18, 0x18, 0x10, 0x70, 0x60
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 158, .box_w = 8, .box_h = 15, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 15, .adv_w = 158, .box_w = 5, .box_h = 15, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 25, .adv_w = 158, .box_w = 8, .box_h = 15, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 40, .adv_w = 158, .box_w = 7, .box_h = 15, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 54, .adv_w = 158, .box_w = 10, .box_h = 15, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 73, .adv_w = 158, .box_w = 8, .box_h = 15, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 88, .adv_w = 158, .box_w = 8, .box_h = 15, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 103, .adv_w = 158, .box_w = 8, .box_h = 15, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 118, .adv_w = 158, .box_w = 8, .box_h = 15, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 133, .adv_w = 158, .box_w = 8, .box_h = 15, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 148, .adv_w = 75, .box_w = 2, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 151, .adv_w = 154, .box_w = 8, .box_h = 15, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 166, .adv_w = 242, .box_w = 12, .box_h = 15, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 189, .adv_w = 166, .box_w = 9, .box_h = 15, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 206, .adv_w = 167, .box_w = 10, .box_h = 15, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 225, .adv_w = 244, .box_w = 14, .box_h = 15, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 252, .adv_w = 153, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 262, .adv_w = 159, .box_w = 8, .box_h = 15, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 277, .adv_w = 150, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 288, .adv_w = 155, .box_w = 7, .box_h = 15, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 302, .adv_w = 73, .box_w = 2, .box_h = 15, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 306, .adv_w = 155, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 316, .adv_w = 161, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 327, .adv_w = 98, .box_w = 5, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 334, .adv_w = 146, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 344, .adv_w = 95, .box_w = 6, .box_h = 14, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 355, .adv_w = 155, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 365, .adv_w = 133, .box_w = 8, .box_h = 15, .ofs_x = 0, .ofs_y = -4}
};

/*---------------------
 *  CHARACTER MAPPING
 *--------------------*/

static const uint16_t unicode_list_1[] = {
    0x0, 0x7, 0xd, 0xe, 0x11, 0x1b, 0x1e, 0x1f,
    0x22, 0x23, 0x28, 0x29, 0x2c, 0x2d, 0x2e, 0x2f,
    0x33
};

/*Collect the unicode lists and glyph_id offsets*/
static const lv_font_fmt_txt_cmap_t cmaps[] =
{
    {
        .range_start = 48, .range_length = 11, .glyph_id_start = 1,
        .unicode_list = NULL, .glyph_id_ofs_list = NULL, .list_length = 0, .type = LV_FONT_FMT_TXT_CMAP_FORMAT0_TINY
    },
    {
        .range_start = 70, .range_length = 52, .glyph_id_start = 12,
        .unicode_list = unicode_list_1, .glyph_id_ofs_list = NULL, .list_length = 17, .type = LV_FONT_FMT_TXT_CMAP_SPARSE_TINY
    }
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
    .kern_dsc = NULL,
    .kern_scale = 0,
    .cmap_num = 2,
    .bpp = 1,
    .kern_classes = 0,
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
const lv_font_t roboto_date = {
#else
lv_font_t roboto_date = {
#endif
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,    /*Function pointer to get glyph's data*/
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,    /*Function pointer to get glyph's bitmap*/
    .line_height = 19,          /*The maximum line height required by the font*/
    .base_line = 4,             /*Baseline measured from the bottom of the line*/
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



#endif /*#if ROBOTO_DATE*/

