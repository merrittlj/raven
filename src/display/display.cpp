#include "display/display.hpp"

#include "stm32wbxx_hal.h"

#include <vector>


namespace Display
{
    Controller::~Controller()
    {
        delete theInstance;
    }

    Controller *Controller::Instance(Controller *cur)
    {
        if (!theInstance) theInstance = cur;
        return theInstance;
    }

    Manager Controller::Get_Manager()
    {
        return manager;
    }

    void Controller::Init()
    {
        display.Init();
        lvgl.Init();
        lvgl.Create();
    }

    void Controller::Process()
    {
        lv_timer_periodic_handler();
    }

    void Controller::Update_Time(Sys::Time value)
    {
        lvgl.Time(value);
    }

    void Controller::Alert_Send(Sys::Alert alert)
    {
        lvgl.Alert(alert);
    }

    void Controller::Button_One()
    {
        lvgl.Button_One();
    }

    void Controller::Button_Two()
    {
        lvgl.Button_Two();
    }

    void Controller::Button_Three()
    {
        lvgl.Button_Three();
    }
    void Controller::Button_Four()
    {
        lvgl.Button_Four();
    }
}
