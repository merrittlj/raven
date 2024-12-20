
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

#ifndef LV_ATTRIBUTE_TURN_SHARP_LEFT
#define LV_ATTRIBUTE_TURN_SHARP_LEFT
#endif

static const
LV_ATTRIBUTE_MEM_ALIGN LV_ATTRIBUTE_LARGE_CONST LV_ATTRIBUTE_TURN_SHARP_LEFT
uint8_t turn_sharp_left_map[] = {

    0x02,0x00,0x00,0x00,0x6e,0x01,0x00,0x00,0x1c,0x05,0x00,0x00,0x4c,0x09,0x09,0x09,
    0xff,0x01,0x00,0x18,0xf0,0x11,0x00,0x0f,0x0d,0x00,0x9f,0x27,0xe0,0x01,0xb6,0x00,
    0x35,0x00,0x00,0x7f,0xc3,0x00,0x45,0xfc,0x00,0x00,0x3f,0x0d,0x00,0x45,0xf0,0x00,
    0x00,0x1f,0x0d,0x00,0x45,0xe0,0x00,0x00,0x0f,0x0d,0x00,0x18,0x80,0x0d,0x00,0x17,
    0x00,0x0d,0x00,0x54,0xfe,0x00,0x00,0x00,0x07,0x27,0x00,0x18,0xfc,0x0d,0x00,0x18,
    0xf8,0x0d,0x00,0x41,0xf0,0x00,0x07,0xe0,0x27,0x00,0x72,0xf7,0xff,0xff,0xff,0xc0,
    0x00,0x3f,0x0d,0x00,0x72,0xe3,0xff,0xff,0xff,0x80,0x00,0x7f,0x0d,0x00,0x75,0xc1,
    0xff,0xff,0xff,0x00,0x00,0xff,0x0d,0x00,0x36,0xfe,0x00,0x01,0x0d,0x00,0x36,0xfc,
    0x00,0x07,0x0d,0x00,0x33,0xf8,0x00,0x0f,0x0d,0x00,0x63,0xc0,0xff,0xff,0xe0,0x00,
    0x1f,0x0d,0x00,0x11,0x80,0x5a,0x00,0x06,0x0d,0x00,0x34,0x80,0x00,0x7f,0x0d,0x00,
    0x55,0x7f,0xff,0x00,0x00,0xff,0x0d,0x00,0x34,0xfe,0x00,0x03,0x0d,0x00,0x56,0x00,
    0x7f,0xfc,0x00,0x07,0x0d,0x00,0x35,0xf0,0x00,0x0f,0x0d,0x00,0x46,0x3f,0xe0,0x00,
    0x1f,0x0d,0x00,0x36,0xc0,0x00,0x3f,0x0d,0x00,0x33,0x80,0x00,0xff,0x0d,0x00,0x56,
    0xfe,0x00,0x3f,0x00,0x01,0x0d,0x00,0x36,0x1e,0x00,0x03,0x0d,0x00,0x36,0x18,0x00,
    0x07,0x0d,0x00,0x34,0x00,0x00,0x0f,0x0d,0x00,0x58,0xfc,0x00,0x00,0x00,0x1f,0x0d,
    0x00,0x18,0x7f,0x0d,0x00,0x17,0xff,0x0d,0x00,0x18,0x01,0x0d,0x00,0x15,0x03,0x0d,
    0x00,0x21,0xf8,0x00,0x5a,0x00,0x02,0xd0,0x00,0x12,0xf8,0x5a,0x00,0x05,0x0d,0x00,
    0x18,0x1f,0x27,0x00,0x18,0x0f,0x0d,0x00,0x06,0x41,0x00,0x18,0xf0,0x68,0x00,0x54,
    0xf0,0x00,0x00,0x00,0x3f,0x41,0x00,0x22,0xf0,0x00,0x35,0x00,0x01,0x86,0x01,0x22,
    0xf0,0x00,0x35,0x00,0x01,0x0d,0x00,0x22,0xe0,0x00,0x35,0x00,0x06,0x0d,0x00,0x04,
    0x11,0x01,0x01,0x1a,0x00,0x04,0x38,0x01,0x0f,0x0d,0x00,0x07,0x22,0xc0,0x00,0xf8,
    0x00,0x01,0x41,0x00,0x45,0xc0,0x00,0x00,0xbf,0x9c,0x00,0x04,0x5b,0x03,0x01,0x1a,
    0x00,0x0f,0x0d,0x00,0xff,0x07,0x16,0xf0,0x8e,0x03,0x01,0x02,0x00,0x06,0x2b,0x01,
    0x0f,0x0d,0x00,0x54,0x50,0xff,0xff,0xff,0xff,0xf0,

};

const lv_image_dsc_t turn_sharp_left = {
  .header.magic = LV_IMAGE_HEADER_MAGIC,
  .header.cf = LV_COLOR_FORMAT_I1,
  .header.flags = 0 | LV_IMAGE_FLAGS_COMPRESSED,
  .header.w = 100,
  .header.h = 100,
  .header.stride = 13,
  .data_size = sizeof(turn_sharp_left_map),
  .data = turn_sharp_left_map,
};

