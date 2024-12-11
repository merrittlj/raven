#include "display/display.hpp"

#include "sys/spi.hpp"

#include "stm32wbxx_hal.h"
#include "lvgl.h"

#include <vector>
#include <string>


LV_FONT_DECLARE(gloock_18_date)
LV_FONT_DECLARE(gloock_80_time)
LV_FONT_DECLARE(axel_22_ui)
LV_FONT_DECLARE(axel_20_text)
/* LV_FONT_DECLARE(lato_18) */
/* LV_FONT_DECLARE(sunflower_80) */

static unsigned char WaveformFullRefresh[159] = {											
    0x80,	0x48,	0x40,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,
    0x40,	0x48,	0x80,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,
    0x80,	0x48,	0x40,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,
    0x40,	0x48,	0x80,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,
    0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,
    0xA,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,					
    0x8,	0x1,	0x0,	0x8,	0x1,	0x0,	0x2,					
    0xA,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,					
    0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,					
    0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,					
    0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,					
    0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,					
    0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,					
    0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,					
    0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,					
    0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,					
    0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,					
    0x22,	0x22,	0x22,	0x22,	0x22,	0x22,	0x0,	0x0,	0x0,			
    0x22,	0x17,	0x41,	0x0,	0x32,	0x20,
};

static unsigned char WaveformPartialRefresh[159] = {
    0x0,0x40,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
    0x80,0x80,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
    0x40,0x40,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
    0x0,0x80,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
    0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
    0xF,0x0,0x0,0x0,0x0,0x0,0x0,
    0x1,0x1,0x0,0x0,0x0,0x0,0x0,
    0x0,0x0,0x0,0x0,0x0,0x0,0x0,
    0x0,0x0,0x0,0x0,0x0,0x0,0x0,
    0x0,0x0,0x0,0x0,0x0,0x0,0x0,
    0x0,0x0,0x0,0x0,0x0,0x0,0x0,
    0x0,0x0,0x0,0x0,0x0,0x0,0x0,
    0x0,0x0,0x0,0x0,0x0,0x0,0x0,
    0x0,0x0,0x0,0x0,0x0,0x0,0x0,
    0x0,0x0,0x0,0x0,0x0,0x0,0x0,
    0x0,0x0,0x0,0x0,0x0,0x0,0x0,
    0x0,0x0,0x0,0x0,0x0,0x0,0x0,
    0x22,0x22,0x22,0x22,0x22,0x22,0x0,0x0,0x0,
    0x02,0x17,0x41,0xB0,0x32,0x28,
};

namespace Display
{
    uint16_t Manager::Width_Bytes()
    {
        return (width % 8 == 0) ? (width / 8) : (width / 8 + 1);
    }

    uint16_t Manager::Buffer_Size()
    {
        return (Width_Bytes() * height);
    }


    EInk::EInk()
    {}

    EInk::EInk(Display::Manager man, Sys::SPIController ctrl)
    {
        manager = man;
        spi = ctrl;
    }


    std::vector<uint8_t> *EInk::GetBuf()
    {
        return &buf;
    }

    void EInk::SetWindows(uint16_t Xstart, uint16_t Ystart, uint16_t Xend, uint16_t Yend)
    {
        spi.SendCommand(0x44);  /* SET_RAM_X_ADDRESS_START_END_POSITION */
        spi.SendData((Xstart >> 3) & 0xFF);
        spi.SendData((Xend >> 3) & 0xFF);

        spi.SendCommand(0x45);  /* SET_RAM_Y_ADDRESS_START_END_POSITION */
        spi.SendData(Ystart & 0xFF);
        spi.SendData((Ystart >> 8) & 0xFF);
        spi.SendData(Yend & 0xFF);
        spi.SendData((Yend >> 8) & 0xFF);
    }

    void EInk::SetCursor(uint16_t x, uint16_t y)
    {
        spi.SendCommand(0x4E);
        /* x point must be the multiple of 8 or the last 3 bits will be ignored */
        spi.SendData((x >> 3) & 0xFF);
        spi.SendCommand(0x4F);
        spi.SendData(y & 0xFF);
        spi.SendData((y >> 8) & 0xFF);
        spi.BlockBusy();
    }

