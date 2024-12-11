#ifndef LVGL_HPP
#define LVGL_HPP


#include "display/display.hpp"
#include "sys/state.hpp"

#include "lvgl.h"

#include <cstdint>
#include <vector>


namespace Display
{
    class LVGL
    {
        private:
            Sys::State *state;

            Display::Manager manager;
            std::vector<uint8_t> buf1;

            lv_obj_t *faceScreen;
            lv_obj_t *time;
            lv_obj_t *date;

            lv_obj_t *alertScreen;
            lv_obj_t *source;
            lv_obj_t *title;
            lv_obj_t *body;

            lv_obj_t *activeScreen;
            lv_obj_t *alertsList;

        public:
            LVGL();
            LVGL(Display::Manager man, Sys::State *sysState);

            void Init();
            void Create();
            static void Flush(lv_display_t *display, const lv_area_t *area, uint8_t *px_map);

            void Time(Sys::Time value);
            void Alert(Sys::Alert alert);

            /* [1 - - - 3]
             * |  - - -  |
             * |  - - -  |
             * [2 - - - 4]
            /* Button One: Universal return to face button */
            void Button_One();
            /* Button Two: Open active screens/tasks */
            void Button_Two();
            /* Button Three: Multi-purpose #1, confirm, scroll up, dismiss, etc. */
            void Button_Three();
            /* Button Four: Multi-purpose #2, cancel, scroll down, etc. */
            void Button_Four();
    };
}


#endif  /* LVGL_HPP */
