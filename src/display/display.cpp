#include "display/display.hpp"

#include "sys/spi.hpp"

#include "stm32wbxx_hal.h"

#include <vector>


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

Display::EInk::EInk(uint16_t displayWidth, uint16_t displayHeight, Sys::SPIController ctrl)
{
    this->width = displayWidth;
    this->height = displayHeight;
    this->spi = ctrl;
}

uint16_t Display::EInk::Get_Width_Bytes()
{
    return (width % 8 == 0) ? (width / 8) : (width / 8 + 1);
}

uint16_t Display::EInk::Get_Buffer_Size()
{
    return Get_Width_Bytes() * height;
}

void Display::EInk::SetWindows(uint16_t Xstart, uint16_t Ystart, uint16_t Xend, uint16_t Yend)
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

void Display::EInk::SetCursor(uint16_t x, uint16_t y)
{
    spi.SendCommand(0x4E);
    /* x point must be the multiple of 8 or the last 3 bits will be ignored */
    spi.SendData((x >> 3) & 0xFF);
    spi.SendCommand(0x4F);
    spi.SendData(y & 0xFF);
    spi.SendData((y >> 8) & 0xFF);
    spi.BlockBusy();
}

void Display::EInk::WriteLUT(uint8_t *value)
{
    spi.SendCommand(0x32);  /* Write LUT register */
    for (uint8_t i = 0; i < 153; ++i)
        spi.SendData(value[i]);
    spi.BlockBusy();
}

void Display::EInk::InitRegisters(uint8_t *lut)
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

void Display::EInk::TurnOnDisplay()
{
    spi.SendCommand(0x22);  /* Display update control */
    spi.SendData(0xC7); 
    spi.SendCommand(0x20);  /* Display update activation */
    spi.BlockBusy();
}

void Display::EInk::TurnOnDisplayPart()
{
    spi.SendCommand(0x22);  /* Display update control */
    spi.SendData(0xCF);
    spi.SendCommand(0x20);  /* Display update activation */
    spi.BlockBusy();
}

void Display::EInk::Init()
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

    SetWindows(0, 0, width - 1, height - 1);

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

void Display::EInk::Init_Partial()
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
}

void Display::EInk::Clear()
{
    uint16_t widthBytes = Get_Width_Bytes();

    spi.SendCommand(0x24);  /* Write RAM(BW) */
    for (uint16_t j = 0; j < height; j++)
        for (uint16_t i = 0; i < widthBytes; i++)
            spi.SendData(0xFF);
    spi.SendCommand(0x26);  /* Write RAM(RED)? */

    for (uint16_t j = 0; j < height; j++)
        for (uint16_t i = 0; i < widthBytes; i++)
            spi.SendData(0xFF);
    TurnOnDisplay();
}

/* image is not malloced or passed in correctly, */
/* either allocate or pass in differently, any reads past image[0] go ballistic */
void Display::EInk::Display(std::vector<uint8_t> const &image)
{
    uint16_t widthBytes = Get_Width_Bytes();

    SetWindows(0, 0, width - 1, height - 1);
    SetCursor(0, 0);

    spi.SendCommand(0x24);  /* Write RAM(BW) */
    for (uint16_t j = 0; j < height; j++) {
        for (uint16_t i = 0; i < widthBytes; i++) {
            spi.SendData(image.at(i + (j * widthBytes)));
        }
    }
    TurnOnDisplay();
}

void Display::EInk::DisplayPartBaseImage(std::vector<uint8_t> const &image)
{
    uint16_t widthBytes = Get_Width_Bytes();

    spi.SendCommand(0x24);  /* Write RAM(BW) */
    for (uint16_t j = 0; j < height; j++) {
        for (uint16_t i = 0; i < widthBytes; i++) {
            spi.SendData(image.at(i + (j * widthBytes)));
        }
    }
    spi.SendCommand(0x26);  /* Write RAM(RED)? */
    for (uint16_t j = 0; j < height; j++) {
        for (uint16_t i = 0; i < widthBytes; i++) {
            spi.SendData(image.at(i + (j * widthBytes)));
        }
    }
    TurnOnDisplayPart();
}

void Display::EInk::DisplayPart(std::vector<uint8_t> const &image)
{
    uint16_t widthBytes = Get_Width_Bytes();

    spi.SendCommand(0x24);  /* Write RAM(BW) */
    for (uint16_t j = 0; j < height; j++) {
        for (uint16_t i = 0; i < widthBytes; i++) {
            spi.SendData(image.at(i + (j * widthBytes)));
        }
    }
    TurnOnDisplayPart();
}

void Display::EInk::Sleep()
{
    spi.SendCommand(0x10);  /* Deep sleep mode control */
    spi.SendData(0x01);
    HAL_Delay(100);
}
