#include "Lijnvolger.h"
#include <Arduino.h>

Lijnvolger::Lijnvolger(Motorcontroller* m):ls(),mc(m) {
}

void Lijnvolger::init() {
  ls.initFiveSensors();
  calibreer();
}

void Lijnvolger::calibreer() {
  delay(1000);
  for(uint16_t i = 0; i < 120; i++) {
    if (i > 30 && i <= 90) {
      mc->maakBocht(0);
    } else {
      mc->maakBocht(1);
    }

    ls.calibrate();
  }
  mc->stop();
}

void Lijnvolger::start() {
  //Zo bepalen we de positie van de robot.
  position = ls.readLine(lineSensorValues);
  //Serial.println(position);

  //De error die wie hier maken is hoe ver de Zumo van de midden van de lijn verwijderd is, dit komt overeen met de positie 2000.
  error = position - 2000;

  //Dit is een speciale formule om de speedDifference uit te rekenen.
  speedDifference = error / 4 + 6 * (error - lastError);
  lastError = error;

  //Hiermee pakken we de snelheden van links en rechts, de speedDifference bepaald of die links of rechts stuurt.
  leftSpeed = (int16_t)maxSpeed + speedDifference;
  rightSpeed = (int16_t)maxSpeed - speedDifference;

  //Hiermee beperken we de snelheden van 0 tot de maxSpeed die we eerder hebben ingesteld. Hij rijdt in principe altijd op de maximale snelheid tenzij die stilstaat.
  leftSpeed = constrain(leftSpeed, 0, (int16_t)maxSpeed);
  rightSpeed = constrain(rightSpeed, 0, (int16_t)maxSpeed);

  mc->zetSnelheid(leftSpeed, rightSpeed);  
}

int Lijnvolger::leesKleur() {
  ls.readCalibrated(lineSensorValues);
  for(int i =0; i<5;i++){
    Serial.print(lineSensorValues[i]);
    Serial.print(", ");
  
  }
  Serial.println("");
  return 0;  
}