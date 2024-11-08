#include "gpio/gpio.hpp"


GPIO_InitTypeDef GPIO::Types::LED = {
    Mode = GPIO_MODE_OUTPUT_PP;
    Pull = GPIO_PULLUP;
    Speed = GPIO_SPEED_FREQ_HIGH;
};

GPIO::Pin::Pin(GPIO_TypeDef pBank, uint32_t pPinNum)
{
    this.Bank = pBank;
    this.PinNum = pPinNum;
}

GPIO::Component::Component(GPIO::Pin pPin, GPIO_InitTypeDef pType)
{
    this.Pin = pPin;
    this.Type = pType;
}

GPIO::Component::Config()
{
    /* Avoid LL calls, just use switch */
    switch (this.Pin.Bank) {
        case GPIOB:
            __HAL_RCC_GPIOB_CLK_ENABLE();
            break;
        default:
            break;
    }
}

GPIO::Component::Init()
{
    GPIO_InitTypeDef GPIOInit = this.Type;
    GPIOInit.Pin = (uint16_t)(1 << (this.Pin.PinNum - 1));
    HAL_GPIO_Init(this.Pin.Bank, &GPIOInit);
}

GPIO::Component::Write(FlagStatus pStatus)
{
    if (pStatus == SET)
        HAL_GPIO_WritePin(this.Pin.Bank, this.Pin.PinNum, GPIO_PIN_SET); 
    if (pStatus == RESET)
        HAL_GPIO_WritePin(this.Pin.Bank, this.Pin.PinNum, GPIO_PIN_RESET); 
}

GPIO::Controller::~Controller()
{

}

GPIO::Controller::Controller(std::vector<GPIO::Component> Components)
{
    this.Components = Components;
}

/**
 * @brief Configure GPIO controller
 * @param None
 * @retval None
 */
void GPIO::Controller::Config(void)
{
    for (GPIO::Component c : components)
        c.Config();
}

void GPIO::Controller::Init(void)
{
    for (GPIO::Component c : components)
        c.Init();
}

void GPIO::Controller::Add_Component(GPIO::Component pComponent)
{
    this.Components.push_back(pComponent);
}
