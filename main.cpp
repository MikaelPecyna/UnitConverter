/**
 * @file main.cpp
 * @brief Unit converter application entry point
 *
 * This is a simple unit converter that uses a Lexer/Parser pipeline
 * to process human-readable conversion expressions.
 *
 * Usage:
 *   ./Convertisseur "convert 1.3 kg to lb"
 *   ./Convertisseur "convert 100 m to ft"
 *   ./Convertisseur "convert 25 C to F"
 */

#include "include/Convertisseur.hpp"
#include <iostream>
#include <string>

/**
 * @brief Displays usage information and supported unit types
 * @param programName The name of the executable
 */
void printUsage(const char *programName) {
    std::cout << "=== UNIT CONVERTER ===" << std::endl << std::endl;
    std::cout << "Usage: " << programName
              << " \"convert <value> <source_unit> to <target_unit>\""
              << std::endl
              << std::endl;

    std::cout << "WEIGHT: kg, g, mg, t, ton, lb, oz, st, ct" << std::endl;
    std::cout << "DISTANCE: m, km, cm, mm, μm, nm, mi, yd, ft, in, nmi"
              << std::endl;
    std::cout << "VOLUME: L, l, mL, ml, cL, cl, dL, dl, m³, m3, cm³, cm3, gal, "
                 "qt, pt, cup, fl oz, tbsp, tsp"
              << std::endl;
    std::cout << "TIME: s, ms, μs, ns, min, h, hr, day, week, month, year, yr"
              << std::endl;
    std::cout << "TEMPERATURE: °C, C, °F, F, K" << std::endl;
    std::cout
        << "AREA: m², m2, km², km2, cm², cm2, mm², mm2, ha, acre, ft², ft2, "
           "yd², yd2"
        << std::endl;
    std::cout << "SPEED: m/s, km/h, mph, ft/s, knot, kn" << std::endl;
    std::cout << "PRESSURE: Pa, kPa, MPa, bar, mbar, psi, atm, mmHg, inHg"
              << std::endl
              << std::endl;

    std::cout << "Examples:" << std::endl;
    std::cout << "  " << programName << " \"convert 1.3 kg to lb\""
              << std::endl;
    std::cout << "  " << programName << " \"convert 100 m to ft\"" << std::endl;
    std::cout << "  " << programName << " \"convert 25 C to F\"" << std::endl;
}

/**
 * @brief Main entry point
 * @param argc Number of command-line arguments
 * @param argv Command-line arguments
 * @return 0 on success, 1 on error
 */
int main(int argc, char *argv[]) {
    // Validate command-line arguments
    if (argc != 2) {
        printUsage(argv[0]);
        return 1;
    }

    try {
        // Parse and convert the input
        std::string input = argv[1];
        Convertisseur converter(input);
        converter.convert();
        return 0;
    } catch (const std::exception &e) {
        // Display error message and usage help
        std::cerr << "Error: " << e.what() << std::endl;
        printUsage(argv[0]);
        return 1;
    }
}
