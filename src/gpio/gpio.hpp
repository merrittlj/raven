#ifndef GPIO_HPP
#define GPIO_HPP


#include "hw/if.hpp"

#include <cstdint>
#include <vector>


namespace GPIO
{
    struct Pin
    {
        GPIO_TypeDef *Bank;
        uint32_t PinNum;

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

        void Write(FlagStatus pStatus);
    };

    namespace Types
    {
        extern GPIO_InitTypeDef LED;
    }

    class Controller
    {
        private:
            std::vector<GPIO::Component> Components;
        public:
            Controller(std::vector<GPIO::Component> pComponents = std::vector<GPIO::Component>());
            ~Controller();

            void Config();
            void Init();

            uint32_t Add_Component(GPIO::Component pComponent);
            void Write_Component(uint32_t pIndex, FlagStatus pStatus);
    };
}


#endif /* GPIO_HPP */
