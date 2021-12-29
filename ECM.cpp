#include "ECM.h"

    ECM::ECM() {}

    //Getters
    int32_t ECM::RPM() {
        return _rpm;
    }

    byte ECM::MAP() {
        return _map;
    }

    byte ECM::BARO() {
        return _baro;
    }

    int8_t ECM::CLT() {
        return _clt;
    }

    int8_t ECM::AIT() {
        return _ait;
    }

    byte ECM::OIL_PRESSURE() {
        return _oilp;
    }

    float ECM::AFR() {
        return _afr;
    }

    float ECM::LAMBDA(){
      return _lambda;
    }

    byte ECM::BOOST_PERCENT() {
        return _boostpercent;
    }

    bool ECM::SPARK_MAP() {
        return _sparkmap;
    }

    float ECM::FUEL_USAGE() {
        return _fuelusage;
    }

    int32_t ECM::SPEED() {
        return _speed;
    }

    bool ECM::LOCKED() {
      return _mutex;
    }

    //Setter Functions
    void ECM::SET_BOOST_PERCENTAGE(byte val) {
        if (val < 0) {
            val = 0;
        }
        if (val > 100) {
            val = 100;
        }
        _boostpercent = val;
    }

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

    void ECM::SET_SPARK_MAP() {
        _sparkmap = !_sparkmap;
    }

    void ECM::LOCK() { _mutex = true; }

    void ECM::UNLOCK() { _mutex = false; }

    void ECM::RPM(byte firstbyte, byte secondbyte){
      int32_t val = (int32_t)firstbyte | ((int32_t)secondbyte << 8);
      _rpm = val;
    }
    void ECM::MAP(byte byt){
      _map = byt;
    }
    void ECM::BARO(byte byt){
      _baro = byt;
    }
    void ECM::CLT(byte byt){
      _clt = byt;
    }
    void ECM::AIT(byte byt){
      _ait = byt;
    }
    void ECM::OIL_PRESSURE(byte byt){
      float val = (float)byt / 21.0f;
      val = val * 14.5038f;
      _oilp = (int32_t)val;
    }
    void ECM::AFR(byte byt){}
    void ECM::LAMBDA(byte byt){
      float val = (float)byt / 128.0f;
      _lambda = val;
      val = val * 14.68f;
      _afr = val;
    }
    void ECM::SPEED(byte firstbyte, byte secondbyte){
      int32_t val = (int32_t)firstbyte | ((int32_t)secondbyte << 8);
      _speed = val;
    }