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
    void Parser::parse(const std::string &filePath, nts::Circuit &circuit) {
        std::cout << "Parsing file: " << filePath << std::endl;
        // First, tokenize the file.
        std::vector<Token> tokens = tokenize(filePath);
        size_t pos = 0;
        // We'll use a state machine to know which section we're parsing.
        enum class ParseState { None, Chipsets, Links };
        ParseState state = ParseState::None;
        while (pos < tokens.size()) {
            Token token = tokens[pos];
            std::cout << "Token: " << token.value << " (Type: " << static_cast<int>(token.type) << ")" << std::endl;
            // Switch section if we encounter a section token.
            if (token.type == TokenType::Chipsets) {
                state = ParseState::Chipsets;
                pos++;
                std::cout << "Entering Chipsets section" << std::endl;
                continue;
            }
            if (token.type == TokenType::Links) {
                state = ParseState::Links;
                pos++;
                std::cout << "Entering Links section" << std::endl;
                continue;
            }
            // Skip end-of-line tokens.
            if (token.type == TokenType::EndOfLine) {
                pos++;
                continue;
            }
            if (state == ParseState::Chipsets) {
                if (token.type == TokenType::Identifier || token.type == TokenType::Number) {
                    std::string compType = token.value;
                    pos++;
                    if (pos < tokens.size() && tokens[pos].type == TokenType::Identifier) {
                        std::string compName = tokens[pos].value;
                        pos++;
                        std::cout << "Creating component: Type = " << compType << ", Name = " << compName << std::endl;
                        auto component = circuit.createComponent(compType);
                        if (!component)
                            throw UnknownComponentError(compType);
                        circuit.addComponent(compName, std::move(component));
                    } else {
                        throw NtsException("Expected a component name after type " + compType);
                    }
                } else {
                    pos++; // skip tokens that are not part of a valid declaration.
                }
            } else if (state == ParseState::Links) {
                if (token.type == TokenType::Identifier) {
                    std::string comp1 = token.value;
                    pos++;
                    if (pos < tokens.size() && tokens[pos].type == TokenType::Colon) {
                        pos++;
                        if (pos < tokens.size() && tokens[pos].type == TokenType::Number) {
                            int pin1 = std::stoi(tokens[pos].value);
                            pos++;
                            if (pos < tokens.size() && tokens[pos].type == TokenType::Identifier) {
                                std::string comp2 = tokens[pos].value;
                                pos++;
                                if (pos < tokens.size() && tokens[pos].type == TokenType::Colon) {
                                    pos++;
                                    if (pos < tokens.size() && tokens[pos].type == TokenType::Number) {
                                        int pin2 = std::stoi(tokens[pos].value);
                                        pos++;
                                        std::cout << "Linking components: " << comp1 << ":" << pin1 << " -> " << comp2 << ":" << pin2 << std::endl;
                                        auto* component1 = circuit.findComponent(comp1);
                                        auto* component2 = circuit.findComponent(comp2);
                                        if (!component1)
                                            throw nts::NtsException("Unknown component: " + comp1);
                                        if (!component2)
                                            throw nts::NtsException("Unknown component: " + comp2);
                                        component1->setLink(pin1, *component2, pin2);
                                    } else {
                                        throw nts::NtsException("Expected a pin number after ':' for " + comp2);
                                    }
                                } else {
                                    throw nts::NtsException("Expected ':' after component name " + comp2 + " in link");
                                }
                            } else {
                                throw nts::NtsException("Expected second component name in link");
                            }
                        } else {
                            throw nts::NtsException("Expected a pin number after ':' for " + comp1);
                        }
                    } else {
                        throw nts::NtsException("Expected ':' after component name " + comp1 + " in link");
                    }
                } else {
                    pos++; // skip tokens that are not valid start of a link.
                }
            } else {
                // In state None, skip tokens until a valid section is found.
                pos++;
            }
        }
    }
}
