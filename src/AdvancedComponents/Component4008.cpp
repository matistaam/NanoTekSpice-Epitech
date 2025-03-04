/*
** EPITECH PROJECT, 2025
** B-OOP-400-LYN-4-1-tekspice-matis.taam
** File description:
** Component4008
*/

#include "Component4008.hpp"
#include "NtsException.hpp"

namespace nts {
    Component4008::Component4008() : _pins(16, {nullptr, 0}), _values(16, Tristate::UNDEFINED)
    {
    }

    void Component4008::simulate(std::size_t tick)
    {
        (void)tick;
    }

    Tristate Component4008::compute(std::size_t pin)
    {
        Tristate carry = Tristate::UNDEFINED;

        if (pin < 1 || pin > 16)
            throw InvalidPinError("4008", pin);
        // For output pins, perform the full 4-bit addition.
        // Results: sum bits on pins 10, 11, 12, 13; final carry on pin 14.
        if (pin == 10 || pin == 11 || pin == 12 || pin == 13 || pin == 14) {
            carry = getValue(9); // initial carry in from in_c
            auto bit0 = fullAdder(getValue(7), getValue(6), carry);
            auto bit1 = fullAdder(getValue(5), getValue(4), bit0.second);
            auto bit2 = fullAdder(getValue(3), getValue(2), bit1.second);
            auto bit3 = fullAdder(getValue(1), getValue(15), bit2.second);
            switch(pin) {
                case 10:
                    return (bit0.first);  // out_0
                case 11:
                    return (bit1.first);  // out_1
                case 12:
                    return (bit2.first);  // out_2
                case 13:
                    return (bit3.first);  // out_3
                case 14:
                    return (bit3.second); // out_c
            }
        }
        return (getValue(pin)); // For non-output pins, return the value provided by a linked component or stored value.
    }

    void Component4008::setLink(std::size_t pin, IComponent &other, std::size_t otherPin)
    {
        if (pin < 1 || pin > 16)
            throw InvalidPinError("4008", pin);
        this->_pins[pin - 1] = {&other, otherPin};
    }

    Tristate Component4008::getValue(std::size_t pin)
    {
        Link link = {nullptr, 0};

        if (pin < 1 || pin > 16)
            throw InvalidPinError("4008", pin);
        link = this->_pins[pin - 1];
        if (link.comp != nullptr)
            return (link.comp->compute(link.pin));
        return (this->_values[pin - 1]);
    }

    Tristate Component4008::computeAnd(Tristate a, Tristate b)
    {
        if (a == Tristate::FALSE || b == Tristate::FALSE)
            return (Tristate::FALSE);
        if (a == Tristate::UNDEFINED && b == Tristate::UNDEFINED)
            return (Tristate::UNDEFINED);
        return (Tristate::TRUE);
    }

    Tristate Component4008::computeOr(Tristate a, Tristate b)
    {
        if (a == Tristate::TRUE || b == Tristate::TRUE)
            return (Tristate::TRUE);
        if (a == Tristate::UNDEFINED || b == Tristate::UNDEFINED)
            return (Tristate::UNDEFINED);
        return (Tristate::FALSE);
    }

    Tristate Component4008::computeXor(Tristate a, Tristate b)
    {
        if (a == Tristate::UNDEFINED || b == Tristate::UNDEFINED)
            return (Tristate::UNDEFINED);
        if ((a == Tristate::TRUE && b == Tristate::FALSE) ||
            (a == Tristate::FALSE && b == Tristate::TRUE))
            return (Tristate::TRUE);
        return (Tristate::FALSE);
    }

    std::pair<Tristate, Tristate> Component4008::fullAdder(Tristate a, Tristate b, Tristate carry) // Full-adder for one bit: returns {sum, carry_out}
    {
        Tristate tmp = computeXor(a, b);
        Tristate sum = computeXor(tmp, carry);
        Tristate carry_out = computeOr(computeAnd(a, b), computeAnd(carry, tmp));

        return {sum, carry_out};
    }
}
