#include <Zumo32U4Buttons.h>
#include <Zumo32U4Buzzer.h>
#include "Afstandbediening.h"
#include "Routeplanner.h"
#include "Motorcontroller.h"

// Declareer lijstje met modi
enum modi : uint8_t {
  ONBEKEND,
  ROUTEPLANNER,
  AFSTANDSBEDIENING
};

modi modus = modi::ONBEKEND;

// Maak hulpobjecten aan uit Zumo32U4 Library
Zumo32U4ButtonC buttonC;
Zumo32U4Buzzer buzzer;

// Maak objecten aan voor modi
Motorcontroller mc = Motorcontroller();
Afstandbediening ab = Afstandbediening(&mc);
Routeplanner rp = Routeplanner(&mc);

uint8_t kiesModus() {
  // Initialiseer button objecten
  Zumo32U4ButtonA buttonA;
  Zumo32U4ButtonB buttonB;

  // Kies de modus door middel van de knoppen
  while (modus == modi::ONBEKEND) {
    if (buttonA.getSingleDebouncedPress()) {
      modus = modi::ROUTEPLANNER;
      rp.init();
      Serial.println("routeplanner");

      delay(100);
      buttonA.waitForButton();
    }
    if (buttonB.getSingleDebouncedPress()) {
      modus = modi::AFSTANDSBEDIENING;
      ab.koppel();
      Serial.println("afstandsbediening");
    }
  }
}

void setup() {
  Serial.begin(9600);
  Serial.println("VSZumo");

  // Selecteer modus met behulp van knoppen
  kiesModus();
}

void loop() {
  if (buttonC.getSingleDebouncedPress()) {
    mc.stop();
    exit(0);
  }
  if (modus == modi::ROUTEPLANNER) {
    rp.start();
  }

  if (modus == modi::AFSTANDSBEDIENING) {
    ab.start();
  }
}
