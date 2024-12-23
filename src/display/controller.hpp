#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP


#include "sys/state.hpp"

#include "display/display.hpp"
#include "display/eink.hpp"
#include "display/lvgl.hpp"

#include <cstdint>


namespace Display
{
    class Controller
    {
        private:
            inline static Controller *theInstance;

            Sys::State *state;

            Display::Manager manager;

            Display::EInk display;
            Display::LVGL lvgl;

        public:
            Controller();
            Controller(uint16_t displayWidth, uint16_t displayHeight, Sys::SPIController ctrl, Sys::State *sysState);
            ~Controller();

            static Controller *Instance(Controller *cur = nullptr);
            Manager Get_Manager();

            void Init();
            void Process();

            void Update_Time(Sys::TimeInfo value);
            void Alert_Send(Sys::AlertInfo alert);
            void Event_Send(Sys::EventInfo event);

            void Button(uint8_t b);
    };
}


#endif  /* CONTROLLER_HPP */
