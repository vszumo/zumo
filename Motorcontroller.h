#ifndef MOTORCONTROLLER_H
#define MOTORCONTROLLER_H

#pragma once
#include <Zumo32U4Motors.h>

class Motorcontroller
{
public:
  Motorcontroller();
  void rijdRecht(int);
  void maakBocht(bool);
  void stop();
  void zetBochtSnelheid(int);
  void zetSnelheid(int16_t, int16_t);

private: 
  Zumo32U4Motors motors;
  int bochtsnelheid;
};

#endif

