#include <Arduino.h>
#include <string.h>
#include "Motorcontroller.h"

/**
 * @brief Afstandbediening klasse wordt gebruikt om de Zumo robot via de Xbee te besturen op afstand.
 */
class Afstandbediening 
{
public:
  /**
   * Construeer een nieuw Afstandbediening object
   * @brief Constructor.
   * @param mc Pointer van de motorcontroller.
   */
  Afstandbediening(Motorcontroller*);

  /**
   * @brief Start het Afstandbediening proces.
   */
  void start();

  /**
   * @brief Koppel de afstandbediening aan de seriele verbinding.
   */
  void koppel();

private:
  /**
   * Pointer van de motorcontroller
   */
  Motorcontroller* mc;

  /**
   * Opgeslagen waarde die ontvangen is van de seriele verbinding
   */
  String letter;

};