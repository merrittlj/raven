/*******************************************************************************
 * Size: 13 px
 * Bpp: 1
 * Opts: --bpp 1 --size 13 --font RobotoCondensed-Bold.ttf --symbols JanFebMarAprMayJunJulAugSepOctNovDec --format lvgl -o roboto_date.c
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
    /* U+0041 "A" */
    0x30, 0x70, 0xe3, 0x46, 0x89, 0xbf, 0x62, 0xc6,

    /* U+0044 "D" */
    0xf3, 0x2c, 0xf3, 0xcf, 0x3c, 0xf2, 0xf0,

    /* U+0046 "F" */
    0xfe, 0x31, 0x8f, 0xe3, 0x18, 0xc0,

    /* U+004A "J" */
    0xc, 0x30, 0xc3, 0xc, 0x30, 0xdb, 0x78,

    /* U+004D "M" */
    0xe7, 0xe7, 0xe7, 0xe7, 0xff, 0xff, 0xdb, 0xdb,
    0xdb,

    /* U+004E "N" */
    0xc7, 0xcf, 0x9f, 0xbd, 0x7b, 0xf3, 0xe7, 0xc6,

    /* U+004F "O" */
    0x38, 0xdb, 0x1e, 0x3c, 0x78, 0xf1, 0xb2, 0x3c,

    /* U+0053 "S" */
    0x7b, 0x3c, 0x3c, 0x78, 0x7c, 0xf3, 0x78,

    /* U+0061 "a" */
    0x76, 0xc6, 0xfd, 0xed, 0xe0,

    /* U+0062 "b" */
    0xc6, 0x31, 0xed, 0xef, 0x7b, 0xdf, 0x80,

    /* U+0063 "c" */
    0x76, 0xf1, 0x8c, 0x6d, 0xc0,

    /* U+0065 "e" */
    0x73, 0x2c, 0xbf, 0xc3, 0x27, 0x80,

    /* U+0067 "g" */
    0x7f, 0x3c, 0xf3, 0xcf, 0x37, 0xc3, 0x4d, 0xe0,

    /* U+006C "l" */
    0xff, 0xff, 0xf0,

    /* U+006E "n" */
    0xf6, 0xf7, 0xbd, 0xef, 0x60,

    /* U+006F "o" */
    0x7b, 0x3c, 0xf3, 0xcf, 0x37, 0x80,

    /* U+0070 "p" */
    0xf6, 0xf7, 0xbd, 0xef, 0xd8, 0xc6, 0x0,

    /* U+0072 "r" */
    0xfc, 0xcc, 0xcc, 0xc0,

    /* U+0074 "t" */
    0x66, 0xf6, 0x66, 0x67, 0x70,

    /* U+0075 "u" */
    0xde, 0xf7, 0xbd, 0xed, 0xe0,

    /* U+0076 "v" */
    0x6d, 0xb6, 0xdb, 0x38, 0xe3, 0x80,

    /* U+0079 "y" */
    0xcd, 0xa7, 0x9e, 0x38, 0xc3, 0xc, 0x71, 0x80
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 124, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 8, .adv_w = 118, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 15, .adv_w = 99, .box_w = 5, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 21, .adv_w = 102, .box_w = 6, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 28, .adv_w = 158, .box_w = 8, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 37, .adv_w = 127, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 45, .adv_w = 126, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 53, .adv_w = 112, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 60, .adv_w = 98, .box_w = 5, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 65, .adv_w = 103, .box_w = 5, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 72, .adv_w = 96, .box_w = 5, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 77, .adv_w = 100, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 83, .adv_w = 105, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 91, .adv_w = 52, .box_w = 2, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 94, .adv_w = 102, .box_w = 5, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 99, .adv_w = 103, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 105, .adv_w = 103, .box_w = 5, .box_h = 10, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 112, .adv_w = 69, .box_w = 4, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 116, .adv_w = 64, .box_w = 4, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 121, .adv_w = 102, .box_w = 5, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 126, .adv_w = 93, .box_w = 6, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 132, .adv_w = 93, .box_w = 6, .box_h = 10, .ofs_x = 0, .ofs_y = -3}
};

/*---------------------
 *  CHARACTER MAPPING
 *--------------------*/

static const uint16_t unicode_list_0[] = {
    0x0, 0x3, 0x5, 0x9, 0xc, 0xd, 0xe, 0x12,
    0x20, 0x21, 0x22, 0x24, 0x26, 0x2b, 0x2d, 0x2e,
    0x2f, 0x31, 0x33, 0x34, 0x35, 0x38
};

/*Collect the unicode lists and glyph_id offsets*/
static const lv_font_fmt_txt_cmap_t cmaps[] =
{
    {
        .range_start = 65, .range_length = 57, .glyph_id_start = 1,
        .unicode_list = unicode_list_0, .glyph_id_ofs_list = NULL, .list_length = 22, .type = LV_FONT_FMT_TXT_CMAP_SPARSE_TINY
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
    .cmap_num = 1,
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
    .line_height = 13,          /*The maximum line height required by the font*/
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



#endif /*#if ROBOTO_DATE*/

