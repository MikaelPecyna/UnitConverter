#pragma once
#include "Lexer.hpp"
#include "Parser.hpp"
#include "Unit.hpp"
#include <string>

/**
 * @class Convertisseur
 * @brief Main unit converter engine
 *
 * Combines Lexer and Parser to process user input, then performs
 * unit conversion calculations.
 *
 * Usage:
 *   Convertisseur conv("convert 1.3 kg to lb");
 *   float result = conv.convert();  // Prints: "1.3 kg = 2.86601 lb"
 */
class Convertisseur {
  public:
    /**
     * @brief Constructor: parses and validates the conversion request
     * @param input Conversion expression (e.g., "convert 100 m to ft")
     * @throw std::runtime_error if parsing or validation fails
     */
    Convertisseur(const std::string &input);

    /**
     * @brief Performs the unit conversion
     * @return The converted value
     * @throw std::runtime_error if units are invalid or incompatible
     *
     * Also prints result: "<value> <unit> = <result> <unit>"
     */
    float convert();

  private:
    float convertWeight();     ///< Convert weight units (base: kg)
    float convertDistance();   ///< Convert distance units (base: m)
    float convertVolume();     ///< Convert volume units (base: L)
    float convertTime();       ///< Convert time units (base: s)
    float convertTemperatur(); ///< Convert temperature (base: °C)
    float convertArea();       ///< Convert area units (base: m²)
    float convertSpeed();      ///< Convert speed units (base: m/s)
    float convertPressure();   ///< Convert pressure units (base: Pa)

    ConversionRequest cr; ///< The parsed conversion request
};