    void EInk::WriteLUT(uint8_t *value)
    {
        spi.SendCommand(0x32);  /* Write LUT register */
        for (uint8_t i = 0; i < 153; ++i)
            spi.SendData(value[i]);
        spi.BlockBusy();
    }

    void EInk::InitRegisters(uint8_t *lut)
    {
        WriteLUT(lut);

        spi.SendCommand(0x3f);  /* Cannot find documentation */
        spi.SendData(lut[153]);

        spi.SendCommand(0x03);  /* Set Gate driving voltage */
        spi.SendData(lut[154]);

        spi.SendCommand(0x04);  /* Set Source driving voltage */
        spi.SendData(lut[155]);
        spi.SendData(lut[156]);
        spi.SendData(lut[157]);

        spi.SendCommand(0x2C);  /* Write VCOM register */
        spi.SendData(lut[158]);
    }

    void EInk::TurnOnDisplay()
    {
        spi.SendCommand(0x22);  /* Display update control */
        spi.SendData(0xC7); 
        spi.SendCommand(0x20);  /* Display update activation */
        spi.BlockBusy();
    }

    void EInk::TurnOnDisplayPart()
    {
        spi.SendCommand(0x22);  /* Display update control */
        spi.SendData(0xCF);
        spi.SendCommand(0x20);  /* Display update activation */
        spi.BlockBusy();
    }

    void EInk::Init()
    {
        spi.Reset();

        spi.BlockBusy();
        spi.SendCommand(0x12);  /* SWRESET */
        spi.BlockBusy();

        spi.SendCommand(0x01);  /* Driver output control */
        spi.SendData(0xC7);
        spi.SendData(0x00);
        spi.SendData(0x00);

        spi.SendCommand(0x11);  /* Data entry mode */
        spi.SendData(0x03);

        SetWindows(0, 0, manager.width - 1, manager.height - 1);

        spi.SendCommand(0x3C);  /* BorderWavefrom */
        spi.SendData(0x01);

        spi.SendCommand(0x18);  /* Undocumented */
        spi.SendData(0x80);

        spi.SendCommand(0x22);  /* Load temp. and waveform settings */
        spi.SendData(0xB1);
        spi.SendCommand(0x20);  /* Display update activation */

        spi.SendCommand(0x4E);   // set RAM x address count to 0;
        spi.SendData(0x00);
        spi.SendCommand(0x4F);   // set RAM y address count to 0X199;
        spi.SendData(0xC7);
        spi.SendData(0x00);
        spi.BlockBusy();

        WriteLUT(WaveformFullRefresh);
    }

    void EInk::Init_Partial()
    {
        spi.Reset();
        spi.BlockBusy();

        WriteLUT(WaveformPartialRefresh);
        spi.SendCommand(0x37);  /* Undocumented */
        spi.SendData(0x00);  
        spi.SendData(0x00);  
        spi.SendData(0x00);  
        spi.SendData(0x00); 
        spi.SendData(0x00);  	
        spi.SendData(0x40);  
        spi.SendData(0x00);  
        spi.SendData(0x00);   
        spi.SendData(0x00);  
        spi.SendData(0x00);

        spi.SendCommand(0x3C);  /* BorderWavefrom */
        spi.SendData(0x80);

        spi.SendCommand(0x22);  /* Display update control */
        spi.SendData(0xc0); 
        spi.SendCommand(0x20);  /* Display update activation */
        spi.BlockBusy();

        Clear();
    }

    void EInk::Clear()
    {
        uint16_t widthBytes = manager.Width_Bytes();

        spi.SendCommand(0x24);  /* Write RAM(BW) */
        for (uint16_t j = 0; j < manager.height; j++)
            for (uint16_t i = 0; i < widthBytes; i++)
                spi.SendData(0xFF);
        spi.SendCommand(0x26);  /* Write RAM(RED)? */

        for (uint16_t j = 0; j < manager.height; j++)
            for (uint16_t i = 0; i < widthBytes; i++)
                spi.SendData(0xFF);
        TurnOnDisplay();
    }

