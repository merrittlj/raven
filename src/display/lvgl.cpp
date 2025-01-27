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

    void LVGL::Safe_Screen_Load(lv_obj_t *screen)
    {
        if (displayReady) lv_scr_load(screen);
    }

    void LVGL::Init()
    {
        lv_init();
        lv_tick_set_cb(HAL_GetTick);

        eInk = lv_display_create(manager.width, manager.height);
        lv_display_set_antialiasing(eInk, false);
        buf1 = std::vector<uint8_t>(manager.Buffer_Size() + 8);
        lv_display_set_buffers(eInk, &buf1[0], NULL, buf1.size(), LV_DISPLAY_RENDER_MODE_DIRECT);  /* TODO: dual buffers & diff render mode */
        lv_display_set_flush_cb(eInk, Flush);
    }

    void LVGL::Create_Selectors(lv_obj_t *screen, std::vector<std::string> items)
    {
        static lv_style_t styleLine;
        lv_style_init(&styleLine);
        lv_style_set_line_width(&styleLine, 2);
        lv_style_set_line_rounded(&styleLine, true);
        lv_style_set_line_color(&styleLine, lv_color_hex(0x000000));

        static lv_style_t texts;
        lv_style_init(&texts);
        lv_style_set_text_color(&texts, lv_color_hex(0x000000));
        lv_style_set_text_font(&texts, &axel_text);


        bool isSummary = (lv_screen_active() == summaryScreen);

        const uint8_t lineHeight = (200 / 9);
        uint8_t curRow = 0;

        lv_point_precise_t *vertPoints;
        if (isSummary) vertPoints = new lv_point_precise_t[2] {{(lv_value_precise_t)100, (lv_value_precise_t)lineHeight}, {(lv_value_precise_t)100, (lv_value_precise_t)200}};
        else vertPoints = new lv_point_precise_t[2] {{(lv_value_precise_t)30, (lv_value_precise_t)0}, {(lv_value_precise_t)30, (lv_value_precise_t)200}};

        lv_obj_t *vertLine;
        vertLine = lv_line_create(screen);
        lv_line_set_points(vertLine, vertPoints, 2);
        lv_obj_add_style(vertLine, &styleLine, 0);
        lv_obj_align(vertLine, LV_ALIGN_TOP_LEFT, 0, 0);

        for (uint8_t i = 1; i < 4; ++i) {
            for (uint8_t j = 1; j < 4; ++j) {
                uint8_t curHeight = curRow * lineHeight;

                if (curRow < items.size()) {
                    if (!isSummary) {
                        /* Draw x.x text */
                        lv_obj_t *selectorText = lv_label_create(screen);
                        lv_obj_add_style(selectorText, &texts, 0);
                        lv_label_set_text(selectorText, (std::to_string(i) + "." + std::to_string(j)).c_str());
                        lv_obj_set_style_text_font(selectorText, &axel_ui, 0);
                        lv_obj_set_x(selectorText, 0);
                        lv_obj_set_y(selectorText, curHeight + 2);
                    }

                    const uint8_t offset = (isSummary ? 0 : 35);
                    lv_obj_t *itemText = lv_label_create(screen);
                    lv_obj_add_style(itemText, &texts, 0);
                    lv_label_set_text(itemText, Truncate_Text(items.at(curRow), 200 - offset).c_str());
                    lv_obj_set_style_text_font(itemText, &axel_text, 0);
                    lv_obj_set_x(itemText, offset);
                    lv_obj_set_y(itemText, curHeight + 2);
                }

                if (curRow < 8) {
                    /* Draw horizontal line */
                    lv_point_precise_t *horizPoints = new lv_point_precise_t[2] {{(lv_value_precise_t)0, (lv_value_precise_t)curHeight + lineHeight}, {(lv_value_precise_t)200, (lv_value_precise_t)curHeight + lineHeight}};

                    lv_obj_t *horizLine;
                    horizLine = lv_line_create(screen);
                    lv_line_set_points(horizLine, horizPoints, 2);
                    lv_obj_add_style(horizLine, &styleLine, 0);
                    lv_obj_align(horizLine, LV_ALIGN_TOP_LEFT, 0, 0);
                }

                ++curRow;
            }
        }
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

        eventType = lv_label_create(eventScreen);
        lv_obj_add_style(eventType, &texts, 0);
        lv_label_set_text(eventType, "Event Type");
        lv_obj_set_style_text_font(eventType, &axel_text, 0);
        lv_obj_align(eventType, LV_ALIGN_TOP_MID, 0, 0);

        eventTitle = lv_label_create(eventScreen);
        lv_obj_add_style(eventTitle, &texts, 0);
        lv_label_set_text(eventTitle, "Event Title");
        lv_obj_set_style_text_font(eventTitle, &axel_text, 0);
        lv_obj_align(eventTitle, LV_ALIGN_TOP_MID, 0, -20);

        eventDesc = lv_label_create(eventScreen);
        lv_obj_add_style(eventDesc, &texts, 0);
        lv_label_set_text(eventDesc, "Event Description");
        lv_obj_set_style_text_font(eventDesc, &axel_text, 0);
        lv_obj_align(eventDesc, LV_ALIGN_CENTER, 0, 0);

        eventTime = lv_label_create(eventScreen);
        lv_obj_add_style(eventTime, &texts, 0);
        lv_label_set_text(eventTime, "Event Time");
        lv_obj_set_style_text_font(eventTime, &axel_text, 0);
        lv_obj_align(eventTime, LV_ALIGN_BOTTOM_LEFT, 0, 0);

        eventRepdur = lv_label_create(eventScreen);
        lv_obj_add_style(eventRepdur, &texts, 0);
        lv_label_set_text(eventRepdur, "Event Repetition/Duration");
        lv_obj_set_style_text_font(eventRepdur, &axel_text, 0);
        lv_obj_align(eventRepdur, LV_ALIGN_BOTTOM_RIGHT, 0, 0);

        eventBorder = lv_obj_create(eventScreen);
        lv_obj_add_style(eventBorder, &box, 0);
        lv_obj_align(eventBorder, LV_ALIGN_CENTER, 0, 0);
        lv_obj_move_background(eventBorder);
        lv_obj_set_size(eventBorder, 200, 200);


        activeScreen = lv_obj_create(NULL);


        alertsListScreen = lv_obj_create(NULL);


        eventsListScreen = lv_obj_create(NULL);


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
        displayReady = false;

        Manager man = Controller::Instance()->Get_Manager();

        uint8_t *screen_data = px_map + 8;

        std::vector<uint8_t> *handlingBuffer = man.displayCallback->GetBuf();
        *handlingBuffer = std::vector<uint8_t>(screen_data, screen_data + man.Buffer_Size());

        man.displayCallback->Init();
        man.displayCallback->Display();
        lv_display_flush_ready(display);

        displayReady = lv_disp_flush_is_last(display);
    }

    void LVGL::Refresh()
    {
        lv_obj_invalidate(lv_screen_active());
    }

    void LVGL::Set_Face(Face *value)
    {
        face = value;
        face->Create();
        face->Load_Screen();
    }

    void LVGL::Tag()
    {
        Safe_Screen_Load(tagScreen);
    }

    void LVGL::Summary()
    {
        lv_obj_clean(summaryScreen);

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
        std::vector<std::string> items;
        for (Sys::AlertInfo alert : *stateAlerts) {
            std::string itemText = alert.source + " - " + alert.title;
            items.push_back(itemText);
        }

        Create_Selectors(summaryScreen, items);

        Safe_Screen_Load(summaryScreen);
    }

    void LVGL::Time(Sys::TimeInfo value)
    {
        if (face != nullptr) {
            if (lv_screen_active() == tagScreen) hapticCtrl->Vibrate_Pulse(500);
            face->Draw(value);
        }
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

        Safe_Screen_Load(alertScreen);
        state->Screen_Activate(Sys::Screen::ALERTS_LIST);  /* Until dismissal, activate unread alerts */
    }

    void LVGL::Event(Sys::EventInfo info)
    {
        /* Display event type */
        /* Display title */
        /* Display description */
        /* Display timestamp(probably now) */
        /* Display repetition/duration */
        /* Display w/wo border depending on type, view vs. alert modes */

        Safe_Screen_Load(eventScreen);
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
            Safe_Screen_Load(navScreen);
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
            Safe_Screen_Load(musicScreen);
            state->Screen_Activate(Sys::Screen::MUSIC);
        }
    }

    void LVGL::Active_Screen()
    {
        lv_obj_clean(activeScreen);

        std::array<uint8_t, (size_t)Sys::Screen::Enum_Length> screens = state->Get_Screens();
        for (uint8_t i = 0; i < screens.size(); ++i) {
            if (!i) continue;
            if ((Sys::Screen)i == Sys::Screen::TAG) continue;
            if ((Sys::Screen)i == Sys::Screen::FACE) activeItems.push_back("Watch Face");
            if ((Sys::Screen)i == Sys::Screen::SUMMARY) activeItems.push_back("Summary");
            if ((Sys::Screen)i == Sys::Screen::ALERT) continue;
            if ((Sys::Screen)i == Sys::Screen::ACTIVE) continue;
            if ((Sys::Screen)i == Sys::Screen::ALERTS_LIST) activeItems.push_back("Unread Alerts");
            if ((Sys::Screen)i == Sys::Screen::EVENTS_LIST) activeItems.push_back("Upcoming Events");
            if ((Sys::Screen)i == Sys::Screen::NAVIGATION) activeItems.push_back("Navigation");
            if ((Sys::Screen)i == Sys::Screen::MUSIC) activeItems.push_back("Music");
        }
        Create_Selectors(alertsListScreen, activeItems);

        Safe_Screen_Load(activeScreen);
    }

    void LVGL::Alerts_List_Screen()
    {
        lv_obj_clean(alertsListScreen);

        std::vector<Sys::AlertInfo> *stateAlerts = state->Get_Alerts();
        std::vector<std::string> stateSources;
        for (Sys::AlertInfo alert : *stateAlerts) {
            std::string itemText = alert.source + " - " + alert.title;
            stateSources.push_back(itemText);
        }
        Create_Selectors(alertsListScreen, stateSources);

        Safe_Screen_Load(alertsListScreen);
    }

    void LVGL::Events_List_Screen()
    {
        lv_obj_clean(eventsListScreen);

        std::vector<Sys::EventInfo> stateEvents = state->Get_Events();
        std::vector<std::string> stateTitles;
        for (Sys::EventInfo event : stateEvents) {
            stateTitles.push_back(event.title);
        }
        Create_Selectors(eventsListScreen, stateTitles);

        Safe_Screen_Load(eventsListScreen);
    }

    uint16_t LVGL::List_Handler(uint8_t group, uint8_t item)
    {
        return (group - 1) * 3 + (item - 1);
    }

    void LVGL::Load_Screen_By_Name(std::string name)
    {
        if (name == "Watch Face") face->Load_Screen();
        if (name == "Summary") Safe_Screen_Load(summaryScreen);
        if (name == "Unread Alerts") Safe_Screen_Load(alertsListScreen);
        if (name == "Upcoming Events") Safe_Screen_Load(eventsListScreen);
        if (name == "Navigation") Safe_Screen_Load(navScreen);
        if (name == "Music") Safe_Screen_Load(musicScreen);
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
            Active_Screen();
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
                /* If the group has been selected */
                if (prevButton > 0) {
                    uint16_t index = List_Handler(prevButton, 1);
                    prevButton = 0;
                    Load_Screen_By_Name(activeItems.at(index));
                }
                else prevButton = 1;
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
                        Sys::EventInfo passedEvent = stateEvents.at(eventIndex);
                        passedEvent.mode = 1;  /* View */
                        Event(passedEvent);
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
                /* If the group has been selected */
                if (prevButton > 0) {
                    uint16_t index = List_Handler(prevButton, 2);
                    prevButton = 0;
                    Load_Screen_By_Name(activeItems.at(index));
                }
                else prevButton = 2;
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
        /* Why does this crash ?? */
        /* hapticCtrl->Vibrate_Pulse(50); */
        /* Button 1 & 2 double press */
        if ((b1 == 1 && b2 == 2) || (b1 == 2 && b2 == 1)) {
            /* Global summary screen */
            Summary();
        }
        /* Button 3 & 4 double press */
        if ((b1 == 3 && b2 == 4) || (b1 == 4 && b2 == 3)) {
            if (lv_screen_active() == activeScreen) {
                /* If the group has been selected */
                if (prevButton > 0) {
                    uint16_t index = List_Handler(prevButton, 3);
                    prevButton = 0;
                    Load_Screen_By_Name(activeItems.at(index));
                }
                else prevButton = 3;
            }
            /* Alerts list screen: selector */
            if (lv_screen_active() == alertsListScreen) {
                /* If the group has been selected */
                if (prevButton > 0) {
                    uint16_t index = List_Handler(prevButton, 3);
                    prevButton = 0;
                    std::vector<Sys::AlertInfo> *stateAlerts = state->Get_Alerts();
                    if (index < stateAlerts->size())
                        Alert(stateAlerts->at(index));
                }
                else prevButton = 3;
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
