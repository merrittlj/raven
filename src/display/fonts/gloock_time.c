/*******************************************************************************
 * Size: 70 px
 * Bpp: 1
 * Opts: --bpp 1 --size 70 --font Gloock-Regular.ttf --symbols 1234567890: --format lvgl -o gloock_time.c
 ******************************************************************************/

#ifdef LV_LVGL_H_INCLUDE_SIMPLE
#include "lvgl.h"
#else
#include "lvgl/lvgl.h"
#endif

#ifndef GLOOCK_TIME
#define GLOOCK_TIME 1
#endif

#if GLOOCK_TIME

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+0030 "0" */
    0x0, 0x0, 0xff, 0x80, 0x0, 0x0, 0x3, 0xe0,
    0xf8, 0x0, 0x0, 0x7, 0xe0, 0x3f, 0x0, 0x0,
    0x7, 0xe0, 0xf, 0xc0, 0x0, 0xf, 0xe0, 0x3,
    0xf8, 0x0, 0xf, 0xf0, 0x1, 0xfe, 0x0, 0xf,
    0xf0, 0x0, 0x7f, 0x80, 0x7, 0xf8, 0x0, 0x3f,
    0xc0, 0x7, 0xfc, 0x0, 0x1f, 0xf0, 0x7, 0xfc,
    0x0, 0x7, 0xfc, 0x3, 0xfe, 0x0, 0x3, 0xfe,
    0x3, 0xff, 0x0, 0x1, 0xff, 0x81, 0xff, 0x0,
    0x0, 0x7f, 0xc1, 0xff, 0x80, 0x0, 0x3f, 0xf0,
    0xff, 0xc0, 0x0, 0x1f, 0xf8, 0x7f, 0xe0, 0x0,
    0xf, 0xfc, 0x7f, 0xf0, 0x0, 0x7, 0xff, 0x3f,
    0xf8, 0x0, 0x3, 0xff, 0x9f, 0xf8, 0x0, 0x0,
    0xff, 0xcf, 0xfc, 0x0, 0x0, 0x7f, 0xef, 0xfe,
    0x0, 0x0, 0x3f, 0xf7, 0xff, 0x0, 0x0, 0x1f,
    0xff, 0xff, 0x80, 0x0, 0xf, 0xff, 0xff, 0xc0,
    0x0, 0x7, 0xff, 0xff, 0xe0, 0x0, 0x3, 0xff,
    0xff, 0xf0, 0x0, 0x1, 0xff, 0xff, 0xf8, 0x0,
    0x0, 0xff, 0xff, 0xfc, 0x0, 0x0, 0x7f, 0xff,
    0xfe, 0x0, 0x0, 0x3f, 0xff, 0xff, 0x0, 0x0,
    0x1f, 0xff, 0xff, 0x80, 0x0, 0xf, 0xff, 0xff,
    0xc0, 0x0, 0x7, 0xff, 0xff, 0xe0, 0x0, 0x3,
    0xff, 0xff, 0xf0, 0x0, 0x1, 0xff, 0xff, 0xf8,
    0x0, 0x0, 0xff, 0xcf, 0xfc, 0x0, 0x0, 0x7f,
    0xe7, 0xfe, 0x0, 0x0, 0x3f, 0xf3, 0xff, 0x80,
    0x0, 0x3f, 0xf9, 0xff, 0xc0, 0x0, 0x1f, 0xfc,
    0x7f, 0xe0, 0x0, 0xf, 0xfc, 0x3f, 0xf0, 0x0,
    0x7, 0xfe, 0x1f, 0xf8, 0x0, 0x3, 0xff, 0x7,
    0xfc, 0x0, 0x1, 0xff, 0x3, 0xff, 0x0, 0x1,
    0xff, 0x80, 0xff, 0x80, 0x0, 0xff, 0x80, 0x7f,
    0xc0, 0x0, 0x7f, 0xc0, 0x1f, 0xf0, 0x0, 0x7f,
    0xc0, 0x7, 0xf8, 0x0, 0x3f, 0xc0, 0x3, 0xfc,
    0x0, 0x1f, 0xe0, 0x0, 0xff, 0x0, 0x1f, 0xe0,
    0x0, 0x3f, 0x80, 0xf, 0xe0, 0x0, 0xf, 0xe0,
    0xf, 0xc0, 0x0, 0x1, 0xf8, 0xf, 0xc0, 0x0,
    0x0, 0x3e, 0xf, 0x80, 0x0, 0x0, 0x3, 0xfe,
    0x0, 0x0,

    /* U+0031 "1" */
    0x0, 0x0, 0x40, 0x0, 0x0, 0x40, 0x0, 0x0,
    0xc0, 0x0, 0x0, 0xc0, 0x0, 0x1, 0xc0, 0x0,
    0x3, 0xc0, 0x0, 0x7, 0xc0, 0x0, 0xf, 0xc0,
    0x0, 0x1f, 0xc0, 0x0, 0x7f, 0xc0, 0x1, 0xff,
    0xc0, 0x7f, 0xff, 0xc0, 0xff, 0xff, 0xc0, 0x7,
    0xff, 0xc0, 0x3, 0xff, 0xc0, 0x1, 0xff, 0xc0,
    0x1, 0xff, 0xc0, 0x1, 0xff, 0xc0, 0x1, 0xff,
    0xc0, 0x1, 0xff, 0xc0, 0x1, 0xff, 0xc0, 0x1,
    0xff, 0xc0, 0x1, 0xff, 0xc0, 0x1, 0xff, 0xc0,
    0x1, 0xff, 0xc0, 0x1, 0xff, 0xc0, 0x1, 0xff,
    0xc0, 0x1, 0xff, 0xc0, 0x1, 0xff, 0xc0, 0x1,
    0xff, 0xc0, 0x1, 0xff, 0xc0, 0x1, 0xff, 0xc0,
    0x1, 0xff, 0xc0, 0x1, 0xff, 0xc0, 0x1, 0xff,
    0xc0, 0x1, 0xff, 0xc0, 0x1, 0xff, 0xc0, 0x1,
    0xff, 0xc0, 0x1, 0xff, 0xc0, 0x1, 0xff, 0xc0,
    0x1, 0xff, 0xc0, 0x1, 0xff, 0xc0, 0x1, 0xff,
    0xc0, 0x1, 0xff, 0xc0, 0x1, 0xff, 0xc0, 0x1,
    0xff, 0xc0, 0x1, 0xff, 0xc0, 0x1, 0xff, 0xc0,
    0x1, 0xff, 0xc0, 0x1, 0xff, 0xc0, 0x1, 0xff,
    0xc0, 0x3, 0xff, 0xe0, 0x7, 0xff, 0xf0, 0xf,
    0xff, 0xf8, 0x7f, 0xff, 0xff,

    /* U+0032 "2" */
    0x0, 0x1f, 0xfc, 0x0, 0x1, 0xfe, 0xf, 0xf0,
    0x0, 0x7e, 0x1, 0xfe, 0x0, 0x1f, 0x0, 0x3f,
    0xe0, 0x7, 0x80, 0x7, 0xfc, 0x3, 0xc0, 0x1,
    0xff, 0x80, 0xe0, 0x0, 0x3f, 0xe0, 0x38, 0x0,
    0xf, 0xfc, 0xc, 0x0, 0x3, 0xff, 0x3, 0x0,
    0x0, 0xff, 0xe0, 0x80, 0x0, 0x3f, 0xf8, 0x60,
    0x0, 0xf, 0xfe, 0x10, 0x0, 0x3, 0xff, 0x84,
    0x0, 0x0, 0xff, 0xe1, 0x0, 0x0, 0x7f, 0xf8,
    0x40, 0x0, 0x1f, 0xfe, 0x0, 0x0, 0x7, 0xff,
    0x0, 0x0, 0x1, 0xff, 0xc0, 0x0, 0x0, 0xff,
    0xe0, 0x0, 0x0, 0x3f, 0xf8, 0x0, 0x0, 0xf,
    0xfc, 0x0, 0x0, 0x7, 0xff, 0x0, 0x0, 0x1,
    0xff, 0x80, 0x0, 0x0, 0xff, 0xc0, 0x0, 0x0,
    0x3f, 0xf0, 0x0, 0x0, 0x1f, 0xf8, 0x0, 0x0,
    0x7, 0xfc, 0x0, 0x0, 0x3, 0xfe, 0x0, 0x0,
    0x0, 0xff, 0x0, 0x0, 0x0, 0x7f, 0x80, 0x0,
    0x0, 0x1f, 0xc0, 0x0, 0x0, 0xf, 0xe0, 0x0,
    0x0, 0x7, 0xf0, 0x0, 0x0, 0x1, 0xf8, 0x0,
    0x0, 0x0, 0xfc, 0x0, 0x0, 0x0, 0x3e, 0x0,
    0x0, 0x0, 0x1f, 0x0, 0x0, 0x0, 0xf, 0x80,
    0x0, 0x0, 0x3, 0xc0, 0x0, 0x4, 0x1, 0xe0,
    0x0, 0x2, 0x0, 0xf0, 0x0, 0x0, 0x80, 0x30,
    0x0, 0x0, 0x20, 0x18, 0x0, 0x0, 0x8, 0xc,
    0x0, 0x0, 0x6, 0x2, 0x0, 0x0, 0x3f, 0x81,
    0xff, 0xff, 0xff, 0xc0, 0xff, 0xff, 0xff, 0xf0,
    0x3f, 0xff, 0xff, 0xfc, 0x1f, 0xff, 0xff, 0xff,
    0xf, 0xff, 0xff, 0xff, 0xc3, 0xff, 0xff, 0xff,
    0xf1, 0xff, 0xff, 0xff, 0xf8, 0x7f, 0xff, 0xff,
    0xfe, 0x3f, 0xff, 0xff, 0xff, 0x80,

    /* U+0033 "3" */
    0x0, 0x7f, 0xf0, 0x0, 0xf, 0xe0, 0x7f, 0x0,
    0x7, 0xe0, 0x1f, 0xe0, 0x3, 0xc0, 0xf, 0xfc,
    0x1, 0xc0, 0x3, 0xff, 0x0, 0xe0, 0x1, 0xff,
    0x80, 0xe0, 0x0, 0xff, 0xe0, 0x60, 0x0, 0x7f,
    0xf0, 0x30, 0x0, 0x3f, 0xf8, 0x10, 0x0, 0x1f,
    0xfc, 0x8, 0x0, 0xf, 0xfe, 0x4, 0x0, 0x7,
    0xfe, 0x4, 0x0, 0x7, 0xff, 0x2, 0x0, 0x3,
    0xff, 0x1, 0x0, 0x1, 0xff, 0x0, 0x80, 0x1,
    0xff, 0x0, 0x0, 0x0, 0xff, 0x0, 0x0, 0x0,
    0xff, 0x0, 0x0, 0x0, 0xfe, 0x0, 0x0, 0x0,
    0xfc, 0x0, 0x0, 0x0, 0x7f, 0xc0, 0x0, 0x0,
    0x7f, 0xfc, 0x0, 0x0, 0x7f, 0xff, 0x80, 0x0,
    0xff, 0xff, 0xe0, 0x0, 0xc0, 0x7f, 0xf8, 0x0,
    0x0, 0xf, 0xfe, 0x0, 0x0, 0x3, 0xff, 0x0,
    0x0, 0x0, 0xff, 0xc0, 0x0, 0x0, 0x7f, 0xe0,
    0x0, 0x0, 0x1f, 0xf8, 0x0, 0x0, 0xf, 0xfc,
    0x0, 0x0, 0x7, 0xfe, 0x0, 0x0, 0x1, 0xff,
    0x80, 0x0, 0x0, 0xff, 0xc0, 0x0, 0x0, 0x7f,
    0xe0, 0x0, 0x0, 0x3f, 0xf0, 0x0, 0x0, 0x1f,
    0xf8, 0x0, 0x0, 0xf, 0xfc, 0x0, 0x0, 0x7,
    0xff, 0x0, 0x0, 0x3, 0xff, 0x80, 0x0, 0x1,
    0xff, 0xc0, 0x0, 0x0, 0xff, 0xa0, 0x0, 0x0,
    0x7f, 0xd8, 0x0, 0x0, 0x7f, 0xe4, 0x0, 0x0,
    0x3f, 0xe2, 0x0, 0x0, 0x1f, 0xf1, 0x80, 0x0,
    0x1f, 0xf0, 0xc0, 0x0, 0xf, 0xf8, 0x70, 0x0,
    0xf, 0xf8, 0x3c, 0x0, 0x7, 0xf8, 0x1e, 0x0,
    0x7, 0xf8, 0x7, 0x80, 0x7, 0xf8, 0x3, 0xf0,
    0x7, 0xf0, 0x1, 0xfe, 0xf, 0xe0, 0x0, 0x7,
    0xff, 0x0, 0x0,

    /* U+0034 "4" */
    0x0, 0x0, 0x0, 0x2, 0x0, 0x0, 0x0, 0x0,
    0x4, 0x0, 0x0, 0x0, 0x0, 0x18, 0x0, 0x0,
    0x0, 0x0, 0x70, 0x0, 0x0, 0x0, 0x1, 0xe0,
    0x0, 0x0, 0x0, 0x3, 0xc0, 0x0, 0x0, 0x0,
    0xf, 0x80, 0x0, 0x0, 0x0, 0x3f, 0x0, 0x0,
    0x0, 0x0, 0xfe, 0x0, 0x0, 0x0, 0x1, 0xfc,
    0x0, 0x0, 0x0, 0x7, 0xf8, 0x0, 0x0, 0x0,
    0x1f, 0xf0, 0x0, 0x0, 0x0, 0x3f, 0xe0, 0x0,
    0x0, 0x0, 0xff, 0xc0, 0x0, 0x0, 0x3, 0xff,
    0x80, 0x0, 0x0, 0xf, 0xff, 0x0, 0x0, 0x0,
    0x2f, 0xfe, 0x0, 0x0, 0x0, 0x9f, 0xfc, 0x0,
    0x0, 0x1, 0x3f, 0xf8, 0x0, 0x0, 0x4, 0x7f,
    0xf0, 0x0, 0x0, 0x10, 0xff, 0xe0, 0x0, 0x0,
    0x41, 0xff, 0xc0, 0x0, 0x0, 0x83, 0xff, 0x80,
    0x0, 0x2, 0x7, 0xff, 0x0, 0x0, 0x8, 0xf,
    0xfe, 0x0, 0x0, 0x10, 0x1f, 0xfc, 0x0, 0x0,
    0x40, 0x3f, 0xf8, 0x0, 0x1, 0x0, 0x7f, 0xf0,
    0x0, 0x4, 0x0, 0xff, 0xe0, 0x0, 0x8, 0x1,
    0xff, 0xc0, 0x0, 0x20, 0x3, 0xff, 0x80, 0x0,
    0x80, 0x7, 0xff, 0x0, 0x1, 0x0, 0xf, 0xfe,
    0x0, 0x4, 0x0, 0x1f, 0xfc, 0x0, 0xf, 0xff,
    0xff, 0xff, 0xf8, 0x3f, 0xff, 0xff, 0xff, 0xf0,
    0xff, 0xff, 0xff, 0xff, 0xe1, 0xff, 0xff, 0xff,
    0xff, 0xc7, 0xff, 0xff, 0xff, 0xff, 0x9f, 0xff,
    0xff, 0xff, 0xff, 0x7f, 0xff, 0xff, 0xff, 0xfe,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xf8, 0x0, 0x0, 0x7f, 0xf0, 0x0, 0x0,
    0x0, 0xff, 0xe0, 0x0, 0x0, 0x1, 0xff, 0xc0,
    0x0, 0x0, 0x3, 0xff, 0x80, 0x0, 0x0, 0x7,
    0xff, 0x0, 0x0, 0x0, 0xf, 0xfe, 0x0, 0x0,
    0x0, 0x1f, 0xfc, 0x0, 0x0, 0x0, 0x3f, 0xf8,
    0x0, 0x0, 0x0, 0xff, 0xf8, 0x0, 0x0, 0x3,
    0xff, 0xf8, 0x0, 0x0, 0xf, 0xff, 0xf8, 0x0,
    0x0, 0xff, 0xff, 0xfe, 0x0,

    /* U+0035 "5" */
    0x4, 0x0, 0x0, 0x1, 0x1, 0x80, 0x0, 0x0,
    0x80, 0x78, 0x0, 0x0, 0xc0, 0x3f, 0x80, 0x0,
    0xf0, 0xf, 0xfe, 0x1, 0xf8, 0x3, 0xff, 0xff,
    0xfc, 0x0, 0xff, 0xff, 0xfe, 0x0, 0x3f, 0xff,
    0xff, 0x0, 0xf, 0xff, 0xff, 0x0, 0x3, 0xff,
    0xff, 0x80, 0x0, 0xff, 0xff, 0x80, 0x0, 0x7f,
    0xff, 0x80, 0x0, 0x11, 0xff, 0x0, 0x0, 0x4,
    0x0, 0x0, 0x0, 0x1, 0x0, 0x0, 0x0, 0x0,
    0x40, 0x0, 0x0, 0x0, 0x10, 0x0, 0x0, 0x0,
    0x4, 0x0, 0x0, 0x0, 0x2, 0x0, 0x0, 0x0,
    0x0, 0x80, 0x0, 0x0, 0x0, 0x20, 0x1f, 0xf8,
    0x0, 0x9, 0xf8, 0x7f, 0xc0, 0x3, 0xe0, 0x7,
    0xfc, 0x0, 0xf0, 0x0, 0x7f, 0xc0, 0x30, 0x0,
    0x1f, 0xf8, 0xc, 0x0, 0x3, 0xff, 0x2, 0x0,
    0x0, 0x7f, 0xe1, 0x0, 0x0, 0x1f, 0xf8, 0x0,
    0x0, 0x3, 0xff, 0x0, 0x0, 0x0, 0xff, 0xc0,
    0x0, 0x0, 0x3f, 0xf8, 0x0, 0x0, 0xf, 0xfe,
    0x0, 0x0, 0x1, 0xff, 0x80, 0x0, 0x0, 0x7f,
    0xf0, 0x0, 0x0, 0x1f, 0xfc, 0x0, 0x0, 0x7,
    0xff, 0x0, 0x0, 0x1, 0xff, 0xc0, 0x0, 0x0,
    0x7f, 0xf8, 0x0, 0x0, 0x1f, 0xfe, 0x0, 0x0,
    0x7, 0xff, 0x80, 0x0, 0x1, 0xff, 0xe0, 0x0,
    0x0, 0x7f, 0xf8, 0x0, 0x0, 0x3f, 0xf9, 0x0,
    0x0, 0xf, 0xfe, 0x40, 0x0, 0x3, 0xff, 0x90,
    0x0, 0x0, 0xff, 0xc6, 0x0, 0x0, 0x7f, 0xe1,
    0x80, 0x0, 0x1f, 0xf8, 0x70, 0x0, 0xf, 0xfc,
    0x1e, 0x0, 0x3, 0xfe, 0x3, 0x80, 0x1, 0xff,
    0x0, 0xf0, 0x0, 0xff, 0x80, 0x3f, 0x0, 0x7f,
    0x80, 0xf, 0xf0, 0x7f, 0x80, 0x0, 0xf, 0xfe,
    0x0, 0x0,

    /* U+0036 "6" */
    0x0, 0x0, 0x7f, 0xf0, 0x0, 0x0, 0x1f, 0xc0,
    0xff, 0x0, 0x1, 0xfe, 0x0, 0xfc, 0x0, 0xf,
    0xe0, 0x1, 0xf0, 0x0, 0x7f, 0x0, 0x3, 0xc0,
    0x3, 0xfc, 0x0, 0x7, 0x80, 0x1f, 0xe0, 0x0,
    0xe, 0x0, 0xff, 0x0, 0x0, 0x18, 0x7, 0xfc,
    0x0, 0x0, 0x60, 0x1f, 0xe0, 0x0, 0x0, 0x80,
    0xff, 0x80, 0x0, 0x2, 0x7, 0xfe, 0x0, 0x0,
    0x8, 0x1f, 0xf8, 0x0, 0x0, 0x20, 0x7f, 0xc0,
    0x0, 0x0, 0x43, 0xff, 0x0, 0x0, 0x1, 0xf,
    0xfc, 0x0, 0x0, 0x4, 0x3f, 0xf0, 0x0, 0x0,
    0x1, 0xff, 0x80, 0x0, 0x0, 0x7, 0xfe, 0x0,
    0x0, 0x0, 0x1f, 0xf8, 0x0, 0x0, 0x0, 0x7f,
    0xe0, 0x1f, 0xf0, 0x3, 0xff, 0x83, 0xff, 0xf0,
    0xf, 0xfe, 0x3f, 0xff, 0xf0, 0x3f, 0xf9, 0xc1,
    0xff, 0xe0, 0xff, 0xe8, 0x1, 0xff, 0xc3, 0xff,
    0xc0, 0x3, 0xff, 0x8f, 0xfe, 0x0, 0x7, 0xfe,
    0x3f, 0xf8, 0x0, 0x1f, 0xfc, 0xff, 0xe0, 0x0,
    0x3f, 0xf3, 0xff, 0x80, 0x0, 0xff, 0xef, 0xfe,
    0x0, 0x1, 0xff, 0xbf, 0xf8, 0x0, 0x7, 0xfe,
    0xff, 0xe0, 0x0, 0x1f, 0xff, 0xff, 0x80, 0x0,
    0x3f, 0xff, 0xfe, 0x0, 0x0, 0xff, 0xdf, 0xf8,
    0x0, 0x3, 0xff, 0x7f, 0xe0, 0x0, 0xf, 0xfd,
    0xff, 0x80, 0x0, 0x3f, 0xf7, 0xfe, 0x0, 0x0,
    0xff, 0xcf, 0xfc, 0x0, 0x3, 0xff, 0x3f, 0xf0,
    0x0, 0xf, 0xfc, 0xff, 0xc0, 0x0, 0x3f, 0xf1,
    0xff, 0x0, 0x0, 0xff, 0x87, 0xfc, 0x0, 0x3,
    0xfe, 0xf, 0xf0, 0x0, 0x1f, 0xf8, 0x3f, 0xe0,
    0x0, 0x7f, 0xc0, 0x7f, 0x80, 0x1, 0xff, 0x0,
    0xfe, 0x0, 0xf, 0xf8, 0x3, 0xfc, 0x0, 0x3f,
    0xc0, 0x7, 0xf0, 0x1, 0xff, 0x0, 0xf, 0xe0,
    0x7, 0xf8, 0x0, 0x1f, 0x80, 0x3f, 0xc0, 0x0,
    0x1f, 0x1, 0xfc, 0x0, 0x0, 0x1f, 0xf, 0xc0,
    0x0, 0x0, 0xf, 0xf8, 0x0, 0x0,

    /* U+0037 "7" */
    0x3f, 0xff, 0xff, 0xff, 0xe7, 0xff, 0xff, 0xff,
    0xf8, 0xff, 0xff, 0xff, 0xfe, 0x3f, 0xff, 0xff,
    0xff, 0x87, 0xff, 0xff, 0xff, 0xf0, 0xff, 0xff,
    0xff, 0xfc, 0x1f, 0xff, 0xff, 0xff, 0x3, 0xff,
    0xff, 0xff, 0xe0, 0x7f, 0xff, 0xff, 0xf8, 0xc,
    0x0, 0x0, 0x3, 0x3, 0x0, 0x0, 0x0, 0xc0,
    0x40, 0x0, 0x0, 0x38, 0x8, 0x0, 0x0, 0xe,
    0x1, 0x0, 0x0, 0x3, 0xc0, 0x20, 0x0, 0x0,
    0xf0, 0x0, 0x0, 0x0, 0x3e, 0x0, 0x0, 0x0,
    0x7, 0xc0, 0x0, 0x0, 0x1, 0xf0, 0x0, 0x0,
    0x0, 0x7e, 0x0, 0x0, 0x0, 0xf, 0x80, 0x0,
    0x0, 0x3, 0xf0, 0x0, 0x0, 0x0, 0xfe, 0x0,
    0x0, 0x0, 0x1f, 0x80, 0x0, 0x0, 0x7, 0xf0,
    0x0, 0x0, 0x0, 0xfe, 0x0, 0x0, 0x0, 0x3f,
    0xc0, 0x0, 0x0, 0x7, 0xf0, 0x0, 0x0, 0x1,
    0xfe, 0x0, 0x0, 0x0, 0x3f, 0xc0, 0x0, 0x0,
    0xf, 0xf8, 0x0, 0x0, 0x1, 0xfe, 0x0, 0x0,
    0x0, 0x7f, 0xc0, 0x0, 0x0, 0xf, 0xf8, 0x0,
    0x0, 0x1, 0xff, 0x0, 0x0, 0x0, 0x7f, 0xe0,
    0x0, 0x0, 0xf, 0xf8, 0x0, 0x0, 0x1, 0xff,
    0x0, 0x0, 0x0, 0x7f, 0xe0, 0x0, 0x0, 0xf,
    0xfc, 0x0, 0x0, 0x1, 0xff, 0x80, 0x0, 0x0,
    0x7f, 0xf0, 0x0, 0x0, 0xf, 0xfe, 0x0, 0x0,
    0x1, 0xff, 0xc0, 0x0, 0x0, 0x3f, 0xf0, 0x0,
    0x0, 0x7, 0xfe, 0x0, 0x0, 0x0, 0xff, 0xc0,
    0x0, 0x0, 0x3f, 0xf8, 0x0, 0x0, 0x7, 0xff,
    0x0, 0x0, 0x0, 0xff, 0xe0, 0x0, 0x0, 0x1f,
    0xfc, 0x0, 0x0, 0x3, 0xff, 0x80, 0x0, 0x0,
    0x7f, 0xf0, 0x0, 0x0, 0xf, 0xfe, 0x0, 0x0,

    /* U+0038 "8" */
    0x0, 0x3, 0xff, 0x80, 0x0, 0x0, 0xfe, 0x1f,
    0xe0, 0x0, 0xf, 0xf0, 0x1f, 0xe0, 0x0, 0xff,
    0x80, 0x3f, 0xe0, 0x7, 0xfe, 0x0, 0xff, 0xc0,
    0x3f, 0xf8, 0x3, 0xff, 0x80, 0xff, 0xc0, 0x7,
    0xfe, 0x7, 0xff, 0x0, 0x1f, 0xfc, 0x1f, 0xfc,
    0x0, 0x7f, 0xf0, 0x7f, 0xf0, 0x1, 0xff, 0xc1,
    0xff, 0xc0, 0x7, 0xff, 0x7, 0xff, 0x0, 0x1f,
    0xfc, 0x1f, 0xfc, 0x0, 0x7f, 0xf0, 0x3f, 0xf0,
    0x1, 0xff, 0x80, 0x7f, 0xe0, 0xf, 0xfc, 0x1,
    0xff, 0x80, 0x3f, 0xe0, 0x1, 0xff, 0x1, 0xff,
    0x0, 0x3, 0xfc, 0x7, 0xf8, 0x0, 0x1, 0xfc,
    0x7f, 0x0, 0x0, 0x0, 0x3f, 0x80, 0x0, 0x0,
    0xf, 0x87, 0xe0, 0x0, 0x1, 0xf8, 0x7, 0xe0,
    0x0, 0x1f, 0xc0, 0xf, 0xe0, 0x0, 0xff, 0x0,
    0x3f, 0xc0, 0x7, 0xf8, 0x0, 0x7f, 0x80, 0x3f,
    0xe0, 0x1, 0xff, 0x1, 0xff, 0x0, 0x3, 0xfe,
    0x7, 0xfc, 0x0, 0xf, 0xfc, 0x3f, 0xf0, 0x0,
    0x3f, 0xf1, 0xff, 0xc0, 0x0, 0xff, 0xe7, 0xfe,
    0x0, 0x1, 0xff, 0x9f, 0xf8, 0x0, 0x7, 0xfe,
    0xff, 0xe0, 0x0, 0x1f, 0xfb, 0xff, 0x80, 0x0,
    0x7f, 0xff, 0xfe, 0x0, 0x1, 0xff, 0xff, 0xf8,
    0x0, 0x7, 0xff, 0xff, 0xe0, 0x0, 0x1f, 0xff,
    0xff, 0x80, 0x0, 0x7f, 0xff, 0xfe, 0x0, 0x1,
    0xff, 0xff, 0xf8, 0x0, 0x7, 0xff, 0xff, 0xe0,
    0x0, 0x1f, 0xff, 0xff, 0x80, 0x0, 0x7f, 0xf7,
    0xfe, 0x0, 0x1, 0xff, 0x9f, 0xfc, 0x0, 0xf,
    0xfe, 0x7f, 0xf0, 0x0, 0x3f, 0xf8, 0xff, 0xc0,
    0x0, 0xff, 0xc3, 0xff, 0x0, 0x3, 0xff, 0x7,
    0xfe, 0x0, 0x1f, 0xf8, 0xf, 0xf8, 0x0, 0x7f,
    0xc0, 0x1f, 0xe0, 0x1, 0xfe, 0x0, 0x3f, 0xc0,
    0xf, 0xf0, 0x0, 0x7f, 0x80, 0x7f, 0x80, 0x0,
    0x7f, 0x1, 0xf8, 0x0, 0x0, 0x7e, 0x1f, 0x80,
    0x0, 0x0, 0x3f, 0xf0, 0x0, 0x0,

    /* U+0039 "9" */
    0x0, 0x7, 0xfe, 0x0, 0x0, 0x0, 0xfc, 0x3f,
    0x0, 0x0, 0xf, 0xc0, 0x3f, 0x0, 0x0, 0x7e,
    0x0, 0xfe, 0x0, 0x7, 0xf8, 0x1, 0xfc, 0x0,
    0x3f, 0xc0, 0x3, 0xf8, 0x0, 0xff, 0x0, 0xf,
    0xf0, 0x7, 0xf8, 0x0, 0x1f, 0xe0, 0x3f, 0xe0,
    0x0, 0x7f, 0xc0, 0xff, 0x80, 0x1, 0xff, 0x7,
    0xfe, 0x0, 0x3, 0xfe, 0x1f, 0xf0, 0x0, 0xf,
    0xf8, 0x7f, 0xc0, 0x0, 0x3f, 0xf3, 0xff, 0x0,
    0x0, 0xff, 0xcf, 0xfc, 0x0, 0x3, 0xff, 0x3f,
    0xf0, 0x0, 0xf, 0xfe, 0xff, 0xc0, 0x0, 0x1f,
    0xfb, 0xff, 0x0, 0x0, 0x7f, 0xef, 0xfc, 0x0,
    0x1, 0xff, 0xbf, 0xf0, 0x0, 0x7, 0xfe, 0xff,
    0xc0, 0x0, 0x1f, 0xff, 0xff, 0x0, 0x0, 0x7f,
    0xff, 0xfe, 0x0, 0x1, 0xff, 0xdf, 0xf8, 0x0,
    0x7, 0xff, 0x7f, 0xe0, 0x0, 0x1f, 0xfd, 0xff,
    0xc0, 0x0, 0x7f, 0xf3, 0xff, 0x0, 0x1, 0xff,
    0xcf, 0xfc, 0x0, 0x7, 0xff, 0x1f, 0xf8, 0x0,
    0x1f, 0xfc, 0x7f, 0xf0, 0x0, 0xff, 0xf0, 0xff,
    0xe0, 0x5, 0xff, 0xc1, 0xff, 0xe0, 0xe7, 0xff,
    0x3, 0xff, 0xff, 0x1f, 0xfc, 0x3, 0xff, 0xf0,
    0x7f, 0xf0, 0x1, 0xfe, 0x1, 0xff, 0x80, 0x0,
    0x0, 0x7, 0xfe, 0x0, 0x0, 0x0, 0x1f, 0xf8,
    0x0, 0x0, 0x0, 0x7f, 0xe0, 0x0, 0x0, 0x3,
    0xff, 0x8, 0x0, 0x0, 0xf, 0xfc, 0x20, 0x0,
    0x0, 0x3f, 0xf0, 0x40, 0x0, 0x0, 0xff, 0x81,
    0x0, 0x0, 0x7, 0xfe, 0x4, 0x0, 0x0, 0x1f,
    0xf8, 0x10, 0x0, 0x0, 0x7f, 0xc0, 0x60, 0x0,
    0x3, 0xfe, 0x1, 0x80, 0x0, 0xf, 0xf8, 0x7,
    0x0, 0x0, 0x3f, 0xc0, 0x1c, 0x0, 0x1, 0xfe,
    0x0, 0x38, 0x0, 0xf, 0xf0, 0x0, 0xf0, 0x0,
    0x3f, 0x80, 0x3, 0xe0, 0x1, 0xfc, 0x0, 0xf,
    0xc0, 0xf, 0xe0, 0x0, 0x3f, 0xc0, 0xfe, 0x0,
    0x0, 0x3, 0xff, 0xc0, 0x0, 0x0,

    /* U+003A ":" */
    0x0, 0x1, 0xf8, 0x3f, 0xc7, 0xfe, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xf7, 0xfe, 0x7f,
    0xe3, 0xfc, 0xf, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xf,
    0x3, 0xfc, 0x7f, 0xef, 0xfe, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0x7f, 0xe7, 0xfe, 0x3f, 0xc0,
    0xf0
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 736, .box_w = 41, .box_h = 55, .ofs_x = 2, .ofs_y = -1},
    {.bitmap_index = 282, .adv_w = 365, .box_w = 24, .box_h = 55, .ofs_x = -1, .ofs_y = 0},
    {.bitmap_index = 447, .adv_w = 564, .box_w = 34, .box_h = 54, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 677, .adv_w = 598, .box_w = 33, .box_h = 55, .ofs_x = 2, .ofs_y = -1},
    {.bitmap_index = 904, .adv_w = 673, .box_w = 39, .box_h = 55, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1173, .adv_w = 613, .box_w = 34, .box_h = 55, .ofs_x = 2, .ofs_y = -1},
    {.bitmap_index = 1407, .adv_w = 697, .box_w = 38, .box_h = 55, .ofs_x = 3, .ofs_y = -1},
    {.bitmap_index = 1669, .adv_w = 566, .box_w = 35, .box_h = 53, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 1901, .adv_w = 694, .box_w = 38, .box_h = 55, .ofs_x = 2, .ofs_y = -1},
    {.bitmap_index = 2163, .adv_w = 697, .box_w = 38, .box_h = 55, .ofs_x = 2, .ofs_y = -1},
    {.bitmap_index = 2425, .adv_w = 258, .box_w = 12, .box_h = 38, .ofs_x = 2, .ofs_y = -1}
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

