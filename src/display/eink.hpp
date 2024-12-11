#ifndef LVGL_HPP
#define LVGL_HPP


#include "display/display.hpp"

#include "sys/spi.hpp"

#include <cstdint>
#include <vector>


namespace Display
{
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
}
