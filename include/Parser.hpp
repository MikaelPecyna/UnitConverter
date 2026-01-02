#pragma once
#include "Lexer.hpp"
#include <optional>
#include <stdexcept>
#include <vector>

/**
 * @struct ConversionRequest
 * @brief Represents a parsed conversion request
 *
 * This structure holds the result of parsing a conversion expression:
 * the numeric value and the source/target units.
 */
struct ConversionRequest {
    float value;          ///< The numeric value to convert
    std::string fromUnit; ///< The source unit
    std::string toUnit;   ///< The target unit
};

/**
 * @class ParseError
 * @brief Custom exception for parser errors
 */
class ParseError : public std::runtime_error {
  public:
    /**
     * @brief Constructor for ParseError
     * @param message Error description
     */
    explicit ParseError(const std::string &message);
};

/**
 * @class Parser
 * @brief Syntax analyzer for conversion expressions
 *
 * Validates that tokens form: convert <DECIMAL> <UNIT> to <UNIT>
 * and extracts values into a ConversionRequest structure.
 */
class Parser {
  public:
    /**
     * @brief Constructor for the Parser
     * @param tokens The token stream from the Lexer
     */
    explicit Parser(const std::vector<Token> &tokens);

    /**
     * @brief Returns the current token without consuming it
     * @return The current token
     * @throw ParseError if at end of tokens
     */
    Token peek();

    /**
     * @brief Returns and consumes the current token
     * @return The current token
     * @throw ParseError if at end of tokens
     */
    Token consume();

    /**
     * @brief Checks if the token stream is exhausted
     * @return true if at the end of tokens, false otherwise
     */
    bool isAtEnd();

    /**
     * @brief Validates that the current token has the expected type
     * @param type The expected token type
     * @param errorMessage Error message if validation fails
     * @throw ParseError if the current token doesn't match the type
     */
    void expect(TokenType type, const std::string &errorMessage);

    /**
     * @brief Parses the token stream into a ConversionRequest
     * @return An optional ConversionRequest; empty if parsing fails
     *
     * Expected format: convert <number> <unit> to <unit>
     */
    [[nodiscard]] std::optional<ConversionRequest> parse();

  private:
    std::vector<Token> tokens; ///< The token stream
    size_t idx;                ///< Current position in the token stream
};
