#ifndef GPIO_CONTROLLER_H
#define GPIO_CONTROLLER_H


class GPIO_Controller
{
    private:
        std::vector<uint16_t> leds;
    public:
        GPIO_Controller();
        ~GPIO_Controller();
};


#endif /* GPIO_CONTROLLER_H */
