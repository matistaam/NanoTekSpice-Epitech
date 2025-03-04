/*
** EPITECH PROJECT, 2025
** B-OOP-400-LYN-4-1-tekspice-matis.taam
** File description:
** Component4040
*/

#include "NtsException.hpp"
#include "Component4040.hpp"

namespace nts {
    Component4040::Component4040() : _pins(16, {nullptr, 0}), _values(16, Tristate::UNDEFINED), _counter(0), _prevClock(Tristate::UNDEFINED)
    {
    }

    void Component4040::simulate(std::size_t tick)
    {
        (void)tick;
        Tristate clockVal = getValue(10); // Retrieve clock (pin 10)
        Tristate resetVal = getValue(11); // Reset (pin 11) values

        if (resetVal == Tristate::TRUE) { // If reset is TRUE, clear the counter
            this->_counter = 0;
        } else {
            if (this->_prevClock == Tristate::TRUE && clockVal == Tristate::FALSE) // Detect a falling edge on the clock: previously TRUE and now FALSE
                this->_counter = (this->_counter + 1) & 0xFFF; // Keep only 12 bits (modulo 4096)
        }
        this->_prevClock = clockVal;
    }

    Tristate Component4040::compute(std::size_t pin)
    {
        if (pin < 1 || pin > 16)
            throw InvalidPinError("4040", pin);
        switch (pin) { // Map the outputs based on the 4040 pin configuration
            case 1:
                return ((this->_counter & (1 << 11)) ? Tristate::TRUE : Tristate::FALSE);
            case 2:
                return ((this->_counter & (1 << 5)) ? Tristate::TRUE : Tristate::FALSE);
            case 3:
                return ((this->_counter & (1 << 4)) ? Tristate::TRUE : Tristate::FALSE);
            case 4:
                return ((this->_counter & (1 << 6)) ? Tristate::TRUE : Tristate::FALSE);
            case 5:
                return ((this->_counter & (1 << 3)) ? Tristate::TRUE : Tristate::FALSE);
            case 6:
                return ((this->_counter & (1 << 2)) ? Tristate::TRUE : Tristate::FALSE);
            case 7:
                return ((this->_counter & (1 << 1)) ? Tristate::TRUE : Tristate::FALSE);
            case 8:  // Power pin (ignored)
                return (Tristate::UNDEFINED);
            case 9:  // out_00 (bit 0)
                return ((this->_counter & (1 << 0)) ? Tristate::TRUE : Tristate::FALSE);
            case 10: // Clock input
                return getValue(10);
            case 11: // Reset input
                return getValue(11);
            case 12:
                return ((this->_counter & (1 << 8)) ? Tristate::TRUE : Tristate::FALSE);
            case 13:
                return ((this->_counter & (1 << 7)) ? Tristate::TRUE : Tristate::FALSE);
            case 14:
                return ((this->_counter & (1 << 9)) ? Tristate::TRUE : Tristate::FALSE);
            case 15:
                return ((this->_counter & (1 << 10)) ? Tristate::TRUE : Tristate::FALSE);
            case 16: // Power pin (ignored)
                return (Tristate::UNDEFINED);
            default:
                return (Tristate::UNDEFINED);
        }
    }

    void Component4040::setLink(std::size_t pin, IComponent &other, std::size_t otherPin)
    {
        if (pin < 1 || pin > 16)
            throw InvalidPinError("4040", pin);
        this->_pins[pin - 1] = {&other, otherPin};
    }

    Tristate Component4040::getValue(std::size_t pin)
    {
        Link link = {nullptr, 0};

        if (pin < 1 || pin > 16)
            throw InvalidPinError("4040", pin);
        link = this->_pins[pin - 1];
        if (link.comp != nullptr)
            return (link.comp->compute(link.pin));
        return (this->_values[pin - 1]);
    }
}
