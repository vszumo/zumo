#ifndef BOTSDETECTIE_H
#define BOTSDETECTIE_H

#include <Zumo32U4ProximitySensors.h>
#include <Zumo32U4Motors.h>
#include <Zumo32U4Encoders.h>

#define LEFT 0
#define RIGHT 1

class BotsDetectie
{
public:
  BotsDetectie();
  void start();
  void links();
  void rechts();
  void rechtdoor(int);
  void stop();


private:
  Zumo32U4ProximitySensors proxSensors;
  Zumo32U4Motors motors;
  Zumo32U4Encoders encoders;

  uint8_t leftSensor;
  uint8_t rightSensor;
  uint8_t countsLinks;
  uint8_t countsRechts;
  bool objectSeen;
  bool turningLeft;
  bool turningRight;
  uint16_t turnSpeed;
  uint16_t lastTimeObjectSeen;

  const uint16_t turnSpeedMax = 200;
  const uint16_t turnSpeedMin = 100;
  const uint16_t deceleration = 100;
  const uint16_t acceleration = 100;
  const uint8_t sensorLevel = 4;
  bool senseDir;

};
#endif

