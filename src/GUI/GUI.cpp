#include "GUI.h"

#define LCD_ORIENTATION_90 90
#define GUI_RIGHT 320
#define GUI_BOTTOM 240


const unsigned short BACKGROUND_COLOR = WHITE;
const unsigned short SCREEN_BORDER_COLOR = BLACK;
const unsigned short RIGHT_MENU_WIDTH = 40;
const unsigned short RIGHT_MENU = GUI_RIGHT - RIGHT_MENU_WIDTH;
const unsigned short VERTICAL_SEPARATOR = 140;
const unsigned short HORIZONTAL_SEPARATOR_1 = 81;
const unsigned short HORIZONTAL_SEPARATOR_2 = 160;


GUI::GUI( Fridge* fridge, Light* light, PowerManager* PowerManager )
{
    m_fridge = fridge;
    m_light = light;
    m_powerManager = PowerManager;

    // Init screen 
    initLCD();
    changePage(PAGE_MAIN);

    // Set time
    gettimeofday(&m_time_now,NULL);
    gettimeofday(&m_time_lastPush,NULL);

}

GUI::~GUI()
{
    Serial.print("GUI IS DEAD (X__X) ");
}

void GUI::initLCD(void)
{
    Config_Init();
    LCD_Init();
    LCD_Clear(0xffff);
    Paint_NewImage(LCD_WIDTH, LCD_HEIGHT, 90, YELLOW);
}

void GUI::it_update(void)
{
    // READ PushButtons
    if(digitalRead(PIN_BUTTON_1)) m_button1 = true;
    if(digitalRead(PIN_BUTTON_2)) m_button2 = true;
    if(digitalRead(PIN_BUTTON_3)) m_button3 = true;
}

void GUI::refreshGUI(void)
{
    // TESTING
    Serial.print("BAT RELAY : ");
    Serial.println(m_powerManager->getBatteryConnected());


    // Get time
    gettimeofday(&m_time_now, NULL);
    int64_t currentTime_us = (int64_t)m_time_now.tv_sec * 1000000L + (int64_t)m_time_now.tv_usec;

    // Reset screen timer and detect button
    if( m_button1 or m_button2 or m_button3 )
    {   
        m_button_pressed = true;
        gettimeofday(&m_time_lastPush,NULL);
        m_time_lastPush_us = (int64_t)m_time_lastPush.tv_sec * 1000000L + (int64_t)m_time_now.tv_usec;
    }

    // Timeout Screen
    if( currentTime_us - m_time_lastPush_us > m_timeout )
    {
        // //LCD_SetBackLight(0);
        // if( m_screenON == true )
        // { 
        //     m_screenON = false; 
        //     Serial.print("Screen OFF"); 
        // }
        //Serial.println("kikou");
    }
    else
    {
        // if( m_screenON == false )
        // { 
        //     m_screenON = true; 
        //     Serial.println("Screen ON"); 
        // }
        // //LCD_SetBackLight(255);
    }

    switch (m_currentPage)
    {
    case PAGE_MAIN:
        refreshMainPage();
        break;
    case PAGE_SETTINGS:
        refreshSettingsPage();
        break;
    default:
        break;
    }


    // Reset Buttons
    if( m_button_pressed )
    {
        m_button1 = false;
        m_button2 = false;
        m_button3 = false;
        m_button_pressed = false;
    }

}

void GUI::changePage(pageEnum page)
{
    m_currentPage = page;
    drawPage();
}

void GUI::drawPage(void)
{
    switch (m_currentPage)
    {
    case PAGE_MAIN:
        drawMainPage();
        break;
    case PAGE_SETTINGS:
        drawSettingsPage();
        break;
    
    default:
        break;
    }

}

