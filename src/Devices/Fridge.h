////////////////////////////////////
//         F R I D G E            //
////////////////////////////////////
// 
//  Control 12V fridge using PWM 
//  via MOSFET.
//  
//  Temperature is measured using
//  -----
//


#ifndef FRIDGE_H
#define FRIDGE_H

#include "../PINS.h"
#include <Arduino.h>

class Fridge
{
public:
    Fridge(/* args */);
    ~Fridge();

    void setTemperature(int setTemp_mC );
    int getTemperatureSet( void );
    int getTemperatureMes( void );
    
    void it_update( void );

private:
    int m_tempSet = 0;
    int m_tempMes = 0;
    bool m_relayState = true;
};


#endif // !FRIDGE_H