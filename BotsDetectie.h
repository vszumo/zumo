#ifndef BOTSDETECTIE_H
#define BOTSDETECTIE_H

#include <Zumo32U4ProximitySensors.h>
#include <Zumo32U4Motors.h>
#include <Zumo32U4Encoders.h>
#include "Motorcontroller.h"

#define LEFT 0
#define RIGHT 1

/**
 * @brief Botsdetectie klasse die gebruikt wordt om een object te vinden en deze uit een cirkel te duwen.
 */
class BotsDetectie
{
public:
  /**
   * Construeer de Botsdetectie.
   * @brief Constructor.
   * @param mc Pointer van de motorcontroller.
   */
  BotsDetectie(Motorcontroller*);

  /**
   * @brief Start het Botsdetectie proces.
   */
  void start();

  /**
   * @brief Draai naar links.
   */
  void links();

  /**
   * @brief Draai naar rechts.
   */
  void rechts();

  /**
   * @brief Stop met bewegen.
   */
  void stop();


private:
  /**
   * Pointer van de motorcontroller
   */
  Motorcontroller* mc;

  /**
   * Zumo32U4ProximitySensors object waarmee de proximitysensors worden uitgelezen.
   */
  Zumo32U4ProximitySensors proxSensors;

  /**
   * Zumo32U4Encoders object waarmee de encoders worden uitgelezen.
   */
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

