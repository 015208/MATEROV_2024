#include <interface.h>

Interface::Interface(uint8_t LCD_COLS, uint8_t LCD_ROWS, bool EN_LCD)
    : m_LCD_COLS(LCD_COLS), m_LCD_ROWS(LCD_ROWS), m_EN_LCD(EN_LCD)
{
}

void Interface::init()
{
    if (m_EN_LCD == true)
    {
        int lcdBeginStatus =
            begin(m_LCD_COLS, m_LCD_ROWS);
        if (lcdBeginStatus)
        {
            hd44780::fatalError(lcdBeginStatus);
        }
        clear();
        backlight();
    }
    
}