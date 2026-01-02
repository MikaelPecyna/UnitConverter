#pragma once
#include "Unit.hpp"
#include <cctype>
#include <string>
#include <vector>

/**
 * @enum TokenType
 * @brief Token types recognized by the lexical analyzer
 */
enum class TokenType {
    KEYWORD, ///< Keywords: "convert", "to"
    UNIT,    ///< Recognized unit names
    DECIMAL, ///< Floating-point numbers
    UNKNOWN  ///< Unknown tokens
};

/**
 * @struct Token
 * @brief Represents a single token in the input stream
 */
struct Token {
    TokenType type;    ///< The type of this token
    std::string value; ///< The lexical value of this token
    Token(TokenType t, const std::string &s) : type(t), value(s) {};
};

/**
 * @class Lexer
 * @brief Lexical analyzer for conversion expressions
 *
 * The Lexer takes a string input like "convert 1.3 kg to lb" and breaks it
 * down into a sequence of tokens. It handles keywords, decimal numbers, unit
 * names (including Unicode characters), and whitespace.
 */
class Lexer {
  public:
    /**
     * @brief Constructor for the Lexer
     * @param text The input string to tokenize
     */
    Lexer(std::string text) : text(std::move(text)), idx(0) {};

    /**
     * @brief Tokenizes the input string
     * @return A vector of tokens extracted from the input
     */
    [[nodiscard]] std::vector<Token> lex();

  private:
    /**
     * @brief Peeks at a character without consuming it
     * @param offset Position ahead to peek (default 0 = current)
     * @return Character at idx+offset, or '\0' if out of bounds
     */
    char pick(size_t offset = 0);

    /**
     * @brief Consumes and returns the current character
     * @return Character at idx, or '\0' if out of bounds
     */
    char consume();

    std::string text; ///< The input string being tokenized
    size_t idx;       ///< Current position in the string
};
