/*
** EPITECH PROJECT, 2025
** B-OOP-400-LYN-4-1-tekspice-matis.taam
** File description:
** Parser
*/

#pragma once
#include <vector>
#include <string>
#include "Circuit.hpp"

// Define the possible token types
enum class TokenType {
    Identifier,
    Number,
    Colon,
    EndOfLine,
    EndOfFile,
    Unknown,
    Chipsets,
    Links
};

// Token struct holds token details
struct Token {
    TokenType type;
    std::string value;
    int line;
};

namespace nts {
    class Parser{
        public:
            std::vector<Token> tokenize(const std::string &filePath);
            void parse(const std::string &filePath, nts::Circuit &circuit);
            void printTokens(const std::vector<Token> &tokens);

        private:
            void parseChipsets(std::istringstream &iss, nts::Circuit &circuit);
            void parseLinks(std::istringstream &iss, nts::Circuit &circuit);
    };
}
