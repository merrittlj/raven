#include "display/lvgl.hpp"

#include "display/controller.hpp"

#include "sys/state.hpp"

#include "stm32wbxx_hal.h"
#include "lvgl.h"

#include <array>
#include <vector>
#include <string>


#ifndef LV_ATTRIBUTE_MEM_ALIGN
#define LV_ATTRIBUTE_MEM_ALIGN
#endif

LV_FONT_DECLARE(gloock_18_date)
LV_FONT_DECLARE(gloock_70_time)
LV_FONT_DECLARE(axel_22_ui)
LV_FONT_DECLARE(axel_20_text)
LV_FONT_DECLARE(tag)  /* 110 font size */

LV_IMAGE_DECLARE(cont);
LV_IMAGE_DECLARE(cont_left);
LV_IMAGE_DECLARE(cont_right);
LV_IMAGE_DECLARE(turn_left);
LV_IMAGE_DECLARE(turn_slight_left);
LV_IMAGE_DECLARE(turn_sharp_left);
LV_IMAGE_DECLARE(turn_right);
LV_IMAGE_DECLARE(turn_slight_right);
LV_IMAGE_DECLARE(turn_sharp_right);
LV_IMAGE_DECLARE(roundabout_left);
LV_IMAGE_DECLARE(roundabout_right);
LV_IMAGE_DECLARE(uturn);
LV_IMAGE_DECLARE(close);
LV_IMAGE_DECLARE(flag);

namespace Display
{
    LVGL::LVGL()
    {

    }

    LVGL::LVGL(Display::Manager man, Sys::State *sysState)
    {
        manager = man;
        state = sysState;
    }

    void LVGL::Init()
    {
        lv_init();
        lv_tick_set_cb(HAL_GetTick);

        lv_display_t *eInk = lv_display_create(manager.width, manager.height);
        buf1 = std::vector<uint8_t>(manager.Buffer_Size() + 8);
        lv_display_set_buffers(eInk, &buf1[0], NULL, buf1.size(), LV_DISPLAY_RENDER_MODE_DIRECT);  /* TODO: dual buffers & diff render mode */
        lv_display_set_flush_cb(eInk, Flush);
    }

    lv_obj_t *LVGL::Create_List(lv_obj_t *screen, std::string text)
    {
        lv_obj_t *list = lv_list_create(screen);
        lv_obj_set_size(list, 200, 200);
        lv_obj_align(list, LV_ALIGN_TOP_LEFT, 0, 0);
        lv_list_add_text(list, text.c_str());
        return list;
    }

