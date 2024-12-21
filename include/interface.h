#pragma once
#include <Arduino.h>
#include <Wire.h>
#include <hd44780.h>
#include <hd44780ioClass/hd44780_I2Cexp.h>

class Interface : public hd44780_I2Cexp
{
private:
    uint8_t m_LCD_COLS, m_LCD_ROWS;
    bool m_EN_LCD;

public:
    Interface(uint8_t LCD_COLS, uint8_t LCD_ROWS, bool EN_LCD);
    void init();
};
