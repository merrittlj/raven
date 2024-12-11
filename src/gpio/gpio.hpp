#ifndef GPIO_HPP
#define GPIO_HPP


#include "hw/if.hpp"

#include <cstdint>
#include <array>


namespace GPIO
{
    struct Pin
    {
        GPIO_TypeDef *Bank;
        uint32_t PinNum;
        /* HAL usually wants pins using their macros of GPIO_PIN_x, so we have to do some bit manipulation rather than passing in just the pin num */
        uint16_t FormattedPinNum;

        Pin();
        Pin(GPIO_TypeDef *pBank, uint32_t pPinNum);
    };

    struct Component
    {
        GPIO::Pin Pin;
        GPIO_InitTypeDef Type;

        Component();
        Component(GPIO::Pin pPin, GPIO_InitTypeDef pType);

        void Config();
        void Init();

        FlagStatus Read();
        void Write(FlagStatus pStatus);
        void Toggle();
    };

    namespace Types
    {
        extern GPIO_InitTypeDef LED;
        extern GPIO_InitTypeDef SPI;
        extern GPIO_InitTypeDef Button;
    }

    class Controller
    {
        private:
            uint8_t cmpPos = 0;
            std::array<GPIO::Component, 128> components;
        public:
            Controller();
            Controller(std::array<GPIO::Component, 128> pComponents);
            ~Controller();

            void Config();
            void Init();

            uint32_t Add_Component(GPIO::Component pComponent);
            GPIO::Component Get_Component(uint32_t index);
            FlagStatus Read_Component(uint32_t index);
            void Write_Component(uint32_t pIndex, FlagStatus pStatus);
            void Toggle_Component(uint32_t pIndex);
    };
}


#endif /* GPIO_HPP */
