#include "Lijnvolger.h"
#include <Arduino.h>

#define snelheid 200

Lijnvolger::Lijnvolger(Motorcontroller* m):ls(),mc(m) {
}

void Lijnvolger::init() {
  Serial.println("bababooey");
  mc->zetSnelheid(snelheid);
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