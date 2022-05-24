 #include "PowerManager.h"

PowerManager::PowerManager(/* args */)
{
    pinMode(PIN_BAT_RELAY, OUTPUT);
    pinMode(PIN_CHARGE_LED, INPUT_PULLDOWN);
    pinMode(PIN_IGNITION, INPUT_PULLDOWN);
    pinMode(PIN_CURRENT_IN_SENSOR, ANALOG);
    pinMode(PIN_CURRENT_OUT_SENSOR, ANALOG);
    pinMode(PIN_VOLTAGE_BAT, ANALOG);
    pinMode(PIN_TEMP_CAB, ANALOG);
    pinMode(PIN_TEMP_ELEC, ANALOG);

    digitalWrite(PIN_BAT_RELAY,HIGH);

}

PowerManager::~PowerManager()
{

}

void PowerManager::init()
{
    analogReadResolution(ANALOG_RESOLUTION);
}

void PowerManager::it_update( void )
{
    m_chargeCurrent_mA      = analogRead(PIN_CURRENT_IN_SENSOR)*CURRENT_CONVERSION;
    m_dischargeCurrent_mA   = analogRead(PIN_CURRENT_OUT_SENSOR)*CURRENT_CONVERSION;
    m_batVoltageMes_mV      = analogRead(PIN_VOLTAGE_BAT)*VOLTAGE_CONVERSION;
    // m_ignitionStatus        = digitalRead(PIN_IGNITION);
    // m_chargerStatusLed      = digitalRead(PIN_CHARGE_LED);
    // m_temperatureCab        = analogRead(PIN_TEMP_CAB)*TEMPERATURE_CONVERSION;
    // m_temperatureElec       = analogRead(PIN_TEMP_ELEC)*TEMPERATURE_CONVERSION;

    /* Battery capacity */
    // refreshBatCapacity();

    /* Battery disconnect on low power */
    // if(m_batCapacity < BAT_CUTTOF_LEVEL_PERCENT or m_batVoltageMes_mV < BAT_CUTTOF_LEVEL_1)
    // {   m_batteryConnected = false; }
    // else
    // {   m_batteryConnected = true;  }

    // digitalWrite(PIN_BAT_RELAY,m_batteryConnected);
}

void PowerManager::refreshBatCapacity( void )
{
    /* BATTERY CALCULATION */
    // - Depending on the current draw, the capacity of the 
    //   battery is changing 
    // - Using peukerts equation we can calculate how many hours
    //   the battery would work with the current current (lol)
    // - The number of hours can be converted to millisecond
    // - Every 50 millisecond we assume the current was the same
    //   beetween the measure.
    // - We can then consider what percentage of the battery we lost
    // 
    // ex : 63A -> 1hour capacity 
    // in 50ms we loose 1 / 72_000 of the battery -> 0,00138 %



    // ** Peukerts equation : **
    //   T = H ( C / I / H )^n
    //   
    //   T : time remaining
    //   H : Rated Discharge time
    //   C : Capacity at rated discharge time
    //   I : Current measured
    //   n : Peukert's exponent


    // DT = 50ms = 0,05s = 0,00083333333 min = 1,3888888888 E-5 Hour

    // Current getting out of the battery 
    // negative means battery is charging
    float batCurrent_A = float(m_dischargeCurrent_mA - m_chargeCurrent_mA )/1000.0;

    double timeRemaining_hr = RATED_DISCHARGE_TIME_Hr* pow( RATED_CURRENT_A / batCurrent_A , BAT_PEUKERTS_CONST );

    m_batCapacity = m_batCapacity - ( timeRemaining_hr * IT_TIME_MS / MILLISECOND_IN_HOUR / PERCENTAGE );

    // linear regression from battery manufacturer data
    //  BAT CAPACITY = 41.13 * Voltage  - 436.2 

     
}

unsigned int PowerManager::getBatVoltageMes( void )
{
    return m_batVoltageMes_mV;
}
unsigned int PowerManager::getChargeCurrent( void )
{
    return m_chargeCurrent_mA;
}
unsigned int PowerManager::getDischargeCurrent( void )
{
    return m_dischargeCurrent_mA;
}
unsigned int PowerManager::getBatCapacity( void )
{
    return m_batCapacity;
}
bool PowerManager::getBatteryConnected ( void )
{
    return m_batteryConnected;
}
bool PowerManager::getChargerStatusLed( void )
{
    return m_chargerStatusLed;
}
PowerManager::chargeMode PowerManager::getChargeMode( void )
{
    return m_chargerMode;
}
    
bool PowerManager::getIgnitionStatus()
{
    return m_ignitionStatus;
}

unsigned int PowerManager::getTemperatureElec()
{
    return m_temperatureElec;
}

unsigned int PowerManager::getTemperatureCab()
{
    return m_temperatureCab;
}
