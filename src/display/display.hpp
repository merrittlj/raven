#ifndef DISPLAY_HPP
#define DISPLAY_HPP


#include "sys/spi.hpp"

#include <vector>


namespace Display
{
    class EInk
    {
        private:
            uint16_t width;
            uint16_t height;

            Sys::SPIController spi;

            void SetWindows(uint16_t Xstart, uint16_t Ystart, uint16_t Xend, uint16_t Yend);
            void SetCursor(uint16_t x, uint16_t y);

            /* Lookup table */
            void WriteLUT(uint8_t *value);
            void InitRegisters(uint8_t *lut);

        public:
            EInk(uint16_t displayWidth, uint16_t displayHeight, Sys::SPIController ctrl);

            uint16_t Get_Width_Bytes();
            uint16_t Get_Buffer_Size();

            void TurnOnDisplay();
            void TurnOnDisplayPart();

            void Init();
            void Init_Partial();
            void Clear();
            void Display(std::vector<uint8_t> const &image);
            void DisplayPartBaseImage(std::vector<uint8_t> const &image);
            void DisplayPart(std::vector<uint8_t> const &image);
            void Sleep();
    };
}


#endif /* DISPLAY_HPP */
