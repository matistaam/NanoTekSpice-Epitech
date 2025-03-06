/*
** EPITECH PROJECT, 2025
** B-OOP-400-LYN-4-1-tekspice-matis.taam
** File description:
** LoggerComponent
*/

#include "NtsException.hpp"
#include "LoggerComponent.hpp"

namespace nts {
    LoggerComponent::LoggerComponent() : _lastClock(false)
    {
        this->_file.open("./log.bin", std::ios::binary | std::ios::trunc);
    }

    LoggerComponent::~LoggerComponent()
    {
        if (this->_file.is_open())
            this->_file.close();
    }

    void LoggerComponent::simulate(std::size_t tick)
    {
        (void)tick;
        Tristate clock = getLink(9);
        Tristate inhibit = getLink(10);
        char c = 0;

        if (clock == Tristate::TRUE && !this->_lastClock && inhibit == Tristate::FALSE) {
            c = computeChar();
            this->_file.write(&c, 1);
            this->_file.flush();
        }
        this->_lastClock = (clock == Tristate::TRUE);
    }

    Tristate LoggerComponent::compute(std::size_t pin)
    {
        if (pin < 1 || pin > 10)
            throw InvalidPinError("LoggerComponent", pin);
        return (getLink(pin));
    }

    char LoggerComponent::computeChar() const
    {
        char c = 0;
        Tristate bit = Tristate::UNDEFINED;

        for (int i = 0; i < 8; i++) {
            bit = getLink(i + 1);
            if (bit == Tristate::TRUE)
                c |= (1 << i);
        }
        return (c);
    }
}
