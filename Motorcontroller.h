#ifndef MOTORCONTROLLER_H
#define MOTORCONTROLLER_H

#pragma once
#include <Zumo32U4Motors.h>

class Motorcontroller
{
public:
  Motorcontroller(int);
  void rijdRecht(int);
  void maakBocht(bool);
  void stop();
  void zetSnelheid(int);

private: 
  Zumo32U4Motors motors;
  int bochtsnelheid;
};

#endif

