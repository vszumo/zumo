#ifndef LIJNVOLGER_H
#define LIJNVOLGER_H

#include <stdint.h>
#include <Zumo32U4LineSensors.h>
#include <Zumo32U4Buttons.h>
#include "Motorcontroller.h"

// Declareer lijstje met kleuren
enum kleur : uint8_t {
  ANDERS,
  ZWART,
  GRIJS,
  BRUIN,
  GROEN,
  WIT
};

class Lijnvolger
{
public:
  Lijnvolger(Motorcontroller*);
  void init();
  void start();
  kleur leesKleur(int);

private:
  Zumo32U4LineSensors ls;
  Motorcontroller* mc;
  Zumo32U4ButtonC buttonc;
  unsigned int lineSensorValues[5];
  unsigned int waardes[3][5];
  int16_t position;
  int16_t lastError;
  int16_t error;
  int16_t speedDifference;
  int16_t leftSpeed;
  int16_t rightSpeed;
  const uint16_t maxSpeed = 200;
  void calibreerzwart();
  void calibreerkleuren();
};
#endif

