#include "display/face.hpp"
#include "display/lvgl.hpp"
#include "sys/state.hpp"

#include "lvgl.h"

#include <math.h>
#include <array>
#include <string>
#include <ctime>


#define DEG2RAD 0.0174532925

    LV_FONT_DECLARE(gloock_time)  /* Gloock 70 regular */
    LV_FONT_DECLARE(gloock_date)  /* Gloock 18 regular */
    LV_FONT_DECLARE(seg)  /* 55 bold */
    LV_FONT_DECLARE(axel_ui)  /* Axel 22 bold */
    LV_FONT_DECLARE(montserrat_time) /* Montserrat 20 medium */
    LV_FONT_DECLARE(roboto_dow) /* Roboto Condensed 7 light */
    LV_FONT_DECLARE(roboto_date) /* Roboto Condensed 13 bold */
LV_FONT_DECLARE(axel_time_date) /* Axel 22 bold */

    LV_IMAGE_DECLARE(image1_face_bg);  
    LV_IMAGE_DECLARE(image2_face_bg);  

    namespace Display
{

    void Draw_Ticks(float startAngle, float endAngle, uint32_t radius, uint32_t width, uint32_t thickness, lv_color_t color, uint32_t step, lv_obj_t *screen)
    {
        uint8_t center_x = 100;
        uint8_t center_y = 100;

        lv_style_t *styleLine = new lv_style_t;
        lv_style_init(styleLine);
        lv_style_set_line_width(styleLine, thickness);
        lv_style_set_line_rounded(styleLine, true);
        lv_style_set_line_color(styleLine, color);

        // Draw colour blocks every inc degrees
        for (float i = startAngle; i <= endAngle; i += step) {
            float cx1 = center_x + (radius - width / 2) * cos((i - 90) * (float)DEG2RAD);
            float cy1 = center_y + (radius - width / 2) * sin((i - 90) * (float)DEG2RAD);
            float cx2 = center_x + (radius + width / 2) * cos((i - 90) * (float)DEG2RAD);
            float cy2 = center_y + (radius + width / 2) * sin((i - 90) * (float)DEG2RAD);

            lv_point_precise_t *linePoints = new lv_point_precise_t[2] {{(lv_value_precise_t)cx1, (lv_value_precise_t)cy1}, {(lv_value_precise_t)cx2, (lv_value_precise_t)cy2}};

            lv_obj_t *line;
            line = lv_line_create(screen);
            lv_line_set_points(line, linePoints, 2);
            lv_obj_add_style(line, styleLine, 0);
            lv_obj_align(line, LV_ALIGN_TOP_LEFT, 0, 0);
        }
    }

    std::string Digital_Time(Sys::TimeInfo info)
    {
        return (info.hour < 10 ? "0" : "") + std::to_string(info.hour) + ":" + (info.minute < 10 ? "0" : "") + std::to_string(info.minute);
    }

    std::string Day_Suffix(uint8_t day)
    {
        std::string result = std::to_string(day);
        if (day % 10 == 1 && day != 11) result += "st";
        else if (day % 10 == 2 && day != 12) result += "nd";
        else if (day % 10 == 3 && day != 13) result += "rd";
        else result += "th";
        return result;
    }

    Big_Face::Big_Face()
    {}

    Big_Face::~Big_Face()
    {
        lv_obj_clean(screen);
    }

    void Big_Face::Create()
    {
        static lv_style_t texts;
        lv_style_init(&texts);
        lv_style_set_text_color(&texts, lv_color_hex(0x000000));
        lv_style_set_text_font(&texts, &gloock_time);

        screen = lv_obj_create(NULL);

        time = lv_label_create(screen);
        lv_obj_add_style(time, &texts, 0);
        lv_label_set_text(time, "00:00");
        lv_obj_align(time, LV_ALIGN_CENTER, 0, -10);

        date = lv_label_create(screen);
        lv_obj_add_style(date, &texts, 0);
        lv_label_set_text(date, "Month Day Year");
        lv_obj_set_style_text_font(date, &gloock_date, 0);
        lv_obj_align(date, LV_ALIGN_CENTER, 0, 45);
    }

    void Big_Face::Load_Screen()
    {
        LVGL::Safe_Screen_Load(screen);
    }

    void Big_Face::Draw(Sys::TimeInfo info)
    {
        lv_label_set_text(time, Digital_Time(info).c_str());
        lv_label_set_text(date, (months[info.month - 1] + " " + Day_Suffix(info.day)).c_str());
    }

    Digital_Face::Digital_Face()
    {}

    Digital_Face::~Digital_Face()
    {
        lv_obj_clean(screen);
    }

