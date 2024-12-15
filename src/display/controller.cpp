#include "display/controller.hpp"


namespace Display
{
    Controller::Controller(uint16_t displayWidth, uint16_t displayHeight, Sys::SPIController ctrl, Sys::State *sysState)
    {
        Controller::Instance(this);

        manager = { 0 };
        manager.width = displayWidth;
        manager.height = displayHeight;

        display = Display::EInk(manager, ctrl);
        manager.displayCallback = &display;

        lvgl = Display::LVGL(manager, sysState);
    }

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
        display.Clear();
        /* lvgl.Init(); */
        /* lvgl.Create(); */
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
