#include "Afstandbediening.h"
#include <Arduino.h>

Afstandbediening::Afstandbediening():mc(Motorcontroller()) {
  
}

void Afstandbediening::koppel(){
  Serial1.begin(9600); //de seriele poort te openen.
  Serial.println("Serial1 geopend");
}

void Afstandbediening::start(){
  while(true) {

    letter = Serial1.readString(); //Voor het inlezen van de input en deze input in de variabele letter stoppen.
    Serial.println(letter);

    if(letter.indexOf("w") == 0){ //Als de letter w ingevoerd word wordt het onderstaande uitgevoerd.
      mc.rijdVooruit(100);
    }

    if(letter.indexOf("s") == 0){ //Als de letter s ingevoerd word wordt het onderstaande uitgevoerd.
      mc.rijdVooruit(-100);
    }

    if(letter.indexOf("p") == 0){ //Als de letter p ingevoerd word wordt het onderstaande uitgevoerd.
      mc.stop();
    }

    if(letter.indexOf("a") == 0){ //Als de letter a ingevoerd word wordt het onderstaande uitgevoerd.
      mc.maakBocht(0);
    }

    if(letter.indexOf("d") == 0){ //Als de letter d ingevoerd word wordt het onderstaande uitgevoerd.
      mc.maakBocht(1);
    }
  }
}