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
  Motorcontroller* mc;
  Lijnvolger lv;
  BotsDetectie bd;
  Zumo32U4IMU imu;
  bool links;
  bool rechts;
  bool beide;
  bool cirkel;

};
#endif

