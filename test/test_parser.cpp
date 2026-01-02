#include "../include/Lexer.hpp"
#include "../include/Parser.hpp"
#include <cassert>
#include <iostream>

void test_parse_valid_conversion() {
    std::cout << "Test: Valid conversion request\n";
    Lexer lexer("convert 100 m to cm");
    auto tokens = lexer.lex();

    Parser parser(tokens);
    auto result = parser.parse();

    assert(result.has_value());
    assert(result->value == 100.0f);
    assert(result->fromUnit == "m");
    assert(result->toUnit == "cm");
    std::cout << "✓ Valid conversion test passed\n\n";
}

void test_parse_decimal_value() {
    std::cout << "Test: Decimal value in conversion\n";
    Lexer lexer("convert 3.14 kg to g");
    auto tokens = lexer.lex();

    Parser parser(tokens);
    auto result = parser.parse();

    assert(result.has_value());
    assert(result->value == 3.14f);
    assert(result->fromUnit == "kg");
    assert(result->toUnit == "g");
    std::cout << "✓ Decimal value test passed\n\n";
}

void test_parse_missing_convert_keyword() {
    std::cout << "Test: Missing 'convert' keyword\n";
    Lexer lexer("100 m to cm");
    auto tokens = lexer.lex();

    Parser parser(tokens);
    auto result = parser.parse();

    assert(!result.has_value());
    std::cout << "✓ Missing 'convert' keyword test passed\n\n";
}

void test_parse_missing_number() {
    std::cout << "Test: Missing number\n";
    Lexer lexer("convert m to cm");
    auto tokens = lexer.lex();

    Parser parser(tokens);
    auto result = parser.parse();

    assert(!result.has_value());
    std::cout << "✓ Missing number test passed\n\n";
}

void test_parse_missing_source_unit() {
    std::cout << "Test: Missing source unit\n";
    Lexer lexer("convert 100 to cm");
    auto tokens = lexer.lex();

    Parser parser(tokens);
    auto result = parser.parse();

    assert(!result.has_value());
    std::cout << "✓ Missing source unit test passed\n\n";
}

void test_parse_missing_to_keyword() {
    std::cout << "Test: Missing 'to' keyword\n";
    Lexer lexer("convert 100 m cm");
    auto tokens = lexer.lex();

    Parser parser(tokens);
    auto result = parser.parse();

    assert(!result.has_value());
    std::cout << "✓ Missing 'to' keyword test passed\n\n";
}

void test_parse_missing_target_unit() {
    std::cout << "Test: Missing target unit\n";
    Lexer lexer("convert 100 m to");
    auto tokens = lexer.lex();

    Parser parser(tokens);
    auto result = parser.parse();

    assert(!result.has_value());
    std::cout << "✓ Missing target unit test passed\n\n";
}

void test_parse_extra_tokens() {
    std::cout << "Test: Extra tokens at end\n";
    Lexer lexer("convert 100 m to cm extra");
    auto tokens = lexer.lex();

    Parser parser(tokens);
    auto result = parser.parse();

    assert(!result.has_value());
    std::cout << "✓ Extra tokens test passed\n\n";
}

void test_parse_empty_tokens() {
    std::cout << "Test: Empty token list\n";
    std::vector<Token> tokens;

    Parser parser(tokens);
    auto result = parser.parse();

    assert(!result.has_value());
    std::cout << "✓ Empty tokens test passed\n\n";
}

void test_parse_small_value() {
    std::cout << "Test: Small decimal value\n";
    Lexer lexer("convert 0.001 m to mm");
    auto tokens = lexer.lex();

    Parser parser(tokens);
    auto result = parser.parse();

    assert(result.has_value());
    assert(result->value == 0.001f);
    assert(result->fromUnit == "m");
    assert(result->toUnit == "mm");
    std::cout << "✓ Small value test passed\n\n";
}

void test_parse_large_value() {
    std::cout << "Test: Large value\n";
    Lexer lexer("convert 1000000 km to m");
    auto tokens = lexer.lex();

    Parser parser(tokens);
    auto result = parser.parse();

    assert(result.has_value());
    assert(result->value == 1000000.0f);
    assert(result->fromUnit == "km");
    assert(result->toUnit == "m");
    std::cout << "✓ Large value test passed\n\n";
}

void test_parse_different_units() {
    std::cout << "Test: Different unit conversions\n";

    // Test 1: weight
    Lexer lexer1("convert 5 kg to lb");
    auto tokens1 = lexer1.lex();
    Parser parser1(tokens1);
    auto result1 = parser1.parse();
    assert(result1.has_value());
    assert(result1->fromUnit == "kg");
    assert(result1->toUnit == "lb");

    // Test 2: time
    Lexer lexer2("convert 60 s to min");
    auto tokens2 = lexer2.lex();
    Parser parser2(tokens2);
    auto result2 = parser2.parse();
    assert(result2.has_value());
    assert(result2->fromUnit == "s");
    assert(result2->toUnit == "min");

    std::cout << "✓ Different units test passed\n\n";
}

int main() {
    std::cout << "=== Parser Tests ===\n\n";

    test_parse_valid_conversion();
    test_parse_decimal_value();
    test_parse_missing_convert_keyword();
    test_parse_missing_number();
    test_parse_missing_source_unit();
    test_parse_missing_to_keyword();
    test_parse_missing_target_unit();
    test_parse_extra_tokens();
    test_parse_empty_tokens();
    test_parse_small_value();
    test_parse_large_value();
    test_parse_different_units();

    std::cout << "=== All Parser tests passed! ===\n";

    return 0;
}
