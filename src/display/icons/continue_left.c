
#if defined(LV_LVGL_H_INCLUDE_SIMPLE)
#include "lvgl.h"
#elif defined(LV_BUILD_TEST)
#include "../lvgl.h"
#else
#include "lvgl/lvgl.h"
#endif


#ifndef LV_ATTRIBUTE_MEM_ALIGN
#define LV_ATTRIBUTE_MEM_ALIGN
#endif

#ifndef LV_ATTRIBUTE_CONTINUE_LEFT
#define LV_ATTRIBUTE_CONTINUE_LEFT
#endif

static const
LV_ATTRIBUTE_MEM_ALIGN LV_ATTRIBUTE_LARGE_CONST LV_ATTRIBUTE_CONTINUE_LEFT
uint8_t continue_left_map[] = {

    0x09,0x09,0x09,0xff,0xff,0xff,0xff,0xff,

    0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xf0,
    0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xf0,
    0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xf0,
    0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xf0,
    0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xf0,
    0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xf0,
    0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xf0,
    0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xf0,
    0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xf0,
    0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xf0,
    0xff,0xff,0xff,0xff,0xff,0xcf,0xff,0xff,0xff,0xff,0xff,0xff,0xf0,
    0xff,0xff,0xff,0xff,0xff,0x07,0xff,0xff,0xff,0xff,0xff,0xff,0xf0,
    0xff,0xff,0xff,0xff,0xfe,0x07,0xff,0xff,0xff,0xff,0xff,0xff,0xf0,
    0xff,0xff,0xff,0xff,0xfc,0x0f,0xff,0xff,0xff,0xff,0xff,0xff,0xf0,
    0xff,0xff,0xff,0xff,0xf0,0x0f,0xff,0xff,0xff,0xff,0xff,0xff,0xf0,
    0xff,0xff,0xff,0xff,0xe0,0x0f,0xff,0xff,0xff,0xff,0xff,0xff,0xf0,
    0xff,0xff,0xff,0xff,0xc0,0x1f,0xff,0xff,0xff,0xff,0xff,0xff,0xf0,
    0xff,0xff,0xff,0xff,0x00,0x1f,0xff,0xff,0xff,0xff,0xff,0xff,0xf0,
    0xff,0xff,0xff,0xfe,0x00,0x3f,0xff,0xff,0xff,0xff,0xff,0xff,0xf0,
    0xff,0xff,0xff,0xfc,0x00,0x3f,0xff,0xff,0xff,0xff,0xff,0xff,0xf0,
    0xff,0xff,0xff,0xf8,0x00,0x7f,0xff,0xff,0xff,0xff,0xff,0xff,0xf0,
    0xff,0xff,0xff,0xe0,0x00,0x7f,0xff,0xff,0xff,0xff,0xff,0xff,0xf0,
    0xff,0xff,0xff,0xc0,0x00,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xf0,
    0xff,0xff,0xff,0x80,0x00,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xf0,
    0xff,0xff,0xfe,0x00,0x01,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xf0,
    0xff,0xff,0xfc,0x00,0x01,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xf0,
    0xff,0xff,0xf8,0x00,0x01,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xf0,
    0xff,0xff,0xf0,0x00,0x03,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xf0,
    0xff,0xff,0xc0,0x00,0x03,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xf0,
    0xff,0xff,0x80,0x00,0x01,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xf0,
    0xff,0xff,0x00,0x00,0x00,0x00,0x00,0xff,0xff,0xff,0xff,0xff,0xf0,
    0xff,0xfc,0x00,0x00,0x00,0x00,0x00,0x0f,0xff,0xff,0xff,0xff,0xf0,
    0xff,0xf8,0x00,0x00,0x00,0x00,0x00,0x03,0xff,0xff,0xff,0xff,0xf0,
    0xff,0xf0,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0xff,0xff,0xff,0xf0,
    0xff,0xe0,0x00,0x00,0x00,0x00,0x00,0x00,0x3f,0xff,0xff,0xff,0xf0,
    0xff,0xe0,0x00,0x00,0x00,0x00,0x00,0x00,0x1f,0xff,0xff,0xff,0xf0,
    0xff,0xf0,0x00,0x00,0x00,0x00,0x00,0x00,0x07,0xff,0xff,0xff,0xf0,
    0xff,0xf8,0x00,0x00,0x00,0x00,0x00,0x00,0x03,0xff,0xff,0xff,0xf0,
    0xff,0xfc,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0xff,0xff,0xff,0xf0,
    0xff,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0xff,0xff,0xf0,
    0xff,0xff,0x80,0x00,0x03,0xff,0xfc,0x00,0x00,0x7f,0xff,0xff,0xf0,
    0xff,0xff,0xc0,0x00,0x03,0xff,0xff,0x80,0x00,0x3f,0xff,0xff,0xf0,
    0xff,0xff,0xf0,0x00,0x03,0xff,0xff,0xe0,0x00,0x3f,0xff,0xff,0xf0,
    0xff,0xff,0xf8,0x00,0x01,0xff,0xff,0xf8,0x00,0x1f,0xff,0xff,0xf0,
    0xff,0xff,0xfc,0x00,0x01,0xff,0xff,0xfc,0x00,0x0f,0xff,0xff,0xf0,
    0xff,0xff,0xff,0x00,0x00,0xff,0xff,0xff,0x00,0x0f,0xff,0xff,0xf0,
    0xff,0xff,0xff,0x80,0x00,0xff,0xff,0xff,0x80,0x07,0xff,0xff,0xf0,
    0xff,0xff,0xff,0xc0,0x00,0xff,0xff,0xff,0x80,0x07,0xff,0xff,0xf0,
    0xff,0xff,0xff,0xe0,0x00,0x7f,0xff,0xff,0xc0,0x03,0xff,0xff,0xf0,
    0xff,0xff,0xff,0xf8,0x00,0x7f,0xff,0xff,0xe0,0x03,0xff,0xff,0xf0,
    0xff,0xff,0xff,0xfc,0x00,0x3f,0xff,0xff,0xe0,0x03,0xff,0xff,0xf0,
    0xff,0xff,0xff,0xfe,0x00,0x3f,0xff,0xff,0xf0,0x01,0xff,0xff,0xf0,
    0xff,0xff,0xff,0xff,0x80,0x1f,0xff,0xff,0xf0,0x01,0xff,0xff,0xf0,
    0xff,0xff,0xff,0xff,0xc0,0x1f,0xff,0xff,0xf8,0x01,0xff,0xff,0xf0,
    0xff,0xff,0xff,0xff,0xe0,0x0f,0xff,0xff,0xf8,0x00,0xff,0xff,0xf0,
    0xff,0xff,0xff,0xff,0xf8,0x0f,0xff,0xff,0xf8,0x00,0xff,0xff,0xf0,
    0xff,0xff,0xff,0xff,0xfc,0x07,0xff,0xff,0xfc,0x00,0xff,0xff,0xf0,
    0xff,0xff,0xff,0xff,0xfe,0x07,0xff,0xff,0xfc,0x00,0xff,0xff,0xf0,
    0xff,0xff,0xff,0xff,0xff,0x07,0xff,0xff,0xfc,0x00,0xff,0xff,0xf0,
    0xff,0xff,0xff,0xff,0xff,0xcf,0xff,0xff,0xfc,0x00,0xff,0xff,0xf0,
    0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xfc,0x00,0xff,0xff,0xf0,
    0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xfc,0x00,0xff,0xff,0xf0,
    0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xfc,0x00,0xff,0xff,0xf0,
    0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xfc,0x00,0xff,0xff,0xf0,
    0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xfc,0x00,0xff,0xff,0xf0,
    0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xfc,0x00,0xff,0xff,0xf0,
    0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xfc,0x00,0xff,0xff,0xf0,
    0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xfc,0x00,0xff,0xff,0xf0,
    0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xfc,0x00,0xff,0xff,0xf0,
    0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xfc,0x00,0xff,0xff,0xf0,
    0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xfc,0x00,0xff,0xff,0xf0,
    0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xfc,0x00,0xff,0xff,0xf0,
    0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xfc,0x00,0xff,0xff,0xf0,
    0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xfc,0x00,0xff,0xff,0xf0,
    0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xfc,0x00,0xff,0xff,0xf0,
    0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xfc,0x00,0xff,0xff,0xf0,
    0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xfc,0x00,0xff,0xff,0xf0,
    0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xfc,0x00,0xff,0xff,0xf0,
    0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xfc,0x00,0xff,0xff,0xf0,
    0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xfc,0x00,0xff,0xff,0xf0,
    0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xfc,0x00,0xff,0xff,0xf0,
    0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xfc,0x00,0xff,0xff,0xf0,
    0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xfc,0x00,0xff,0xff,0xf0,
    0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xfc,0x00,0xff,0xff,0xf0,
    0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xfc,0x00,0xff,0xff,0xf0,
    0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xfc,0x00,0xff,0xff,0xf0,
    0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xfc,0x00,0xff,0xff,0xf0,
    0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xfc,0x00,0xff,0xff,0xf0,
    0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xfc,0x00,0xff,0xff,0xf0,
    0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xfe,0x01,0xff,0xff,0xf0,
    0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xf0,
    0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xf0,
    0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xf0,
    0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xf0,
    0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xf0,
    0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xf0,
    0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xf0,
    0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xf0,
    0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xf0,
    0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xf0,

};

const lv_image_dsc_t cont_left = {
  .header.magic = LV_IMAGE_HEADER_MAGIC,
  .header.cf = LV_COLOR_FORMAT_I1,
  .header.flags = 0,
  .header.w = 100,
  .header.h = 100,
  .header.stride = 13,
  .data_size = sizeof(continue_left_map),
  .data = continue_left_map,
};

