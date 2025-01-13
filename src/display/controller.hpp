#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP


#include "sys/state.hpp"
#include "sys/sys.hpp"
#include "haptic/haptic.hpp"

#include "display/display.hpp"
#include "display/eink.hpp"
#include "display/lvgl.hpp"
#include "services/info.hpp"

#include <cstdint>


namespace Display
{
    class Controller
    {
        private:
            inline static Controller *theInstance;

            Sys::State *state;
            Sys::Controller *sysCtrl;

            BLE::InfoService *info;

            Display::Manager manager;

            Display::EInk display;
            Display::LVGL lvgl;

        public:
            Controller();
            Controller(uint16_t displayWidth, uint16_t displayHeight, Sys::SPI_Controller ctrl, Sys::State *sysState, Sys::Controller *userSys, Haptic::Controller *userHaptic, BLE::InfoService *infoService);
            ~Controller();

            static Controller *Instance(Controller *cur = nullptr);
            Manager Get_Manager();

            Sys::State *Get_State();

            void Init();
            void Process();
            void Refresh();

            void Tag_Screen();
            void Update_Face();
            Sys::TimeInfo Get_RTC();
            void Set_RTC(Sys::TimeInfo value);
            void Time(Sys::TimeInfo value);

            void Alert_Send(Sys::AlertInfo alert);
            void Event_Send(Sys::EventInfo event);
            void Nav_Send(Sys::NavInfo nav);
            void Music_Send(Sys::MusicInfo music);

            void Button(uint8_t b);
            void Button_Double(uint8_t b1, uint8_t b2);
    };
}


#endif  /* CONTROLLER_HPP */
