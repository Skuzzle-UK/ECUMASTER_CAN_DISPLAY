#include "ECM.h"

//////////////////////////////////////////////////////////////

    ECM::ECM() {
      ECM::SetupEEPROM();
      ECM::ReadEEPROM();
    }

//////////////////////////////////////////////////////////////

    //Getters
    int32_t ECM::RPM() {return _rpm;}
    byte ECM::MAP() {return _map;}
    byte ECM::BARO() {return _baro;}
    int8_t ECM::CLT() {return _clt;}
    int8_t ECM::AIT() {return _ait;}
    byte ECM::OIL_PRESSURE() {return _oilp;}
    float ECM::AFR() {return _afr;}
    float ECM::LAMBDA(){return _lambda;}
    byte ECM::BOOST_PERCENT() {return _boostpercent;}
    bool ECM::SPARK_MAP() {return _sparkmap;}
    float ECM::FUEL_USAGE() {return _fuelusage;}
    int32_t ECM::SPEED() {return _speed;}
    bool ECM::LOCKED() {return _mutex;}

//////////////////////////////////////////////////////////////

    byte ECM::IGNITION_SWITCH_CAN_OUT(){
      if(_sparkmap){return 0xFF;}
      else{return 0x00;}
    }

//////////////////////////////////////////////////////////////

    byte ECM::BOOST_PRESSURE_CAN_OUT(){
      float inc = 255.0f / 100.0f;
      float val = (float)_boostpercent * inc;
      val = 255 - val;
      return (byte)val;
    }

//////////////////////////////////////////////////////////////

    //Setter Functions

    void ECM::MAP(byte byt){_map = byt;}
    void ECM::BARO(byte byt){_baro = byt;}
    void ECM::CLT(byte byt){_clt = byt;}
    void ECM::AIT(byte byt){_ait = byt;}
    void ECM::AFR(byte byt){}

//////////////////////////////////////////////////////////////

    void ECM::SET_BOOST_PERCENTAGE(byte val) {
        if (val <= 1) {
            val = 1;
        }
        if (val >= 100) {
            val = 100;
        }
        _boostpercent = val;
    }

//////////////////////////////////////////////////////////////

    void ECM::SET_BOOST_PRESSURE(DIRECTION dir){
      switch(dir){
        case DIRECTION::UP: {
          ECM::SET_BOOST_PERCENTAGE(_boostpercent + 1);
          break;
        }
        case DIRECTION::DOWN: {
          ECM::SET_BOOST_PERCENTAGE(_boostpercent - 1);
          break;
        }
      }
    }

//////////////////////////////////////////////////////////////

    void ECM::SET_SPARK_MAP() {_sparkmap = !_sparkmap;}
    void ECM::LOAD_SPARK_MAP(bool val){ _sparkmap = val; }
    void ECM::LOCK() { _mutex = true; }
    void ECM::UNLOCK() {
      _mutex = false;
      ECM::WriteEEPROM();
    }

//////////////////////////////////////////////////////////////
    
    void ECM::RPM(byte firstbyte, byte secondbyte){
      int32_t val = (int32_t)firstbyte | ((int32_t)secondbyte << 8);
      _rpm = val;
    }

//////////////////////////////////////////////////////////////

    void ECM::OIL_PRESSURE(byte byt){
      float val = (float)byt / 21.0f;
      val = val * 14.5038f;
      _oilp = (int32_t)val;
    }

//////////////////////////////////////////////////////////////  

    void ECM::LAMBDA(byte byt){
      float val = (float)byt / 128.0f;
      _lambda = val;
      val = val * 14.68f;
      _afr = val;
    }

//////////////////////////////////////////////////////////////

    void ECM::SPEED(byte firstbyte, byte secondbyte){
      int32_t val = (int32_t)firstbyte | ((int32_t)secondbyte << 8);
      _speed = val;
    }

//////////////////////////////////////////////////////////////

void ECM::SetupEEPROM(){
  byte savedcheckbyte;
  EEPROM.get(MEM_LOCATION_CHECKBYTE, savedcheckbyte);
  if (savedcheckbyte != checkbyte){
    EEPROM.put(MEM_LOCATION_CHECKBYTE, checkbyte);
    EEPROM.put(MEM_LOCATION_BOOST, 0x01);
    EEPROM.put(MEM_LOCATION_SPARK_MAP, false);
  }
}

//////////////////////////////////////////////////////////////

void ECM::ReadEEPROM(){
  EEPROM.get(MEM_LOCATION_BOOST, _boostpercent);
  EEPROM.get(MEM_LOCATION_SPARK_MAP, _sparkmap);
}

//////////////////////////////////////////////////////////////

void ECM::WriteEEPROM(){
    EEPROM.put(MEM_LOCATION_BOOST, _boostpercent);
    EEPROM.put(MEM_LOCATION_SPARK_MAP, _sparkmap);
}

//////////////////////////////////////////////////////////////