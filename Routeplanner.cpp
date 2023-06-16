#include "Routeplanner.h"
#include <Arduino.h>

Routeplanner::Routeplanner(Motorcontroller* m):mc(m),lv(m),bd(m),imu() {

}

void Routeplanner::init() {
  lv.init();
  Wire.begin();
  imu.enableDefault();
}

void Routeplanner::start() {
  // Lees de kleuren in en bepaal wat er gedaan moet worden
  kleur l = lv.leesKleur(0);
  kleur m = lv.leesKleur(2);
  kleur r = lv.leesKleur(4);
  if (!links && !rechts && !cirkel) {
    if (l==kleur::GRIJS && r==kleur::GRIJS) {
      // Wacht
      imu.read();
      if(imu.a.x <= -2000) return;
    } else if (l==kleur::GRIJS) {
      // Sla links af
      Serial.println("links");
      mc->rijdAfstand(200,5);
      links = true;
      return;
    } else if (r==kleur::GRIJS) {
      // Sla rechts af
      Serial.println("rechts");
      mc->rijdRecht(150);
      rechts = true;
      return;
    } else if (r==kleur::BRUIN) {
      // Sla op dat de robot in de cirkel is en rijd eerst recht de cirkel in
      Serial.println("cirkel");
      mc->rijdAfstand(200, 20);
      cirkel = true;
      return;
    }
    
  }

  // Start de botsdetectie als de robot zich in de cirkel bevind en stop het programma bij het overschrijven van de zwarte lijn
  if (cirkel) {
    bd.start();
    if (l==kleur::ZWART | m==kleur::ZWART | r==kleur::ZWART) {
      exit(0);
    }
    return;
  }

  // Ga naar links als er net een opkomende bocht is geregistreerd naar links en er nu links een zwarte lijn zichtbaar is
  if (links && l==kleur::ZWART) {
    mc->maakAfslag(1);
    links = false;
    Serial.println("links klaar");
    return;
  }

  // Ga naar rechts als er net een opkomende bocht is geregistreerd naar rechts en er nu rechts een zwarte lijn zichtbaar is
  if (rechts && r==kleur::ZWART) {
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

  kleur linkskleur = lv.leesKleur(0);
  switch(linkskleur) {
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

  Serial.print(", ");

  kleur midkleur = lv.leesKleur(2);
  switch(midkleur) {
    case kleur::ANDERS:
      Serial.print("anders");
      break;
    case kleur::ZWART:
      Serial.print("zwart");
      break;
    case kleur::GRIJS:
      Serial.print("grijs");
      break;
    case kleur::BRUIN:
      Serial.print("bruin");
      break;
    case kleur::GROEN:
      Serial.print("groen");
      break;
  }

  Serial.print(", ");

  kleur rechtskleur = lv.leesKleur(4);
  switch(rechtskleur) {
    case kleur::ANDERS:
      Serial.print("anders");
      break;
    case kleur::ZWART:
      Serial.print("zwart");
      break;
    case kleur::GRIJS:
      Serial.print("grijs");
      break;
    case kleur::BRUIN:
      Serial.print("bruin");
      break;
    case kleur::GROEN:
      Serial.print("groen");
      break;
  }

  Serial.println("");
  delay(500);
}