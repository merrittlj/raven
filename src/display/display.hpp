#ifndef DISPLAY_HPP
#define DISPLAY_HPP


#include "display/eink.hpp"
#include "display/lvgl.hpp"

#include <cstdint>


namespace Display
{
    struct Manager
    {
        uint16_t width;
        uint16_t height;

        EInk *displayCallback;

        uint16_t Width_Bytes();
        uint16_t Buffer_Size();
    };

        class Controller
    {
        private:
            inline static Controller *theInstance;

            Display::Manager manager;

            Display::EInk display;
            Display::LVGL lvgl;

        public:
            Controller(uint16_t displayWidth, uint16_t displayHeight, Sys::SPIController ctrl, Sys::State *sysState);
            ~Controller();

            static Controller *Instance(Controller *cur = nullptr);
            Manager Get_Manager();

            void Init();
            void Process();

            void Update_Time(Sys::Time value);
            void Alert_Send(Sys::Alert alert);

            void Button_One();
            void Button_Two();
            void Button_Three();
            void Button_Four();
    };
}


#endif /* DISPLAY_HPP */
