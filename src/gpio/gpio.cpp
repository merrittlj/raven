#include "gpio/gpio.hpp"

#include <cstdint>
#include <vector>


GPIO_InitTypeDef GPIO::Types::LED = {
    .Mode = GPIO_MODE_OUTPUT_PP,
    .Pull = GPIO_PULLUP,
    .Speed = GPIO_SPEED_FREQ_HIGH,
};

GPIO::Pin::Pin()
{

}

GPIO::Pin::Pin(GPIO_TypeDef *pBank, uint32_t pPinNum)
{
    this->Bank = pBank;
    this->PinNum = pPinNum;
}

GPIO::Component::Component()
{

}

GPIO::Component::Component(GPIO::Pin pPin, GPIO_InitTypeDef pType)
{
    this->Pin = pPin;
    this->Type = pType;
}

void GPIO::Component::Config()
{
    /* Avoid LL calls, just use ifs */
    if (this->Pin.Bank == GPIOB)
        __HAL_RCC_GPIOB_CLK_ENABLE();
}

void GPIO::Component::Init()
{
    GPIO_InitTypeDef GPIOInit = this->Type;
    GPIOInit.Pin = (uint16_t)(1 << (this->Pin.PinNum - 1));
    HAL_GPIO_Init(this->Pin.Bank, &GPIOInit);
}

void GPIO::Component::Write(FlagStatus pStatus)
{
    if (pStatus == SET)
        HAL_GPIO_WritePin(this->Pin.Bank, this->Pin.PinNum, GPIO_PIN_SET); 
    if (pStatus == RESET)
        HAL_GPIO_WritePin(this->Pin.Bank, this->Pin.PinNum, GPIO_PIN_RESET); 
}

GPIO::Controller::Controller(std::vector<GPIO::Component> pComponents)
{
    this->Components = pComponents;
}

GPIO::Controller::~Controller()
{

}

/**
 * @brief Configure GPIO controller
 * @param None
 * @retval None
 */
void GPIO::Controller::Config(void)
{
    for (GPIO::Component c : this->Components)
        c.Config();
}

void GPIO::Controller::Init(void)
{
    for (GPIO::Component c : this->Components)
        c.Init();
}

uint32_t GPIO::Controller::Add_Component(GPIO::Component pComponent)
{
    this->Components.push_back(pComponent);
    return this->Components.size() - 1;
}

void GPIO::Controller::Write_Component(uint32_t pIndex, FlagStatus pStatus)
{
    this->Components.at(pIndex).Write(pStatus);
}
