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
  kleur l = lv.leesKleur(0);
  kleur m = lv.leesKleur(2);
  kleur r = lv.leesKleur(4);
  if (!links && !rechts && !cirkel) {
    if (l==kleur::GRIJS && r==kleur::GRIJS) {
      imu.read();
      if(imu.a.x <= -2000) return;
    } else if (l==kleur::GRIJS) {
      Serial.println("links");
      mc->rijdAfstand(200,5);
      links = true;
      return;
    } else if (r==kleur::GRIJS) {
      Serial.println("rechts");
      mc->rijdRecht(150);
      rechts = true;
      return;
    } else if (r==kleur::BRUIN) {
      Serial.println("cirkel");
      mc->rijdAfstand(200, 20);
      cirkel = true;
      return;
    }
    
  }

  if (cirkel) {
    bd.start();
    if (l==kleur::ZWART | m==kleur::ZWART | r==kleur::ZWART) {
      exit(0);
    }
    return;
  }


  if (links && l==kleur::ZWART) {
    mc->maakAfslag(1);
    links = false;
    Serial.println("links klaar");
    return;
  }

  if (rechts && r==kleur::ZWART) {
    mc->maakAfslag(0);
    Serial.println("rechts klaar");
    rechts = false;
    return;
  }

  
  lv.start();
  //printKleur();
}

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