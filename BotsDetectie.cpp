#include "BotsDetectie.h";
#include <Arduino.h>;

BotsDetectie::BotsDetectie():
  proxSensors(),motors(),turningLeft(false),turningRight(false),turnSpeed(turnSpeedMax),lastTimeObjectSeen(0),senseDir(RIGHT) {
  proxSensors.initThreeSensors();
}

void BotsDetectie::start() {
  while(true) {

    proxSensors.read();

    leftSensor = proxSensors.countsFrontWithLeftLeds();
    rightSensor = proxSensors.countsFrontWithRightLeds();

    bool objectSeen = leftSensor >= sensorLevel || rightSensor >= sensorLevel;

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
      rechtdoor(500);
      lastTimeObjectSeen = millis();

      if (leftSensor < rightSensor) {
        rechts();
        senseDir = RIGHT;

      } else if (leftSensor > rightSensor) {
        links();
        senseDir = LEFT;
        
      } else {
        rechtdoor(500);
      }
    } else {
      if (senseDir == RIGHT)
      {

      rechts();

      } else {
      
      links();

      }
    }
  }
}

void BotsDetectie::links() {
  motors.setSpeeds(-turnSpeed, turnSpeed);
  turningLeft = false;
  turningRight = true;
}

void BotsDetectie::rechts() {
  motors.setSpeeds(turnSpeed, -turnSpeed);
  turningLeft = false;
  turningRight = true;
}

void BotsDetectie::rechtdoor(int s) {
  motors.setSpeeds(s, s);
}

void BotsDetectie::stop() {
  motors.setSpeeds(0, 0);
  turningLeft = false;
  turningRight = false;
}
