#include "../include/Convertisseur.hpp"
#include "../include/Unit.hpp"
#include <iostream>
#include <stdexcept>

// Constructeur: lexe et parse la chaîne d'entrée
Convertisseur::Convertisseur(const std::string &input) {
    // Lexical analysis
    Lexer lexer(input);
    std::vector<Token> tokens = lexer.lex();

    // Parsing
    Parser parser(tokens);
    auto conversionRequest = parser.parse();

    if (!conversionRequest.has_value()) {
        throw std::runtime_error(
            "Erreur: Impossible de parser la requête de conversion");
    }

    cr = conversionRequest.value();
}

// Fonction principale de conversion
float Convertisseur::convert() {
    // Vérifier que les deux unités existent
    if (UnitSet.find(cr.fromUnit) == UnitSet.end()) {
        throw std::runtime_error("Unité source invalide: " + cr.fromUnit);
    }
    if (UnitSet.find(cr.toUnit) == UnitSet.end()) {
        throw std::runtime_error("Unité cible invalide: " + cr.toUnit);
    }

    UnitType sourceType = UnitSet[cr.fromUnit];
    UnitType targetType = UnitSet[cr.toUnit];

    // Vérifier que les deux unités sont de la même dimension
    if (sourceType != targetType) {
        throw std::runtime_error("Impossible de convertir " + cr.fromUnit +
                                 " en " + cr.toUnit +
                                 " : dimensions incompatibles");
    }
    float result = 0.0f;

    switch (sourceType) {
    case UnitType::WEIGHT:
        result = convertWeight();
        break;
    case UnitType::DISTANCE:
        result = convertDistance();
        break;
    case UnitType::VOLUME:
        result = convertVolume();
        break;
    case UnitType::TIME:
        result = convertTime();
        break;
    case UnitType::TEMPERATURE:
        result = convertTemperatur();
        break;
    case UnitType::AREA:
        result = convertArea();
        break;
    case UnitType::SPEED:
        result = convertSpeed();
        break;
    case UnitType::PRESSURE:
        result = convertPressure();
        break;
    default:
        throw std::runtime_error("Type d'unité non supporté");
    }

    std::cout << cr.value << " " << cr.fromUnit << " = " << result << " "
              << cr.toUnit << std::endl;

    return result;
}

// Conversion de poids (en kg comme unité de base)
float Convertisseur::convertWeight() {
    // Tableaux de conversion vers kg
    std::unordered_map<std::string, float> toKg = {
        {"kg", 1.0f},       {"g", 0.001f},
        {"mg", 0.000001f},  {"t", 1000.0f}, // tonne métrique
        {"ton", 1000.0f},                   // tonne métrique
        {"lb", 0.453592f},                  // pound
        {"oz", 0.0283495f},                 // ounce
        {"st", 6.35029f},                   // stone
        {"ct", 0.0002f}                     // carat
    };

    float valueInKg = cr.value * toKg[cr.fromUnit];
    return valueInKg / toKg[cr.toUnit];
}

// Conversion de distance (en mètre comme unité de base)
float Convertisseur::convertDistance() {
    std::unordered_map<std::string, float> toM = {
        {"m", 1.0f},          {"km", 1000.0f},   {"cm", 0.01f},
        {"mm", 0.001f},       {"μm", 0.000001f}, // micromètre
        {"nm", 0.000000001f},                    // nanomètre
        {"mi", 1609.34f},                        // mile
        {"yd", 0.9144f},                         // yard
        {"ft", 0.3048f},                         // foot
        {"in", 0.0254f},                         // inch
        {"nmi", 1852.0f}                         // nautical mile
    };

    float valueInM = cr.value * toM[cr.fromUnit];
    return valueInM / toM[cr.toUnit];
}

// Conversion de volume (en litre comme unité de base)
float Convertisseur::convertVolume() {
    std::unordered_map<std::string, float> toL = {
        {"L", 1.0f},          {"l", 1.0f},           {"mL", 0.001f},
        {"ml", 0.001f},       {"cL", 0.01f},         {"cl", 0.01f},
        {"dL", 0.1f},         {"dl", 0.1f},          {"m³", 1000.0f},
        {"m3", 1000.0f},      {"cm³", 0.001f},       {"cm3", 0.001f},
        {"gal", 3.78541f},                           // gallon US
        {"qt", 0.946353f},                           // quart
        {"pt", 0.473176f},                           // pint
        {"cup", 0.236588f},   {"fl oz", 0.0295735f}, // fluid ounce
        {"tbsp", 0.0147868f},                        // tablespoon
        {"tsp", 0.00492892f}                         // teaspoon
    };

    float valueInL = cr.value * toL[cr.fromUnit];
    return valueInL / toL[cr.toUnit];
}

