#ifndef ROUTEPLANNER_H
#define ROUTEPLANNER_H

#include "Motorcontroller.h"
#include "Lijnvolger.h"
#include "BotsDetectie.h"
#include "Zumo32U4IMU.h"
#include <Wire.h>

class Routeplanner
{
public:
  Routeplanner(Motorcontroller*);
  void init();
  void start();
  void printKleur();

private:
  /**
   * Pointer van de motorcontroller.
   */
  Motorcontroller* mc;

  /**
   * Lijnvolger object wat aangeroepen kan worden.
   */
  Lijnvolger lv;

  /**
   * BotsDetectie object wat aangeroepen kan worden.
   */
  BotsDetectie bd;

  /**
   * Zumo32U4IMU object waarmee de accelerometer uitgelezen wordt.
   */
  Zumo32U4IMU imu;

  /**
   * Is er op dit moment opgeslagen dat de robot linksaf moet slaan.
   */
  bool links;

  /**
   * Is er op dit moment opgeslagen dat de robot rechtsaf moet slaan.
   */
  bool rechts;

  /**
   * Bevind de robot zich op dit moment in de cirkel (botsdetectie modus).
   */
  bool cirkel;

};
#endif

