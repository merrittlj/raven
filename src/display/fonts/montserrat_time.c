/*******************************************************************************
 * Size: 20 px
 * Bpp: 1
 * Opts: --bpp 1 --size 20 --font Montserrat-Medium.ttf --symbols 0123456789: --format lvgl -o montserrat_time.c
 ******************************************************************************/

#ifdef LV_LVGL_H_INCLUDE_SIMPLE
#include "lvgl.h"
#else
#include "lvgl/lvgl.h"
#endif

#ifndef MONTSERRAT_TIME
#define MONTSERRAT_TIME 1
#endif

#if MONTSERRAT_TIME

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+0030 "0" */
    0x1f, 0x6, 0x31, 0x83, 0x30, 0x6c, 0x7, 0x80,
    0xf0, 0x1e, 0x3, 0xc0, 0x78, 0xd, 0x83, 0x30,
    0x63, 0x18, 0x3e, 0x0,

    /* U+0031 "1" */
    0xf8, 0xc6, 0x31, 0x8c, 0x63, 0x18, 0xc6, 0x31,
    0x8c,

    /* U+0032 "2" */
    0x7e, 0x30, 0xc0, 0x18, 0x6, 0x1, 0x80, 0x60,
    0x30, 0x1c, 0xe, 0x7, 0x3, 0x81, 0xc0, 0x60,
    0x3f, 0xf0,

    /* U+0033 "3" */
    0x7f, 0xc0, 0x18, 0x6, 0x1, 0x80, 0x30, 0xc,
    0x3, 0xe0, 0x6, 0x0, 0x60, 0xc, 0x1, 0xa0,
    0x36, 0xc, 0x7f, 0x0,

    /* U+0034 "4" */
    0x1, 0x80, 0x18, 0x1, 0xc0, 0xc, 0x0, 0xc0,
    0xc, 0x0, 0xc3, 0xe, 0x18, 0x60, 0xc7, 0xff,
    0xc0, 0x30, 0x1, 0x80, 0xc, 0x0, 0x60,

    /* U+0035 "5" */
    0x7f, 0x98, 0x6, 0x1, 0x80, 0x60, 0x18, 0x7,
    0xf0, 0x6, 0x0, 0xc0, 0x30, 0xe, 0x3, 0xc1,
    0x9f, 0xc0,

    /* U+0036 "6" */
    0xf, 0xc6, 0x9, 0x80, 0x20, 0xc, 0x1, 0x9f,
    0x3c, 0x37, 0x3, 0xe0, 0x78, 0xd, 0x81, 0xb0,
    0x73, 0xc, 0x3e, 0x0,

    /* U+0037 "7" */
    0xff, 0xf8, 0x1b, 0x3, 0x60, 0xc0, 0x18, 0x3,
    0x0, 0xc0, 0x18, 0x6, 0x0, 0xc0, 0x30, 0x6,
    0x1, 0xc0, 0x30, 0x0,

    /* U+0038 "8" */
    0x3f, 0x8c, 0x1b, 0x1, 0xe0, 0x3c, 0x6, 0xc1,
    0x8f, 0xe3, 0x6, 0xc0, 0x78, 0xf, 0x1, 0xe0,
    0x36, 0xc, 0x3e, 0x0,

    /* U+0039 "9" */
    0x3f, 0xc, 0x33, 0x3, 0x60, 0x2c, 0x7, 0x81,
    0xd8, 0x79, 0xfb, 0x0, 0x60, 0xc, 0x3, 0x0,
    0x64, 0x38, 0xfc, 0x0,

    /* U+003A ":" */
    0xfc, 0x0, 0xfc
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 213, .box_w = 11, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 20, .adv_w = 118, .box_w = 5, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 29, .adv_w = 184, .box_w = 10, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 47, .adv_w = 183, .box_w = 11, .box_h = 14, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 67, .adv_w = 214, .box_w = 13, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 90, .adv_w = 184, .box_w = 10, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 108, .adv_w = 197, .box_w = 11, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 128, .adv_w = 191, .box_w = 11, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 148, .adv_w = 206, .box_w = 11, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 168, .adv_w = 197, .box_w = 11, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 188, .adv_w = 73, .box_w = 2, .box_h = 11, .ofs_x = 1, .ofs_y = 0}
};

/*---------------------
 *  CHARACTER MAPPING
 *--------------------*/



/*Collect the unicode lists and glyph_id offsets*/
static const lv_font_fmt_txt_cmap_t cmaps[] =
{
    {
        .range_start = 48, .range_length = 11, .glyph_id_start = 1,
        .unicode_list = NULL, .glyph_id_ofs_list = NULL, .list_length = 0, .type = LV_FONT_FMT_TXT_CMAP_FORMAT0_TINY
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
const lv_font_t montserrat_time = {
#else
lv_font_t montserrat_time = {
#endif
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,    /*Function pointer to get glyph's data*/
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,    /*Function pointer to get glyph's bitmap*/
    .line_height = 14,          /*The maximum line height required by the font*/
    .base_line = 0,             /*Baseline measured from the bottom of the line*/
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



#endif /*#if MONTSERRAT_TIME*/

