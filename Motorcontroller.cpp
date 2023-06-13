#include "Motorcontroller.h"
#include <Arduino.h>

#define toerenpercm 95

Motorcontroller::Motorcontroller():bochtsnelheid(0),motors(),encoders() {
  encoders.init();
}

void Motorcontroller::zetBochtSnelheid(int s) {
  bochtsnelheid = s;
}

void Motorcontroller::zetSnelheid(int16_t l, int16_t r) {
  motors.setSpeeds(l, r);
}

void Motorcontroller::rijdRecht(int snelheid) {
  motors.setSpeeds(snelheid, snelheid);
}

void Motorcontroller::rijdAfstand(int snelheid, int afstand) {
  int16_t begin = encoders.getCountsLeft();
  motors.setSpeeds(snelheid, snelheid);
  while (encoders.getCountsLeft - begin <= toerenpercm*afstand);
  stop();
  
}

void Motorcontroller::maakBocht(bool bocht) {
  if(bocht) motors.setSpeeds(-bochtsnelheid, bochtsnelheid);

  if(!bocht) motors.setSpeeds(bochtsnelheid, -bochtsnelheid);
}

void Motorcontroller::stop() {
  motors.setSpeeds(0, 0);
}