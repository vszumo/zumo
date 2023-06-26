#include <Arduino.h>
#include <string.h>
#include "Motorcontroller.h"

class Afstandbediening 
{
public:
  Afstandbediening(Motorcontroller*);
  void start();
  void koppel();

private:
  Motorcontroller* mc;
  String letter;

};