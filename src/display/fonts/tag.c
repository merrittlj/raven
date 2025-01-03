/*******************************************************************************
 * Size: 110 px
 * Bpp: 1
 * Opts: --bpp 1 --size 110 --font aAnotherTag.ttf --symbols Raven --format lvgl -o tag.c
 ******************************************************************************/

#ifdef LV_LVGL_H_INCLUDE_SIMPLE
#include "lvgl.h"
#else
#include "lvgl/lvgl.h"
#endif

#ifndef TAG
#define TAG 1
#endif

#if TAG

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+0052 "R" */
    0x6, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0xe0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x1f, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x3, 0xf8, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x3f, 0x80,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x7,
    0xfc, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x7f, 0xc0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0xf, 0xfe, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0xff, 0xf0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x7, 0xff, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x7f,
    0xf8, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x3, 0xff, 0xc0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x1f, 0xfe, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x1, 0xff, 0xf0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0xf, 0xff, 0x80,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xff,
    0xfc, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x7, 0xff, 0xe0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x3f, 0xff, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x3, 0xff, 0xf8, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x1f, 0xff, 0xe0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x1, 0xff,
    0xff, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x1f, 0xff, 0xf8, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x1, 0xff, 0xff, 0xc0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x1f, 0xff, 0xfe, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x1, 0xff, 0xff, 0xf8,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xf, 0xff,
    0xff, 0xc0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0xff, 0xff, 0xfe, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0xf, 0xff, 0xff, 0xf0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x7f, 0xff, 0xff, 0x80, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x7, 0xff, 0xff, 0xfc,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x7f, 0xff,
    0xff, 0xe0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x3,
    0xfe, 0xff, 0xff, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x3f, 0xe7, 0xff, 0xf8, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x3, 0xfe, 0x3f, 0xff, 0xc0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x1f, 0xf0, 0xff, 0xfe,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x1, 0xff, 0x7,
    0xff, 0xf0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x1f,
    0xf0, 0x3f, 0xff, 0x80, 0x0, 0x0, 0x0, 0x0,
    0x0, 0xff, 0x81, 0xff, 0xf8, 0x0, 0x0, 0x0,
    0x0, 0x0, 0xf, 0xf8, 0xf, 0xff, 0xc0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0xff, 0x80, 0x7f, 0xfc,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x7, 0xfc, 0x3,
    0xff, 0xc0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x7f,
    0xc0, 0x1f, 0xfc, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x7, 0xfe, 0x0, 0xff, 0x80, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x3f, 0xfe, 0x7, 0xf8, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x3, 0xff, 0xff, 0xff, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x3f, 0xff, 0xff,
    0xf0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x3, 0xff,
    0xff, 0xfe, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x1f, 0xff, 0xff, 0xc0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x1, 0xff, 0xff, 0xf8, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x1f, 0xff, 0xfe, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0xff, 0xff, 0xe0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xf, 0xff,
    0xff, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0xff, 0xff, 0xfc, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x7, 0xff, 0xff, 0xe0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x7f, 0xff, 0xff, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x7, 0xfb, 0xff, 0xf8,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x3f, 0xdf,
    0xff, 0xc0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x3,
    0xfc, 0xff, 0xfe, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x3f, 0xe7, 0xff, 0xf0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x3, 0xfe, 0x1f, 0xff, 0xc0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x1f, 0xe0, 0xff, 0xfe,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x1, 0xff, 0x7,
    0xff, 0xf0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x1f,
    0xf0, 0x3f, 0xff, 0x80, 0x0, 0x0, 0x0, 0x0,
    0x0, 0xff, 0x81, 0xff, 0xfc, 0x0, 0x0, 0x0,
    0x0, 0x0, 0xf, 0xf8, 0xf, 0xff, 0xe0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0xff, 0x80, 0x7f, 0xff,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x7, 0xfc, 0x3,
    0xff, 0xfc, 0x0, 0x0, 0x0, 0x0, 0x0, 0x7f,
    0xc0, 0x1f, 0xff, 0xe0, 0x10, 0x0, 0x0, 0x0,
    0x7, 0xfc, 0x0, 0xff, 0xff, 0x3, 0x80, 0x0,
    0x0, 0x0, 0x3f, 0x80, 0x7, 0xff, 0xf8, 0x38,
    0x0, 0x0, 0x0, 0x3, 0xf9, 0x0, 0x3f, 0xff,
    0xc7, 0xc0, 0x0, 0x0, 0x0, 0x3f, 0x10, 0x1,
    0xff, 0xfe, 0xfc, 0x0, 0x0, 0x0, 0x1, 0xf3,
    0x0, 0xf, 0xff, 0xff, 0xe0, 0x0, 0x0, 0x0,
    0x1e, 0x38, 0x0, 0x3f, 0xff, 0xfe, 0x0, 0x0,
    0x0, 0x0, 0xc7, 0x0, 0x1, 0xff, 0xff, 0xf0,
    0x0, 0x0, 0x0, 0x0, 0x70, 0x0, 0xf, 0xff,
    0xff, 0x0, 0x0, 0x0, 0x0, 0xe, 0x0, 0x0,
    0x7f, 0xff, 0xf8, 0x0, 0x0, 0x0, 0x1, 0xe0,
    0x0, 0x3, 0xff, 0xff, 0xc0, 0x0, 0x0, 0x0,
    0x3c, 0x0, 0x0, 0x1f, 0xff, 0xfc, 0x0, 0x0,
    0x0, 0x3, 0x80, 0x0, 0x0, 0xff, 0xff, 0xe0,
    0x0, 0x0, 0x0, 0x38, 0x0, 0x0, 0x7, 0xff,
    0xff, 0x0, 0x0, 0x0, 0x1, 0x0, 0x0, 0x0,
    0x3f, 0xff, 0xf0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x1, 0xff, 0xff, 0x80, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0xf, 0xff, 0xf8, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x7f, 0xff, 0xc0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x3, 0xff,
    0xfe, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0xf, 0xff, 0xe0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x7f, 0xff, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x3, 0xff, 0xf0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x1f, 0xfe, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xff,
    0xe0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x7, 0xfc, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x3f, 0x80, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x1, 0xf8, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0xf, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x60,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0,

    /* U+0061 "a" */
    0x0, 0x0, 0x0, 0x1, 0x80, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x1c, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x1, 0xf8, 0x0, 0x0, 0x0, 0x0, 0x0, 0xf,
    0xe0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xff, 0x0,
    0x0, 0x0, 0x0, 0x0, 0xf, 0xf8, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x7f, 0xc0, 0x0, 0x0, 0x0,
    0x0, 0x7, 0xfe, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x3f, 0xf0, 0x0, 0x0, 0x0, 0x0, 0x1, 0xff,
    0xc0, 0x0, 0x0, 0x0, 0x0, 0x7, 0xfe, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x3f, 0xf0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0xff, 0xc0, 0x0, 0x0, 0x0,
    0x0, 0x7, 0xfe, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x1f, 0xf0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xff,
    0xc0, 0x0, 0x0, 0x0, 0x0, 0x7, 0xfe, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x3f, 0xf0, 0x0, 0x0,
    0x0, 0x0, 0x1, 0xff, 0xc0, 0x0, 0x0, 0x0,
    0x0, 0xf, 0xfe, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x7f, 0xf8, 0x0, 0x0, 0x0, 0x0, 0x7, 0xff,
    0xc0, 0x0, 0x0, 0x0, 0x0, 0x3f, 0xff, 0x0,
    0x0, 0x0, 0x0, 0x1, 0xff, 0xf8, 0x0, 0x7,
    0xf0, 0x0, 0xf, 0xff, 0xc0, 0x0, 0x7f, 0xf8,
    0x0, 0xfb, 0xff, 0x0, 0x3, 0xff, 0xfc, 0x7,
    0xdf, 0xf8, 0x0, 0x3f, 0xff, 0xfc, 0x3c, 0x7f,
    0xe0, 0x3, 0xff, 0xff, 0xff, 0xe3, 0xff, 0x0,
    0x1f, 0xff, 0xff, 0xff, 0xf, 0xfc, 0x1, 0xff,
    0xff, 0xff, 0xf8, 0x7f, 0xe0, 0x1f, 0xff, 0xff,
    0xff, 0xf3, 0xff, 0x80, 0xff, 0xff, 0xff, 0xff,
    0xef, 0xfc, 0x7, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xf0, 0x0, 0x1f, 0xff, 0xff, 0xff, 0xff, 0x80,
    0x0, 0xf, 0xff, 0xff, 0xff, 0xfe, 0x0, 0x0,
    0xf, 0xff, 0xff, 0xff, 0xf0, 0x0, 0x0, 0xf,
    0xff, 0xff, 0xff, 0xc0, 0x0, 0x0, 0xf, 0xff,
    0xff, 0xfe, 0x0, 0x0, 0x0, 0x3f, 0xff, 0xff,
    0xf8, 0x0, 0x0, 0x1, 0xff, 0xff, 0xff, 0xc0,
    0x0, 0x0, 0xf, 0xbf, 0xff, 0xff, 0x0, 0x0,
    0x0, 0x78, 0x7f, 0xff, 0xf8, 0x0, 0x0, 0x3,
    0x80, 0xff, 0xff, 0xe0, 0x0, 0x0, 0x3c, 0x3,
    0xff, 0xff, 0x0, 0x0, 0x1, 0xc0, 0x7, 0xff,
    0xfc, 0x0, 0x0, 0xe, 0x0, 0x1f, 0xff, 0xe0,
    0x0, 0x0, 0xe0, 0x0, 0x3f, 0xfe, 0x0, 0x0,
    0x7, 0x0, 0x0, 0xff, 0xf0, 0x0, 0x0, 0x30,
    0x0, 0x3, 0xff, 0x0, 0x0, 0x1, 0x0, 0x0,
    0xf, 0xf8, 0x0, 0x0, 0x10, 0x0, 0x0, 0x3f,
    0x80, 0x0, 0x0, 0x0, 0x0, 0x0, 0x78, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x1, 0xc0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x4, 0x0,

    /* U+0065 "e" */
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x80, 0x0, 0x0, 0x0, 0x0, 0x0,
    0xc0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xc0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x60, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x60, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x70, 0x0, 0x0, 0x0, 0x0, 0x0, 0x30, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x38, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x38, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x1c, 0x0, 0x0, 0x0, 0x0, 0x0, 0x1e, 0x0,
    0x0, 0x0, 0x0, 0x0, 0xe, 0x0, 0x0, 0x0,
    0x0, 0x0, 0xf, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x7, 0x80, 0x0, 0x0, 0x0, 0x0, 0x7, 0xc0,
    0x0, 0x0, 0x0, 0x0, 0xff, 0xe0, 0x0, 0x0,
    0x0, 0x1, 0xff, 0xf0, 0x0, 0x0, 0x0, 0x1,
    0xff, 0xf8, 0x0, 0x0, 0x0, 0x3, 0xff, 0xfc,
    0x0, 0x0, 0x0, 0x3, 0xff, 0xfe, 0x0, 0x0,
    0x0, 0x3, 0xff, 0xff, 0x0, 0x0, 0x0, 0x1,
    0xff, 0xff, 0x80, 0x0, 0x0, 0x1, 0xff, 0xff,
    0xe0, 0x0, 0x0, 0x1, 0xff, 0xff, 0xf0, 0x0,
    0x0, 0x1, 0xe0, 0x7f, 0xf8, 0x0, 0x0, 0x0,
    0xe0, 0xf, 0xfc, 0x0, 0x0, 0x0, 0xe0, 0x3,
    0xfe, 0x0, 0x0, 0x0, 0x70, 0x1, 0xfe, 0x0,
    0x0, 0x0, 0x78, 0x0, 0x7f, 0x0, 0x0, 0x0,
    0x3e, 0x0, 0x1f, 0x0, 0x0, 0x0, 0x3f, 0x0,
    0xf, 0x80, 0x0, 0x0, 0x1f, 0xc0, 0x7, 0x80,
    0x0, 0x0, 0x1f, 0xf0, 0x1, 0x80, 0x0, 0x0,
    0xf, 0xfc, 0x0, 0x80, 0x0, 0x8, 0x7, 0xff,
    0x0, 0x0, 0x0, 0xc, 0x3, 0xff, 0xc0, 0x0,
    0x0, 0xe, 0x1, 0xff, 0xf8, 0x0, 0x0, 0xf,
    0x0, 0xff, 0xff, 0x0, 0x0, 0xf, 0x80, 0x3f,
    0xff, 0xe0, 0x0, 0x7, 0xc0, 0x1f, 0xff, 0xfe,
    0x0, 0x7, 0xf0, 0x7, 0xff, 0xff, 0x80, 0x3,
    0xf8, 0x3, 0xff, 0xff, 0xf0, 0x1, 0xfc, 0x0,
    0xff, 0xff, 0xf8, 0x0, 0xfe, 0x0, 0x3f, 0xff,
    0xfc, 0x0, 0x7f, 0x80, 0x7, 0xff, 0xfe, 0x0,
    0x3f, 0xc0, 0x1, 0xff, 0xfe, 0x0, 0x1f, 0xe0,
    0x0, 0x3f, 0xff, 0x0, 0xf, 0xf8, 0x0, 0x7,
    0xff, 0x0, 0x7, 0xfc, 0x0, 0x0, 0xff, 0x0,
    0x1, 0xfe, 0x0, 0x0, 0xf, 0x0, 0x0, 0xff,
    0x80, 0x0, 0xf, 0x80, 0x0, 0x7f, 0xc0, 0x0,
    0xf, 0x80, 0x0, 0x3f, 0xe0, 0x0, 0xf, 0x80,
    0x0, 0xf, 0xf8, 0x0, 0xf, 0x80, 0x0, 0x7,
    0xfc, 0x0, 0xf, 0x80, 0x0, 0x3, 0xfe, 0x0,
    0xf, 0x80, 0x0, 0x0, 0xff, 0x80, 0xf, 0x80,
    0x3f, 0xff, 0xff, 0xc0, 0xf, 0x87, 0xff, 0xff,
    0xff, 0xe0, 0xf, 0xbf, 0xff, 0xff, 0xff, 0xf0,
    0xf, 0xff, 0xff, 0xff, 0xff, 0xf8, 0xf, 0xff,
    0xff, 0xff, 0xff, 0xf8, 0xf, 0xff, 0xff, 0xff,
    0xff, 0xfc, 0x7, 0xff, 0xff, 0xff, 0xff, 0xfc,
    0x7, 0xff, 0xff, 0xff, 0xff, 0xfe, 0x7, 0xff,
    0xff, 0xff, 0xff, 0xfe, 0x7, 0xff, 0xfc, 0x0,
    0x7, 0xff, 0x3, 0xff, 0xc0, 0x0, 0x0, 0x1f,
    0x3, 0xfe, 0x0, 0x0, 0x0, 0x0, 0x3, 0xf8,
    0x0, 0x0, 0x0, 0x0, 0x1, 0xf0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0xc0, 0x0, 0x0, 0x0, 0x0,
    0x0,

    /* U+006E "n" */
    0x0, 0x0, 0x0, 0x0, 0x8, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x70, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x3, 0xc0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x1f, 0x80, 0x0, 0x0, 0x0, 0x0, 0x0, 0x7e,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x3, 0xf8, 0x0,
    0x0, 0x0, 0x0, 0x0, 0xf, 0xf0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x7f, 0xc0, 0x0, 0x0, 0x0,
    0x0, 0x1, 0xff, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x3, 0xfc, 0x0, 0x0, 0x0, 0x0, 0x0, 0xf,
    0xf8, 0x0, 0x0, 0x0, 0x0, 0x0, 0x3f, 0xe0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0xff, 0x80, 0x0,
    0x0, 0x0, 0x0, 0x1, 0xff, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x7, 0xfc, 0x0, 0x0, 0xc, 0x0,
    0x0, 0x1f, 0xf0, 0x0, 0x0, 0x70, 0x0, 0x0,
    0x3f, 0xe0, 0x0, 0xf, 0xe0, 0x0, 0x0, 0xff,
    0x80, 0x0, 0xff, 0x80, 0x0, 0x3, 0xfe, 0x0,
    0x7, 0xff, 0x0, 0x0, 0x7, 0xfc, 0x0, 0x1f,
    0xfc, 0x0, 0x0, 0x1f, 0xf0, 0x0, 0xff, 0xf8,
    0x0, 0x0, 0x7f, 0xc0, 0x7, 0xff, 0xf0, 0x0,
    0x0, 0xff, 0x0, 0x1f, 0xff, 0xe0, 0x0, 0x3,
    0xfe, 0x0, 0xff, 0xff, 0xc0, 0x0, 0xf, 0xf8,
    0x3, 0xff, 0xff, 0xc0, 0x0, 0x3f, 0xe0, 0x3,
    0xff, 0xff, 0x80, 0x0, 0x7f, 0xc0, 0x7, 0xff,
    0xff, 0x0, 0x1, 0xff, 0x0, 0xf, 0xff, 0xff,
    0x0, 0x7, 0xfc, 0x0, 0xf, 0xff, 0xfe, 0x0,
    0xf, 0xf8, 0x0, 0x1f, 0xff, 0xfe, 0x0, 0x3f,
    0xe0, 0x0, 0x1f, 0xff, 0xfc, 0x0, 0xff, 0x80,
    0x0, 0x7f, 0xff, 0xf8, 0x1, 0xff, 0x0, 0x0,
    0xff, 0xff, 0xf8, 0x7, 0xfc, 0x0, 0x3, 0xff,
    0xff, 0xf0, 0x1f, 0xf0, 0x0, 0x7, 0xff, 0xff,
    0xe0, 0x3f, 0xe0, 0x0, 0x1f, 0xff, 0xff, 0xe0,
    0xff, 0x80, 0x0, 0x7f, 0xff, 0xff, 0xc3, 0xfe,
    0x0, 0x0, 0xff, 0xff, 0xff, 0xcf, 0xfc, 0x0,
    0x3, 0xff, 0xff, 0xff, 0x9f, 0xf0, 0x0, 0x7,
    0xff, 0xff, 0xff, 0x7f, 0xc0, 0x0, 0x1f, 0xfb,
    0xff, 0xff, 0xff, 0x80, 0x0, 0x7f, 0xe7, 0xff,
    0xff, 0xfe, 0x0, 0x0, 0xff, 0xcf, 0xff, 0xff,
    0xf8, 0x0, 0x3, 0xff, 0xf, 0xff, 0xff, 0xf0,
    0x0, 0xf, 0xfc, 0x1f, 0xff, 0xff, 0xc0, 0x0,
    0x1f, 0xf0, 0x3f, 0xff, 0xff, 0x0, 0x0, 0x7f,
    0xe0, 0x3f, 0xff, 0xfe, 0x0, 0x0, 0xff, 0x80,
    0x7f, 0xff, 0xf8, 0x0, 0x3, 0xfe, 0x0, 0xff,
    0xff, 0xe0, 0x0, 0xf, 0xfc, 0x1, 0xff, 0xff,
    0xc0, 0x0, 0x1f, 0xf0, 0x1, 0xff, 0xfe, 0x0,
    0x0, 0x7f, 0xc0, 0x3, 0xff, 0xf8, 0x0, 0x1,
    0xff, 0x80, 0x7, 0xff, 0xc0, 0x0, 0x3, 0xfe,
    0x0, 0x7, 0xff, 0x0, 0x0, 0xf, 0xf8, 0x0,
    0xf, 0xf8, 0x0, 0x0, 0x3f, 0xf0, 0x0, 0x1f,
    0xc0, 0x0, 0x0, 0x7f, 0xc0, 0x0, 0x1e, 0x0,
    0x0, 0x1, 0xff, 0x0, 0x0, 0x30, 0x0, 0x0,
    0x3, 0xfc, 0x0, 0x0, 0x0, 0x0, 0x0, 0xf,
    0xe0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x3f, 0x80,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x7c, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x1, 0xe0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x7, 0x80, 0x0, 0x0, 0x0, 0x0,
    0x0, 0xc, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x20, 0x0, 0x0, 0x0, 0x0,

    /* U+0076 "v" */
    0x0, 0x0, 0x0, 0x0, 0x0, 0x40, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x8, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x3, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x60, 0x0, 0x0, 0x0, 0x0, 0x0, 0x1c, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x7, 0x80, 0x0, 0x0,
    0x0, 0x0, 0x0, 0xf0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x3e, 0x0, 0x0, 0x0, 0x0, 0x0, 0xf,
    0xc0, 0x0, 0x0, 0x0, 0x0, 0x1, 0xfc, 0x0,
    0x0, 0x7c, 0x0, 0x0, 0x3f, 0x80, 0x0, 0x1f,
    0xe0, 0x0, 0x7, 0xf0, 0x0, 0xf, 0xfe, 0x0,
    0x0, 0xfe, 0x0, 0x3, 0xff, 0xe0, 0x0, 0x1f,
    0xc0, 0x0, 0x7f, 0xfe, 0x0, 0x3, 0xf8, 0x0,
    0x1f, 0xff, 0xe0, 0x0, 0x7f, 0x0, 0x7, 0xff,
    0xfe, 0x0, 0xf, 0xe0, 0x0, 0xff, 0xff, 0xe0,
    0x1, 0xfc, 0x0, 0x3f, 0xff, 0xfe, 0x0, 0x3f,
    0x80, 0x7, 0xbf, 0xff, 0xc0, 0x7, 0xf0, 0x1,
    0xe1, 0xff, 0xfc, 0x0, 0xfe, 0x0, 0x3c, 0xf,
    0xff, 0xc0, 0x1f, 0xc0, 0xf, 0x80, 0xff, 0xf8,
    0x3, 0xf8, 0x1, 0xf0, 0xf, 0xff, 0x80, 0x7f,
    0x0, 0x3e, 0x0, 0xff, 0xf8, 0xf, 0xe0, 0x7,
    0xc0, 0xf, 0xff, 0x81, 0xfc, 0x1, 0xf8, 0x0,
    0xff, 0xf0, 0x3f, 0x80, 0x3f, 0x0, 0xf, 0xff,
    0x7, 0xf8, 0x7, 0xe0, 0x1, 0xff, 0xe0, 0xff,
    0x0, 0xfc, 0x0, 0x1f, 0xfe, 0xf, 0xe0, 0x1f,
    0x80, 0x1, 0xff, 0xe1, 0xfc, 0x3, 0xe0, 0x0,
    0x3f, 0xfc, 0x3f, 0x80, 0xfc, 0x0, 0x3, 0xff,
    0xc7, 0xf0, 0x1f, 0x80, 0x0, 0x3f, 0xfc, 0xfe,
    0x3, 0xf0, 0x0, 0x7, 0xff, 0x9f, 0xc0, 0x7e,
    0x0, 0x0, 0x7f, 0xfb, 0xf8, 0xf, 0x80, 0x0,
    0x7, 0xff, 0x7f, 0x81, 0xf0, 0x0, 0x0, 0xff,
    0xff, 0xf0, 0x3e, 0x0, 0x0, 0xf, 0xff, 0xfe,
    0x7, 0xc0, 0x0, 0x0, 0xff, 0xff, 0xc0, 0xf0,
    0x0, 0x0, 0x1f, 0xff, 0xf8, 0x1c, 0x0, 0x0,
    0x1, 0xff, 0xff, 0x3, 0x80, 0x0, 0x0, 0x3f,
    0xff, 0xe0, 0x60, 0x0, 0x0, 0x3, 0xff, 0xfe,
    0x8, 0x0, 0x0, 0x0, 0x3f, 0xff, 0xc0, 0x0,
    0x0, 0x0, 0x7, 0xff, 0xf8, 0x0, 0x0, 0x0,
    0x0, 0x7f, 0xff, 0x0, 0x0, 0x0, 0x0, 0xf,
    0xff, 0xe0, 0x0, 0x0, 0x0, 0x0, 0xff, 0xfe,
    0x0, 0x0, 0x0, 0x0, 0xf, 0xff, 0xc0, 0x0,
    0x0, 0x0, 0x1, 0xff, 0xf8, 0x0, 0x0, 0x0,
    0x0, 0x1f, 0xff, 0x80, 0x0, 0x0, 0x0, 0x3,
    0xff, 0xf0, 0x0, 0x0, 0x0, 0x0, 0x3f, 0xfe,
    0x0, 0x0, 0x0, 0x0, 0x3, 0xff, 0xc0, 0x0,
    0x0, 0x0, 0x0, 0x7f, 0xfc, 0x0, 0x0, 0x0,
    0x0, 0x7, 0xff, 0x80, 0x0, 0x0, 0x0, 0x0,
    0xff, 0xf0, 0x0, 0x0, 0x0, 0x0, 0xf, 0xff,
    0x0, 0x0, 0x0, 0x0, 0x1, 0xff, 0xe0, 0x0,
    0x0, 0x0, 0x0, 0x1f, 0xfc, 0x0, 0x0, 0x0,
    0x0, 0x1, 0xff, 0xc0, 0x0, 0x0, 0x0, 0x0,
    0x3f, 0xf8, 0x0, 0x0, 0x0, 0x0, 0x3, 0xfe,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x7f, 0xc0, 0x0,
    0x0, 0x0, 0x0, 0x7, 0xf0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0xfc, 0x0, 0x0, 0x0, 0x0, 0x0,
    0xf, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xe0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x18, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 483, .box_w = 76, .box_h = 97, .ofs_x = -10, .ofs_y = -21},
    {.bitmap_index = 922, .adv_w = 504, .box_w = 53, .box_h = 55, .ofs_x = -16, .ofs_y = 4},
    {.bitmap_index = 1287, .adv_w = 677, .box_w = 49, .box_h = 72, .ofs_x = -2, .ofs_y = 0},
    {.bitmap_index = 1728, .adv_w = 660, .box_w = 54, .box_h = 67, .ofs_x = -8, .ofs_y = -3},
    {.bitmap_index = 2181, .adv_w = 555, .box_w = 51, .box_h = 71, .ofs_x = -13, .ofs_y = -2}
};

