/*******************************************************************************
 * Size: 7 px
 * Bpp: 1
 * Opts: --bpp 1 --size 7 --font RobotoCondensed-Light.ttf --symbols ADFMNORSTUWYadehinorstuy --format lvgl -o roboto_dow.c
 ******************************************************************************/

#ifdef LV_LVGL_H_INCLUDE_SIMPLE
#include "lvgl.h"
#else
#include "lvgl/lvgl.h"
#endif

#ifndef ROBOTO_DOW
#define ROBOTO_DOW 1
#endif

#if ROBOTO_DOW

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+0041 "A" */
    0x5b, 0x70,

    /* U+0044 "D" */
    0xe9, 0x99, 0xa0,

    /* U+0046 "F" */
    0x93, 0xc8,

    /* U+004D "M" */
    0x8c, 0x77, 0xda, 0x80,

    /* U+004E "N" */
    0x9d, 0xdb, 0x90,

    /* U+004F "O" */
    0x69, 0x99, 0xe0,

    /* U+0052 "R" */
    0xd7, 0x4a,

    /* U+0053 "S" */
    0xf1, 0x1e,

    /* U+0054 "T" */
    0x49, 0x24,

    /* U+0055 "U" */
    0x99, 0x99, 0xe0,

    /* U+0057 "W" */
    0xa5, 0x77, 0xa4, 0x0,

    /* U+0059 "Y" */
    0x97, 0x24,

    /* U+0061 "a" */
    0x6e, 0xd0,

    /* U+0064 "d" */
    0x3e, 0xde,

    /* U+0065 "e" */
    0xfe, 0x70,

    /* U+0068 "h" */
    0x9a, 0xda,

    /* U+0069 "i" */
    0x78,

    /* U+006E "n" */
    0xd6, 0xd0,

    /* U+006F "o" */
    0xd6, 0xe0,

    /* U+0072 "r" */
    0xaa,

    /* U+0073 "s" */
    0xf1, 0xf0,

    /* U+0074 "t" */
    0xf8,

    /* U+0075 "u" */
    0xb6, 0xf0,

    /* U+0079 "y" */
    0xbb, 0x24, 0x0
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 61, .box_w = 3, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2, .adv_w = 64, .box_w = 4, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 5, .adv_w = 55, .box_w = 3, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 7, .adv_w = 84, .box_w = 5, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 11, .adv_w = 69, .box_w = 4, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 14, .adv_w = 66, .box_w = 4, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 17, .adv_w = 62, .box_w = 3, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 19, .adv_w = 58, .box_w = 3, .box_h = 5, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 21, .adv_w = 58, .box_w = 3, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 23, .adv_w = 64, .box_w = 4, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 26, .adv_w = 86, .box_w = 5, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 30, .adv_w = 59, .box_w = 3, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 32, .adv_w = 53, .box_w = 3, .box_h = 4, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 34, .adv_w = 55, .box_w = 3, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 36, .adv_w = 51, .box_w = 3, .box_h = 4, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 38, .adv_w = 54, .box_w = 3, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 40, .adv_w = 24, .box_w = 1, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 41, .adv_w = 54, .box_w = 3, .box_h = 4, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 43, .adv_w = 55, .box_w = 3, .box_h = 4, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 45, .adv_w = 34, .box_w = 2, .box_h = 4, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 46, .adv_w = 50, .box_w = 3, .box_h = 4, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 48, .adv_w = 33, .box_w = 1, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 49, .adv_w = 54, .box_w = 3, .box_h = 4, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 51, .adv_w = 47, .box_w = 3, .box_h = 6, .ofs_x = 0, .ofs_y = -2}
};

/*---------------------
 *  CHARACTER MAPPING
 *--------------------*/

static const uint16_t unicode_list_0[] = {
    0x0, 0x3, 0x5, 0xc, 0xd, 0xe, 0x11, 0x12,
    0x13, 0x14, 0x16, 0x18, 0x20, 0x23, 0x24, 0x27,
    0x28, 0x2d, 0x2e, 0x31, 0x32, 0x33, 0x34, 0x38
};

/*Collect the unicode lists and glyph_id offsets*/
static const lv_font_fmt_txt_cmap_t cmaps[] =
{
    {
        .range_start = 65, .range_length = 57, .glyph_id_start = 1,
        .unicode_list = unicode_list_0, .glyph_id_ofs_list = NULL, .list_length = 24, .type = LV_FONT_FMT_TXT_CMAP_SPARSE_TINY
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
const lv_font_t roboto_dow = {
#else
lv_font_t roboto_dow = {
#endif
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,    /*Function pointer to get glyph's data*/
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,    /*Function pointer to get glyph's bitmap*/
    .line_height = 7,          /*The maximum line height required by the font*/
    .base_line = 2,             /*Baseline measured from the bottom of the line*/
#if !(LVGL_VERSION_MAJOR == 6 && LVGL_VERSION_MINOR == 0)
    .subpx = LV_FONT_SUBPX_NONE,
#endif
#if LV_VERSION_CHECK(7, 4, 0) || LVGL_VERSION_MAJOR >= 8
    .underline_position = -1,
    .underline_thickness = 0,
#endif
    .dsc = &font_dsc,          /*The custom font data. Will be accessed by `get_glyph_bitmap/dsc` */
#if LV_VERSION_CHECK(8, 2, 0) || LVGL_VERSION_MAJOR >= 9
    .fallback = &lv_font_montserrat_28,
#endif
    .user_data = NULL,
};



#endif /*#if ROBOTO_DOW*/

