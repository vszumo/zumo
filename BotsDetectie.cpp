#include "BotsDetectie.h"
#include <Arduino.h>

BotsDetectie::BotsDetectie(Motorcontroller* m):
  mc(m), proxSensors(),leftSensor(0),rightSensor(0),objectSeen(false),turningLeft(false),turningRight(false),turnSpeed(turnSpeedMax),lastTimeObjectSeen(0),senseDir(RIGHT) {
  proxSensors.initThreeSensors();
}

void BotsDetectie::start() {
  while(true) {
    //Zorgen dat er waardes worden gelezen met de sensor.
    proxSensors.read();
    //int waardes van sensoren toekennen.
    leftSensor = proxSensors.countsFrontWithLeftLeds();
    rightSensor = proxSensors.countsFrontWithRightLeds();

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

    if (objectSeen) {
      //Object is zichtbaar.
      mc->rijdRecht(500);
      lastTimeObjectSeen = millis();

      if (leftSensor < rightSensor) {
        //Rechter sensor value is groter, dus stuur naar rechts.
        links();
        senseDir = RIGHT;

      } else if (leftSensor > rightSensor) {
        //Linker sensor value is groter, dus stuur naar links.
        rechts();
        senseDir = LEFT;

      } else {
        //sensor zijn gelijk, dus rij richting.
        mc->rijdRecht(500);
      }
    } else {
      //Geen object is zichtbaar, dus draai richting het laatst gevonden object.
      if (senseDir == RIGHT) {
        links();
      } else {
        rechts();
      }
    }
  }
}

void BotsDetectie::links() {
  mc->maakBocht(0);
  turningLeft = true;
  turningRight = false;
}

void BotsDetectie::rechts() {
  mc->maakBocht(1);
  turningLeft = false;
  turningRight = true;
}

void BotsDetectie::stop() {
  mc->stop();
  turningLeft = false;
  turningRight = false;
}
