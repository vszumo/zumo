#include "Motorcontroller.h"
#include <Arduino.h>

void Motorcontroller::rijdVooruit(int snelheid) {
  motors.setSpeeds(snelheid, snelheid);
}

void Motorcontroller::maakBocht(bool bocht) {
  if(bocht){ 
    motors.setSpeeds(0, 100);
    delay(2050);
    motors.setSpeeds(0,0);
  }

  if(!bocht){ 
    motors.setSpeeds(100, 0);
    delay(2050);
    motors.setSpeeds(0,0);
  }
}

void Motorcontroller::stop() {
  motors.setSpeeds(0, 0);
}