#include "Fridge.h"

Fridge::Fridge( void )
{
    pinMode( PIN_FRIDGE , OUTPUT );
}

Fridge::~Fridge()
{
}

void Fridge::it_update(void)
{
    // Read sensor


    // if tempMes <= tempSet
    //      MOS_OFF
    // else
    //      MOS_ON

    digitalWrite(PIN_FRIDGE, m_relayState); 
}   

void Fridge::setTemperature(int setTemp_mC )
{
    m_tempSet = setTemp_mC;
}

int Fridge::getTemperatureSet( void )
{
    return m_tempSet;
}

int Fridge::getTemperatureMes( void )
{
    return m_tempMes;
}