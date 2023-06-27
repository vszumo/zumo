#include "BotsDetectie.h"
#include <Arduino.h>

// BotsDetectie() construeert de botsdetectie, initialiseert hierbij een aantal attributen en de proximity sensor.
BotsDetectie::BotsDetectie(Motorcontroller* m):
  mc(m), proxSensors(),leftSensor(0),rightSensor(0),objectSeen(false),turningLeft(false),turningRight(false),turnSpeed(turnSpeedMax),lastTimeObjectSeen(0),senseDir(RIGHT) {
  proxSensors.initThreeSensors();
}

// start() begint de botsdetectie cyclus
void BotsDetectie::start() {

    //Zorgen dat er waardes worden gelezen met de sensor.
    proxSensors.read();

    //int waardes van sensoren toekennen.
    leftSensor = proxSensors.countsFrontWithLeftLeds();
    rightSensor = proxSensors.countsFrontWithRightLeds();

    //opslaan of er een object zichtbaar is
    objectSeen = leftSensor >= sensorLevel || rightSensor >= sensorLevel;

    if (objectSeen) { 
      //Om oscillatie te voorkomen, remmen we de motoren af.
      turnSpeed -= deceleration;
    } else {
      //Object is niet zichtbaar dus we versnellen de motor.
      turnSpeed += acceleration;
    }

    //Gemiddelde van turnspeed.
    turnSpeed = constrain(turnSpeed, turnSpeedMin, turnSpeedMax);
    mc->zetBochtSnelheid(turnSpeed);

    //Object is zichtbaar.
    if (objectSeen) {
      
      //rijd vooruit en sla de huidige tijd op waarop een object is gezien
      mc->rijdRecht(500);
      lastTimeObjectSeen = millis();

      //Rechter sensor value is groter, dus stuur naar rechts.
      if (leftSensor < rightSensor) {
        links();
        senseDir = RIGHT;
      }
      
      //Linker sensor value is groter, dus stuur naar links.
      else if (leftSensor > rightSensor) {
        rechts();
        senseDir = LEFT;
      }
      
      //sensor zijn gelijk, dus rij richting.
      else {
        mc->rijdRecht(500);
      }

    }
    
    //Geen object is zichtbaar, dus draai richting het laatst gevonden object.
    else {
      if (senseDir == RIGHT) {
        links();
      } else {
        rechts();
      }
    }
  
}

// links() roept de motorcontroller om linksaf te slaan en slaat de richting op
void BotsDetectie::links() {
  mc->maakBocht(0);
  turningLeft = true;
  turningRight = false;
}

// rechts() roept de motorcontroller om rechtsaf te slaan en slaat de richting op
void BotsDetectie::rechts() {
  mc->maakBocht(1);
  turningLeft = false;
  turningRight = true;
}

// stop() roept de motorcontroller aan om te stoppen en slaat de richting op
void BotsDetectie::stop() {
  mc->stop();
  turningLeft = false;
  turningRight = false;
}
