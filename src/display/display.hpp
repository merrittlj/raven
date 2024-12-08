#ifndef DISPLAY_HPP
#define DISPLAY_HPP


#include "sys/spi.hpp"


#define DISPLAY_HEIGHT 200
#define DISPLAY_WIDTH 200

namespace Display
{
    class EInk
    {
        private:
            Sys::SPIController spi;

            void SetWindows(uint16_t Xstart, uint16_t Ystart, uint16_t Xend, uint16_t Yend);
            void SetCursor(uint16_t Xstart, uint16_t Ystart);

            /* Lookup table */
            void WriteLUT(uint8_t *value);
            void InitRegisters(uint8_t *lut);

        public:
            EInk(Sys::SPIController ctrl);

            void TurnOnDisplay();
            void TurnOnDisplayPart();

            void Init();
            void Init_Partial();
            void Clear();
            void Display(uint8_t *image);
            void DisplayPartBaseImage(uint8_t *image);
            void DisplayPart(uint8_t *image);
            void Sleep();
            void Test();
    };
}


#endif /* DISPLAY_HPP */
