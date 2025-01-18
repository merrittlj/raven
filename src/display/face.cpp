#include "display/face.hpp"
#include "sys/state.hpp"

#include "lvgl.h"

#include <math.h>
#include <array>
#include <string>


#define DEG2RAD 0.0174532925

    LV_FONT_DECLARE(gloock_time)  /* 70 regular */
    LV_FONT_DECLARE(gloock_date)  /* 18 regular */
    LV_FONT_DECLARE(seg)  /* 55 bold */
LV_FONT_DECLARE(axel_ui)  /* 22 bold */

    namespace Display
{
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
        lv_scr_load(screen);
    }

    void Big_Face::Draw(Sys::TimeInfo info)
    {
        std::string timeValue = (info.hour < 10 ? "0" : "") + std::to_string(info.hour) + ":" + (info.minute < 10 ? "0" : "") + std::to_string(info.minute);

        const std::string months[12] = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};
        std::string day = std::to_string(info.day);
        if (info.day % 10 == 1 && info.day != 11) day += "st";
        else if (info.day % 10 == 2 && info.day != 12) day += "nd";
        else if (info.day % 10 == 3 && info.day != 13) day += "rd";
        else day += "th";

        lv_label_set_text(time, timeValue.c_str());
        lv_label_set_text(date, (months[info.month - 1] + " " + day).c_str());

        Load_Screen();
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
        lv_scr_load(screen);
    }

    void Digital_Face::Draw(Sys::TimeInfo info)
    {
        std::string timeValue = (info.hour < 10 ? "0" : "") + std::to_string(info.hour) + ":" + (info.minute < 10 ? "0" : "") + std::to_string(info.minute);

        lv_label_set_text(time, timeValue.c_str());

        Load_Screen();
    }

    Arcs_Face::Arcs_Face()
    {}

    Arcs_Face::~Arcs_Face()
    {
        lv_obj_clean(screen);
    }

    void Arcs_Face::Create()
    {
        static lv_style_t texts;
        lv_style_init(&texts);
        lv_style_set_text_color(&texts, lv_color_hex(0x000000));
        lv_style_set_text_font(&texts, &gloock_time);

        screen = lv_obj_create(NULL);
    }

    void Arcs_Face::Load_Screen()
    {
        lv_scr_load(screen);
    }

    void Arcs_Face::Draw(Sys::TimeInfo info)
    {
        Draw_Minute(info.minute);
        Draw_Hour(info.hour);
        Draw_Day(info.day);
        Draw_Month(info.month);

        Load_Screen();
    }

    void Arcs_Face::Draw_Minute(uint8_t minute)
    {
        float minuteAngle = 360.0 * (minute / 60.0);
        uint8_t tick = (uint8_t)(360 / 60);

        static lv_style_t arcs;
        lv_style_init(&arcs);
        lv_style_set_arc_color(&arcs, lv_color_hex(0x000000));
        lv_style_set_arc_width(&arcs, 13);
        lv_style_set_arc_rounded(&arcs, false);

        lv_obj_t *arc = lv_arc_create(screen);
        lv_obj_add_style(arc, &arcs, 0);
        lv_arc_set_bg_angles(arc, 0, minuteAngle);
        lv_obj_remove_style(arc, NULL, LV_PART_KNOB);  /* Remove knob */
        lv_obj_remove_flag(arc, LV_OBJ_FLAG_CLICKABLE);
        lv_arc_set_value(arc, 100);
        lv_obj_set_size(arc, faceRadius*2, faceRadius*2);
        lv_arc_set_rotation(arc, 270);  /* Start from top */
        lv_obj_center(arc);
        lv_obj_move_background(arc);

        /* Existing ticks */
        Arc_Ticks(tick, minuteAngle - tick, faceRadius - 13/2, 15, lv_color_hex(0xffffff), tick);
        /* Future ticks */
        Arc_Ticks(minuteAngle + tick, 360 - tick, faceRadius - 13/2, 7, lv_color_hex(0x000000), tick);
    }

    void Arcs_Face::Draw_Hour(uint8_t hour)
    {

    }

    void Arcs_Face::Draw_Day(uint8_t day)
    {

    }

    void Arcs_Face::Draw_Month(uint8_t month)
    {

    }

    void Arcs_Face::Arc_Ticks(float startAngle, float endAngle, uint32_t radius, uint32_t width, lv_color_t color, uint32_t step)
    {
        uint8_t center_x = 100;
        uint8_t center_y = 100;

        lv_style_t *styleLine = new lv_style_t;
        lv_style_init(styleLine);
        lv_style_set_line_width(styleLine, 3);
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
        lv_scr_load(screen);
    }

    void Analog_Face::Draw(Sys::TimeInfo info)
    {
        Draw_Hands(info.hour, info.minute);

        Load_Screen();
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

    Speed_Face::Speed_Face()
    {}

    Speed_Face::~Speed_Face()
    {
        lv_obj_clean(screen);
    }

    void Speed_Face::Create()
    {
        static lv_style_t texts;
        lv_style_init(&texts);
        lv_style_set_text_color(&texts, lv_color_hex(0x000000));

        screen = lv_obj_create(NULL);

        lv_obj_t *tmp = lv_label_create(screen);
        lv_obj_add_style(tmp, &texts, 0);
        lv_label_set_text(tmp, "Speed Face");
        lv_obj_set_style_text_font(tmp, &axel_ui, 0);
        lv_obj_align(tmp, LV_ALIGN_CENTER, 0, 0);
    }

    void Speed_Face::Load_Screen()
    {
        lv_scr_load(screen);
    }

    void Speed_Face::Draw(Sys::TimeInfo info)
    {
        /* Draw circle */
        /* Draw small(subsecond) ticks */
        /* Draw second ticks */
        /* Draw hour ticks */
        /* Draw circles */
        /* Draw hands */

        Load_Screen();
    }
}
