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
    Token Parser::processNumber(const std::string &line, size_t &i, int lineNumber)
    {
        std::string tokenStr = "";

        if (i > 0 && line[i - 1] == '-')
            throw ParseError("Negative numbers are not allowed at line " + std::to_string(lineNumber));
        tokenStr.push_back(line[i]);
        i++;
        while (i < line.size() && std::isdigit(line[i])) {
            tokenStr.push_back(line[i]);
            i++;
        }
        i--;
        return {TokenType::Number, tokenStr, lineNumber};
    }

    Token Parser::processIdentifier(const std::string &line, size_t &i, int lineNumber)
    {
        std::string tokenStr = "";

        tokenStr.push_back(line[i]);
        i++;
        while (i < line.size() && (std::isalnum(line[i]) || line[i] == '_' || line[i] == '.')) {
            tokenStr.push_back(line[i]);
            i++;
        }
        i--;
        if (tokenStr == ".chipsets")
            return {TokenType::Chipsets, tokenStr, lineNumber};
        if (tokenStr == ".links")
            return {TokenType::Links, tokenStr, lineNumber};
        return {TokenType::Identifier, tokenStr, lineNumber};
    }

    void Parser::processLine(const std::string &line, int lineNumber, std::vector<Token> &tokens)
    {
        char c = line[0];

        for (size_t i = 0; i < line.size(); i++) {
            if (std::isspace(line[i]))
                continue;
            c = line[i];
            if (std::isalpha(c) || c == '_' || c == '.')
                tokens.push_back(processIdentifier(line, i, lineNumber));
            else if (std::isdigit(c))
                tokens.push_back(processNumber(line, i, lineNumber));
            else if (c == ':')
                tokens.push_back({TokenType::Colon, ":", lineNumber});
            else
                tokens.push_back({TokenType::Unknown, std::string(1, c), lineNumber});
        }
        tokens.push_back({TokenType::EndOfLine, "\\n", lineNumber});
    }

    Parser::FileContent Parser::readFile(const std::string &filePath)
    {
        FileContent content = {};
        std::stringstream buffer = {};

        if (filePath.substr(filePath.find_last_of(".") + 1) != "nts")
            throw ParseError("Invalid file extension, expected .nts file");
        content.file.open(filePath);
        if (!content.file)
            throw ParseError("Unable to open file: " + filePath);
        content.file.seekg(0, std::ios::end);
        if (content.file.tellg() == 0)
            throw ParseError("Empty file: " + filePath);
        content.file.seekg(0, std::ios::beg);
        buffer << content.file.rdbuf();
        content.content = buffer.str();
        return (content);
    }

    std::vector<Token> Parser::tokenize(const std::string &filePath)
    {
        FileContent content = readFile(filePath);
        std::vector<Token> tokens = {};
        std::istringstream iss(content.content);
        std::string line = "";
        int lineNumber = 0;
        size_t commentPos = 0;
        bool hasChipsets = false;
        bool hasLinks = false;
        bool chipsetsFound = false;
        bool linksFound = false;

        while (std::getline(iss, line)) {
            lineNumber++;
            commentPos = line.find('#');
            if (commentPos != std::string::npos)
                line = line.substr(0, commentPos);
            if (line.find_first_not_of(" \t") == std::string::npos)
                continue;
            processLine(line, lineNumber, tokens);
            if (line.find(".chipsets") != std::string::npos) {
                if (linksFound == true)
                    throw ParseError("Chipsets section must come before links section");
                chipsetsFound = true;
                if (hasChipsets == true)
                    throw ParseError("Duplicate .chipsets section at line " + std::to_string(lineNumber));
                hasChipsets = true;
            }
            if (line.find(".links") != std::string::npos) {
                if (chipsetsFound == false)
                    throw ParseError("Links section must come after chipsets section");
                linksFound = true;
                if (hasLinks == true)
                    throw ParseError("Duplicate .links section at line " + std::to_string(lineNumber));
                hasLinks = true;
            }
        }
        if (!hasChipsets || !hasLinks)
            throw ParseError("Missing required sections: file must contain both .chipsets and .links");
        tokens.push_back({TokenType::EndOfFile, "", lineNumber});
        return (tokens);
    }
}