    void Digital_Face::Create()
    {
        static lv_style_t texts;
        lv_style_init(&texts);
        lv_style_set_text_color(&texts, lv_color_hex(0x000000));

        screen = lv_obj_create(NULL);

        time = lv_label_create(screen);
        lv_obj_add_style(time, &texts, 0);
        lv_label_set_text(time, "00:00");
        lv_obj_set_style_text_font(time, &seg, 0);
        lv_obj_align(time, LV_ALIGN_CENTER, 0, 0);
    }

    void Digital_Face::Load_Screen()
    {
        LVGL::Safe_Screen_Load(screen);
    }

    void Digital_Face::Draw(Sys::TimeInfo info)
    {
        lv_label_set_text(time, Digital_Time(info).c_str());
    }

    Analog_Face::Analog_Face()
    {}

    Analog_Face::~Analog_Face()
    {
        lv_obj_clean(screen);
    }

    void Analog_Face::Create()
    {
        static lv_style_t texts;
        lv_style_init(&texts);
        lv_style_set_text_color(&texts, lv_color_hex(0x000000));

        screen = lv_obj_create(NULL);

        Draw_Numbers();

        /* Two styles for different line widths, but I like them essentially the same */
        static lv_style_t hourStyle;
        lv_style_init(&hourStyle);
        lv_style_set_line_width(&hourStyle, 5);
        lv_style_set_line_color(&hourStyle, lv_color_hex(0x000000));
        lv_style_set_line_rounded(&hourStyle, false);

        static lv_style_t minuteStyle;
        lv_style_init(&minuteStyle);
        lv_style_set_line_width(&minuteStyle, 5);
        lv_style_set_line_color(&minuteStyle, lv_color_hex(0x000000));
        lv_style_set_line_rounded(&minuteStyle, false);


        hourPoints = new lv_point_precise_t[2] {
            {0,0},
                {0,0}
        };

        minutePoints = new lv_point_precise_t[2] {
            {0,0},
                {0,0}
        };

        hourHand = lv_line_create(screen);
        lv_line_set_points(hourHand, hourPoints, 2);
        lv_obj_add_style(hourHand, &hourStyle, 0);
        lv_obj_align(hourHand, LV_ALIGN_TOP_LEFT, 0, 0);

        minuteHand = lv_line_create(screen);
        lv_line_set_points(minuteHand, minutePoints, 2);
        lv_obj_add_style(minuteHand, &minuteStyle, 0);
        lv_obj_align(minuteHand, LV_ALIGN_TOP_LEFT, 0, 0);
    }

    void Analog_Face::Load_Screen()
    {
        LVGL::Safe_Screen_Load(screen);
    }

    void Analog_Face::Draw(Sys::TimeInfo info)
    {
        Draw_Hands(info.hour, info.minute);
    }

    void Analog_Face::Draw_Numbers()
    {
        uint8_t hourStep = (uint8_t)(360 / 12);

        static lv_style_t arcs;
        lv_style_init(&arcs);
        lv_style_set_arc_width(&arcs, 13);

        lv_obj_t *arc = lv_arc_create(screen);
        lv_obj_add_style(arc, &arcs, 0);
        lv_arc_set_bg_angles(arc, 0, 360);
        lv_obj_remove_style(arc, NULL, LV_PART_KNOB);  /* Remove knob */
        lv_obj_remove_flag(arc, LV_OBJ_FLAG_CLICKABLE);
        lv_obj_set_size(arc, radius*2, radius*2);
        lv_arc_set_rotation(arc, 270);  /* Start from top */
        /* lv_arc_set_range(arc, 0, 360); */
        lv_arc_set_value(arc, 0);
        lv_obj_center(arc);
        lv_obj_add_flag(arc, LV_OBJ_FLAG_HIDDEN);

        static lv_style_t texts;
        lv_style_init(&texts);
        lv_style_set_text_color(&texts, lv_color_hex(0x000000));

        for (uint8_t i = 1; i < 13; ++i) {
            lv_obj_t *num = lv_label_create(screen);
            lv_obj_add_style(num, &texts, 0);
            lv_label_set_text(num, std::to_string(i).c_str());
            lv_obj_set_style_text_font(num, &axel_ui, 0);

            uint8_t value = (uint8_t)((hourStep * i) / 3.6);
            lv_arc_set_value(arc, value);
            lv_arc_align_obj_to_angle(arc, num, 0);
        }
    }

