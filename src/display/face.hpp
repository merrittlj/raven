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

    void Draw_Ticks(float startAngle, float endAngle, uint32_t radius, uint32_t width, uint32_t thickness, lv_color_t color, uint32_t step, lv_obj_t *screen);
    std::string Digital_Time(Sys::TimeInfo info);
    std::string Day_Suffix(uint8_t day);

    /* Necessary characters to display: JanuryFebMchApilgstSmOoNvD */
    const std::string months[12] = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};
    /* JanFebMrApyulgSOctNovD */
    const std::string months_abr[12] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
    /* MondayTuesWhrFiSt */
    const std::string dows[7] = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};
    /* MonTueWdhFriSat */
    const std::string dows_abr[7] = {"Mon", "Tue", "Wed", "Thu", "Fri", "Sat", "Sun"};

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

    /* Square minimal analog face */
    class Square_Analog_Face : public Face
    {
        private:
            lv_obj_t *screen;
            lv_obj_t *hourHand;
            lv_obj_t *minuteHand;

            const uint8_t faceRadius = 88;

            lv_point_precise_t *hourPoints;
            lv_point_precise_t *minutePoints;

            void Draw_Hands(uint8_t hour, uint8_t minute);

        public:
            Square_Analog_Face();
            ~Square_Analog_Face();

            void Create();
            void Load_Screen();
            void Draw(Sys::TimeInfo info);
    };

    /* Simple face with DOW, date, and time with an image background(inspired by Kitty-for-Watchy) */
    class Image1_Face : public Face
    {
        private:
            lv_obj_t *screen;
            lv_obj_t *dow;
            lv_obj_t *date;
            lv_obj_t *time;
            lv_obj_t *bg;

        public:
            Image1_Face();
            ~Image1_Face();

            void Create();
            void Load_Screen();
            void Draw(Sys::TimeInfo info);
    };

    /* Simple image face with time and date over image background */
    class Image2_Face : public Face
    {
        private:
            lv_obj_t *screen;
            lv_obj_t *date;
            lv_obj_t *time;
            lv_obj_t *bg;

        public:
            Image2_Face();
            ~Image2_Face();

            void Create();
            void Load_Screen();
            void Draw(Sys::TimeInfo info);
    };

}


#endif /* FACE_HPP */