    void LVGL::Create()
    {
        static lv_style_t texts;
        lv_style_init(&texts);
        lv_style_set_text_color(&texts, lv_color_hex(0x000000));
        lv_style_set_text_font(&texts, &gloock_70_time);

        tagScreen = lv_screen_active();
        lv_obj_t *tagText = lv_label_create(tagScreen);
        lv_obj_add_style(tagText, &texts, 0);
        lv_label_set_text(tagText, "Raven");
        lv_obj_set_style_text_font(tagText, &tag, 0);
        lv_obj_align(tagText, LV_ALIGN_CENTER, 0, 0);


        faceScreen = lv_obj_create(NULL);

        time = lv_label_create(faceScreen);
        lv_obj_add_style(time, &texts, 0);
        lv_label_set_text(time, "00:00");
        lv_obj_align(time, LV_ALIGN_CENTER, 0, -10);

        date = lv_label_create(faceScreen);
        lv_obj_add_style(date, &texts, 0);
        lv_label_set_text(date, "Month Day Year");
        lv_obj_set_style_text_font(date, &gloock_18_date, 0);
        lv_obj_align(date, LV_ALIGN_CENTER, 0, 45);


        alertScreen = lv_obj_create(NULL);
        static lv_style_t box;
        lv_style_set_border_width(&box, 3);
        lv_style_set_border_color(&box, lv_color_hex(0x000000));
        lv_style_set_bg_color(&box, lv_color_hex(0xffffff));
        lv_style_set_radius(&box, 5);

        lv_obj_t *sourceBox = lv_obj_create(alertScreen);
        lv_obj_add_style(sourceBox, &box, 0);
        lv_obj_align(sourceBox, LV_ALIGN_TOP_LEFT, 5, 5);
        lv_obj_move_background(sourceBox);
        lv_obj_set_size(sourceBox, 190, 30);

        lv_obj_t *titleBox = lv_obj_create(alertScreen);
        lv_obj_add_style(titleBox, &box, 0);
        lv_obj_align(titleBox, LV_ALIGN_TOP_LEFT, 5, 40);
        lv_obj_move_background(titleBox);
        lv_obj_set_size(titleBox, 190, 30);

        lv_obj_t *bodyBox = lv_obj_create(alertScreen);
        lv_obj_add_style(bodyBox, &box, 0);
        lv_obj_align(bodyBox, LV_ALIGN_TOP_LEFT, 5, 75);
        lv_obj_move_background(bodyBox);
        lv_obj_set_size(bodyBox, 190, 120);

        source = lv_label_create(alertScreen);
        lv_obj_add_style(source, &texts, 0);
        lv_label_set_text(source, "Alert Source");
        lv_obj_set_style_text_font(source, &axel_22_ui, 0);
        lv_obj_set_style_max_width(source, 185, 0);
        lv_obj_align(source, LV_ALIGN_TOP_LEFT, 15, 10);

        title = lv_label_create(alertScreen);
        lv_obj_add_style(title, &texts, 0);
        lv_label_set_text(title, "Alert Title");
        lv_obj_set_style_text_font(title, &axel_22_ui, 0);
        lv_obj_set_style_max_width(title, 185, 0);
        lv_obj_align(title, LV_ALIGN_TOP_LEFT, 15, 45);

        body = lv_label_create(alertScreen);
        lv_obj_add_style(body, &texts, 0);
        lv_label_set_text(body, "Alert Body");
        lv_obj_set_style_text_font(body, &axel_20_text, 0);
        lv_obj_set_style_max_width(body, 185, 0);
        lv_obj_align(body, LV_ALIGN_TOP_LEFT, 15, 85);

        lv_obj_t *alertBorder = lv_obj_create(alertScreen);
        lv_obj_add_style(alertBorder, &box, 0);
        lv_obj_align(alertBorder, LV_ALIGN_CENTER, 0, 0);
        lv_obj_move_background(alertBorder);
        lv_obj_set_size(alertBorder, 200, 200);


        eventScreen = lv_obj_create(NULL);

        lv_obj_t *eventBorder = lv_obj_create(eventScreen);
        lv_obj_add_style(eventBorder, &box, 0);
        lv_obj_align(eventBorder, LV_ALIGN_CENTER, 0, 0);
        lv_obj_move_background(eventBorder);
        lv_obj_set_size(eventBorder, 200, 200);


        activeScreen = lv_obj_create(NULL);
        lv_obj_t *activeTitle = lv_label_create(activeScreen);
        lv_obj_add_style(activeTitle, &texts, 0);
        lv_label_set_text(activeTitle, "Active Screens");
        lv_obj_set_style_text_font(activeTitle, &axel_22_ui, 0);
        lv_obj_align(activeTitle, LV_ALIGN_CENTER, 0, 0);

        activeList = Create_List(activeScreen, "Screens");


        alertsListScreen = lv_obj_create(NULL);
        alertsList = Create_List(alertsListScreen, "Alerts");


        eventsListScreen = lv_obj_create(NULL);
        eventsList = Create_List(eventsListScreen, "Events");


        navScreen = lv_obj_create(NULL);
        navInstruction = lv_label_create(navScreen);
        lv_obj_add_style(navInstruction, &texts, 0);
        lv_label_set_text(navInstruction, "Instruction");
        lv_obj_set_style_max_width(navInstruction, 185, 0);
        lv_obj_set_style_text_font(navInstruction, &axel_22_ui, 0);
        lv_obj_align(navInstruction, LV_ALIGN_BOTTOM_MID, 0, 0);

        navDistance = lv_label_create(navScreen);
        lv_obj_add_style(navDistance, &texts, 0);
        lv_label_set_text(navDistance, "Distance");
        lv_obj_set_style_text_font(navDistance, &axel_22_ui, 0);
        lv_obj_align(navDistance, LV_ALIGN_LEFT_MID, 10, 0);

        navETA = lv_label_create(navScreen);
        lv_obj_add_style(navETA, &texts, 0);
        lv_label_set_text(navETA, "ETA");
        lv_obj_set_style_text_font(navETA, &axel_22_ui, 0);
        lv_obj_align(navETA, LV_ALIGN_RIGHT_MID, -10, 0);

        navAction = lv_image_create(navScreen);
        lv_image_set_src(navAction, &flag);
        lv_obj_align(navAction, LV_ALIGN_CENTER, 0, -10);
        lv_obj_move_background(navAction);


        musicScreen = lv_obj_create(NULL);

        musicTrack = lv_label_create(musicScreen);
        lv_obj_add_style(musicTrack, &texts, 0);
        lv_label_set_text(musicTrack, "Track");
        lv_obj_set_style_text_font(musicTrack, &axel_22_ui, 0);
        lv_obj_align(musicTrack, LV_ALIGN_TOP_LEFT, 10, 10);

        musicArtist = lv_label_create(musicScreen);
        lv_obj_add_style(musicArtist, &texts, 0);
        lv_label_set_text(musicArtist, "Artist");
        lv_obj_set_style_text_font(musicArtist, &axel_20_text, 0);
        lv_obj_align(musicArtist, LV_ALIGN_TOP_LEFT, 10, 50);

        musicAlbum = lv_label_create(musicScreen);
        lv_obj_add_style(musicAlbum, &texts, 0);
        lv_label_set_text(musicAlbum, "Album");
        lv_obj_set_style_text_font(musicAlbum, &axel_20_text, 0);
        lv_obj_align(musicAlbum, LV_ALIGN_BOTTOM_MID, 0, -20);
        lv_obj_add_flag(musicAlbum, LV_OBJ_FLAG_HIDDEN);  /* We will display album art anyways */

        /* Hide for album art testing */
        lv_obj_add_flag(musicArtist, LV_OBJ_FLAG_HIDDEN);  
        lv_obj_add_flag(musicTrack, LV_OBJ_FLAG_HIDDEN);  

        musicBG = lv_image_create(musicScreen);
        lv_image_set_src(musicBG, &flag);
        lv_obj_align(musicBG, LV_ALIGN_CENTER, 0, 0);
        lv_obj_move_background(musicBG);


        aboutScreen = lv_obj_create(NULL);

        lv_obj_t *ravenIcon = lv_image_create(aboutScreen);
        lv_image_set_src(ravenIcon, &flag);
        lv_obj_align(ravenIcon, LV_ALIGN_CENTER, 0, 0);

        lv_obj_t *version = lv_label_create(aboutScreen);
        lv_obj_add_style(version, &texts, 0);
        lv_label_set_text(version, "V0.7");
        lv_obj_set_style_text_font(version, &axel_22_ui, 0);
        lv_obj_align(version, LV_ALIGN_CENTER, 0, 30);

        lv_obj_t *edition = lv_label_create(aboutScreen);
        lv_obj_add_style(edition, &texts, 0);
        lv_label_set_text(edition, "Edition #1");
        lv_obj_set_style_text_font(edition, &axel_22_ui, 0);
        lv_obj_align(edition, LV_ALIGN_CENTER, 0, 50);

        lv_obj_t *credit = lv_label_create(aboutScreen);
        lv_obj_add_style(credit, &texts, 0);
        lv_label_set_text(credit, "Designer/Programmer:\nLucas Merritt\n(merrittlj)");
        lv_obj_set_style_text_font(credit, &axel_22_ui, 0);
        lv_obj_align(credit, LV_ALIGN_CENTER, 0, 70);
    }

