#ifndef POWERMANAGER_H
#define POWERMANAGER_H

#include <Arduino.h>
#include "../PINS.h"

// At 5v, sensor output 66mV per Amp
// need resistor so lower it down to 2.45v of esp
// 

#define MAX_ADC_MES 2450        // 2450mv at 11dB attenuation
#define ANALOG_SCALE 4095       // 2^12 -1
#define ANALOG_RESOLUTION 12
#define VOLTAGE_CONVERSION MAX_ADC_MES / ANALOG_SCALE
#define CURRENT_CONVERSION MAX_ADC_MES / ANALOG_SCALE
#define TEMPERATURE_CONVERSION MAX_ADC_MES / ANALOG_SCALE

#define BAT_CUTTOF_LEVEL_1 10500
#define BAT_CUTTOF_LEVEL_2 9600
#define BAT_CUTTOF_LEVEL_PERCENT 60
#define BAT_PEUKERTS_CONST 1.251031242
#define RATED_CAPACITY_AHr 100
#define RATED_DISCHARGE_TIME_Hr 10
#define RATED_CURRENT_A RATED_CAPACITY_AHr/RATED_DISCHARGE_TIME_Hr
#define IT_TIME_MS 50
#define MILLISECOND_IN_HOUR 3600000 
#define PERCENTAGE 100

class PowerManager
{
public:
    PowerManager(/* args */);
    ~PowerManager();

    enum chargeMode
    {
        DISCONECTED,
        BULK,
        ABSORBSTION,
        FLOAT
    };


    void            init                    ( void );
    void            it_update               ( void );

    unsigned int    getBatVoltageMes        ( void );
    unsigned int    getChargeCurrent        ( void );
    unsigned int    getDischargeCurrent     ( void );
    unsigned int    getTemperatureElec      ( void );
    unsigned int    getTemperatureCab       ( void );
    unsigned int    getBatCapacity          ( void );
    bool            getBatteryConnected     ( void );
    bool            getChargerStatusLed     ( void );
    chargeMode      getChargeMode           ( void );
    bool            getIgnitionStatus       ( void );
    


private:
    void            refreshBatCapacity(void);

    unsigned int    m_batVoltageMes_mV = 12900;
    unsigned int    m_chargeCurrent_mA = 0;
    unsigned int    m_dischargeCurrent_mA = 0;
    double          m_batCapacity = 60/100;
    bool            m_batteryConnected = true;
    bool            m_chargerStatusLed = false;
    bool            m_ignitionStatus = false;
    chargeMode      m_chargerMode = DISCONECTED;
    unsigned int    m_temperatureElec = 0;
    unsigned int    m_temperatureCab = 0;
};

#endif // !POWERMANAGER_H