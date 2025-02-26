/*
** EPITECH PROJECT, 2025
** B-OOP-400-LYN-4-1-tekspice-matis.taam
** File description:
** parser
*/

#include "Parser.hpp"
#include "NtsException.hpp"
#include <sstream>
#include <cctype>
#include <iostream>
#include <fstream>

namespace nts {
    std::vector<Token> Parser::tokenize(const std::string &filePath) {
        std::ifstream file(filePath);
        if (!file)
            throw ParseError("Unable to open file: " + filePath);
        std::stringstream buffer;
        buffer << file.rdbuf();
        std::string source = buffer.str();
        std::vector<Token> tokens;
        std::istringstream iss(source);
        std::string line;
        int lineNumber = 0;

        while (std::getline(iss, line)) {
            lineNumber++;
            // Remove any comment (anything after '#' is ignored)
            size_t commentPos = line.find('#');
            if (commentPos != std::string::npos)
                line = line.substr(0, commentPos);
            // Skip empty lines (or lines that are only whitespace)
            if (line.find_first_not_of(" \t") == std::string::npos)
                continue;
            // Process the line character by character.
            for (size_t i = 0; i < line.size(); i++) {
                // Skip whitespace characters.
                if (std::isspace(line[i]))
                    continue;
                char c = line[i];
                // Handle identifiers: start with a letter, underscore, or dot.
                if (std::isalpha(c) || c == '_' || c == '.') {
                    std::string tokenStr;
                    tokenStr.push_back(c);
                    i++;
                    while (i < line.size() && (std::isalnum(line[i]) || line[i] == '_' || line[i] == '.')) {
                        tokenStr.push_back(line[i]);
                        i++;
                    }
                    i--; // adjust index since the outer loop also increments it
                    // Check for specific section tokens
                    if (tokenStr == ".chipsets") {
                        tokens.push_back({TokenType::Chipsets, tokenStr, lineNumber});
                    } else if (tokenStr == ".links") {
                        tokens.push_back({TokenType::Links, tokenStr, lineNumber});
                    } else {
                        tokens.push_back({TokenType::Identifier, tokenStr, lineNumber});
                    }
                }
                // Handle numbers: consecutive digits.
                else if (std::isdigit(c)) {
                    std::string tokenStr;
                    tokenStr.push_back(c);
                    i++;
                    while (i < line.size() && std::isdigit(line[i])) {
                        tokenStr.push_back(line[i]);
                        i++;
                    }
                    i--;
                    tokens.push_back({TokenType::Number, tokenStr, lineNumber});
                }
                // Handle the colon punctuation.
                else if (c == ':') {
                    tokens.push_back({TokenType::Colon, ":", lineNumber});
                }
                // If encountering any other character, store it as unknown.
                else {
                    tokens.push_back({TokenType::Unknown, std::string(1, c), lineNumber});
                }
            }
            // Optionally add an EndOfLine token after processing each line.
            tokens.push_back({TokenType::EndOfLine, "\\n", lineNumber});
        }
        // Mark the end of file.
        tokens.push_back({TokenType::EndOfFile, "", lineNumber});
        return (tokens);
    }

    void Parser::printTokens(const std::vector<Token> &tokens) {
        for (const auto &token : tokens) {
            std::cout << "Line " << token.line << ": ";
            switch (token.type) {
                case TokenType::Identifier:
                    std::cout << "Identifier(" << token.value << ")";
                    break;
                case TokenType::Number:
                    std::cout << "Number(" << token.value << ")";
                    break;
                case TokenType::Colon:
                    std::cout << "Colon";
                    break;
                case TokenType::EndOfLine:
                    std::cout << "EOL";
                    break;
                case TokenType::EndOfFile:
                    std::cout << "EOF";
                    break;
                default:
                    std::cout << "Unknown(" << token.value << ")";
                    break;
            }
            std::cout << "\n";
        }
    }
}
