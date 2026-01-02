# Unit Converter - Lexer/Parser Learning Project

## ⚠️ Educational Disclaimer

This is a **learning project** created to explore lexical analysis and parsing concepts. **It is NOT intended for real-world use** and should not be trusted for critical conversions.

This project demonstrates:

- Lexical analysis (tokenization)
- Syntax analysis (parsing)
- Building a simple domain-specific language (DSL)

For precise unit conversions in production, use established libraries like:

- [udunits2](https://www.unidata.ucar.edu/software/udunits/)
- [pint](https://pint.readthedocs.io/) (Python)
- [quantities](https://github.com/python-quantities/python-quantities) (Python)

---

## Project Overview

A command-line unit converter that uses a **Lexer → Parser → Converter** pipeline to process human-readable conversion expressions like `"convert 1.3 kg to lb"`.

### Architecture

```
Input String
    ↓
[Lexer] → Tokenize → Token Stream
    ↓
[Parser] → Parse Tokens → ConversionRequest Struct
    ↓
[Convertisseur] → Convert & Calculate → Output
```

---

## Features

### Supported Unit Types

| Category        | Units                                                                              |
| --------------- | ---------------------------------------------------------------------------------- |
| **Weight**      | kg, g, mg, t, ton, lb, oz, st, ct                                                  |
| **Distance**    | m, km, cm, mm, μm, nm, mi, yd, ft, in, nmi                                         |
| **Volume**      | L, l, mL, ml, cL, cl, dL, dl, m³, m3, cm³, cm3, gal, qt, pt, cup, fl oz, tbsp, tsp |
| **Time**        | s, ms, μs, ns, min, h, hr, day, week, month, year, yr                              |
| **Temperature** | °C, C, °F, F, K                                                                    |
| **Area**        | m², m2, km², km2, cm², cm2, mm², mm2, ha, acre, ft², ft2, yd², yd2                 |
| **Speed**       | m/s, km/h, mph, ft/s, knot, kn                                                     |
| **Pressure**    | Pa, kPa, MPa, bar, mbar, psi, atm, mmHg, inHg                                      |

### Unicode Support

The lexer handles Unicode characters like:

- Greek letters: `μ` (mu), `°` (degree)
- Superscripts: `²` (squared), `³` (cubed)

---

## Building

### Prerequisites

- C++17 compiler
- [Meson](https://mesonbuild.com/) build system
- Ninja build tool

### Build Steps

```bash
cd Convertisseur
meson setup build
ninja -C build
```

### Run Tests

```bash
ninja -C build test
```

---

## Usage

```bash
./build/Convertisseur "convert <value> <source_unit> to <target_unit>"
```

### Examples

```bash
# Weight conversion
./build/Convertisseur "convert 1.3 kg to lb"
# Output: 1.3 kg = 2.86601 lb

# Distance conversion
./build/Convertisseur "convert 100 m to ft"
# Output: 100 m = 328.084 ft

# Temperature conversion
./build/Convertisseur "convert 25 C to F"
# Output: 25 C = 77 F

# Speed conversion
./build/Convertisseur "convert 50 km/h to mph"
# Output: 50 km/h = 31.0686 mph
```

### Error Handling

```bash
# Invalid unit combination
./build/Convertisseur "convert 25 C to m"
# Error: Cannot convert C to m : incompatible dimensions

# Invalid syntax
./build/Convertisseur "convert 100 meters to feet"
# Error: Cannot parse conversion request
```

---

## Architecture & Design

### Component Breakdown

#### 1. **Lexer** (`Lexer.hpp`, `Lexer.cpp`)

**Responsibility:** Break the input string into tokens

**Process:**

- Scans characters sequentially
- Recognizes three token types:
  - `KEYWORD`: "convert", "to"
  - `UNIT`: Registered unit names
  - `DECIMAL`: Floating-point numbers
  - `UNKNOWN`: Unrecognized tokens
- Handles Unicode multi-byte characters

**Example:**

```
Input:  "convert 1.3 kg to lb"
Output: [KEYWORD("convert"), DECIMAL("1.3"), UNIT("kg"), KEYWORD("to"), UNIT("lb")]
```

#### 2. **Parser** (`Parser.hpp`, `Parser.cpp`)

**Responsibility:** Validate token sequence and extract conversion parameters

**Grammar (Expected Format):**

```
conversion → "convert" DECIMAL UNIT "to" UNIT
```

**Output:** `ConversionRequest` struct containing:

- `value`: The numeric amount
- `fromUnit`: Source unit
- `toUnit`: Target unit

**Example:**

```
Input:  [KEYWORD("convert"), DECIMAL("1.3"), UNIT("kg"), KEYWORD("to"), UNIT("lb")]
Output: ConversionRequest{1.3, "kg", "lb"}
```

#### 3. **Unit System** (`Unit.hpp`, `Unit.cpp`)

**Responsibility:** Maintain unit definitions and type mappings

**Features:**

- Global `UnitSet` map: `unit_string → UnitType`
- Defines 8 unit categories (Weight, Distance, Volume, etc.)
- Validates that source and target units are compatible

#### 4. **Convertisseur** (`Convertisseur.hpp`, `Convertisseur.cpp`)

**Responsibility:** Orchestrate the pipeline and perform conversions

**Process:**

1. Constructor:
   - Lexes the input string
   - Parses the token stream
   - Stores the conversion request
2. `convert()` method:
   - Validates units exist and are compatible
   - Dispatches to appropriate conversion function
   - Prints and returns the result

**Conversion Strategy:**
Each unit type has a "base unit" (e.g., kg for weight, m for distance):

```
value_in_base = source_value × factor[source_unit]
result = value_in_base ÷ factor[target_unit]
```

---

## Code Structure

```
Convertisseur/
├── include/
│   ├── Convertisseur.hpp    # Main converter class
│   ├── Lexer.hpp            # Tokenizer interface
│   ├── Parser.hpp           # Parser interface & ConversionRequest
│   └── Unit.hpp             # Unit type definitions
├── src/
│   ├── Convertisseur.cpp    # Conversion logic & pipeline
│   ├── Lexer.cpp            # Tokenization implementation
│   ├── Parser.cpp           # Parsing implementation
│   └── Unit.cpp             # Unit type mappings
├── test/
│   ├── test_lexer.cpp       # Lexer unit tests
│   └── test_parser.cpp      # Parser unit tests
├── main.cpp                 # Application entry point
├── meson.build              # Build configuration
└── README.md                # This file
```

---

## Implementation Notes

### Conversion Factors

All conversions use precise SI-based factors:

**Weight (base: kg)**

```cpp
{"lb", 0.453592f}   // 1 lb = 0.453592 kg
{"oz", 0.0283495f}  // 1 oz = 0.0283495 kg
```

**Distance (base: m)**

```cpp
{"ft", 0.3048f}     // 1 ft = 0.3048 m
{"mi", 1609.34f}    // 1 mi = 1609.34 m
```

**Temperature** (special case - uses intermediate conversion)

```
Celsius ← → Fahrenheit: °F = (°C × 9/5) + 32
Celsius ← → Kelvin:     K = °C + 273.15
```

### Error Handling

The project uses exceptions for error propagation:

- `ParseError`: Thrown when syntax validation fails
- `std::runtime_error`: Thrown for unit validation errors

---

## Testing

Run the included unit tests:

```bash
ninja -C build test
```

### Test Coverage

- **Lexer tests:** Token recognition, whitespace handling, Unicode support
- **Parser tests:** Syntax validation, error cases, token consumption

---

## Known Limitations

1. **Precision**: Uses `float` (32-bit) instead of `double` - acceptable for educational purposes, not for critical applications
2. **Temperature**: Simplified temperature conversion (no absolute zero validation)
3. **Month/Year**: Time conversions use fixed durations (30 days/year) - not accounting for leap years or actual month lengths
4. **No Custom Units**: Cannot add units at runtime
5. **No Compound Units**: Cannot handle expressions like "convert 60 m/s to km/h" in natural form (but can be rewritten)

---

## Educational Value

This project teaches:

✅ **Lexical Analysis**

- Character-by-character tokenization
- Unicode handling
- Token classification

✅ **Syntax Analysis**

- Grammar definition (BNF-like)
- Token consumption & validation
- Error recovery

✅ **Domain-Specific Language (DSL) Design**

- Creating a language for a specific problem domain
- Mapping language to operations

✅ **C++ Modern Features**

- Enums and structs
- Standard containers (`std::vector`, `std::unordered_map`)
- Optional types (`std::optional`)
- Exception handling
- Move semantics (`std::move`)

---

## Future Enhancement Ideas

If extending this project for learning purposes:

1. **Add compound units**: `convert 60 m/s to km/h`
2. **User-defined units**: Allow creation of aliases
3. **Bidirectional conversion**: Show both directions
4. **Error recovery**: Continue parsing after encountering errors
5. **Multi-step conversions**: Calculate conversion paths
6. **Precision modes**: Support `double` or arbitrary precision
7. **Expression parsing**: Handle `(1.5 + 2.3) kg to lb`
8. **Interactive REPL**: Line-by-line input mode

---

## License

This is a learning project. Use freely for educational purposes.

---

## Author Notes

Built to explore compiler/interpreter fundamentals through a non-traditional domain.
The focus is on the pipeline (Lexer → Parser) rather than precision.

For questions or improvements, refer to the well-documented code in each component.