void GUI::drawMainPage(void)
{
    /* 
                    1           2   3
                    4           8   2
    1               0           0   0
    +---------------+-----------+---+ 1
    |               |    TEMP   |   |
    |               +-----------+---+ 81
    |    POWER      |   LIGHT   |   |
    |               +-----------+---+ 180
    |               |   FRIDG   |   |
    +---------------+-----------+---+ 240

    */

    Paint_Clear(BACKGROUND_COLOR);

    // Borders /////////////////////////////////////////////////////////////////
    Paint_DrawRectangle(1,1,GUI_RIGHT,GUI_BOTTOM,SCREEN_BORDER_COLOR,DOT_PIXEL_1X1,DRAW_FILL_EMPTY);
    Paint_DrawLine(VERTICAL_SEPARATOR,1,VERTICAL_SEPARATOR,GUI_BOTTOM,BLACK,DOT_PIXEL_1X1,LINE_STYLE_SOLID);
    Paint_DrawLine(VERTICAL_SEPARATOR,HORIZONTAL_SEPARATOR_1,RIGHT_MENU,HORIZONTAL_SEPARATOR_1,BLACK,DOT_PIXEL_1X1,LINE_STYLE_SOLID);
    Paint_DrawLine(VERTICAL_SEPARATOR,HORIZONTAL_SEPARATOR_2,RIGHT_MENU,HORIZONTAL_SEPARATOR_2,BLACK,DOT_PIXEL_1X1,LINE_STYLE_SOLID);
    
    // Right menu /////////////////////////////////////////////////////////////////
    const unsigned short MENU_BACKGROUND_COLOR = LGRAYBLUE;
    const unsigned short RIGHT_MENU_FONT_COLOR = BLACK;
    Paint_DrawRectangle(RIGHT_MENU,1,GUI_RIGHT-1,GUI_BOTTOM-1,MENU_BACKGROUND_COLOR,DOT_PIXEL_1X1,DRAW_FILL_FULL);
    Paint_DrawLine(RIGHT_MENU,1,RIGHT_MENU,GUI_BOTTOM,BLACK,DOT_PIXEL_1X1,LINE_STYLE_SOLID);
    Paint_DrawLine(RIGHT_MENU,HORIZONTAL_SEPARATOR_1,GUI_RIGHT,HORIZONTAL_SEPARATOR_1,BLACK,DOT_PIXEL_1X1,LINE_STYLE_SOLID);
    Paint_DrawLine(RIGHT_MENU,HORIZONTAL_SEPARATOR_2,GUI_RIGHT,HORIZONTAL_SEPARATOR_2,BLACK,DOT_PIXEL_1X1,LINE_STYLE_SOLID);
    Paint_DrawChar(RIGHT_MENU+13, 5,'S',&Font20,BACKGROUND_COLOR,RIGHT_MENU_FONT_COLOR);
    Paint_DrawChar(RIGHT_MENU+13,30,'E',&Font20,BACKGROUND_COLOR,RIGHT_MENU_FONT_COLOR);
    Paint_DrawChar(RIGHT_MENU+13,55,'T',&Font20,BACKGROUND_COLOR,RIGHT_MENU_FONT_COLOR);
    Paint_DrawChar(RIGHT_MENU+13,HORIZONTAL_SEPARATOR_1+ 5,'L',&Font20,BACKGROUND_COLOR,RIGHT_MENU_FONT_COLOR);
    Paint_DrawChar(RIGHT_MENU+13,HORIZONTAL_SEPARATOR_1+30,'O',&Font20,BACKGROUND_COLOR,RIGHT_MENU_FONT_COLOR);
    Paint_DrawChar(RIGHT_MENU+13,HORIZONTAL_SEPARATOR_1+55,'G',&Font20,BACKGROUND_COLOR,RIGHT_MENU_FONT_COLOR);
    Paint_DrawChar(RIGHT_MENU+13,HORIZONTAL_SEPARATOR_2+ 5,'O',&Font20,BACKGROUND_COLOR,RIGHT_MENU_FONT_COLOR);
    Paint_DrawChar(RIGHT_MENU+13,HORIZONTAL_SEPARATOR_2+30,'F',&Font20,BACKGROUND_COLOR,RIGHT_MENU_FONT_COLOR);
    Paint_DrawChar(RIGHT_MENU+13,HORIZONTAL_SEPARATOR_2+55,'F',&Font20,BACKGROUND_COLOR,RIGHT_MENU_FONT_COLOR);

    // POWER /////////////////////////////////////////////////////////////////

        /* Line */
    Paint_DrawLine(15,1,15,GUI_BOTTOM-1,BLACK,DOT_PIXEL_2X2,LINE_STYLE_SOLID);


        /* LED STATUS */
    Paint_DrawString_EN(25,50,"Ign",&Font16,BACKGROUND_COLOR,BLACK);
    Paint_DrawCircle(70,57,6,BLACK,DOT_PIXEL_2X2,DRAW_FILL_EMPTY);
    Paint_DrawCircle(70,57,6,RED,DOT_PIXEL_1X1,DRAW_FILL_FULL);
    Paint_DrawString_EN(85,50,"Chg",&Font16,BACKGROUND_COLOR,BLACK);
    Paint_DrawCircle(VERTICAL_SEPARATOR-10,57,6,BLACK,DOT_PIXEL_2X2,DRAW_FILL_EMPTY);
    Paint_DrawCircle(VERTICAL_SEPARATOR-10,57,6,BLUE,DOT_PIXEL_1X1,DRAW_FILL_FULL);

        /* Charger */
    Paint_DrawString_EN(25,70,"Mode",&Font16,BACKGROUND_COLOR,BLACK);

        /* Vbat */
    Paint_DrawString_EN(25,90,"Vbat=",&Font16,BACKGROUND_COLOR,BLACK);

        /* IN */
    Paint_DrawArrow(15,115,21,DIRECTION_DOWN,RED,DRAW_FILL_FULL);
    Paint_DrawString_EN(25,110,"Iin =",&Font16,BACKGROUND_COLOR,BLACK);

        /* BAT Connector */
    Paint_DrawLine(15,135,45,135,BLACK,DOT_PIXEL_2X2,LINE_STYLE_SOLID);
    Paint_DrawLine(45,135,45,145,BLACK,DOT_PIXEL_2X2,LINE_STYLE_SOLID);
    Paint_DrawLine(105,135,105,145,BLACK,DOT_PIXEL_2X2,LINE_STYLE_SOLID);
    Paint_DrawLine(105,135,130,135,BLACK,DOT_PIXEL_2X2,LINE_STYLE_SOLID);
    Paint_DrawLine(130,135,130,140,BLACK,DOT_PIXEL_2X2,LINE_STYLE_SOLID);
    Paint_DrawLine(125,140,136,140,BLACK,DOT_PIXEL_2X2,LINE_STYLE_SOLID);
    Paint_DrawLine(128,144,133,144,BLACK,DOT_PIXEL_2X2,LINE_STYLE_SOLID);
    Paint_DrawLine(130,148,131,148,BLACK,DOT_PIXEL_2X2,LINE_STYLE_SOLID);

        /* BAT */
    Paint_DrawRectangle(30,145,VERTICAL_SEPARATOR-20,195,GRAY,DOT_PIXEL_1X1,DRAW_FILL_FULL);
    Paint_DrawRectangle(30,145,VERTICAL_SEPARATOR-20,195,BLACK,DOT_PIXEL_1X1,DRAW_FILL_EMPTY);
    Paint_DrawChar(38,145,'+',&Font20,BACKGROUND_COLOR,BLACK);
    Paint_DrawChar(VERTICAL_SEPARATOR-40,145,'-',&Font20,BACKGROUND_COLOR,BLACK);
    Paint_DrawChar(90,170,'%',&Font20,GRAY,BLACK);


        /* Relay */
    Paint_DrawLine(15,200,15,215,BACKGROUND_COLOR,DOT_PIXEL_2X2,LINE_STYLE_SOLID);
    Paint_DrawCircle(15,215,3,BLACK,DOT_PIXEL_1X1,DRAW_FILL_FULL);
    Paint_DrawLine(15,200,20,215,BLACK,DOT_PIXEL_2X2,LINE_STYLE_SOLID);
    Paint_DrawLine(1,208,25,208,BLACK,DOT_PIXEL_2X2,LINE_STYLE_DOTTED);
    Paint_DrawString_EN(30,200,"Relay",&Font16,BACKGROUND_COLOR,BLACK);

        /* OUT */
    Paint_DrawArrow(15,225,20,DIRECTION_DOWN,RED,DRAW_FILL_FULL);
    Paint_DrawString_EN(25,220,"Iout= ",&Font16,BACKGROUND_COLOR,BLACK);


    // TEMPERATURE /////////////////////////////////////////////////////////////////
    const unsigned short TEMPERATURE_FONT_COLOR_1 = BLACK;
    Paint_DrawCircle(VERTICAL_SEPARATOR+10,HORIZONTAL_SEPARATOR_1-10,6,RED,DOT_PIXEL_1X1,DRAW_FILL_FULL);
    Paint_DrawCircle(VERTICAL_SEPARATOR+10,HORIZONTAL_SEPARATOR_1-10,6,BLACK,DOT_PIXEL_1X1,DRAW_FILL_EMPTY);
    Paint_DrawRectangle(VERTICAL_SEPARATOR+7,8,VERTICAL_SEPARATOR+13,HORIZONTAL_SEPARATOR_1-14,BLACK,DOT_PIXEL_1X1,DRAW_FILL_EMPTY);
    Paint_DrawRectangle(VERTICAL_SEPARATOR+8,20,VERTICAL_SEPARATOR+12,HORIZONTAL_SEPARATOR_1-12,RED,DOT_PIXEL_1X1,DRAW_FILL_FULL);
    Paint_SetPixel(VERTICAL_SEPARATOR+7,8,BACKGROUND_COLOR);
    Paint_SetPixel(VERTICAL_SEPARATOR+13,8,BACKGROUND_COLOR);
    for(unsigned char i = 14; i < 60;i=i+5)
    {
        Paint_DrawLine(VERTICAL_SEPARATOR+10,i,VERTICAL_SEPARATOR+12,i,BLACK,DOT_PIXEL_1X1,LINE_STYLE_SOLID);
    }
    Paint_DrawString_EN(VERTICAL_SEPARATOR+20, 8,"Cabine:",&Font16,BACKGROUND_COLOR,TEMPERATURE_FONT_COLOR_1);
    Paint_DrawString_EN(VERTICAL_SEPARATOR+20,33,"Fridge:",&Font16,BACKGROUND_COLOR,TEMPERATURE_FONT_COLOR_1);
    Paint_DrawString_EN(VERTICAL_SEPARATOR+20,58,"Elec  :",&Font16,BACKGROUND_COLOR,TEMPERATURE_FONT_COLOR_1);

    // LIGHT /////////////////////////////////////////////////////////////////
    Paint_DrawCircle(VERTICAL_SEPARATOR+20,HORIZONTAL_SEPARATOR_1+35,15,YELLOW,DOT_PIXEL_1X1,DRAW_FILL_FULL);
    Paint_DrawCircle(VERTICAL_SEPARATOR+20,HORIZONTAL_SEPARATOR_1+35,15,BLACK,DOT_PIXEL_1X1,DRAW_FILL_EMPTY);
    Paint_DrawRectangle(VERTICAL_SEPARATOR+12,HORIZONTAL_SEPARATOR_1+48,VERTICAL_SEPARATOR+28,HORIZONTAL_SEPARATOR_2-15,BLACK,DOT_PIXEL_1X1,DRAW_FILL_EMPTY);
    Paint_DrawRectangle(VERTICAL_SEPARATOR+13,HORIZONTAL_SEPARATOR_1+48,VERTICAL_SEPARATOR+27,HORIZONTAL_SEPARATOR_2-15,GRAY,DOT_PIXEL_1X1,DRAW_FILL_FULL);

    Paint_DrawLine(VERTICAL_SEPARATOR+15,HORIZONTAL_SEPARATOR_1+35,VERTICAL_SEPARATOR+25,HORIZONTAL_SEPARATOR_1+35,RED,DOT_PIXEL_1X1,LINE_STYLE_SOLID);
    Paint_DrawLine(VERTICAL_SEPARATOR+15,HORIZONTAL_SEPARATOR_1+35,VERTICAL_SEPARATOR+15,HORIZONTAL_SEPARATOR_1+47,BLACK,DOT_PIXEL_1X1,LINE_STYLE_SOLID);
    Paint_DrawLine(VERTICAL_SEPARATOR+25,HORIZONTAL_SEPARATOR_1+35,VERTICAL_SEPARATOR+25,HORIZONTAL_SEPARATOR_1+47,BLACK,DOT_PIXEL_1X1,LINE_STYLE_SOLID);


    // FRIDGE /////////////////////////////////////////////////////////////////






}

