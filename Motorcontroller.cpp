#include "Motorcontroller.h"
#include <Arduino.h>

Motorcontroller::Motorcontroller(int s):bochtsnelheid(s) {

}

void Motorcontroller::rijdRecht(int snelheid) {
  motors.setSpeeds(snelheid, snelheid);
}

void Motorcontroller::maakBocht(bool bocht) {
  if(bocht){ 
    motors.setSpeeds(0, bochtsnelheid);
    delay(2050);
    stop();
  }

  if(!bocht){ 
    motors.setSpeeds(bochtsnelheid, 0);
    delay(2050);
    stop();
  }
}

void Motorcontroller::stop() {
  motors.setSpeeds(0, 0);
}