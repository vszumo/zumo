#ifndef ROUTEPLANNER_H
#define ROUTEPLANNER_H

#include "Motorcontroller.h"
#include "Lijnvolger.h"
#include "BotsDetectie.h"

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
  bool links;
  bool rechts;
  bool beide;
  bool cirkel;

};
#endif

