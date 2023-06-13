#ifndef LIJNVOLGER_H
#define LIJNVOLGER_H

#include <stdint.h>
#include <Zumo32U4LineSensors.h>
#include "Motorcontroller.h"

class Lijnvolger
{
public:
  Lijnvolger(Motorcontroller*);
  void init();
  void start();
  int leesKleur();

private:
  Zumo32U4LineSensors ls;
  Motorcontroller* mc;
  unsigned int lineSensorValues[5];
  int16_t position;
  int16_t lastError;
  int16_t error;
  int16_t speedDifference;
  int16_t leftSpeed;
  int16_t rightSpeed;
  const uint16_t maxSpeed = 200;
  void calibreer();
};
#endif

