#include <SPI.h>
#include "LCD_Driver.h"
#include "paint.h"
#include "image.h"

#include "../Devices/Fridge.h"
#include "../Devices/Light.h"
#include "../Devices/PowerManager.h"

#include "../PINS.h"

/*

WAVESHARE 2.4 Inch LCD Screen :

LCD    |  ESP GPIO
-------+----------
DIN    |   D23
CLK    |   D18
CS     |   D5
DC     |   D32
RST    |   D33
BL     |   D35



*/

#define DEFAULT_TIMEOUT_SCREEN_US 5000000

#define PIN_BACK_LIGHT 4

class GUI
{
public:
    GUI( Fridge* fridge, Light* light, PowerManager* PowerManager );
    ~GUI();

    enum pageEnum {
        PAGE_MAIN,
        PAGE_SETTINGS,
        PAGE_GRAPH
    };

    void        it_update   ( void );

    void        refreshGUI  ( void );

    void        changePage  ( pageEnum page );


private:

    void initLCD(void);
    void drawPage(void);

    void drawMainPage(void);
    void refreshMainPage(void);
    void drawSettingsPage(void);
    void refreshSettingsPage(void);

    String _formatInt(int number,unsigned int digit,int multiplier,char unit);

    pageEnum m_currentPage = PAGE_MAIN;

    Fridge* m_fridge = nullptr;
    Light* m_light = nullptr;
    PowerManager* m_powerManager = nullptr;

    bool m_button1 = false;
    bool m_button2 = false;
    bool m_button3 = false;

    int m_timeout = DEFAULT_TIMEOUT_SCREEN_US;
    timeval m_time_now;
    timeval m_time_lastPush;
    int64_t m_time_lastPush_us;

    bool m_screenON = true;
    bool m_button_pressed = true; 
};