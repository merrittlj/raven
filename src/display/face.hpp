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

    class Arcs_Face : public Face
    {
        private:
            lv_obj_t *screen;

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

    class Analog_Face : public Face
    {
        private:
            lv_obj_t *screen;

            void Draw_Numbers();
            void Draw_Hand(uint8_t angle, uint8_t length);
            void Draw_Hands(uint8_t hour, uint8_t minute);

        public:
            Analog_Face();
            ~Analog_Face();

            void Create();
            void Load_Screen();
            void Draw(Sys::TimeInfo info);
    };

    class Speed_Face : public Face
    {
        private:
            lv_obj_t *screen;

        public:
            Speed_Face();
            ~Speed_Face();
            
            void Create();
            void Load_Screen();
            void Draw(Sys::TimeInfo info);
    };
}


#endif /* FACE_HPP */
