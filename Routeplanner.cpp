#include "Routeplanner.h"
#include <Arduino.h>

Routeplanner::Routeplanner(Motorcontroller* m):mc(m),lv(m),bd(m),gs(Zumo32U4IMU()) {

}

void Routeplanner::init() {
  lv.init();
  gs.setup();
}

void Routeplanner::start() {
  kleur l = lv.leesKleur(0);
  kleur m = lv.leesKleur(2);
  kleur r = lv.leesKleur(4);
  if (!links && !rechts && !cirkel) {
    if (l==kleur::GRIJS && r==kleur::GRIJS) {
      mc->rijdAfstand(200, 20);
      cirkel = true;
    } else if (l==kleur::GRIJS) {
      Serial.println("links");
      links = true;
    } else if (r==kleur::GRIJS) {
      Serial.println("rechts");
      rechts = true;
    }
  }

  if (cirkel) {
    bd.start();
    if (l==kleur::ZWART | m==kleur::ZWART | r==kleur::ZWART) {
      exit(0);
    }
    return;
  }

  if (m==kleur::WIT && links) {
    mc->maakBocht(1);
    //check haakse verandering
    delay(500);
    mc->stop();
    links = false;
    Serial.println("links klaar");
    return;
  }

  if (m==kleur::WIT && rechts) {
    mc->maakBocht(0);
    //check haakse verandering
    delay(500);
    mc->stop();
    rechts = false;
    Serial.println("rechts klaar");
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