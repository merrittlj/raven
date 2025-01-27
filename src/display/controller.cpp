#include "display/controller.hpp"
#include "display/face.hpp"
#include "sys/sys.hpp"
#include "ble/uuid.hpp"
#include "services/info.hpp"


namespace Display
{
    Controller::Controller()
    {

    }

    Controller::Controller(uint16_t displayWidth, uint16_t displayHeight, Sys::SPI_Controller ctrl, Sys::State *sysState, Sys::Controller *userSys, Haptic::Controller *userHaptic, BLE::InfoService *infoService)
    {
        state = sysState;
        sysCtrl = userSys;
        
        info = infoService;

        Controller::Instance(this);

        manager = { 0 };
        manager.width = displayWidth;
        manager.height = displayHeight;

        display = Display::EInk(manager, ctrl, sysState);
        manager.displayCallback = &display;

        lvgl = Display::LVGL(manager, sysState, userHaptic, infoService);
        /* Be careful not to use LVGL here, not init'd yet */
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

    Sys::State *Controller::Get_State()
    {
        return state;
    }

    void Controller::Init()
    {
        display.Init();
        display.Clear();
        lvgl.Init();
        lvgl.Create();
    }

    void Controller::Process()
    {
        /* lv_timer_handler does its own locking */
        /* lv_lock(); */
        lv_timer_periodic_handler();
        /* lv_unlock(); */
    }

    void Controller::Refresh()
    {
        lvgl.Refresh();
    }

    void Controller::Tag_Screen()
    {
        lvgl.Tag();
    }

    void Controller::Update_Face()
    {
        std::string pref = state->Get_Pref()->face;

        Face *face = new Digital_Face();
        if (pref == "big") face = new Big_Face();
        else if (pref == "digital") face = new Digital_Face();
        else if (pref == "arcs") face = new Arcs_Face();
        else if (pref == "analog") face = new Analog_Face();
        else if (pref == "speed") face = new Speed_Face();
        lvgl.Set_Face(face);

        Time(Get_RTC());
    }

    Sys::TimeInfo Controller::Get_RTC()
    {
        return sysCtrl->Get_RTC();
    }

    void Controller::Set_RTC(Sys::TimeInfo value)
    {
        sysCtrl->Set_RTC(value);
    }

    void Controller::Time(Sys::TimeInfo value)
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