    void Analog_Face::Draw_Hands(uint8_t hour, uint8_t minute)
    {
        float hourAngle = (360.0 * (hour / 12.0)) + (30.0 * (minute / 60.0));
        float minuteAngle = 360.0 * (minute / 60.0);
        const uint8_t hLength = radius - 50;
        const uint8_t mLength = radius - 20;
        const uint8_t bwLength = 10;

        hourPoints[0].x = (lv_value_precise_t)(100 + -(bwLength) * cos((hourAngle - 90) * (float)DEG2RAD));;
        hourPoints[0].y = (lv_value_precise_t)(100 + -(bwLength) * sin((hourAngle - 90) * (float)DEG2RAD));;
        hourPoints[1].x = (lv_value_precise_t)(100 + hLength * cos((hourAngle - 90) * (float)DEG2RAD));
        hourPoints[1].y = (lv_value_precise_t)(100 + hLength * sin((hourAngle - 90) * (float)DEG2RAD));

        minutePoints[0].x = (lv_value_precise_t)(100 + -(bwLength) * cos((minuteAngle - 90) * (float)DEG2RAD));;
        minutePoints[0].y = (lv_value_precise_t)(100 + -(bwLength) * sin((minuteAngle - 90) * (float)DEG2RAD));;
        minutePoints[1].x = (lv_value_precise_t)(100 + mLength * cos((minuteAngle - 90) * (float)DEG2RAD));
        minutePoints[1].y = (lv_value_precise_t)(100 + mLength * sin((minuteAngle - 90) * (float)DEG2RAD));

        lv_line_set_points(hourHand, hourPoints, 2);
        lv_line_set_points(minuteHand, minutePoints, 2);
    }

    Square_Analog_Face::Square_Analog_Face()
    {}

    Square_Analog_Face::~Square_Analog_Face()
    {
        lv_obj_clean(screen);
    }

    void Square_Analog_Face::Create()
    {
        static lv_style_t texts;
        lv_style_init(&texts);
        lv_style_set_text_color(&texts, lv_color_hex(0x000000));

        screen = lv_obj_create(NULL);

        uint8_t tick = (uint8_t)(360 / 12);
        Draw_Ticks(tick, 360, faceRadius, 15, 3, lv_color_hex(0x000000), tick, screen);

        /* Two styles for different line widths, but I like them essentially the same */
        static lv_style_t hourStyle;
        lv_style_init(&hourStyle);
        lv_style_set_line_width(&hourStyle, 5);
        lv_style_set_line_color(&hourStyle, lv_color_hex(0x000000));
        lv_style_set_line_rounded(&hourStyle, false);

        static lv_style_t minuteStyle;
        lv_style_init(&minuteStyle);
        lv_style_set_line_width(&minuteStyle, 5);
        lv_style_set_line_color(&minuteStyle, lv_color_hex(0x000000));
        lv_style_set_line_rounded(&minuteStyle, false);


        hourPoints = new lv_point_precise_t[2] {
            {0,0},
                {0,0}
        };

        minutePoints = new lv_point_precise_t[2] {
            {0,0},
                {0,0}
        };

        hourHand = lv_line_create(screen);
        lv_line_set_points(hourHand, hourPoints, 2);
        lv_obj_add_style(hourHand, &hourStyle, 0);
        lv_obj_align(hourHand, LV_ALIGN_TOP_LEFT, 0, 0);

        minuteHand = lv_line_create(screen);
        lv_line_set_points(minuteHand, minutePoints, 2);
        lv_obj_add_style(minuteHand, &minuteStyle, 0);
        lv_obj_align(minuteHand, LV_ALIGN_TOP_LEFT, 0, 0);
    }

    void Square_Analog_Face::Load_Screen()
    {
        LVGL::Safe_Screen_Load(screen);
    }

    void Square_Analog_Face::Draw(Sys::TimeInfo info)
    {
        Draw_Hands(info.hour, info.minute);
    }

    void Square_Analog_Face::Draw_Hands(uint8_t hour, uint8_t minute)
    {
        // A square face is just a normal round face w/ extended ticks, use normal angles
        float hourAngle = (360.0 * (hour / 12.0)) + (30.0 * (minute / 60.0));
        float minuteAngle = 360.0 * (minute / 60.0);
        const uint8_t hLength = 50;
        const uint8_t mLength = 20;

        hourPoints[0].x = (lv_value_precise_t)(100 * cos((hourAngle - 90) * (float)DEG2RAD));
        hourPoints[0].y = (lv_value_precise_t)(100 * sin((hourAngle - 90) * (float)DEG2RAD));
        hourPoints[1].x = (lv_value_precise_t)(100 + hLength * cos((hourAngle - 90) * (float)DEG2RAD));
        hourPoints[1].y = (lv_value_precise_t)(100 + hLength * sin((hourAngle - 90) * (float)DEG2RAD));

        minutePoints[0].x = (lv_value_precise_t)(100 * cos((minuteAngle - 90) * (float)DEG2RAD));
        minutePoints[0].y = (lv_value_precise_t)(100 * sin((minuteAngle - 90) * (float)DEG2RAD));
        minutePoints[1].x = (lv_value_precise_t)(100 + mLength * cos((minuteAngle - 90) * (float)DEG2RAD));
        minutePoints[1].y = (lv_value_precise_t)(100 + mLength * sin((minuteAngle - 90) * (float)DEG2RAD));

        lv_line_set_points(hourHand, hourPoints, 2);
        lv_line_set_points(minuteHand, minutePoints, 2);
    }

