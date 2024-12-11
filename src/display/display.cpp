#include "display/display.hpp"

#include "stm32wbxx_hal.h"

#include <vector>


namespace Display
{
    uint16_t Manager::Width_Bytes()
    {
        return (width % 8 == 0) ? (width / 8) : (width / 8 + 1);
    }

    uint16_t Manager::Buffer_Size()
    {
        return (Width_Bytes() * height);
    }
}
