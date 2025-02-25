/*
** EPITECH PROJECT, 2025
** B-OOP-400-LYN-4-1-tekspice-matis.taam
** File description:
** parser
*/

#pragma once

#include <vector>
#include <string>

// Define the possible token types.
enum class TokenType {
    Identifier,  // For names like "input", "in_a1", ".chipsets"
    Number,      // For numeric values like "4008" or "1"
    Colon,       // The ':' character
    EndOfLine,   // End-of-line marker (optional, for parsing convenience)
    EndOfFile,   // End-of-file marker
    Unknown      // Any unrecognized token (could be used for punctuation, etc.)
};

// Token struct to hold a token's type, its string value, and the line number it was found on.
struct Token {
    TokenType type;
    std::string value;
    int line;
};

class Parser {
    public:
        std::vector<Token> tokenize(const std::string& filePath);
        void printTokens(const std::vector<Token>& tokens);
    };