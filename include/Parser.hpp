/*
** EPITECH PROJECT, 2025
** B-OOP-400-LYN-4-1-tekspice-matis.taam
** File description:
** Parser
*/

#pragma once
#include <vector>
#include <string>
#include <fstream>
#include "Circuit.hpp"

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
            //void printTokens(const std::vector<Token> &tokens);

        private:
            struct FileContent {
                std::string content;
                std::ifstream file;
            };
            Token processNumber(const std::string &line, size_t &i, int lineNumber);
            Token processIdentifier(const std::string &line, size_t &i, int lineNumber);
            void processLine(const std::string &line, int lineNumber, std::vector<Token> &tokens);
            FileContent readFile(const std::string &filePath);

            void parseLink(std::vector<Token> &tokens, size_t &pos, Circuit &circuit);
            void parseChipset(std::vector<Token> &tokens, size_t &pos, Circuit &circuit);
    };
}