void GUI::refreshMainPage(void)
{
    Serial.print("Refresh MainPage");
    // Refresh Time


    // Refresh POWER
       
        /* LEDs */
    Serial.print(".");
    m_powerManager->getChargerStatusLed()?
    Paint_DrawCircle(70,57,6,GREEN,DOT_PIXEL_1X1,DRAW_FILL_FULL):
    Paint_DrawCircle(70,57,6,RED,DOT_PIXEL_1X1,DRAW_FILL_FULL);
    
    Serial.print(".");
    m_powerManager->getIgnitionStatus()?
    Paint_DrawCircle(140-10,57,6,BLUE,DOT_PIXEL_1X1,DRAW_FILL_FULL):
    Paint_DrawCircle(140-10,57,6,LGRAY,DOT_PIXEL_1X1,DRAW_FILL_FULL);

        /* Charge mode */
    Serial.print(".");
    switch (m_powerManager->getChargeMode())
    {
    case PowerManager::DISCONECTED:
        Paint_DrawString_EN(75,70,"NCONN",&Font16,BACKGROUND_COLOR,RED);
        break;
    case PowerManager::BULK:
        Paint_DrawString_EN(75,70,"BULK ",&Font16,BACKGROUND_COLOR,GREEN);
        break;
    case PowerManager::ABSORBSTION:
        Paint_DrawString_EN(75,70,"ABSOR",&Font16,BACKGROUND_COLOR,BLUE);
        break;
    case PowerManager::FLOAT:
        Paint_DrawString_EN(75,70,"FLOAT",&Font16,BACKGROUND_COLOR,GREEN);
        break;
    }
        /* Vbat */
    char vbat[6];
    Serial.print(".");
    sprintf(vbat,"%.1fV",float(m_powerManager->getBatVoltageMes())/1000.0);
    Paint_DrawString_EN(80,90,vbat,&Font16,BACKGROUND_COLOR,BLACK);

        /* I_in */
    char iIn[6];
    Serial.print(".");
    sprintf(iIn,"%.1fA",float(m_powerManager->getChargeCurrent())/1000.0);
    Paint_DrawString_EN(80,110,iIn,&Font16,BACKGROUND_COLOR,BLACK);

        /* Relay */
    Serial.print(".");
    m_powerManager->getBatteryConnected()?
    Paint_DrawString_EN(91,200,"ON ",&Font16,BACKGROUND_COLOR,GREEN):
    Paint_DrawString_EN(91,200,"OFF",&Font16,BACKGROUND_COLOR,RED);
        /* I_out */
    char iOut[6];
    Serial.print(".");
    sprintf(iOut,"%.1fA",float(m_powerManager->getDischargeCurrent())/1000.0);
    Paint_DrawString_EN(80,220,iOut,&Font16,BACKGROUND_COLOR,BLACK);


    // Refresh Temperature
    char cabTemp[4];
    char fridgeTemp[4]; 
    char elecTemp[4];
    
    Serial.print(".");
    sprintf(cabTemp,"%2iC",m_powerManager->getTemperatureCab());
    sprintf(fridgeTemp,"%2iC",m_fridge->getTemperatureMes());
    sprintf(elecTemp,"%2iC",m_powerManager->getTemperatureElec());

    Serial.print(".");
    Paint_DrawString_EN(240, 8,cabTemp,&Font16,BACKGROUND_COLOR,BLACK);
    Paint_DrawString_EN(240,33,fridgeTemp,&Font16,BACKGROUND_COLOR,BLACK);
    Paint_DrawString_EN(240,58,elecTemp,&Font16,BACKGROUND_COLOR,BLACK);

    // Refresh Light



    // Refresh Fridge
    Serial.print("Done \n");

}

void GUI::drawSettingsPage(void)
{
    
}

void GUI::refreshSettingsPage(void)
{
    
}

String GUI::_formatInt(int number,unsigned int digit,int multiplier,char unit)
{
    float fnumber = number/multiplier;
    char* str = new char(digit+2);

    sprintf(str,"%*f%c",digit,fnumber);

    String ret(str);
    delete str;

    return ret;
}
