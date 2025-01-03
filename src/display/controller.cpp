#include "display/controller.hpp"


namespace Display
{
    Controller::Controller()
    {

    }

    Controller::Controller(uint16_t displayWidth, uint16_t displayHeight, Sys::SPIController ctrl, Sys::State *sysState)
    {
        state = sysState;

        Controller::Instance(this);

        manager = { 0 };
        manager.width = displayWidth;
        manager.height = displayHeight;

        display = Display::EInk(manager, ctrl, sysState);
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
        lvgl.Init();
        lvgl.Create();

        state->Screen_Activate(Sys::Screen::FACE);
        /* Alerts list shouldn't be default, just as there is no reason to with no unreads */
    }

    void Controller::Process()
    {
        lv_timer_periodic_handler();
    }

    void Controller::Update_Time(Sys::TimeInfo value)
    {
        lvgl.Time(value);
    }

    void Controller::Alert_Send(Sys::AlertInfo alert)
    {
        lvgl.Alert(alert);
    }

    void Controller::Event_Send(Sys::EventInfo event)
    {
        lvgl.Event(event);
    }

    void Controller::Nav_Send(Sys::NavInfo nav)
    {
        lvgl.Nav(nav);
    }

    void Controller::Music_Send(Sys::MusicInfo music)
    {
        lvgl.Music(music);
    }

    void Controller::Button(uint8_t b)
    {
        lvgl.Button(b);
    }


    void Controller::Button_Double(uint8_t b1, uint8_t b2)
    {
        lvgl.Button_Double(b1, b2);
    }
}
