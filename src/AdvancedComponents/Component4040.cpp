/*
** EPITECH PROJECT, 2025
** B-OOP-400-LYN-4-1-tekspice-matis.taam
** File description:
** Component4040
*/

#include "Component4040.hpp"
#include "NtsException.hpp"

namespace nts {
    Component4040::Component4040()
        : _pins(16, {nullptr, 0}), _values(16, Tristate::UNDEFINED), _counter(0), _prevClock(Tristate::UNDEFINED)
    {
    }

    void Component4040::simulate(std::size_t /*tick*/)
    {
        // Retrieve clock (pin 10) and reset (pin 11) values.
        Tristate clockVal = getValue(10);
        Tristate resetVal = getValue(11);

        // If reset is TRUE, clear the counter.
        if (resetVal == Tristate::TRUE) {
            _counter = 0;
        } else {
            // Detect a falling edge on the clock: previously TRUE and now FALSE.
            if (_prevClock == Tristate::TRUE && clockVal == Tristate::FALSE) {
                _counter = (_counter + 1) & 0xFFF; // Keep only 12 bits (modulo 4096)
            }
        }
        _prevClock = clockVal;
    }

    Tristate Component4040::compute(std::size_t pin)
    {
        if (pin < 1 || pin > 16)
            throw InvalidPinError("4040", pin);

        // Map the outputs based on the 4040 pin configuration.
        switch (pin) {
            case 1:  // out_11 (bit 11)
                return ((_counter & (1 << 11)) ? Tristate::TRUE : Tristate::FALSE);
            case 2:  // out_05 (bit 5)
                return ((_counter & (1 << 5)) ? Tristate::TRUE : Tristate::FALSE);
            case 3:  // out_04 (bit 4)
                return ((_counter & (1 << 4)) ? Tristate::TRUE : Tristate::FALSE);
            case 4:  // out_06 (bit 6)
                return ((_counter & (1 << 6)) ? Tristate::TRUE : Tristate::FALSE);
            case 5:  // out_03 (bit 3)
                return ((_counter & (1 << 3)) ? Tristate::TRUE : Tristate::FALSE);
            case 6:  // out_02 (bit 2)
                return ((_counter & (1 << 2)) ? Tristate::TRUE : Tristate::FALSE);
            case 7:  // out_01 (bit 1)
                return ((_counter & (1 << 1)) ? Tristate::TRUE : Tristate::FALSE);
            case 8:  // Power pin (ignored)
                return Tristate::UNDEFINED;
            case 9:  // out_00 (bit 0)
                return ((_counter & (1 << 0)) ? Tristate::TRUE : Tristate::FALSE);
            case 10: // Clock input
                return getValue(10);
            case 11: // Reset input
                return getValue(11);
            case 12:
                return ((_counter & (1 << 8)) ? Tristate::TRUE : Tristate::FALSE);
            case 13:
                return ((_counter & (1 << 7)) ? Tristate::TRUE : Tristate::FALSE);
            case 14:
                return ((_counter & (1 << 9)) ? Tristate::TRUE : Tristate::FALSE);
            case 15:
                return ((_counter & (1 << 10)) ? Tristate::TRUE : Tristate::FALSE);
            case 16: // Power pin (ignored)
                return Tristate::UNDEFINED;
            default:
                return Tristate::UNDEFINED;
        }
    }

    void Component4040::setLink(std::size_t pin, IComponent &other, std::size_t otherPin)
    {
        if (pin < 1 || pin > 16)
            throw InvalidPinError("4040", pin);
        _pins[pin - 1] = { &other, otherPin };
    }

    Tristate Component4040::getValue(std::size_t pin)
    {
        Link link = _pins[pin - 1];
        if (link.comp != nullptr)
            return link.comp->compute(link.pin);
        return _values[pin - 1];
    }
}