// Conversion de temps (en secondes comme unité de base)
float Convertisseur::convertTime() {
    std::unordered_map<std::string, float> toS = {
        {"s", 1.0f},           {"ms", 0.001f},    {"μs", 0.000001f},
        {"ns", 0.000000001f},  {"min", 60.0f},    {"h", 3600.0f},
        {"hr", 3600.0f},       {"day", 86400.0f}, {"week", 604800.0f},
        {"month", 2592000.0f}, // 30 jours
        {"year", 31536000.0f}, // 365 jours
        {"yr", 31536000.0f}    // 365 jours
    };

    float valueInS = cr.value * toS[cr.fromUnit];
    return valueInS / toS[cr.toUnit];
}

// Conversion de température
float Convertisseur::convertTemperatur() {
    std::string fromUnit = cr.fromUnit;
    std::string toUnit = cr.toUnit;

    // Normaliser les unités (enlever les accents/symboles)
    if (fromUnit == "°C")
        fromUnit = "C";
    if (toUnit == "°C")
        toUnit = "C";
    if (fromUnit == "°F")
        fromUnit = "F";
    if (toUnit == "°F")
        toUnit = "F";

    float tempInCelsius = cr.value;

    // Convertir en Celsius d'abord
    if (fromUnit == "F") {
        tempInCelsius = (cr.value - 32.0f) * 5.0f / 9.0f;
    } else if (fromUnit == "K") {
        tempInCelsius = cr.value - 273.15f;
    }
    // Si déjà en Celsius, ne rien faire

    // Convertir depuis Celsius vers l'unité cible
    if (toUnit == "F") {
        return (tempInCelsius * 9.0f / 5.0f) + 32.0f;
    } else if (toUnit == "K") {
        return tempInCelsius + 273.15f;
    }
    // Si cible est Celsius, retourner directement
    return tempInCelsius;
}

// Conversion d'aire/surface (en m² comme unité de base)
float Convertisseur::convertArea() {
    std::unordered_map<std::string, float> toM2 = {
        {"m²", 1.0f},        {"m2", 1.0f},       {"km²", 1000000.0f},
        {"km2", 1000000.0f}, {"cm²", 0.0001f},   {"cm2", 0.0001f},
        {"mm²", 0.000001f},  {"mm2", 0.000001f}, {"ha", 10000.0f}, // hectare
        {"acre", 4046.86f},  {"ft²", 0.092903f}, {"ft2", 0.092903f},
        {"yd²", 0.836127f},  {"yd2", 0.836127f}};

    float valueInM2 = cr.value * toM2[cr.fromUnit];
    return valueInM2 / toM2[cr.toUnit];
}

// Conversion de vitesse (en m/s comme unité de base)
float Convertisseur::convertSpeed() {
    std::unordered_map<std::string, float> toMS = {
        {"m/s", 1.0f},     {"km/h", 0.277778f},
        {"mph", 0.44704f}, // miles per hour
        {"ft/s", 0.3048f}, {"knot", 0.51444f},
        {"kn", 0.51444f}};

    float valueInMS = cr.value * toMS[cr.fromUnit];
    return valueInMS / toMS[cr.toUnit];
}

// Conversion de pression (en Pascal comme unité de base)
float Convertisseur::convertPressure() {
    std::unordered_map<std::string, float> toPa = {
        {"Pa", 1.0f},       {"kPa", 1000.0f},   {"MPa", 1000000.0f},
        {"bar", 100000.0f}, {"mbar", 100.0f},   {"psi", 6894.76f},
        {"atm", 101325.0f}, {"mmHg", 133.322f}, {"inHg", 3386.39f}};

    float valueInPa = cr.value * toPa[cr.fromUnit];
    return valueInPa / toPa[cr.toUnit];
}
