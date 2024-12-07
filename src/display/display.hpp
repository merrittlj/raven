#ifndef DISPLAY_HPP
#define DISPLAY_HPP


#include "sys/spi.hpp"


namespace Display
{
    class EInk
    {
        private:
            Sys::SPIController spi;

        public:
            EInk(Sys::SPIController ctrl);

            void Init();
            void Init_Partial();
            void Clear();
            void Display(uint8_t *image);
            void DisplayPartBaseImage(uint8_t *image);
            void DisplayPart(uint8_t *image);
            void Sleep();
    };
}


#endif /* DISPLAY_HPP */
