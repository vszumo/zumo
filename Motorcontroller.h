#ifndef MOTORCONTROLLER_H
#define MOTORCONTROLLER_H

#pragma once
#include <Zumo32U4Motors.h>
#include <Zumo32U4Encoders.h>

class Motorcontroller
{
public:
  Motorcontroller();
  void rijdRecht(int);
  void rijdAfstand(int, int);
  void maakBocht(bool);
  void stop();
  void zetBochtSnelheid(int);
  void zetSnelheid(int16_t, int16_t);

private: 
  Zumo32U4Motors motors;
  Zumo32U4Encoders encoders;
  int bochtsnelheid;
};

#endif

