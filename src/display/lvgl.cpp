#include "display/lvgl.hpp"

#include "display/controller.hpp"

#include "sys/state.hpp"

#include "stm32wbxx_hal.h"
#include "lvgl.h"

#include <vector>
#include <string>


LV_FONT_DECLARE(gloock_18_date)
LV_FONT_DECLARE(gloock_70_time)
LV_FONT_DECLARE(axel_22_ui)
LV_FONT_DECLARE(axel_20_text)
/* LV_FONT_DECLARE(lato_18) */
/* LV_FONT_DECLARE(sunflower_80) */

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

    void LVGL::Create_Alerts_List()
    {
        alerts = lv_list_create(alertsList);
        lv_obj_set_size(alerts, 200, 200);
        lv_obj_align(alerts, LV_ALIGN_TOP_LEFT, 0, 0);
        lv_list_add_text(alerts, "Alerts");
    }

    void LVGL::Create()
    {
        /*Change the active screen's background color*/
        lv_obj_set_style_bg_color(lv_screen_active(), state->Get_Pref()->userWhite, LV_PART_MAIN);

        faceScreen = lv_screen_active();

        static lv_style_t texts;
        lv_style_init(&texts);
        lv_style_set_text_color(&texts, state->Get_Pref()->userBlack);
        lv_style_set_text_font(&texts, &gloock_70_time);

        time = lv_label_create(lv_screen_active());
        lv_obj_add_style(time, &texts, 0);
        lv_label_set_text(time, "00:00");
        lv_obj_align(time, LV_ALIGN_CENTER, 0, -10);

        date = lv_label_create(lv_screen_active());
        lv_obj_add_style(date, &texts, 0);
        lv_label_set_text(date, "Month Day Year");
        lv_obj_set_style_text_font(date, &gloock_18_date, 0);
        lv_obj_align(date, LV_ALIGN_CENTER, 0, 45);


        alertScreen = lv_obj_create(NULL);
        static lv_style_t box;
        lv_style_set_border_width(&box, 3);
        lv_style_set_border_color(&box, state->Get_Pref()->userBlack);
        lv_style_set_bg_color(&box, state->Get_Pref()->userWhite);
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

        lv_obj_t *border = lv_obj_create(alertScreen);
        lv_obj_add_style(border, &box, 0);
        lv_obj_align(border, LV_ALIGN_CENTER, 0, 0);
        lv_obj_move_background(border);
        lv_obj_set_size(border, 200, 200);



        activeScreen = lv_obj_create(NULL);
        lv_obj_t *activeTitle = lv_label_create(activeScreen);
        lv_obj_add_style(activeTitle, &texts, 0);
        lv_label_set_text(activeTitle, "Active Screens");
        lv_obj_set_style_text_font(activeTitle, &axel_22_ui, 0);
        lv_obj_align(activeTitle, LV_ALIGN_CENTER, 0, 0);


        alertsList = lv_obj_create(NULL);
        Create_Alerts_List();
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

    void LVGL::Time(Sys::Time value)
    {
        lv_label_set_text(time, ((value.hour < 10 ? "0" : "") + std::to_string(value.hour) + ":" + (value.minute < 10 ? "0" : "") + std::to_string(value.minute)).c_str());
        const std::string months[12] = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};
        std::string day = std::to_string(value.day);
        if (value.day % 10 == 1 && value.day != 11) day += "st";
        if (value.day % 10 == 2 && value.day != 12) day += "nd";
        if (value.day % 10 == 3 && value.day != 13) day += "rd";
        else day += "th";
        lv_label_set_text(date, (months[value.month - 1] + " " + day).c_str());
    }

    void LVGL::Alert(Sys::Alert alert)
    {
        lv_label_set_text(source, alert.source.c_str());
        lv_label_set_text(title, alert.title.c_str());
        lv_label_set_text(body, alert.body.c_str());

        lv_scr_load(alertScreen);
    }

    void LVGL::Alerts_List_Screen()
    {
        std::vector<Sys::Alert> *stateAlerts = state->Get_Alerts();
        Create_Alerts_List();
        for (Sys::Alert alert : *stateAlerts) {
            lv_list_add_button(alerts, NULL, (alert.source).c_str());
        }
        lv_scr_load(alertsList);
    }

    uint16_t LVGL::List_Handler(uint8_t group, uint8_t item)
    {
        return (group - 1) * 2 + (item - 1);
    }

    void LVGL::Button_One()
    {
        /* All screens: load face */
        lv_scr_load(faceScreen);
    }

    void LVGL::Button_Two()
    {
        /* All screens but active screens(select): load active screens */
        if (lv_screen_active() == activeScreen) {
            /* Select screen */
        }
        else lv_scr_load(activeScreen);
    }

    void LVGL::Button_Three()
    {
        /* Alert screen: dismiss alert */
        if (lv_screen_active() == alertScreen) {
            state->Alert_Dismiss();
            lv_scr_load(faceScreen);
        }
        /* Active screen: scroll up */
        else if (lv_screen_active() == activeScreen) {
            /* Scroll up */
        }
        /* Alerts list: Group/item selector */
        else if (lv_screen_active() == alertsList) {
            /* If the group has been selected */
            if (prevButton > 0) {
                uint16_t index = List_Handler(prevButton, 1);
                prevButton = 0;
                std::vector<Sys::Alert> *stateAlerts = state->Get_Alerts();
                if (index < stateAlerts->size())
                    Alert(stateAlerts->at(index));
            }
            else prevButton = 1;
        }
    }

    void LVGL::Button_Four()
    {
        /* Alert screen: shortcut to alert list */
        if (lv_screen_active() == alertScreen) {
            Alerts_List_Screen();
        }
        /* Active screen: scroll down */
        else if (lv_screen_active() == activeScreen) {
            /* Scroll down */
        }
        else if (lv_screen_active() == alertsList) {
            /* If the group has been selected */
            if (prevButton > 0) {
                uint16_t index = List_Handler(prevButton, 2);
                prevButton = 0;
                std::vector<Sys::Alert> *stateAlerts = state->Get_Alerts();
                if (index < stateAlerts->size())
                    Alert(stateAlerts->at(index));
            }
            else prevButton = 2;
        }
    }
    
    void LVGL::Button_Double()
    {
        if (lv_screen_active() == alertsList) {
            /* We only have two items so double selector only applies for groups */
            if (prevButton == 0)
                prevButton = 3;
        }
    }
}
