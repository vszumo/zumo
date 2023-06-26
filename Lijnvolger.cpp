#include "Lijnvolger.h"
#include <Arduino.h>

// Lijnvolger() construeert de Lijnvoolger klasse door de linesensor aan te maken en de motorcontroller pointer op te slaan.
Lijnvolger::Lijnvolger(Motorcontroller* m):ls(),mc(m) {
}

// init() initialiseert de linesensor en roept calibreerzwart() aan.
void Lijnvolger::init() {
  ls.initFiveSensors();
  calibreerzwart();
  calibreerkleuren();
}

// calibreerzwart() draait naar links en rechts en calibreert herhaaldelijk de zwartwaarde van de lijnsensoren.
void Lijnvolger::calibreerzwart() {
  delay(1000);
  // Draai heen en weer en calibreer de sensoren steeds
  for(uint16_t i = 0; i < 120; i++) {
    // tussen waarde 30 en 90 van i wordt linksom gedraaid en anders rechtsom
    if (i > 30 && i <= 90) {
      mc->maakBocht(0);
    } else {
      mc->maakBocht(1);
    }

    ls.calibrate();
  }

  // als de loop klaar is worden de motoren weer uitgezet
  mc->stop();
}

// calibreerkleuren() slaat van alle sensoren de waarden per kleur op zodat deze later kunnen worden gebruikt om te checken welke kleur de lijn heeft.
void Lijnvolger::calibreerkleuren() {
  // er draait een loopje wat grijs, bruin en groen opslaat in een 2 dimensionale array
  for (unsigned int kleur=0; kleur<3; kleur++) {
    // de waardes worden pas opgeslagen zodra buttonC is ingedrukt zodat de gebruiker de tijd heeft om de robot goed te positioneren
    buttonc.waitForButton();
    ls.readCalibrated(lineSensorValues);
    
    // sensor links, midden en rechts worden opgeslagen in de 2 dimensionale array
    waardes[kleur][0] = lineSensorValues[0];
    waardes[kleur][1] = lineSensorValues[2];
    waardes[kleur][2] = lineSensorValues[4];
  }
}

// start() leest de waarden van de Linesensor in en stelt de motoren in om de juiste richting te volgen.
void Lijnvolger::start() {
  //Lees de kleuren van de sensoren in en check of ze allemaal wit zijn
  kleur l = leesKleur(0);
  kleur m = leesKleur(2);
  kleur r = leesKleur(4);
  /*
  if (l==kleur::WIT && m==kleur::WIT && r==kleur::WIT) {
    mc->rijdAfstand(200, 5);
    return;
  }
  */

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
  if (m==kleur::GROEN) {
    leftSpeed = constrain(leftSpeed, 0, (int16_t)maxSpeed)/2;
    rightSpeed = constrain(rightSpeed, 0, (int16_t)maxSpeed)/2;
  }

  mc->zetSnelheid(leftSpeed, rightSpeed);  
}

// leesKleur(int) geeft aan de hand van welk sensornummer wordt gevraagd de juiste kleurwaarde terug
kleur Lijnvolger::leesKleur(int sensor) {
  // de waarde wordt opgehaald uit de lijnsensor
  ls.readCalibrated(lineSensorValues);
  unsigned int waarde = lineSensorValues[sensor];

  // de sensorwaarde wordt omgezet naar een kleur en teruggestuurd
  if (waarde >= 700) return kleur::ZWART;

  unsigned int grijs = waardes[0][sensor];
  if (waarde >= grijs-25 && waarde <= grijs+25) return kleur::GRIJS;
  
  unsigned int bruin = waardes[1][sensor];
  if (waarde >= bruin-25 && waarde <= bruin+25) return kleur::BRUIN;

  unsigned int groen = waardes[2][sensor];
  if (waarde >= groen-25 && waarde <= groen+25) return kleur::GROEN;
  
  if (waarde <= 50) return kleur::WIT;

  // als geen van de kleuren overeen komt wordt kleur::ANDERS teruggegeven
  return kleur::ANDERS;
}