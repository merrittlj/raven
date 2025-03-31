#ifndef FACE_HPP
#define FACE_HPP


#include "sys/state.hpp"

#include "lvgl.h"

#include <cstdint>


namespace Display
{
    class Face
    {
        public:
            virtual void Create() = 0;
            virtual void Load_Screen() = 0;
            virtual void Draw(Sys::TimeInfo info) = 0;
    };

    /* Large stylistic time with small date */
    class Big_Face : public Face
    {
        private:
            lv_obj_t *screen;
            lv_obj_t *time;
            lv_obj_t *date;

        public:
            Big_Face();
            ~Big_Face();

            void Create();
            void Load_Screen();
            void Draw(Sys::TimeInfo info);
    };

    /* Just time in a digital font */
    class Digital_Face : public Face
    {
        private:
            lv_obj_t *screen;
            lv_obj_t *time;

        public:
            Digital_Face();
            ~Digital_Face();

            void Create();
            void Load_Screen();
            void Draw(Sys::TimeInfo info);
    };

    /* Circular analog imitating Android's lockscreen(numbers in a circle with two lines) */
    class Analog_Face : public Face
    {
        private:
            lv_obj_t *screen;
            lv_obj_t *hourHand;
            lv_obj_t *minuteHand;

            const uint8_t radius = 95;
            const uint8_t centerX = 100;
            const uint8_t centerY = 100;

            lv_point_precise_t *hourPoints;
            lv_point_precise_t *minutePoints;

            void Draw_Numbers();
            void Draw_Hands(uint8_t hour, uint8_t minute);

        public:
            Analog_Face();
            ~Analog_Face();

            void Create();
            void Load_Screen();
            void Draw(Sys::TimeInfo info);
    };

    /* Simple face with DOW, date, and time with an image background(inspired by Kitty-for-Watchy) */
    class Image_Face : public Face
    {
        private:
            lv_obj_t *screen;
            lv_obj_t *dow;
            lv_obj_t *date;
            lv_obj_t *time;
            lv_obj_t *bg;

        public:
            Image_Face();
            ~Image_Face();

            void Create();
            void Load_Screen();
            void Draw(Sys::TimeInfo info);
    };

    /* UNFINISHED: bad line drawing functions */
    class Arcs_Face : public Face
    {
        private:
            lv_obj_t *screen;

            const uint8_t faceRadius = 88;
            const uint8_t centerX = 100;
            const uint8_t centerY = 100;

            void Arc_Ticks(float startAngle, float endAngle, uint32_t radius, uint32_t width, lv_color_t color, uint32_t step);

            void Draw_Minute(uint8_t minute);
            void Draw_Hour(uint8_t hour);
            void Draw_Day(uint8_t day);
            void Draw_Month(uint8_t month);

        public:
            Arcs_Face();
            ~Arcs_Face();

            void Create();
            void Load_Screen();
            void Draw(Sys::TimeInfo info);
    };
}


#endif /* FACE_HPP */
