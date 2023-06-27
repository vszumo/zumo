#ifndef MOTORCONTROLLER_H
#define MOTORCONTROLLER_H

#pragma once

#include <Zumo32U4Motors.h>
#include <Zumo32U4Encoders.h>

/**
 * @brief Motorcontroller klasse die gebruikt wordt om de motoren van de robot aan te sturen.
 */
class Motorcontroller
{
public:
  /**
   * Construeer de motorcontroller.
   * @brief Constructor.
   */
  Motorcontroller();

  /**
   * @brief Rijd recht vooruit met een gekozen snelheid.
   * @param snelheid Snelheid die gebruikt moet worden.
   */
  void rijdRecht(int);

  /**
   * @brief Rijd recht vooruit met een gekozen snelheid en afstand.
   * @param snelheid Snelheid die gebruikt moet worden.
   * @param afstand Afstand die afgelegd moet worden in cm.
   */
  void rijdAfstand(int, int);

  /**
   * @brief Draai links of rechtsom.
   * @param bocht Richting waarmee de motoren moeten draaien (false voor links, true voor rechts).
   */
  void maakBocht(bool);

  /**
   * @brief Maak een afslag dus een bocht van 90 graden.
   * @param bocht Richting waarmee de afslag moet worden gemaakt (false voor links, true voor rechts).
   */
  void maakAfslag(bool);

  /**
   * @brief Stop de motoren.
   */
  void stop();

  /**
   * @brief Stel de bochtsnelheid in.
   * @param snelheid Snelheid die opgeslagen moet worden.
   */
  void zetBochtSnelheid(int);

  /**
   * @brief Stel handmatig de snelheid van de 2 motoren in.
   * @param l Snelheid die gebruikt moet worden voor de linker motor.
   * @param r Snelheid die gebruikt moet worden voor de rechter motor.
   */
  void zetSnelheid(int16_t, int16_t);

private: 
  /**
   * Zumo32U4Motors object waarmee de fysieke motoren aangestuurd worden.
   */
  Zumo32U4Motors motors;

  /**
   * Zumo32U4Encoders object waarmee de encoders uitgelezen worden.
   */
  Zumo32U4Encoders encoders;

  /**
   * Ingestelde bochtsnelheid.
   */
  int bochtsnelheid;

};

#endif

