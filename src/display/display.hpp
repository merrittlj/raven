#ifndef DISPLAY_HPP
#define DISPLAY_HPP


#include "sys/spi.hpp"
#include "sys/state.hpp"

#include "lvgl.h"

#include <vector>


namespace Display
{
    class EInk;
    struct Manager
    {
        uint16_t width;
        uint16_t height;

        EInk *displayCallback;

        uint16_t Width_Bytes();
        uint16_t Buffer_Size();
    };

    class EInk
    {
        private:
            Display::Manager manager;
            Sys::SPIController spi;
            std::vector<uint8_t> buf;

            void SetWindows(uint16_t Xstart, uint16_t Ystart, uint16_t Xend, uint16_t Yend);
            void SetCursor(uint16_t x, uint16_t y);

            /* Lookup table */
            void WriteLUT(uint8_t *value);
            void InitRegisters(uint8_t *lut);

        public:
            EInk();
            EInk(Display::Manager man, Sys::SPIController ctrl);

            std::vector<uint8_t> *GetBuf();

            void TurnOnDisplay();
            void TurnOnDisplayPart();

            void Init();
            void Init_Partial();
            void Clear();
            void Display();
            void DisplayPartBaseImage();
            void DisplayPart();
            void Sleep();
    };

    class LVGL
    {
        private:
            Display::Manager manager;
            std::vector<uint8_t> buf1;

            lv_obj_t *time;

        public:
            LVGL();
            LVGL(Display::Manager man);

            void Init();
            void Create();
            static void Flush(lv_display_t *display, const lv_area_t *area, uint8_t *px_map);

            void Time(Sys::Time value);
    };

    class Controller
    {
        private:
            inline static Controller *theInstance;

            Display::Manager manager;

            Display::EInk display;
            Display::LVGL lvgl;

        public:
            Controller(uint16_t displayWidth, uint16_t displayHeight, Sys::SPIController ctrl);
            ~Controller();

            static Controller *Instance(Controller *cur = nullptr);
            Manager Get_Manager();

            void Init();
            void Process();

            void Update_Time(Sys::Time value);
    };
}


#endif /* DISPLAY_HPP */
