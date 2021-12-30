#ifndef ECM_h
#define ECM_h

#include <arduino.h>
#include "enums.h"
#include <EEPROM.h>

#define MEM_LOCATION_CHECKBYTE 0
#define MEM_LOCATION_BOOST 1
#define MEM_LOCATION_SPARK_MAP 2

class ECM
{
private:
    byte checkbyte = 0x03; //Increment this to rewrite new EEPROM values from code
    int32_t _rpm = 0;
    byte _map = 100;
    byte _baro = 100;
    int8_t _clt = 21;
    int8_t _ait = 21;
    byte _oilp = 0;
    float _afr = 22.0f;
    float _lambda = 1.0f;
    byte _boostpercent = 0;
    bool _sparkmap = false;
    float _fuelusage = 0; //@@TODO make screen for this and implement mpg etc
    int32_t _speed = 0;
    bool _mutex = false;


public:
    ECM();

    //Getters
    int32_t RPM();
    byte MAP();
    byte BARO();
    int8_t CLT();
    int8_t AIT();
    byte OIL_PRESSURE();
    float AFR();
    float LAMBDA();
    byte BOOST_PERCENT();
    bool SPARK_MAP();
    float FUEL_USAGE();
    int32_t SPEED();
    bool LOCKED();
    byte IGNITION_SWITCH_CAN_OUT();
    byte BOOST_PRESSURE_CAN_OUT();

    //Setter Functions
    void SET_BOOST_PERCENTAGE(byte);
    void SET_BOOST_PRESSURE(DIRECTION);
    void SET_SPARK_MAP();
    void LOAD_SPARK_MAP(bool);
    void LOCK();
    void UNLOCK();
    void RPM(byte, byte);
    void MAP(byte);
    void BARO(byte);
    void CLT(byte);
    void AIT(byte);
    void OIL_PRESSURE(byte);
    void AFR(byte);
    void LAMBDA(byte);
    void SPEED(byte, byte);
    void SetupEEPROM();
    void ReadEEPROM();
    void WriteEEPROM();
};

#endif