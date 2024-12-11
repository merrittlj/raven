#include "gpio/gpio.hpp"

#include <cstdint>
#include <vector>


GPIO_InitTypeDef GPIO::Types::LED = {
    .Mode = GPIO_MODE_OUTPUT_PP,
    .Pull = GPIO_PULLUP,
    .Speed = GPIO_SPEED_FREQ_HIGH,
};

GPIO_InitTypeDef GPIO::Types::SPI = {
    .Mode = GPIO_MODE_OUTPUT_PP,
    .Pull = GPIO_NOPULL,
    .Speed = GPIO_SPEED_FREQ_HIGH,
};

GPIO_InitTypeDef GPIO::Types::Button = {
    .Mode = GPIO_MODE_INPUT,
    .Pull = GPIO_PULL_UP,
    .Speed = GPIO_SPEED_FREQ_HIGH,
}

GPIO::Pin::Pin()
{}

GPIO::Pin::Pin(GPIO_TypeDef *pBank, uint32_t pPinNum)
{
    this->Bank = pBank;
    this->PinNum = pPinNum;
    this->FormattedPinNum = (uint16_t)(1 << pPinNum);
}

GPIO::Component::Component()
{}

GPIO::Component::Component(GPIO::Pin pPin, GPIO_InitTypeDef pType)
{
    this->Pin = pPin;
    this->Type = pType;
}

void GPIO::Component::Config()
{
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();

    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6, GPIO_PIN_RESET);
}

void GPIO::Component::Init()
{
    GPIO_InitTypeDef GPIOInit = this->Type;
    GPIOInit.Pin = this->Pin.FormattedPinNum;
    HAL_GPIO_Init(this->Pin.Bank, &GPIOInit);
}

FlagStatus GPIO::Component::Read()
{
    return (FlagStatus)(HAL_GPIO_ReadPin(Pin.Bank, Pin.FormattedPinNum));
}

void GPIO::Component::Write(FlagStatus pStatus)
{
    if (pStatus == SET)
        HAL_GPIO_WritePin(this->Pin.Bank, this->Pin.FormattedPinNum, GPIO_PIN_SET); 
    if (pStatus == RESET)
        HAL_GPIO_WritePin(this->Pin.Bank, this->Pin.FormattedPinNum, GPIO_PIN_RESET); 
}

void GPIO::Component::Toggle()
{
    HAL_GPIO_WritePin(Pin.Bank, Pin.FormattedPinNum, (GPIO_PinState)(HAL_GPIO_ReadPin(Pin.Bank, Pin.FormattedPinNum) ^ 1));
}

GPIO::Controller::Controller()
{}

GPIO::Controller::Controller(std::array<GPIO::Component, 128> pComponents)
{
    this->components = pComponents;
}

GPIO::Controller::~Controller()
{}

/**
 * @brief Configure GPIO controller
 * @param None
 * @retval None
 */
void GPIO::Controller::Config(void)
{
    for (uint8_t i = 0; i < cmpPos; ++i)
        components.at(i).Config();
}

void GPIO::Controller::Init(void)
{
    for (uint8_t i = 0; i < cmpPos; ++i)
        components.at(i).Init();
}

uint32_t GPIO::Controller::Add_Component(GPIO::Component pComponent)
{
    uint32_t addedPos = this->cmpPos;
    this->components.at(this->cmpPos) = pComponent;
    ++(this->cmpPos);
    return addedPos;
}

GPIO::Component GPIO::Controller::Get_Component(uint32_t index)
{
    return components.at(index);
}

FlagStatus GPIO::Controller::Read_Component(uint32_t index)
{
    if (index < cmpPos)
        return components.at(index).Read();
    return RESET;
}

void GPIO::Controller::Write_Component(uint32_t pIndex, FlagStatus pStatus)
{
    if (pIndex < cmpPos)
        this->components.at(pIndex).Write(pStatus);
}

void GPIO::Controller::Toggle_Component(uint32_t pIndex)
{
    if (pIndex < cmpPos)
        components.at(pIndex).Toggle();
}
