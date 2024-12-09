#include "display/display.hpp"

#include "sys/spi.hpp"

#include "stm32wbxx_hal.h"
#include "lvgl.h"

#include <vector>
#include <string>


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

        static lv_style_t texts;
        lv_style_init(&texts);
        lv_style_set_text_color(&texts, lv_color_hex(0x000000));
        lv_style_set_text_font(&texts, &lv_font_montserrat_28);

        time = lv_label_create(lv_screen_active());
        lv_obj_add_style(time, &texts, 0);
        lv_label_set_text(time, "00:00");
        lv_obj_align(time, LV_ALIGN_CENTER, 0, -50);

        lv_obj_t *title = lv_label_create(lv_screen_active());
        lv_obj_add_style(title, &texts, 0);
        lv_label_set_text(title, "Raven V0.5");
        lv_obj_align(title, LV_ALIGN_CENTER, 0, 0);

        lv_obj_t *desc = lv_label_create(lv_screen_active());
        lv_obj_add_style(desc, &texts, 0);
        lv_label_set_text(desc, "Mosaic Labs");
        lv_obj_align(desc, LV_ALIGN_CENTER, 0, 50);
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
        lv_label_set_text(time, (std::to_string(value.hours) + ":" + std::to_string(value.minutes)).c_str());
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
}
