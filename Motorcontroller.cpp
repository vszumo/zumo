#include "Motorcontroller.h"
#include <Arduino.h>

#define toerenpercm 150

// Motorcontroller() construeert de motorcontroller, stelt de bochtsnelheid op 0 in en maakt de motoren en encoders aan.
Motorcontroller::Motorcontroller():bochtsnelheid(0),motors(),encoders() {
  encoders.init();
}

// zetBochtSnelheid(int) slaat de ingevoerd integer als bochtsnelheid op.
void Motorcontroller::zetBochtSnelheid(int s) {
  bochtsnelheid = s;
}

// zetSnelheid(int16_t, int16_t) stuurt de ingevoerde 2 integers naar de motoren.
void Motorcontroller::zetSnelheid(int16_t l, int16_t r) {
  motors.setSpeeds(l, r);
}

// rijdRecht() stuurt de ingevoerde integer naar de motoren voor een constante snelheid vooruit/achteruit.
void Motorcontroller::rijdRecht(int snelheid) {
  motors.setSpeeds(snelheid, snelheid);
}

// rijdAfstand() blijft vooruit of achteruit rijden met de ingegeven snelheid tot de afstand is bereikt
void Motorcontroller::rijdAfstand(int snelheid, int afstand) {
  // Lees de encoders uit en zet de motoren aan
  int16_t begin = encoders.getCountsLeft();
  motors.setSpeeds(snelheid, snelheid);

  // pauzeer de functie tot de encoders de juiste waarde hebben bereikt en stop dan de motoren
  while (encoders.getCountsLeft() - begin <= toerenpercm*afstand);
  stop();
}

// maakBocht(bool) stelt de motoren in om met de bochtsnelheid de ingevoerde richting op te draaien
void Motorcontroller::maakBocht(bool bocht) {
  if(bocht) motors.setSpeeds(-bochtsnelheid, bochtsnelheid);

  if(!bocht) motors.setSpeeds(bochtsnelheid, -bochtsnelheid);
}

// maakAfslag(bool) maakt een 90 graden bocht door te kijken naar de encoders
void Motorcontroller::maakAfslag(bool bocht) {
  Serial.println("afslag");
  
  // als er een bocht naar rechts moet worden gemaakt worden de motoren ingesteld om te gaan draaien
  if(bocht) {
    // Sla linksaf door de motoren de omgekeerde snelheid te geven
    int16_t begin = encoders.getCountsLeft();
    motors.setSpeeds(-bochtsnelheid, bochtsnelheid);

    // pauzeer de functie tot de encoders de juiste waarde hebben bereikt en stop dan de motoren
    while(begin - encoders.getCountsLeft() <= toerenpercm*5);
    stop();
  }

  // als er een bocht naar links moet worden gemaakt worden de motoren ingesteld om te gaan draaie
  else {
    int16_t begin = encoders.getCountsRight();
    motors.setSpeeds(bochtsnelheid, -bochtsnelheid);

    // pauzeer de functie tot de encoders de juiste waarde hebben bereikt en stop dan de motoren
    while(begin - encoders.getCountsRight() <= toerenpercm*5);
    stop();
  }

  Serial.println("afslag klaar");
}

// stop() stopt de motoren
void Motorcontroller::stop() {
  motors.setSpeeds(0, 0);
}