    void EInk::Display()
    {
        uint16_t widthBytes = manager.Width_Bytes();

        SetWindows(0, 0, manager.width - 1, manager.height - 1);
        SetCursor(0, 0);

        spi.SendCommand(0x24);  /* Write RAM(BW) */
        for (uint16_t j = 0; j < manager.height; j++) {
            for (uint16_t i = 0; i < widthBytes; i++) {
                spi.SendData(buf.at(i + (j * widthBytes)));
            }
        }
        TurnOnDisplay();
    }

    void EInk::DisplayPartBaseImage()
    {
        uint16_t widthBytes = manager.Width_Bytes();

        spi.SendCommand(0x24);  /* Write RAM(BW) */
        for (uint16_t j = 0; j < manager.height; j++) {
            for (uint16_t i = 0; i < widthBytes; i++) {
                spi.SendData(buf.at(i + (j * widthBytes)));
            }
        }
        spi.SendCommand(0x26);  /* Write RAM(RED)? */
        for (uint16_t j = 0; j < manager.height; j++) {
            for (uint16_t i = 0; i < widthBytes; i++) {
                spi.SendData(buf.at(i + (j * widthBytes)));
            }
        }
        TurnOnDisplayPart();
    }

    void EInk::DisplayPart()
    {
        uint16_t widthBytes = manager.Width_Bytes();

        spi.SendCommand(0x24);  /* Write RAM(BW) */
        for (uint16_t j = 0; j < manager.height; j++) {
            for (uint16_t i = 0; i < widthBytes; i++) {
                spi.SendData(buf.at(i + (j * widthBytes)));
            }
        }
        TurnOnDisplayPart();
    }

    void EInk::Sleep()
    {
        spi.SendCommand(0x10);  /* Deep sleep mode control */
        spi.SendData(0x01);
        HAL_Delay(100);
    }

    LVGL::LVGL()
    {

    }

    LVGL::LVGL(Display::Manager man)
    {
        manager = man;
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

    void LVGL::Create()
    {
        /*Change the active screen's background color*/
        lv_obj_set_style_bg_color(lv_screen_active(), lv_color_hex(0xffffff), LV_PART_MAIN);

        faceScreen = lv_screen_active();

        static lv_style_t texts;
        lv_style_init(&texts);
        lv_style_set_text_color(&texts, lv_color_hex(0x000000));
        lv_style_set_text_font(&texts, &gloock_80_time);

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

        lv_obj_t *border = lv_obj_create(alertScreen);
        lv_obj_add_style(border, &box, 0);
        lv_obj_align(border, LV_ALIGN_CENTER, 0, 0);
        lv_obj_move_background(border);
        lv_obj_set_size(border, 200, 200);
    }

    void LVGL::Flush(lv_display_t *display, const lv_area_t *area, uint8_t *px_map)
    {
        Manager man = Controller::Instance()->Get_Manager();

        uint8_t *screen_data = px_map + 8;

        std::vector<uint8_t> *handlingBuffer = man.displayCallback->GetBuf();
        *handlingBuffer = std::vector<uint8_t>(screen_data, screen_data + man.Buffer_Size());

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

    Controller::Controller(uint16_t displayWidth, uint16_t displayHeight, Sys::SPIController ctrl)
    {
        Controller::Instance(this);

        manager = { 0 };
        manager.width = displayWidth;
        manager.height = displayHeight;

        display = Display::EInk(manager, ctrl);
        manager.displayCallback = &display;

        lvgl = Display::LVGL(manager);
    }

    Controller::~Controller()
    {
        delete theInstance;
    }

    Controller *Controller::Instance(Controller *cur)
    {
        if (!theInstance) theInstance = cur;
        return theInstance;
    }

    Manager Controller::Get_Manager()
    {
        return manager;
    }

    void Controller::Init()
    {
        display.Init();
        lvgl.Init();
        lvgl.Create();
    }

    void Controller::Process()
    {
        lv_timer_periodic_handler();
    }

    void Controller::Update_Time(Sys::Time value)
    {
        lvgl.Time(value);
    }

    void Controller::Alert_Send(Sys::Alert alert)
    {
        lvgl.Alert(alert);
    }
}
