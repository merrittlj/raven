#ifndef LVGL_HPP
#define LVGL_HPP


#include "display/display.hpp"
#include "display/face.hpp"
#include "sys/state.hpp"
#include "haptic/haptic.hpp"
#include "services/info.hpp"

#include "lvgl.h"

#include <cstdint>
#include <vector>


namespace Display
{
    class LVGL
    {
        private:
            Sys::State *state;
            Haptic::Controller *hapticCtrl;
            BLE::InfoService *infoServ;

            Display::Manager manager;
            std::vector<uint8_t> buf1;

            lv_display_t *eInk;
            static inline bool displayReady = true;

            Face *face = nullptr;

            uint8_t prevButton = 0;

            uint8_t alertIndex;
            uint8_t eventIndex;

            lv_obj_t *tagScreen;

            lv_obj_t *digital;
            lv_obj_t *digitalTime;

            lv_obj_t *alertScreen;
            lv_obj_t *source;
            lv_obj_t *title;
            lv_obj_t *body;
            lv_obj_t *alertBorder;

            lv_obj_t *eventScreen;
            lv_obj_t *eventType;
            lv_obj_t *eventTitle;
            lv_obj_t *eventDesc;
            lv_obj_t *eventTime;
            lv_obj_t *eventRepDur;
            lv_obj_t *eventBorder;

            lv_obj_t *activeScreen;

            lv_obj_t *alertsListScreen;

            lv_obj_t *eventsListScreen;

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

            std::vector<std::string> activeItems;

            void Recreate_Summary();
            void Create_Selectors(lv_obj_t *screen, bool isSummary, std::vector<std::string> items);
            void Active_Screen();
            void Alerts_List_Screen();
            void Events_List_Screen();

            static void Timer_Check_Update(lv_timer_t *timer);

            /* Handles lists with groups(first button press) and items(second button press) */
            uint16_t List_Handler(uint8_t group, uint8_t item);

            void Load_Screen_By_Name(std::string name);

            std::string Truncate_Text(std::string text, uint32_t limit);

        public:
            LVGL();
            LVGL(Display::Manager man, Sys::State *sysState, Haptic::Controller *ctrl, BLE::InfoService *infoService);

            static void Safe_Screen_Load(lv_obj_t *screen);

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
