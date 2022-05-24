#ifndef PINS_H
#define PINS_H


#define PIN_FRIDGE              17 

#define PIN_POTENTIOMETER       35
#define PIN_LED                 16 

#define PIN_CURRENT_IN_SENSOR   36
#define PIN_CURRENT_OUT_SENSOR  39
#define PIN_VOLTAGE_BAT         32
#define PIN_TEMP_ELEC           33
#define PIN_TEMP_CAB            34
#define PIN_IGNITION            -1 //////////////////////////////
#define PIN_BAT_RELAY           19 
#define PIN_CHARGE_LED          21

#define PIN_LCD_CS              5
#define PIN_LCD_DC              15
#define PIN_LCD_RST             2
#define PIN_LCD_BL              4
#define PIN_LCD_CS              5
#define PIN_LCD_CLK             18
#define PIN_LCD_DIN             23

#define PIN_BUTTON_1            3   
#define PIN_BUTTON_2            1   
#define PIN_BUTTON_3            22  


/*  ASCII art from : https://gist.github.com/iamamused/42cad8a59547ed5580e78d5274220813

                                         +-----------------------+
                                         | O      | USB |      O |
                                         |        -------        |
                                     3V3 | [ ]               [ ] | VIN
                                     GND | [ ]               [ ] | GND
                          [ PIN_LCD_DC ] | [X]               [ ] | GPIO13 / ADC2_4 / HSPI_ID / Touch4
                         [ PIN_LCD_RST ] | [X]               [ ] | GPIO12 / ADC2_5 / HSPI_Q / Touch5
                          [ PIN_LCD_BL ] | [X]               [ ] | GPIO14 / ADC2_6 / HSPI_CLK / Touch6
                             [ PIN_LED ] | [X]               [ ] | GPIO27 / ADC2_7 / Touch7
                          [ PIN_FRIDGE ] | [X]               [ ] | GPIO26 / ADC2_9 / DAC2
                          [ PIN_LCD_CS ] | [X]  ___________  [ ] | GPIO25 / ADC2_8 / DAC1
                         [ PIN_LCD_CLK ] | [X] |           | [X] | [ PIN_TEMP_ELEC ]
                       [ PIN_BAT_RELAY ] | [X] |           | [X] | [ PIN_VOLTAGE_BAT ]
                      [ PIN_CHARGE_LED ] | [X] |           | [X] | [ PIN_POTENTIOMETER ]
                        [ PIN_BUTTON_1 ] | [X] |           | [X] | [ PIN_TEMP_CAB ] 
                        [ PIN_BUTTON_2 ] | [X] |           | [X] | [ PIN_CURRENT_OUT_SENSOR ]
                        [ PIN_BUTTON_3 ] | [X] |           | [X] | [ PIN_CURRENT_IN_SENSOR ]
                         [ PIN_LCD_DIN ] | [X] |___________| [ ] | EN 
                                         |                       |
                                         |  |  |  ____  ____  |  |
                                         |  |  |  |  |  |  |  |  |
                                         |  |__|__|  |__|  |__|  |
                                         | O                   O |
                                         +-----------------------+

*/





#endif // PINS_H