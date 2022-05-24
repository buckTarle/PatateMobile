#include "Light.h"



Light::Light(/* args */)
{
    pinMode(PIN_LED, OUTPUT);
    pinMode(PIN_POTENTIOMETER, ANALOG );
}

Light::~Light()
{
}

void Light::it_update( void )
{
    m_potMesure = analogRead(PIN_POTENTIOMETER);
    m_lightPower = m_potMesure * PWM_LIGHT_CONVERSION;
    analogWrite( PIN_LED, m_lightPower );
}

unsigned int Light::getLightPower( void )
{
    return m_lightPower;
}

unsigned int Light::getPotMes(void)
{
    return m_potMesure;
}

