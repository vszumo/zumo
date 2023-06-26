#include "Routeplanner.h"
#include <Arduino.h>

// Routeplanner() construeert de Routeplanner klasse door de motorcontroller pointer op te slaan en de Lijnvolger, BotsDetectie en Zumo32U4IMU te initialiseren.
Routeplanner::Routeplanner(Motorcontroller* m):mc(m),lv(m),bd(m),imu() {

}

// init() initialiseert de lijnvolger, start de i2c verbinding voor de imu sensoren en initialiseert de imu.
void Routeplanner::init() {
  lv.init();
  Wire.begin();
  imu.enableDefault();
}

// start() controleert met behulp van de kleuren en status of er iets moet worden uitgevoerd en als dit niet het geval is roept deze start() van de lijnvolger aan.
void Routeplanner::start() {
  // de kleuren worden opgevraagd van de lijnvolger klasse
  kleur l = lv.leesKleur(0);
  kleur m = lv.leesKleur(2);
  kleur r = lv.leesKleur(4);
  
  // als er nog geen status (opkomende bocht of eindcirkel) is opgeslagen kan naar de huidige sensorwaarden worden gekeken
  if (!links && !rechts && !cirkel) {

    // als er aan beide kanten een grijze lijn zichtbaar is blijft de robot staan totdat de juiste angle is bereikt
    if (l==kleur::GRIJS && r==kleur::GRIJS) {
      // Wacht
      imu.read();
      if(imu.a.x <= -2000) return;
    } 
    
    // als er links een grijze lijn zichtbaar is wordt dat opgeslagen en wordt er 5cm vooruit gereden
    else if (l==kleur::GRIJS) {
      Serial.println("links");
      mc->rijdAfstand(200,5);
      links = true;
      return;
    }
    
    // als er rechts een grijze lijn zichtbaar is wordt dat opgeslagen en wordt er 5cm vooruit gereden
    else if (r==kleur::GRIJS) {
      Serial.println("rechts");
      mc->rijdAfstand(200,5);
      rechts = true;
      return;
    }
    
    // als er links en rechts een bruine lijn zichtbaar is wordt dat opgeslagen en wordt er 20cm vooruit gereden.
    else if (l==kleur::BRUIN && r==kleur::BRUIN) {
      Serial.println("cirkel");
      mc->rijdAfstand(200, 20);
      cirkel = true;
      return;
    }
  }

  // als de robot zich in de eindcirkel bevind wordt de BotsDetectie gestart
  if (cirkel) {
    bd.start();

    // zodra er een zwarte lijn zichtbaar is wordt het programma afgesloten omdat de robot dan de cirkel uit is
    if (l==kleur::ZWART | m==kleur::ZWART | r==kleur::ZWART) {
      exit(0);
    }
    return;
  }

  // als de robot naar links moet wordt er een afslag gemaakt en opgeslagen dat de bocht voltooid is
  if (links) {
    mc->maakAfslag(1);
    links = false;
    Serial.println("links klaar");
    return;
  }

  // als de robot naar rechts moet wordt er een afslag gemaakt en opgeslagen dat de bocht voltoold is
  if (rechts) {
    mc->maakAfslag(0);
    Serial.println("rechts klaar");
    rechts = false;
    return;
  }
  
  lv.start();
}

// Debug functie voor het controleren van de sensorwaarden
void Routeplanner::printKleur() {
  Serial.print("Kleuren: ");

  // van alle 3 de lijnsensoren wordt de waarde opgevraagd en de corresponderende kleur geprint
  for (unsigned int =0; i<3; i++) {
    kleur sensorkleur;
    if (i==0) sensorkleur = lv.leesKleur(0);
    if (i==1) sensorkleur = lv.leesKleur(2);
    if (i==2) sensorkleur = lv.leesKleur(4);

    // print de corresponderende kleur op basis van de enum waarde kleur
    switch(sensorkleur) {
      case kleur::ANDERS:
        Serial.print("anders");
        break;
      case kleur::GRIJS:
        Serial.print("grijs");
        break;
      case kleur::ZWART:
        Serial.print("zwart");
        break;
      case kleur::BRUIN:
        Serial.print("bruin");
        break;
      case kleur::GROEN:
        Serial.print("groen");
        break;
    }

    // print een comma om de leesbaarheid te verbeteren
    Serial.print(", ");
  }

  // print een newline teken zodat de regel juist wordt afgesloten
  Serial.println("");
  delay(500);
}