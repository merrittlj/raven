#include "display/lvgl.hpp"
#include "display/controller.hpp"
#include "sys/state.hpp"
#include "ble/uuid.hpp"
#include "services/info.hpp"

#include "stm32wbxx_hal.h"
#include "lvgl.h"
#include "src/misc/lv_timer_private.h"


    LV_FONT_DECLARE(axel_ui)  /* 22 bold */
    LV_FONT_DECLARE(axel_text)  /* 20 regular */
LV_FONT_DECLARE(tag)  /* 110 regular */

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
    {}

    LVGL::LVGL(Display::Manager man, Sys::State *sysState, Haptic::Controller *ctrl, BLE::InfoService *infoService)
    {
        manager = man;
        state = sysState;
        hapticCtrl = ctrl;
        infoServ = infoService;
    }

    void LVGL::Init()
    {
        lv_init();
        lv_tick_set_cb(HAL_GetTick);

        lv_display_t *eInk = lv_display_create(manager.width, manager.height);
        lv_display_set_antialiasing(eInk, false);
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
        lv_style_set_text_font(&texts, &axel_text);

        tagScreen = lv_screen_active();
        lv_obj_t *tagText = lv_label_create(tagScreen);
        lv_obj_add_style(tagText, &texts, 0);
        lv_label_set_text(tagText, "Raven");
        lv_obj_set_style_text_font(tagText, &tag, 0);
        lv_obj_align(tagText, LV_ALIGN_CENTER, 0, 0);

        alertScreen = lv_obj_create(NULL);
        static lv_style_t box;
        lv_style_set_border_width(&box, 2);
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
        lv_obj_set_style_text_font(source, &axel_ui, 0);
        lv_obj_set_style_max_width(source, 185, 0);
        lv_obj_align(source, LV_ALIGN_TOP_LEFT, 15, 10);

        title = lv_label_create(alertScreen);
        lv_obj_add_style(title, &texts, 0);
        lv_label_set_text(title, "Alert Title");
        lv_obj_set_style_text_font(title, &axel_ui, 0);
        lv_obj_set_style_max_width(title, 185, 0);
        lv_obj_align(title, LV_ALIGN_TOP_LEFT, 15, 45);

        body = lv_label_create(alertScreen);
        lv_obj_add_style(body, &texts, 0);
        lv_label_set_text(body, "Alert Body");
        lv_obj_set_style_text_font(body, &axel_text, 0);
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
        lv_obj_set_style_text_font(activeTitle, &axel_ui, 0);
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
        lv_obj_set_style_text_font(navInstruction, &axel_ui, 0);
        lv_obj_align(navInstruction, LV_ALIGN_BOTTOM_MID, 0, 0);

        navDistance = lv_label_create(navScreen);
        lv_obj_add_style(navDistance, &texts, 0);
        lv_label_set_text(navDistance, "Distance");
        lv_obj_set_style_text_font(navDistance, &axel_ui, 0);
        lv_obj_align(navDistance, LV_ALIGN_LEFT_MID, 10, 0);

        navETA = lv_label_create(navScreen);
        lv_obj_add_style(navETA, &texts, 0);
        lv_label_set_text(navETA, "ETA");
        lv_obj_set_style_text_font(navETA, &axel_ui, 0);
        lv_obj_align(navETA, LV_ALIGN_RIGHT_MID, -10, 0);

        navAction = lv_image_create(navScreen);
        lv_image_set_src(navAction, &flag);
        lv_obj_align(navAction, LV_ALIGN_CENTER, 0, -10);
        lv_obj_move_background(navAction);


        musicScreen = lv_obj_create(NULL);

        static lv_style_t flexBox;
        lv_style_set_border_width(&flexBox, 2);
        lv_style_set_border_color(&flexBox, lv_color_hex(0x000000));
        lv_style_set_bg_color(&flexBox, lv_color_hex(0xffffff));
        lv_style_set_bg_opa(&flexBox, LV_OPA_100);
        lv_style_set_radius(&flexBox, 5);
        lv_style_set_pad_top(&flexBox, 1);
        lv_style_set_pad_bottom(&flexBox, 1);
        lv_style_set_pad_left(&flexBox, 3);
        lv_style_set_pad_right(&flexBox, 3);


        musicTrack = lv_label_create(musicScreen);
        lv_obj_add_style(musicTrack, &texts, 0);
        lv_obj_add_style(musicTrack, &flexBox, 0);
        lv_label_set_text(musicTrack, "Track");
        lv_obj_set_style_text_font(musicTrack, &axel_text, 0);
        lv_obj_align(musicTrack, LV_ALIGN_BOTTOM_LEFT, 0, -25);

        musicArtist = lv_label_create(musicScreen);
        lv_obj_add_style(musicArtist, &texts, 0);
        lv_obj_add_style(musicArtist, &flexBox, 0);
        lv_label_set_text(musicArtist, "Artist");
        lv_obj_set_style_text_font(musicArtist, &axel_text, 0);
        lv_obj_align(musicArtist, LV_ALIGN_BOTTOM_LEFT, 0, 0);

        musicAlbum = lv_label_create(musicScreen);
        lv_obj_add_style(musicAlbum, &texts, 0);
        lv_label_set_text(musicAlbum, "Album");
        lv_obj_set_style_text_font(musicAlbum, &axel_text, 0);
        lv_obj_align(musicAlbum, LV_ALIGN_BOTTOM_MID, 0, -20);
        lv_obj_add_flag(musicAlbum, LV_OBJ_FLAG_HIDDEN);  /* We will display album art anyways */

        musicBG = lv_image_create(musicScreen);
        lv_image_set_src(musicBG, &flag);
        lv_obj_align(musicBG, LV_ALIGN_CENTER, 0, 0);
        lv_obj_move_background(musicBG);


        summaryScreen = lv_obj_create(NULL);

        summaryDateTime = lv_label_create(summaryScreen);
        lv_obj_add_style(summaryDateTime, &texts, 0);
        lv_label_set_text(summaryDateTime, "x/x/x xx:xx");
        lv_obj_set_style_text_font(summaryDateTime, &axel_text, 0);
        lv_obj_align(summaryDateTime, LV_ALIGN_TOP_LEFT, 0, 0);

        summaryBattery = lv_label_create(summaryScreen);
        lv_obj_add_style(summaryBattery, &texts, 0);
        lv_label_set_text(summaryBattery, "xx%");
        lv_obj_set_style_text_font(summaryBattery, &axel_text, 0);
        lv_obj_align(summaryBattery, LV_ALIGN_TOP_MID, 0, 0);

        summaryWeather = lv_label_create(summaryScreen);
        lv_obj_add_style(summaryWeather, &texts, 0);
        lv_label_set_text(summaryWeather, "xxF");
        lv_obj_set_style_text_font(summaryWeather, &axel_text, 0);
        lv_obj_align(summaryWeather, LV_ALIGN_TOP_RIGHT, 0, 0);

        /* summaryRecent = Create_List(summaryScreen, "Recent"); */
        /* summaryUpcoming = Create_List(summaryScreen, "Upcoming"); */


        lv_timer_t *checkUpdate = lv_timer_create(LVGL::Timer_Check_Update, 500, this);
        lv_timer_set_repeat_count(checkUpdate, -1);
        lv_timer_enable(checkUpdate);
    }

    void LVGL::Timer_Check_Update(lv_timer_t *timer)
    {
        LVGL *data = static_cast<LVGL *>(timer->user_data);

        /* If to update, set timer from saved sys state value */
        if (data->state->App_Flag_Get(Sys::State::App_Flag::LOGIC_TIME_UPDATE_PENDING) == Sys::State::Flag_Val::SET) {
            data->state->Display_Time();
            data->state->App_Flag_Reset(Sys::State::App_Flag::LOGIC_TIME_UPDATE_PENDING);
        }
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

    void LVGL::Refresh()
    {
        lv_obj_invalidate(lv_screen_active());
    }

    void LVGL::Set_Face(Face *value)
    {
        face = value;
        face->Create();
    }

    void LVGL::Tag()
    {
        lv_scr_load(tagScreen);
    }

    void LVGL::Summary()
    {
        Sys::TimeInfo timeInfo = state->Get_Time();

        std::string time = (timeInfo.hour < 10 ? "0" : "") + std::to_string(timeInfo.hour) + ":" + (timeInfo.minute < 10 ? "0" : "") + std::to_string(timeInfo.minute);
        std::string date = std::to_string(timeInfo.month) + "/" + std::to_string(timeInfo.day) + "/" + std::to_string(timeInfo.year);
        lv_label_set_text(summaryDateTime, (date + " " + time).c_str());

        /* Sys::WeatherInfo batteryInfo = state->Get_Battery(); */
        /* lv_label_set_text(summaryBattery, std::to_string(batteryInfo.percent) + "%"); */

        Sys::WeatherInfo weatherInfo = state->Get_Weather();
        lv_label_set_text(summaryWeather, weatherInfo.weather.c_str());

        /* Recent alerts */
        std::vector<Sys::AlertInfo> *stateAlerts = state->Get_Alerts();
        alertsList = Create_List(alertsListScreen, "Alerts");
        for (Sys::AlertInfo alert : *stateAlerts) {
            lv_list_add_button(alertsList, NULL, (alert.source).c_str());
        }

        lv_scr_load(summaryScreen);
    }

    void LVGL::Time(Sys::TimeInfo value)
    {
        if (lv_screen_active() == tagScreen) hapticCtrl->Vibrate_Pulse(500);
        face->Draw(value);
    }

    void LVGL::Alert(Sys::AlertInfo info)
    {
        /* Better UX to have before load rather than after */
        hapticCtrl->Vibrate_Pulse(100);
        Sys::Delay(30);
        hapticCtrl->Vibrate_Pulse(50);

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

    std::string LVGL::Truncate_Text(std::string text, uint32_t limit)
    {
        /* Note: assumes axel_text font! */
        lv_point_t p;
        std::string newText = text;
        lv_text_get_size(&p, newText.c_str(), &axel_text, 0, 0, LV_COORD_MAX, LV_TEXT_FLAG_EXPAND);
        if ((uint32_t)p.x > limit) {
            lv_point_t p2;
            lv_text_get_size(&p2, ">", &axel_text, 0, 0, LV_COORD_MAX, LV_TEXT_FLAG_EXPAND);
            do {
                newText.pop_back();
                lv_text_get_size(&p, newText.c_str(), &axel_text, 0, 0, LV_COORD_MAX, LV_TEXT_FLAG_EXPAND);
            } while ((uint32_t)(p.x + p2.x) > limit);
            newText += ">";
        }

        return newText;
    }

    void LVGL::Music(Sys::MusicInfo info)
    {
        lv_label_set_text(musicTrack, Truncate_Text(info.track, 200).c_str());
        lv_label_set_text(musicArtist, Truncate_Text(info.artist, 200).c_str());
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
            if ((Sys::Screen)i == Sys::Screen::SUMMARY) lv_list_add_button(activeList, NULL, "Summary");  /* Only accessed through shortcut */
            if ((Sys::Screen)i == Sys::Screen::ALERT) continue;  /* Alert is inaccessible directly, but it shouldn't be active anyways */
            if ((Sys::Screen)i == Sys::Screen::ACTIVE) continue;  /* Shouldn't be set active, text is redundant */
            if ((Sys::Screen)i == Sys::Screen::ALERTS_LIST) lv_list_add_button(activeList, NULL, "Unread Alerts");
            if ((Sys::Screen)i == Sys::Screen::EVENTS_LIST) lv_list_add_button(activeList, NULL, "Upcoming Events");
            if ((Sys::Screen)i == Sys::Screen::NAVIGATION) lv_list_add_button(activeList, NULL, "Navigation");
            if ((Sys::Screen)i == Sys::Screen::MUSIC) lv_list_add_button(activeList, NULL, "Music");
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
        hapticCtrl->Vibrate_Pulse(50);
        if (b == 1) {
            /* All screens: load face */
            face->Load_Screen();
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
                face->Load_Screen();
            }
            else if (lv_screen_active() == eventScreen) {
                state->Event_Dismiss(eventIndex);
                /* Deactivate on empty, safe doing here as all dismissals are routed here */
                if (state->Get_Events().size() == 0)
                    state->Screen_Deactivate(Sys::Screen::EVENTS_LIST);
                face->Load_Screen();
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
            /* Music screen: playpause notify */
            else if (lv_screen_active() == musicScreen) {
                uint8_t musicData[1] = {1};
                if (infoServ->Update_Char_Value(BLE::UUID::ExtractUUID16FromLE(infoServ->musicButton.Get_UUID()),
                            infoServ->musicButton.Get_Value_Length(),
                            musicData) != BLE_STATUS_SUCCESS)
                    Sys::Error_Handler();
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
            /* Music screen: next notify */
            else if (lv_screen_active() == musicScreen) {
                uint8_t musicData[1] = {2};
                if (infoServ->Update_Char_Value(BLE::UUID::ExtractUUID16FromLE(infoServ->musicButton.Get_UUID()),
                            infoServ->musicButton.Get_Value_Length(),
                            musicData) != BLE_STATUS_SUCCESS)
                    Sys::Error_Handler();
            }
        }
    }

    void LVGL::Button_Double(uint8_t b1, uint8_t b2)
    {
        hapticCtrl->Vibrate_Pulse(50);
        /* Button 1 & 2 double press */
        /* Button 3 & 4 double press */
        if ((b1 == 1 && b2 == 2) || (b1 == 2 && b2 == 1)) {
            /* Global summary screen */
            Summary();
        }
        if ((b1 == 3 && b2 == 4) || (b1 == 4 && b2 == 3)) {
            /* Alerts list screen: selector */
            if (lv_screen_active() == alertsListScreen) {
                /* We only have two items so double selector only applies for groups */
                if (prevButton == 0)
                    prevButton = 3;  /* TODO: prev button defines */
            }
            /* Music screen: previous notify */
            else if (lv_screen_active() == musicScreen) {
                uint8_t musicData[1] = {3};
                if (infoServ->Update_Char_Value(BLE::UUID::ExtractUUID16FromLE(infoServ->musicButton.Get_UUID()),
                            infoServ->musicButton.Get_Value_Length(),
                            musicData) != BLE_STATUS_SUCCESS)
                    Sys::Error_Handler();
            }
        }
    }
}
