#include "Motorcontroller.h"
#include <Arduino.h>

Motorcontroller::Motorcontroller(int s):bochtsnelheid(s) {

}

void Motorcontroller::zetSnelheid(int s) {
  bochtsnelheid = s;
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