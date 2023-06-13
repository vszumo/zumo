#include "Motorcontroller.h"
#include <Arduino.h>

Motorcontroller::Motorcontroller():bochtsnelheid(0) {

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

void Motorcontroller::maakBocht(bool bocht) {
  if(bocht) motors.setSpeeds(-bochtsnelheid, bochtsnelheid);

  if(!bocht) motors.setSpeeds(bochtsnelheid, -bochtsnelheid);
}

void Motorcontroller::stop() {
  motors.setSpeeds(0, 0);
}