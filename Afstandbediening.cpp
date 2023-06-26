#include "Afstandbediening.h"
#include <Arduino.h>

#define snelheid 250

// Afstandbediening() construeert de Afstandbediening en slaat de motorcontroller pointer op
Afstandbediening::Afstandbediening(Motorcontroller* m):mc(m) {
  mc->zetBochtSnelheid(snelheid);
}

// koppel() start de seriele verbinding met de xbee ontvanger
void Afstandbediening::koppel(){
  Serial1.begin(9600);
  Serial.println("Serial1 geopend");
}

// start() begint met het uitlezen
void Afstandbediening::start(){

  // bij het inlezen van de input slaan we deze op in de variabele letter
  letter = Serial1.readString();

  // als de letter w wordt ingevoerd rijd de robot vooruit met een constante snelheid
  if(letter.indexOf("w") == 0) mc->rijdRecht(snelheid);

  // als de letter s wordt ingevoerd rijd de robot achteruit met een constante snelheid
  if(letter.indexOf("s") == 0) mc->rijdRecht(-snelheid);

  // als de letter p wordt ingevoerd stopt de robot de motoren
  if(letter.indexOf("p") == 0) mc->stop();

  // als de letter a wordt ingevoerd maakt de robot een bocht naar links
  if(letter.indexOf("a") == 0) mc->maakBocht(0);

  // als de letter d wordt ingevoerd maakt de robot een bocht naar rechts
  if(letter.indexOf("d") == 0) mc->maakBocht(1);
}