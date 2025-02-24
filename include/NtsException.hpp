/*
** EPITECH PROJECT, 2025
** B-OOP-400-LYN-4-1-tekspice-matis.taam
** File description:
** NtsException
*/

#pragma once
#include <exception>
#include <string>

namespace nts {
    class NtsException : public std::exception {
        public:
            NtsException(const std::string &message);
            const char *what() const noexcept override;
        private:
            std::string _message;
    };

    class ParseError : public NtsException {
        public:
            ParseError(const std::string &message);
    };

    class UnknownComponentError : public NtsException {
        public:
            UnknownComponentError(const std::string &name);
    };

    class DuplicateComponentError : public NtsException {
        public:
            DuplicateComponentError(const std::string &name);
    };

    class EmptyCircuitError : public NtsException {
        public:
            EmptyCircuitError();
    };
}