/*---------------------
 *  CHARACTER MAPPING
 *--------------------*/

static const uint16_t unicode_list_0[] = {
    0x0, 0xf, 0x13, 0x1c, 0x24
};

/*Collect the unicode lists and glyph_id offsets*/
static const lv_font_fmt_txt_cmap_t cmaps[] =
{
    {
        .range_start = 82, .range_length = 37, .glyph_id_start = 1,
        .unicode_list = unicode_list_0, .glyph_id_ofs_list = NULL, .list_length = 5, .type = LV_FONT_FMT_TXT_CMAP_SPARSE_TINY
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
const lv_font_t tag = {
#else
lv_font_t tag = {
#endif
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,    /*Function pointer to get glyph's data*/
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,    /*Function pointer to get glyph's bitmap*/
    .line_height = 97,          /*The maximum line height required by the font*/
    .base_line = 21,             /*Baseline measured from the bottom of the line*/
#if !(LVGL_VERSION_MAJOR == 6 && LVGL_VERSION_MINOR == 0)
    .subpx = LV_FONT_SUBPX_NONE,
#endif
#if LV_VERSION_CHECK(7, 4, 0) || LVGL_VERSION_MAJOR >= 8
    .underline_position = -8,
    .underline_thickness = 5,
#endif
    .dsc = &font_dsc,          /*The custom font data. Will be accessed by `get_glyph_bitmap/dsc` */
#if LV_VERSION_CHECK(8, 2, 0) || LVGL_VERSION_MAJOR >= 9
    .fallback = &lv_font_montserrat_28,
#endif
    .user_data = NULL,
};



#endif /*#if TAG*/

