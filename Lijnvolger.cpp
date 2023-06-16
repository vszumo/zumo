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
  // Draai heen en weer en calibreer de sensoren steeds
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
  //Lees de kleuren van de sensoren in en check of ze allemaal wit zijn
  kleur l = leesKleur(0);
  kleur m = leesKleur(2);
  kleur r = leesKleur(4);
  if (l==kleur::WIT && m==kleur::WIT && r==kleur::WIT) {
    mc->rijdAfstand(200, 5);
    return;
  }

  //Zo bepalen we de positie van de robot.
  position = ls.readLine(lineSensorValues);
  //Serial.println(position);

  //De error die wie hier maken is hoe ver de Zumo van de midden van de lijn verwijderd is, dit komt overeen met de positie 2000.
  error = position - 2400;

  //Dit is een speciale formule om de speedDifference uit te rekenen.
  speedDifference = error / 4 + 6 * (error - lastError);
  lastError = error;

  //Hiermee pakken we de snelheden van links en rechts, de speedDifference bepaald of die links of rechts stuurt.
  leftSpeed = (int16_t)maxSpeed + speedDifference;
  rightSpeed = (int16_t)maxSpeed - speedDifference;

  //Hiermee beperken we de snelheden van 0 tot de maxSpeed die we eerder hebben ingesteld. Hij rijdt in principe altijd op de maximale snelheid tenzij die stilstaat.
  leftSpeed = constrain(leftSpeed, 0, (int16_t)maxSpeed);
  rightSpeed = constrain(rightSpeed, 0, (int16_t)maxSpeed);
  if (m==kleur::GROEN) {
    leftSpeed = constrain(leftSpeed, 0, (int16_t)maxSpeed)/2;
    rightSpeed = constrain(rightSpeed, 0, (int16_t)maxSpeed)/2;
  }

  mc->zetSnelheid(leftSpeed, rightSpeed);  
}

kleur Lijnvolger::leesKleur(int sensor) {
  //Lees waardes uit de sensor en return de overeenkomende kleur
  ls.readCalibrated(lineSensorValues);
  unsigned int waarde = lineSensorValues[sensor];

  if (waarde >= 700) return kleur::ZWART;
  if (waarde > 175 && waarde < 400) return kleur::GRIJS;
  if (waarde > 75 && waarde < 175) return kleur::GROEN;
  if (waarde <= 50) return kleur::WIT;

  return kleur::ANDERS;
}