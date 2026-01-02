#include "../include/Lexer.hpp"
#include <cassert>
#include <iostream>

void print_token(const Token &token) {
    std::string type_str;
    switch (token.type) {
    case TokenType::KEYWORD:
        type_str = "KEYWORD";
        break;
    case TokenType::UNIT:
        type_str = "UNIT";
        break;
    case TokenType::DECIMAL:
        type_str = "DECIMAL";
        break;
    case TokenType::UNKNOWN:
        type_str = "UNKNOWN";
        break;
    }
    std::cout << "Token(" << type_str << ", \"" << token.value << "\")"
              << std::endl;
}

void test_keywords() {
    std::cout << "Test: Keywords\n";
    Lexer lexer("convert to");
    auto tokens = lexer.lex();

    assert(tokens.size() == 2);
    assert(tokens[0].type == TokenType::KEYWORD);
    assert(tokens[0].value == "convert");
    assert(tokens[1].type == TokenType::KEYWORD);
    assert(tokens[1].value == "to");
    std::cout << "✓ Keywords test passed\n\n";
}

void test_numbers() {
    std::cout << "Test: Numbers\n";
    Lexer lexer("42 3.14 100.5");
    auto tokens = lexer.lex();

    assert(tokens.size() == 3);
    assert(tokens[0].type == TokenType::DECIMAL);
    assert(tokens[0].value == "42");
    assert(tokens[1].type == TokenType::DECIMAL);
    assert(tokens[1].value == "3.14");
    assert(tokens[2].type == TokenType::DECIMAL);
    assert(tokens[2].value == "100.5");
    std::cout << "✓ Numbers test passed\n\n";
}

void test_whitespace() {
    std::cout << "Test: Whitespace handling\n";
    Lexer lexer("   convert   42   m   ");
    auto tokens = lexer.lex();

    assert(tokens.size() == 3);
    assert(tokens[0].value == "convert");
    assert(tokens[1].value == "42");
    assert(tokens[2].value == "m");
    std::cout << "✓ Whitespace test passed\n\n";
}

void test_unknown_tokens() {
    std::cout << "Test: Unknown tokens\n";
    Lexer lexer("xyz @#$");
    auto tokens = lexer.lex();

    assert(tokens.size() == 4);
    assert(tokens[0].type == TokenType::UNKNOWN);
    assert(tokens[0].value == "xyz");
    assert(tokens[1].type == TokenType::UNKNOWN);
    assert(tokens[1].value == "@");
    assert(tokens[2].type == TokenType::UNKNOWN);
    assert(tokens[2].value == "#");
    assert(tokens[3].type == TokenType::UNKNOWN);
    assert(tokens[3].value == "$");
    std::cout << "✓ Unknown tokens test passed\n\n";
}

void test_mixed() {
    std::cout << "Test: Mixed input\n";
    Lexer lexer("convert 100 m to cm");
    auto tokens = lexer.lex();

    std::cout << "Tokens found:\n";
    for (const auto &token : tokens) {
        print_token(token);
    }

    assert(tokens.size() == 5);
    assert(tokens[0].type == TokenType::KEYWORD);
    assert(tokens[0].value == "convert");
    assert(tokens[1].type == TokenType::DECIMAL);
    assert(tokens[1].value == "100");
    assert(tokens[2].type == TokenType::UNIT);
    assert(tokens[2].value == "m");
    assert(tokens[3].type == TokenType::KEYWORD);
    assert(tokens[3].value == "to");
    assert(tokens[4].type == TokenType::UNIT);
    assert(tokens[4].value == "cm");
    std::cout << "✓ Mixed input test passed\n\n";
}

int main() {
    std::cout << "=== Lexer Tests ===\n\n";

    try {
        test_keywords();
        test_numbers();
        test_whitespace();
        test_unknown_tokens();
        test_mixed();

        std::cout << "=== All tests passed! ===\n";
        return 0;
    } catch (const std::exception &e) {
        std::cerr << "Test failed: " << e.what() << std::endl;
        return 1;
    }
}