/*-----------------
 *    KERNING
 *----------------*/


/*Map glyph_ids to kern left classes*/
static const uint8_t kern_left_class_mapping[] =
{
    0, 1, 2, 3, 4, 5, 6, 7,
    8, 9, 10, 0
};

/*Map glyph_ids to kern right classes*/
static const uint8_t kern_right_class_mapping[] =
{
    0, 1, 0, 2, 3, 4, 5, 6,
    7, 8, 9, 0
};

/*Kern values between classes*/
static const int8_t kern_class_values[] =
{
    0, -20, -6, 0, 0, 0, -11, 0,
    -6, -17, 0, -6, -22, -7, -22, -22,
    -22, -22, 0, 0, 0, -11, 0, -11,
    0, -11, -11, -4, -22, 0, 0, -11,
    0, -49, -21, -20, 0, -18, 0, 0,
    -8, 0, 0, 0, 0, 0, -20, 0,
    0, 0, 0, 0, 0, -27, 0, 0,
    0, 0, 0, 0, -29, 0, 0, -38,
    0, 0, -115, -16, -43, 0, -38, -26,
    0, -29, 0, 0, 0, 0, -43, 0,
    -16, 0, -24, -4, -8, 0, 0, -18,
    0, -11
};


/*Collect the kern class' data in one place*/
static const lv_font_fmt_txt_kern_classes_t kern_classes =
{
    .class_pair_values   = kern_class_values,
    .left_class_mapping  = kern_left_class_mapping,
    .right_class_mapping = kern_right_class_mapping,
    .left_class_cnt      = 10,
    .right_class_cnt     = 9,
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
const lv_font_t gloock_time = {
#else
lv_font_t gloock_time = {
#endif
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,    /*Function pointer to get glyph's data*/
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,    /*Function pointer to get glyph's bitmap*/
    .line_height = 56,          /*The maximum line height required by the font*/
    .base_line = 1,             /*Baseline measured from the bottom of the line*/
#if !(LVGL_VERSION_MAJOR == 6 && LVGL_VERSION_MINOR == 0)
    .subpx = LV_FONT_SUBPX_NONE,
#endif
#if LV_VERSION_CHECK(7, 4, 0) || LVGL_VERSION_MAJOR >= 8
    .underline_position = -7,
    .underline_thickness = 4,
#endif
    .dsc = &font_dsc,          /*The custom font data. Will be accessed by `get_glyph_bitmap/dsc` */
#if LV_VERSION_CHECK(8, 2, 0) || LVGL_VERSION_MAJOR >= 9
    .fallback = &lv_font_montserrat_28,
#endif
    .user_data = NULL,
};



#endif /*#if GLOOCK_TIME*/

