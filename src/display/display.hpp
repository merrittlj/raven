#ifndef DISPLAY_HPP
#define DISPLAY_HPP


#include <cstdint>


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
}


#endif /* DISPLAY_HPP */
