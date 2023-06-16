#include "Motorcontroller.h"
#include <Arduino.h>

#define toerenpercm 150

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
  while (encoders.getCountsLeft() - begin <= toerenpercm*afstand);
  stop();
  
}

void Motorcontroller::maakBocht(bool bocht) {
  if(bocht) motors.setSpeeds(-bochtsnelheid, bochtsnelheid);

  if(!bocht) motors.setSpeeds(bochtsnelheid, -bochtsnelheid);
}


void Motorcontroller::maakAfslag(bool bocht) {
  Serial.println("afslag");
  if(bocht) {
    int16_t begin = encoders.getCountsLeft();
    motors.setSpeeds(-bochtsnelheid, bochtsnelheid);
    while(begin - encoders.getCountsLeft() <= toerenpercm*5);
    stop();
  }
  if (!bocht) {
    int16_t begin = encoders.getCountsRight();
    motors.setSpeeds(bochtsnelheid, -bochtsnelheid);
    while(begin - encoders.getCountsRight() <= toerenpercm*5);
    stop();
  }
  Serial.println("afslag klaar");
}

void Motorcontroller::stop() {
  motors.setSpeeds(0, 0);
}