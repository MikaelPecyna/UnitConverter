#pragma once
#include <string>
#include <unordered_map>

/**
 * @enum UnitType
 * @brief Enumeration of all supported unit types
 *
 * Each unit type represents a physical dimension that can be converted.
 * Conversions are only allowed between units of the same type.
 */
enum class UnitType {
    WEIGHT,      ///< Weight/Mass units (kg, lb, oz, etc.)
    DISTANCE,    ///< Distance/Length units (m, km, mi, ft, etc.)
    VOLUME,      ///< Volume units (L, gal, ml, etc.)
    TIME,        ///< Time units (s, min, h, day, year, etc.)
    TEMPERATURE, ///< Temperature units (°C, °F, K)
    AREA,        ///< Area/Surface units (m², km², acre, etc.)
    SPEED,       ///< Speed/Velocity units (m/s, km/h, mph, etc.)
    PRESSURE     ///< Pressure units (Pa, bar, psi, atm, etc.)
};

/// @brief Global mapping of unit strings to their types
extern std::unordered_map<std::string, UnitType> UnitSet;
