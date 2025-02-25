/*
** EPITECH PROJECT, 2025
** B-OOP-400-LYN-4-1-tekspice-matis.taam
** File description:
** NtsException
*/

#include "NtsException.hpp"

namespace nts {
    NtsException::NtsException(const std::string &message) : _message(message)
    {
    }

    const char *NtsException::what() const noexcept
    {
        return (this->_message.c_str());
    }

    ParseError::ParseError(const std::string &message) : NtsException("Parse error: " + message)
    {
    }

    UnknownComponentError::UnknownComponentError(const std::string &name) : NtsException("Unknown component name: " + name)
    {
    }

    DuplicateComponentError::DuplicateComponentError(const std::string &name) : NtsException("Duplicate component name: " + name)
    {
    }

    EmptyCircuitError::EmptyCircuitError() : NtsException("No chipsets found in circuit")
    {
    }
}
