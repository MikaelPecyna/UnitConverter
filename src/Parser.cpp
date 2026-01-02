#include "../include/Parser.hpp"

// Exception ParseError
ParseError::ParseError(const std::string &message)
    : std::runtime_error(message) {}

// Constructeur
Parser::Parser(const std::vector<Token> &tokens) : tokens(tokens), idx(0) {}

// Récupère le token actuel sans avancer
Token Parser::peek() {
    if (isAtEnd()) {
        throw ParseError("Unexpected end of tokens");
    }
    return tokens[idx];
}

// Récupère le token actuel et avance
Token Parser::consume() {
    if (isAtEnd()) {
        throw ParseError("Unexpected end of tokens");
    }
    return tokens[idx++];
}

// Vérifie si on a atteint la fin des tokens
bool Parser::isAtEnd() { return idx == tokens.size(); }

// Vérifie que le token actuel est du type attendu, sinon lève une erreur
void Parser::expect(TokenType type, const std::string &errorMessage) {
    if (isAtEnd()) {
        throw ParseError(errorMessage);
    }
    if (peek().type != type) {
        throw ParseError(errorMessage);
    }
}

// Parse les tokens et retourne une ConversionRequest
// Structure attendue: convert <DECIMAL> <UNIT> to <UNIT>
[[nodiscard]] std::optional<ConversionRequest> Parser::parse() {
    try {
        // Expect "convert" keyword
        expect(TokenType::KEYWORD, "Expected 'convert' keyword");
        if (consume().value != "convert") {
            throw ParseError("Expected 'convert' keyword");
        }

        // Expect decimal number
        expect(TokenType::DECIMAL, "Expected decimal number");
        float value = std::stof(consume().value);

        // Expect source unit
        expect(TokenType::UNIT, "Expected unit");
        std::string fromUnit = consume().value;

        // Expect "to" keyword
        expect(TokenType::KEYWORD, "Expected 'to' keyword");
        if (consume().value != "to") {
            throw ParseError("Expected 'to' keyword");
        }

        // Expect target unit
        expect(TokenType::UNIT, "Expected target unit");
        std::string toUnit = consume().value;

        // Should be at end
        if (!isAtEnd()) {
            throw ParseError("Unexpected tokens after conversion request");
        }

        return ConversionRequest{value, fromUnit, toUnit};
    } catch (const ParseError &) {
        return std::nullopt;
    }
}