    Image1_Face::Image1_Face()
    {}

    Image1_Face::~Image1_Face()
    {
        lv_obj_clean(screen);
    }

    void Image1_Face::Create()
    {
        static lv_style_t texts;
        lv_style_init(&texts);
        lv_style_set_text_color(&texts, lv_color_hex(0x000000));

        screen = lv_obj_create(NULL);

        dow = lv_label_create(screen);
        lv_obj_add_style(dow, &texts, 0);
        lv_label_set_text(dow, "DOW");
        lv_obj_set_style_text_font(dow, &roboto_dow, 0);
        lv_obj_align(dow, LV_ALIGN_TOP_MID, 0, 7);

        date = lv_label_create(screen);
        lv_obj_add_style(date, &texts, 0);
        lv_label_set_text(date, "Month Day");
        lv_obj_set_style_text_font(date, &roboto_date, 0);
        lv_obj_align(date, LV_ALIGN_TOP_MID, 8, 27);

        time = lv_label_create(screen);
        lv_obj_add_style(time, &texts, 0);
        lv_label_set_text(time, "00:00");
        lv_obj_set_style_text_font(date, &montserrat_time, 0);
        lv_obj_align(time, LV_ALIGN_BOTTOM_LEFT, 67, -20);

        bg = lv_image_create(screen);
        lv_image_set_src(bg, &image1_face_bg);
        lv_obj_align(bg, LV_ALIGN_CENTER, 0, 0);
        lv_obj_move_background(bg);
    }

    void Image1_Face::Load_Screen()
    {
        LVGL::Safe_Screen_Load(screen);
    }

    void Image1_Face::Draw(Sys::TimeInfo info)
    {
        std::tm time_in = { info.second, info.minute, info.hour, // second, minute, hour
            info.day, info.month - 1, info.year - 1900 }; // 1-based day, 0-based month, year since 1900
        std::time_t time_temp = std::mktime(&time_in);
        const std::tm * time_out = std::localtime(&time_temp);

        lv_label_set_text(dow, dows[time_out->tm_wday].c_str());
        lv_label_set_text(date, (months_abr[info.month - 1] + " " + std::to_string(info.day)).c_str());
        lv_label_set_text(time, Digital_Time(info).c_str());
    }

    Image2_Face::Image2_Face()
    {}

    Image2_Face::~Image2_Face()
    {
        lv_obj_clean(screen);
    }

    void Image2_Face::Create()
    {
        static lv_style_t texts;
        lv_style_init(&texts);
        lv_style_set_text_color(&texts, lv_color_hex(0x000000));

        static lv_style_t flexBox;
        lv_style_set_border_width(&flexBox, 2);
        lv_style_set_border_color(&flexBox, lv_color_hex(0x000000));
        lv_style_set_bg_color(&flexBox, lv_color_hex(0xffffff));
        lv_style_set_bg_opa(&flexBox, LV_OPA_100);
        lv_style_set_radius(&flexBox, 5);
        lv_style_set_pad_top(&flexBox, 1);
        lv_style_set_pad_bottom(&flexBox, 1);
        lv_style_set_pad_left(&flexBox, 3);
        lv_style_set_pad_right(&flexBox, 3);

        screen = lv_obj_create(NULL);

        date = lv_label_create(screen);
        lv_obj_add_style(date, &texts, 0);
        lv_obj_add_style(date, &flexBox, 0);
        lv_label_set_text(date, "Abr #");
        lv_obj_set_style_text_font(date, &axel_time_date, 0);
        lv_obj_align(date, LV_ALIGN_CENTER, 0, 50);

        time = lv_label_create(screen);
        lv_obj_add_style(time, &texts, 0);
        lv_obj_add_style(time, &flexBox, 0);
        lv_label_set_text(time, "XX:XX");
        lv_obj_set_style_text_font(date, &axel_time_date, 0);
        lv_obj_align(time, LV_ALIGN_CENTER, 0, 20);

        bg = lv_image_create(screen);
        lv_image_set_src(bg, &image2_face_bg);
        lv_obj_align(bg, LV_ALIGN_CENTER, 0, 0);
        lv_obj_move_background(bg);
    }

    void Image2_Face::Load_Screen()
    {
        LVGL::Safe_Screen_Load(screen);
    }

    void Image2_Face::Draw(Sys::TimeInfo info)
    {
        lv_label_set_text(date, (months_abr[info.month - 1] + " " + std::to_string(info.day)).c_str());
        lv_label_set_text(time, Digital_Time(info).c_str());
    }
}
