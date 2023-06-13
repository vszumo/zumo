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

private:
  Zumo32U4LineSensors ls;
  Motorcontroller* mc;
  void calibreer();
};
#endif

