/*
** EPITECH PROJECT, 2025
** B-OOP-400-LYN-4-1-tekspice-matis.taam
** File description:
** Component4013
*/

#include "Component4013.hpp"
#include "NtsException.hpp"

namespace nts {
    Component4013::Component4013() : _pins(14, {nullptr, 0}), _values(14, Tristate::UNDEFINED), _q1(Tristate::UNDEFINED),
    _q2(Tristate::UNDEFINED), _prevClock1(Tristate::UNDEFINED), _prevClock2(Tristate::UNDEFINED)
    {
    }

    void Component4013::simulate(std::size_t tick)
    {
        (void)tick;
        Tristate clock1 = getValue(3);  // Process first flip-flop (pins 1-6)
        Tristate clock2 = getValue(11); // Process second flip-flop (pins 8-13)

        // Process first flip-flop on rising edge
        if (this->_prevClock1 != Tristate::TRUE && clock1 == Tristate::TRUE) { // rising edge detected
            if (getValue(6) == Tristate::FALSE)  // Active low preset: when low, set Q to TRUE
                this->_q1 = Tristate::TRUE;
            else if (getValue(4) == Tristate::FALSE)  // Active low clear: when low, reset Q to FALSE
                this->_q1 = Tristate::FALSE;
            else
                this->_q1 = getValue(5); // Otherwise, sample data from pin 5 (in_1_data)
        }
        this->_prevClock1 = clock1;

        // Process second flip-flop on rising edge
        if (this->_prevClock2 != Tristate::TRUE && clock2 == Tristate::TRUE) { // rising edge detected
            if (getValue(8) == Tristate::FALSE)  // Active low preset: when low, set Q to TRUE
                this->_q2 = Tristate::TRUE;
            else if (getValue(10) == Tristate::FALSE) // Active low clear: when low, reset Q to FALSE
                this->_q2 = Tristate::FALSE;
            else
                this->_q2 = getValue(9); // Otherwise, sample data from pin 9 (in_2_data)
        }
        this->_prevClock2 = clock2;
    }

    Tristate Component4013::compute(std::size_t pin)
    {
        if (pin < 1 || pin > 14)
            throw InvalidPinError("4013", pin);
        if (pin == 1) // First flip-flop outputs:
            return (this->_q1); // Q output (out_1_q).
        if (pin == 2)
            return (computeNot(this->_q1)); // /Q output (out_1_qb).
        if (pin == 13) // Second flip-flop outputs:
            return (this->_q2); // Q output (out_2_q).
        if (pin == 12)
            return (computeNot(this->_q2)); // /Q output (out_2_qb).
        return (getValue(pin));
    }

    void Component4013::setLink(std::size_t pin, IComponent &other, std::size_t otherPin)
    {
        if (pin < 1 || pin > 14)
            throw InvalidPinError("4013", pin);
        this->_pins[pin - 1] = {&other, otherPin};
    }

    Tristate Component4013::getValue(std::size_t pin)
    {
        Link link = {nullptr, 0};

        if (pin < 1 || pin > 14)
            throw InvalidPinError("4013", pin);
        link = this->_pins[pin - 1];
        if (link.comp != nullptr)
            return (link.comp->compute(link.pin));
        return (this->_values[pin - 1]);
    }

    Tristate Component4013::computeNot(Tristate a)
    {
        if (a == Tristate::UNDEFINED)
            return (Tristate::UNDEFINED);
        if (a == Tristate::TRUE)
            return (Tristate::FALSE);
        return (Tristate::TRUE);
    }
}
