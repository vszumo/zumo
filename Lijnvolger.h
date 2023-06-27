#ifndef LIJNVOLGER_H
#define LIJNVOLGER_H

#include <stdint.h>
#include <Zumo32U4LineSensors.h>
#include <Zumo32U4Buttons.h>
#include "Motorcontroller.h"

// Declareer lijstje met kleuren
enum kleur : uint8_t {
  ANDERS,
  ZWART,
  GRIJS,
  BRUIN,
  GROEN,
  WIT
};

/**
 * @brief Lijnvolger klasse die gebruikt wordt om de lijnsensoren uit te lezen en de robot een lijn te laten volgen.
 */
class Lijnvolger
{
public:
  /**
   * Construeer de Lijnvolger.
   * @brief Constructor.
   * @param mc Pointer van de motorcontroller.
   */
  Lijnvolger(Motorcontroller*);

  /**
   * @brief Initialiseer de Lijnvolger.
   */
  void init();

  /**
   * @brief Start het Lijnvolger proces.
   */
  void start();

  /**
   * @brief Geef de kleur terug van de gekozen sensor.
   * @param sensor Gekozen sensornummer.
   * @return Kleur van de gekozen sensor.
  */ 
  kleur leesKleur(int);

private:
  /**
   * Zumo32U4LineSensors object waarmee de lijnsensoren worden uitgelezen.
   */
  Zumo32U4LineSensors ls;

  /**
   * Pointer van de motorcontroller.
   */
  Motorcontroller* mc;

  /**
   * Zumo32U4ButtonC object waarmee de kalibreerkleuren functie wordt bedient.
   */
  Zumo32U4ButtonC buttonc;

  /**
   * Waardes van de 5 lijnsensoren.
   */
  unsigned int lineSensorValues[5];

  /**
   * Gekalibreerde waardes van de 3 kleuren per lijnsensor (5 stuks).
   */
  unsigned int waardes[3][5];

  int16_t position;
  int16_t lastError;
  int16_t error;
  int16_t speedDifference;
  int16_t leftSpeed;
  int16_t rightSpeed;
  const uint16_t maxSpeed = 200;

  /**
   * @brief Kalibreer de zwarte lijn.
   */
  void calibreerzwart();

  /**
   * @brief Kalibreer de kleuren grijs, bruin en groen.
   */
  void calibreerkleuren();

};
#endif

