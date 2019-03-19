#ifndef _RELAY_H
#define _RELAY_H

#include "Arduino.h"
  
class Relay {
public:
    Relay(uint8_t pin, bool isNormallyOpen = false);
    void begin();
    bool getState();
    void turnOn();
    void turnOff();

private:
    uint8_t pin;
    bool normallyOpen;
    bool state;
};

#endif // END _RELAY_H
