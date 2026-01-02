#include "../include/Lexer.hpp"
#include "../include/Unit.hpp"
#include <cctype>
#include <string>

char Lexer::pick(size_t offset) {
    if (idx + offset >= text.size()) {
        return '\0';
    }
    return text[idx + offset];
}

char Lexer::consume() {
    if (idx >= text.size()) {
        return '\0';
    }
    char c = text[idx];
    idx++;
    return c;
}

[[nodiscard]] std::vector<Token> Lexer::lex() {
    std::vector<Token> tokens;
    std::string acc = "";

    while (idx < text.size()) {
        char current = pick();

        // Ignorer les espaces
        if (std::isspace(current)) {
            consume();
            continue;
        }

        // Nombre (entier ou décimal avec point)
        if (std::isdigit(current)) {
            acc = "";
            bool hasDot = false;

            while (std::isdigit(pick()) || (pick() == '.' && !hasDot)) {
                if (pick() == '.') {
                    hasDot = true;
                }
                acc += consume();
            }

            tokens.push_back(Token(TokenType::DECIMAL, acc));
            continue;
        }

        // Mot (keyword ou unit)
        if (std::isalpha(current)) {
            acc = "";

            while (std::isalpha(pick())) {
                acc += consume();
            }

            // Vérifier si c'est un keyword
            if (acc == "convert" || acc == "to") {
                tokens.push_back(Token(TokenType::KEYWORD, acc));
            }
            // Vérifier si c'est une unité valide
            else if (UnitSet.find(acc) != UnitSet.end()) {
                tokens.push_back(Token(TokenType::UNIT, acc));
            }
            // Sinon c'est inconnu
            else {
                tokens.push_back(Token(TokenType::UNKNOWN, acc));
            }
            continue;
        }

        // Caractère spécial UTF-8 (°, ², ³, µ)
        // Ces caractères prennent 2 octets en UTF-8
        if ((unsigned char)current >= 0xC0) {
            acc = "";
            // Consommer les octets UTF-8
            acc += consume();
            if (idx < text.size() &&
                ((unsigned char)text[idx] & 0xC0) == 0x80) {
                acc += consume();
            }

            // Continuer à lire les lettres ASCII après
            while (std::isalpha(pick())) {
                acc += consume();
            }

            // Vérifier si c'est une unité valide
            if (UnitSet.find(acc) != UnitSet.end()) {
                tokens.push_back(Token(TokenType::UNIT, acc));
            } else {
                tokens.push_back(Token(TokenType::UNKNOWN, acc));
            }
            continue;
        }

        // Tout le reste est UNKNOWN
        acc = "";
        acc += consume();
        tokens.push_back(Token(TokenType::UNKNOWN, acc));
    }

    return tokens;
}
