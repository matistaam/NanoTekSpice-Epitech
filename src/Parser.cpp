/*
** EPITECH PROJECT, 2025
** B-OOP-400-LYN-4-1-tekspice-matis.taam
** File description:
** Parser
*/

#include "Parser.hpp"
#include "NtsException.hpp"
#include <iostream>
#include <sstream>
#include <cstdlib>

namespace nts {
    void Parser::parseLink(std::vector<Token> &tokens, size_t &pos, Circuit &circuit)
    {
        Token token = tokens[pos];
        std::string comp1 = "";
        std::string comp2 = "";
        int pin1 = 0;
        int pin2 = 0;

        if (token.type != TokenType::Identifier) {
            pos++;
            return;
        }
        comp1 = token.value;
        pos++;
        if (pos >= tokens.size() || tokens[pos].type != TokenType::Colon)
            throw ParseError("Expected ':' after component name " + comp1 + " in link");
        pos++;
        if (pos >= tokens.size() || tokens[pos].type != TokenType::Number)
            throw ParseError("Expected a pin number after ':' for " + comp1);
        pin1 = std::stoi(tokens[pos].value);
        pos++;
        if (pos >= tokens.size() || tokens[pos].type != TokenType::Identifier)
            throw ParseError("Expected second component name in link");
        comp2 = tokens[pos].value;
        pos++;
        if (pos >= tokens.size() || tokens[pos].type != TokenType::Colon)
            throw ParseError("Expected ':' after component name " + comp2 + " in link");
        pos++;
        if (pos >= tokens.size() || tokens[pos].type != TokenType::Number)
            throw ParseError("Expected a pin number after ':' for " + comp2);
        pin2 = std::stoi(tokens[pos].value);
        pos++;
        try {
            auto *component1 = circuit.findComponent(comp1);
            auto *component2 = circuit.findComponent(comp2);
            if (!component1)
                throw UnknownComponentError(comp1);
            if (!component2)
                throw UnknownComponentError(comp2);
            if (comp1 == comp2 && pin1 == pin2)
                throw ParseError("Component " + comp1 + " cannot connect to itself on pin " + std::to_string(pin1));
            component1->compute(pin1);
            component2->compute(pin2);
            component1->setLink(pin1, *component2, pin2);
            component2->setLink(pin2, *component1, pin1);
        } catch (const InvalidPinError &e) {
            throw ParseError(e.what());
        }
    }

    void Parser::parseChipset(std::vector<Token> &tokens, size_t &pos, Circuit &circuit)
    {
        Token token = tokens[pos];
        std::string compType = "";
        std::string compName = "";

        if (token.type == TokenType::Identifier || token.type == TokenType::Number) {
            compType = token.value;
            pos++;
            if (pos < tokens.size() && tokens[pos].type == TokenType::Identifier) {
                compName = tokens[pos].value;
                pos++;
                auto component = circuit.createComponent(compType);
                if (!component)
                    throw UnknownComponentError(compType);
                circuit.addComponent(compName, std::move(component));
            } else {
                throw ParseError("Expected a component name after type " + compType);
            }
        } else {
            pos++;
        }
    }

    void Parser::parse(const std::string &filePath, Circuit &circuit)
    {
        std::vector<Token> tokens = tokenize(filePath);
        size_t pos = 0;
        enum class ParseState { None, Chipsets, Links };
        ParseState state = ParseState::None;
        Token token = {TokenType::Unknown, "", 0};
        bool EmptyChipsets = false;
        bool EmptyLinks = false;

        while (pos < tokens.size()) {
            token = tokens[pos];
            if (token.type == TokenType::Chipsets) {
                state = ParseState::Chipsets;
                pos++;
                continue;
            }
            if (token.type == TokenType::Links) {
                state = ParseState::Links;
                pos++;
                continue;
            }
            if (token.type == TokenType::EndOfLine) {
                pos++;
                continue;
            }
            switch (state) {
                case ParseState::Chipsets:
                    if (token.type == TokenType::Identifier || token.type == TokenType::Number)
                        EmptyChipsets = true;
                    parseChipset(tokens, pos, circuit);
                    break;
                case ParseState::Links:
                    if (token.type == TokenType::Identifier)
                        EmptyLinks = true;
                    parseLink(tokens, pos, circuit);
                    break;
                default:
                    pos++;
                    break;
            }
        }
        if (EmptyChipsets == false)
            throw ParseError("Empty chipsets section");
        if (EmptyLinks == false)
            throw ParseError("Empty links section");
    }
}
