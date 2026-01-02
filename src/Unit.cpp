#include "../include/Unit.hpp"

std::unordered_map<std::string, UnitType> UnitSet = {
    // WEIGHT / MASSE
    {"kg", UnitType::WEIGHT},
    {"g", UnitType::WEIGHT},
    {"mg", UnitType::WEIGHT},
    {"t", UnitType::WEIGHT},   // tonne métrique
    {"ton", UnitType::WEIGHT}, // tonne métrique
    {"lb", UnitType::WEIGHT},  // pound
    {"oz", UnitType::WEIGHT},  // ounce
    {"st", UnitType::WEIGHT},  // stone
    {"ct", UnitType::WEIGHT},  // carat

    // DISTANCE / LONGUEUR
    {"m", UnitType::DISTANCE},
    {"km", UnitType::DISTANCE},
    {"cm", UnitType::DISTANCE},
    {"mm", UnitType::DISTANCE},
    {"μm", UnitType::DISTANCE},  // micromètre
    {"nm", UnitType::DISTANCE},  // nanomètre
    {"mi", UnitType::DISTANCE},  // mile
    {"yd", UnitType::DISTANCE},  // yard
    {"ft", UnitType::DISTANCE},  // foot
    {"in", UnitType::DISTANCE},  // inch
    {"nmi", UnitType::DISTANCE}, // nautical mile

    // VOLUME
    {"L", UnitType::VOLUME},
    {"l", UnitType::VOLUME},
    {"mL", UnitType::VOLUME},
    {"ml", UnitType::VOLUME},
    {"cL", UnitType::VOLUME},
    {"cl", UnitType::VOLUME},
    {"dL", UnitType::VOLUME},
    {"dl", UnitType::VOLUME},
    {"m³", UnitType::VOLUME},
    {"m3", UnitType::VOLUME},
    {"cm³", UnitType::VOLUME},
    {"cm3", UnitType::VOLUME},
    {"gal", UnitType::VOLUME}, // gallon US
    {"qt", UnitType::VOLUME},  // quart
    {"pt", UnitType::VOLUME},  // pint
    {"cup", UnitType::VOLUME},
    {"fl oz", UnitType::VOLUME}, // fluid ounce
    {"tbsp", UnitType::VOLUME},  // tablespoon
    {"tsp", UnitType::VOLUME},   // teaspoon

    // TEMPS
    {"s", UnitType::TIME},
    {"ms", UnitType::TIME},
    {"μs", UnitType::TIME},
    {"ns", UnitType::TIME},
    {"min", UnitType::TIME},
    {"h", UnitType::TIME},
    {"hr", UnitType::TIME},
    {"day", UnitType::TIME},
    {"week", UnitType::TIME},
    {"month", UnitType::TIME},
    {"year", UnitType::TIME},
    {"yr", UnitType::TIME},

    // TEMPÉRATURE
    {"°C", UnitType::TEMPERATURE},
    {"C", UnitType::TEMPERATURE},
    {"°F", UnitType::TEMPERATURE},
    {"F", UnitType::TEMPERATURE},
    {"K", UnitType::TEMPERATURE}, // Kelvin

    // AIRE / SURFACE
    {"m²", UnitType::AREA},
    {"m2", UnitType::AREA},
    {"km²", UnitType::AREA},
    {"km2", UnitType::AREA},
    {"cm²", UnitType::AREA},
    {"cm2", UnitType::AREA},
    {"mm²", UnitType::AREA},
    {"mm2", UnitType::AREA},
    {"ha", UnitType::AREA}, // hectare
    {"acre", UnitType::AREA},
    {"ft²", UnitType::AREA},
    {"ft2", UnitType::AREA},
    {"yd²", UnitType::AREA},
    {"yd2", UnitType::AREA},

    // VITESSE
    {"m/s", UnitType::SPEED},
    {"km/h", UnitType::SPEED},
    {"mph", UnitType::SPEED}, // miles per hour
    {"ft/s", UnitType::SPEED},
    {"knot", UnitType::SPEED},
    {"kn", UnitType::SPEED},

    // PRESSION
    {"Pa", UnitType::PRESSURE},
    {"kPa", UnitType::PRESSURE},
    {"MPa", UnitType::PRESSURE},
    {"bar", UnitType::PRESSURE},
    {"mbar", UnitType::PRESSURE},
    {"psi", UnitType::PRESSURE},
    {"atm", UnitType::PRESSURE},
    {"mmHg", UnitType::PRESSURE},
    {"inHg", UnitType::PRESSURE}};
