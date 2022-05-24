////////////////////////////////////
//          L I G H T             //
////////////////////////////////////
// 
//  Control 12V Led strip using PWM 
//  via MOSFET.
//  
//  can be controlled via 
//  potentiometer
//  
//

#ifndef LIGHT_H
#define LIGHT_H

#include <Arduino.h>
#include "../PINS.h"

#define MAX_ADC_MES 2450        // 2450mv at 11dB attenuation
#define ANALOG_SCALE 4095       // 2^12 -1
#define ANALOG_RESOLUTION 12
#define PWM_LIGHT_CONVERSION 255 / ANALOG_SCALE


class Light
{
public:
    Light(/* args */);
    ~Light();
    void            it_update(void);
    unsigned int    getLightPower( void );
    unsigned int    getPotMes( void );
private:
    unsigned int m_potMesure = 0;
    unsigned int m_potSaved = 0;
    unsigned char m_lightPower = 0;
};

#endif // !LIGHT_H