    void LVGL::Flush(lv_display_t *display, const lv_area_t *area, uint8_t *px_map)
    {
        Manager man = Controller::Instance()->Get_Manager();

        uint8_t *screen_data = px_map + 8;

        std::vector<uint8_t> *handlingBuffer = man.displayCallback->GetBuf();
        *handlingBuffer = std::vector<uint8_t>(screen_data, screen_data + man.Buffer_Size());

        man.displayCallback->Init();
        man.displayCallback->Display();
        lv_display_flush_ready(display);
    }

    void LVGL::Time(Sys::TimeInfo value)
    {
        lv_label_set_text(time, ((value.hour < 10 ? "0" : "") + std::to_string(value.hour) + ":" + (value.minute < 10 ? "0" : "") + std::to_string(value.minute)).c_str());
        const std::string months[12] = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};
        std::string day = std::to_string(value.day);
        if (value.day % 10 == 1 && value.day != 11) day += "st";
        else if (value.day % 10 == 2 && value.day != 12) day += "nd";
        else if (value.day % 10 == 3 && value.day != 13) day += "rd";
        else day += "th";
        lv_label_set_text(date, (months[value.month - 1] + " " + day).c_str());

        lv_scr_load(faceScreen);
    }

    void LVGL::Alert(Sys::AlertInfo info)
    {
        lv_label_set_text(source, info.source.c_str());
        lv_label_set_text(title, info.title.c_str());
        lv_label_set_text(body, info.body.c_str());

        lv_scr_load(alertScreen);
        state->Screen_Activate(Sys::Screen::ALERTS_LIST);  /* Until dismissal, activate unread alerts */
    }

    void LVGL::Event(Sys::EventInfo info)
    {
        /* set event texts */

        lv_scr_load(eventScreen);
        state->Screen_Activate(Sys::Screen::EVENTS_LIST);
    }

    void LVGL::Nav(Sys::NavInfo info)
    {
        lv_label_set_text(navInstruction, info.instruction.c_str());
        lv_label_set_text(navDistance, info.distance.c_str());
        lv_label_set_text(navETA, info.eta.c_str());

        if (info.action == "continue") lv_image_set_src(navAction, &cont);
        if (info.action == "continue-left") lv_image_set_src(navAction, &cont_left);
        if (info.action == "continue-right") lv_image_set_src(navAction, &cont_right);
        if (info.action == "turn-left") lv_image_set_src(navAction, &turn_left);
        if (info.action == "turn-slight-left") lv_image_set_src(navAction, &turn_slight_left);
        if (info.action == "turn-sharp-left") lv_image_set_src(navAction, &turn_sharp_left);
        if (info.action == "turn-right") lv_image_set_src(navAction, &turn_right);
        if (info.action == "turn-slight-right") lv_image_set_src(navAction, &turn_slight_right);
        if (info.action == "turn-sharp-right") lv_image_set_src(navAction, &turn_sharp_right);
        if (info.action == "roundabout-left") lv_image_set_src(navAction, &roundabout_left);
        if (info.action == "roundabout-right") lv_image_set_src(navAction, &roundabout_right);
        if (info.action == "uturn") lv_image_set_src(navAction, &uturn);
        if (info.action == "close") lv_image_set_src(navAction, &close);
        if (info.action == "flag") lv_image_set_src(navAction, &flag);

        if (!state->Is_Screen_Active(Sys::Screen::NAVIGATION)) {
            lv_scr_load(navScreen);
            state->Screen_Activate(Sys::Screen::NAVIGATION);
        }
    }

    void LVGL::Music(Sys::MusicInfo info)
    {
        lv_label_set_text(musicTrack, info.track.c_str());
        lv_label_set_text(musicArtist, info.artist.c_str());
        lv_label_set_text(musicAlbum, info.album.c_str());

        static lv_image_dsc_t albumArt;

        /* The first 8 bytes of the data should be a palette */
        const size_t dataSize = 5000 + 8;
        albumArt.header.magic = LV_IMAGE_HEADER_MAGIC;
        albumArt.header.flags = 0;
        albumArt.header.w = 200;
        albumArt.header.h = 200;
        albumArt.header.stride = 25;
        albumArt.header.cf = LV_COLOR_FORMAT_I1;
        albumArt.data_size = dataSize;

        static uint8_t builder[dataSize];
        /* Apparently data is stored w/ a palette, 1st 4 bytes are black, 2nd 4 bytes are white */
        uint8_t palette[8] = {0x00,0x00,0x00,0xff,   0xff,0xff,0xff,0xff};
        memcpy(builder, palette, 8);
        memcpy(&builder[8], info.albumArt, dataSize - 8);

        /* Checkerboard */
        /* for (uint32_t i = 8; i < dataSize; ++i) { */
        /*     // Alternate between 0x55 and 0xAA to create a checkerboard pattern */
        /*     if ((i / albumArt.header.stride) % 2 == 0) { */
        /*         cb[i] = 0x55;  // 01010101 (checkerboard-like pattern) */
        /*     } else { */
        /*         cb[i] = 0xAA;  // 10101010 (opposite pattern) */
        /*     } */
        /* } */

        albumArt.data = builder;

        lv_image_set_src(musicBG, &albumArt);

        if (!state->Is_Screen_Active(Sys::Screen::MUSIC)) {
            lv_scr_load(musicScreen);
            state->Screen_Activate(Sys::Screen::MUSIC);
        }
    }

    void LVGL::Active_Screen()
    {
        std::array<uint8_t, (size_t)Sys::Screen::Enum_Length> screens = state->Get_Active_Screens();
        for (size_t i = 0; i < screens.size(); ++i) {
            uint8_t s = screens.at(i);
            if (!s) continue;
            if ((Sys::Screen)i == Sys::Screen::TAG) continue; /* Accessible through startup/shutdown */
            if ((Sys::Screen)i == Sys::Screen::FACE) lv_list_add_button(activeList, NULL, "Watch Face");
            if ((Sys::Screen)i == Sys::Screen::ALERT) continue;  /* Alert is inaccessible directly, but it shouldn't be active anyways */
            if ((Sys::Screen)i == Sys::Screen::ACTIVE) continue;  /* Shouldn't be set active, text is redundant */
            if ((Sys::Screen)i == Sys::Screen::ALERTS_LIST) lv_list_add_button(activeList, NULL, "Unread Alerts");
            if ((Sys::Screen)i == Sys::Screen::EVENTS_LIST) lv_list_add_button(activeList, NULL, "Upcoming Events");
            if ((Sys::Screen)i == Sys::Screen::NAVIGATION) lv_list_add_button(activeList, NULL, "Navigation");
            if ((Sys::Screen)i == Sys::Screen::MUSIC) lv_list_add_button(activeList, NULL, "Music");
            if ((Sys::Screen)i == Sys::Screen::ABOUT) continue;  /* Only accessed through shortcut */
        }
        lv_scr_load(activeScreen);
    }

    void LVGL::Alerts_List_Screen()
    {
        std::vector<Sys::AlertInfo> *stateAlerts = state->Get_Alerts();
        alertsList = Create_List(alertsListScreen, "Alerts");
        for (Sys::AlertInfo alert : *stateAlerts) {
            lv_list_add_button(alertsList, NULL, (alert.source).c_str());
        }
        lv_scr_load(alertsListScreen);
    }

    void LVGL::Events_List_Screen()
    {
        std::vector<Sys::EventInfo> stateEvents = state->Get_Events();
        eventsList = Create_List(eventsListScreen, "Events");
        for (Sys::EventInfo event : stateEvents) {
            lv_list_add_button(eventsList, NULL, (event.title).c_str());
        }
        lv_scr_load(eventsListScreen);
    }

    uint16_t LVGL::List_Handler(uint8_t group, uint8_t item)
    {
        return (group - 1) * 2 + (item - 1);
    }

    void LVGL::Button(uint8_t b)
    {
        if (b == 1) {
            /* All screens: load face */
            lv_scr_load(faceScreen);
        }

        if (b == 2) {
            /* All screens: load active screen */
            lv_scr_load(activeScreen);
        }

        if (b == 3) {
            /* Alert screen: dismiss alert */
            if (lv_screen_active() == alertScreen) {
                state->Alert_Dismiss(alertIndex);
                /* Deactivate on empty, safe doing here as all dismissals are routed here */
                if (state->Get_Alerts()->size() == 0)
                    state->Screen_Deactivate(Sys::Screen::ALERTS_LIST);
                lv_scr_load(faceScreen);
            }
            else if (lv_screen_active() == eventScreen) {
                state->Event_Dismiss(eventIndex);
                /* Deactivate on empty, safe doing here as all dismissals are routed here */
                if (state->Get_Events().size() == 0)
                    state->Screen_Deactivate(Sys::Screen::EVENTS_LIST);
                lv_scr_load(faceScreen);
            }
            /* Active screen: selector */
            else if (lv_screen_active() == activeScreen) {
                /* Implement alerts/events list selectors */
            }
            /* Alerts list: selector */
            else if (lv_screen_active() == alertsListScreen) {
                /* If the group has been selected */
                if (prevButton > 0) {
                    uint16_t index = List_Handler(prevButton, 1);
                    prevButton = 0;
                    std::vector<Sys::AlertInfo> *stateAlerts = state->Get_Alerts();
                    if (index < stateAlerts->size()) {
                        alertIndex = index;
                        Alert(stateAlerts->at(alertIndex));
                    }
                }
                else prevButton = 1;
            }
            /* Events list: selector */
            else if (lv_screen_active() == eventsListScreen) {
                /* If the group has been selected */
                if (prevButton > 0) {
                    uint16_t index = List_Handler(prevButton, 1);
                    prevButton = 0;
                    std::vector<Sys::EventInfo> stateEvents = state->Get_Events();
                    if (index < stateEvents.size()) {
                        eventIndex = index;
                        Event(stateEvents.at(eventIndex));
                    }
                }
                else prevButton = 1;
            }
        }

        if (b == 4) {
            /* Alert screen: shortcut to alert list */
            if (lv_screen_active() == alertScreen) {
                Alerts_List_Screen();
            }
            /* Event screen: shortcut to event list */
            else if (lv_screen_active() == eventScreen) {
                Events_List_Screen();
            }
            /* Active screen: selector */
            else if (lv_screen_active() == activeScreen) {
            }
            /* Alerts list screen: selector */
            else if (lv_screen_active() == alertsListScreen) {
                /* If the group has been selected */
                if (prevButton > 0) {
                    uint16_t index = List_Handler(prevButton, 2);
                    prevButton = 0;
                    std::vector<Sys::AlertInfo> *stateAlerts = state->Get_Alerts();
                    if (index < stateAlerts->size())
                        Alert(stateAlerts->at(index));
                }
                else prevButton = 2;
            }
            /* Events list: selector */
            else if (lv_screen_active() == eventsListScreen) {
                /* If the group has been selected */
                if (prevButton > 0) {
                    uint16_t index = List_Handler(prevButton, 2);
                    prevButton = 0;
                    std::vector<Sys::EventInfo> stateEvents = state->Get_Events();
                    if (index < stateEvents.size())
                        Event(stateEvents.at(index));
                }
                else prevButton = 2;
            }
        }
    }

    void LVGL::Button_Double(uint8_t b1, uint8_t b2)
    {
        /* Button 1 & 2 double press */
        /* Button 3 & 4 double press */
        if ((b1 == 1 && b2 == 2) || (b1 == 2 && b2 == 1)) {
            /* Global about screen */
            lv_scr_load(aboutScreen);
        }
        if ((b1 == 3 && b2 == 4) || (b1 == 4 && b2 == 3)) {
            /* Alerts list screen: selector */
            if (lv_screen_active() == alertsListScreen) {
                /* We only have two items so double selector only applies for groups */
                if (prevButton == 0)
                    prevButton = 3;  /* TODO: prev button defines */
            }
        }
    }
}
