#include "BotsDetectie.h";
#include <Arduino.h>;

BotsDetectie::BotsDetectie():
  proxSensors(),motors(),leftSensor(0),rightSensor(0),objectSeen(false),turningLeft(false),turningRight(false),turnSpeed(turnSpeedMax),lastTimeObjectSeen(0),senseDir(RIGHT) {
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

    if (objectSeen) {
      //Object is zichtbaar.
      rechtdoor(500);
      lastTimeObjectSeen = millis();
      //(left_sensor < right_sensor) && (left_sensor-right_sensor > 1)
      //(left_sensor > right_sensor) && (left_sensor-right_sensor > 1)
      if (leftSensor < rightSensor) {
        //Rechter sensor value is groter, dus stuur naar rechts.
        rechts();
        senseDir = RIGHT;
      } else if (leftSensor > rightSensor) {
        //Linker sensor value is groter, dus stuur naar links.
        links();
        senseDir = LEFT;
      } else {
        //sensor zijn gelijk, dus rij richting.
        rechtdoor(500);
      }
    } else {
      //Geen object is zichtbaar, dus draai richting het laatst gevonden object.
      if (senseDir == RIGHT) {
        rechts();
      } else {
        links();
      }
    }
  }
}

void BotsDetectie::links() {
  motors.setSpeeds(turnSpeed, -turnSpeed);
  turningLeft = false;
  turningRight = true;
}

void BotsDetectie::rechts() {
  motors.setSpeeds(-turnSpeed, turnSpeed);
  turningLeft = true;
  turningRight = false;
}

void BotsDetectie::rechtdoor(int s) {
  motors.setSpeeds(s, s);
}

void BotsDetectie::stop() {
  motors.setSpeeds(0, 0);
  turningLeft = false;
  turningRight = false;
}
