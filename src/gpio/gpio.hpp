#ifndef GPIO_HPP
#define GPIO_HPP


#include "hw/if.hpp"

#include <cstdint>


namespace GPIO
{
    typedef struct 
    {
        GPIO_TypeDef Bank;
        uint32_t PinNum;

        Pin(GPIO_TypeDef pBank, uint32_t pPinNum);
    } Pin;

    typedef struct
    {
        GPIO::Pin Pin;
        GPIO_InitTypeDef Type;

        Component(GPIO::Pin pPin, GPIO_InitTypeDef pType);
        
        void Config();
        void Init();

        void Write(FlagStatus pStatus);
    } Component;

    namespace Types
    {
        extern GPIO_InitTypeDef LED;
    }

    class Controller
    {
        private:
            std::vector<GPIO::Component> Components;
        public:
            GPIO_Controller(std::vector<GPIO::Component> pComponents = std::vector<GPIO::Component>());
            ~GPIO_Controller();

            void Config();
            void Init();

            uint32_t Add_Component(GPIO::Component pComponent);
            void Write_Component(uint32_t pIndex, FlagStatus pStatus);
    };
}


#endif /* GPIO_HPP */