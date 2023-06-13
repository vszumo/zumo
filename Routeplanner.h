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

private:
  Motorcontroller* mc;
  Lijnvolger lv;
  BotsDetectie bd;

};
#endif

