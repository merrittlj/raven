#ifndef LVGL_HPP
#define LVGL_HPP


#include "display/display.hpp"
#include "sys/state.hpp"
#include "haptic/haptic.hpp"
#include "services/info.hpp"

#include "lvgl.h"

#include <cstdint>
#include <vector>


namespace Display
{
    class Face
    {
        public:
            virtual void Load_Screen();
            virtual void Draw(TimeInfo info);
    };

    class Big_Face : Face
    {
        private:
            lv_obj_t *screen;
            lv_obj_t *time;
            lv_obj_t *date;

        public:
            Big_Face();

            void Load_Screen();
            void Draw(TimeInfo info);
    };

    class Digital_Face : Face
    {
        private:
            lv_obj_t *screen;
            lv_obj_t *time;

        public:
            Digital_Face();

            void Load_Screen();
            void Draw(TimeInfo info);
    };

    class LVGL
    {
        private:
            Sys::State *state;
            Haptic::Controller *hapticCtrl;
            BLE::InfoService *infoServ;

            Display::Manager manager;
            std::vector<uint8_t> buf1;

            Face *face;

            uint8_t prevButton;

            uint8_t alertIndex;
            uint8_t eventIndex;

            lv_obj_t *tagScreen;

            lv_obj_t *digital;
            lv_obj_t *digitalTime;

            lv_obj_t *alertScreen;
            lv_obj_t *source;
            lv_obj_t *title;
            lv_obj_t *body;

            lv_obj_t *eventScreen;

            lv_obj_t *activeScreen;
            lv_obj_t *activeList;

            lv_obj_t *alertsListScreen;
            lv_obj_t *alertsList;

            lv_obj_t *eventsListScreen;
            lv_obj_t *eventsList;

            lv_obj_t *navScreen;
            lv_obj_t *navInstruction;
            lv_obj_t *navDistance;
            lv_obj_t *navETA;
            lv_obj_t *navAction;

            lv_obj_t *musicScreen;
            lv_obj_t *musicTrack;
            lv_obj_t *musicArtist;
            lv_obj_t *musicAlbum;
            lv_obj_t *musicBG;

            lv_obj_t *summaryScreen;
            lv_obj_t *summaryDateTime;
            lv_obj_t *summaryBattery;
            lv_obj_t *summaryWeather;
            lv_obj_t *summaryRecent;
            lv_obj_t *summaryUpcoming;

            lv_obj_t *Create_List(lv_obj_t *screen, std::string text);
            void Active_Screen();
            void Alerts_List_Screen();
            void Events_List_Screen();

            static void Timer_Check_Update(lv_timer_t *timer);

            /* Handles lists with groups(first button press) and items(second button press) */
            uint16_t List_Handler(uint8_t group, uint8_t item);

            std::string Truncate_Text(std::string text, uint32_t limit);

        public:
            LVGL();
            LVGL(Display::Manager man, Sys::State *sysState, Haptic::Controller *ctrl, BLE::InfoService *infoService);

            void Init();
            void Create();
            static void Flush(lv_display_t *display, const lv_area_t *area, uint8_t *px_map);
            void Refresh();

            void Set_Face(Face *value);
            void Load_Face_Screen();
            void Tag();
            void Summary();
            void Time(Sys::TimeInfo value);
            void Alert(Sys::AlertInfo info);
            void Event(Sys::EventInfo info);
            void Nav(Sys::NavInfo info);
            void Music(Sys::MusicInfo info);

            /* [1 - - - 3]
             * |  - - -  |
             * |  - - -  |
             * [2 - - - 4] */
            /* Button One: Universal return to face button */
            /* Button Two: Open active screens/tasks */
            /* Button Three: Multi-purpose #1, confirm, scroll up, dismiss, etc. */
            /* Button Four: Multi-purpose #2, cancel, scroll down, etc. */
            /* Button 3 & 4 double press: Multiple-purpose #1 and #2 pressed simultaneously, group 3 selector */
            void Button(uint8_t b);
            void Button_Double(uint8_t b1, uint8_t b2);
    };
}


#endif  /* LVGL_HPP */
