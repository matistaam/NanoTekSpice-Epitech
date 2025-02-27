/*
** EPITECH PROJECT, 2025
** B-OOP-400-LYN-4-1-tekspice-matis.taam
** File description:
** Component4013
*/

#include "Component4013.hpp"
#include <stdexcept>

namespace nts {
    static Tristate tri_not(Tristate a) {
        if (a == Tristate::UNDEFINED)
            return Tristate::UNDEFINED;
        return (a == Tristate::TRUE) ? Tristate::FALSE : Tristate::TRUE;
    }

    Component4013::Component4013() : _pins(14, {nullptr, 0}), _values(14, Tristate::UNDEFINED),
                                    _q1(Tristate::UNDEFINED), _q2(Tristate::UNDEFINED),
                                    _prevClock1(Tristate::UNDEFINED), _prevClock2(Tristate::UNDEFINED) {}

    void Component4013::simulate(std::size_t) {
        // Process first flip-flop (pins 1-6)
        Tristate clock1 = getValue(3);
        // Detect rising edge on cl_1_clock.
        if (_prevClock1 != Tristate::TRUE && clock1 == Tristate::TRUE) {
            // Synchronous priority: set over reset.
            if (getValue(6) == Tristate::TRUE)
                _q1 = Tristate::TRUE;
            else if (getValue(4) == Tristate::TRUE)
                _q1 = Tristate::FALSE;
            else
                _q1 = getValue(5);           // Otherwise, sample data from pin 5 (in_1_data).
        }
        _prevClock1 = clock1;

        // Process second flip-flop (pins 8-13)
        Tristate clock2 = getValue(11);
        if (_prevClock2 != Tristate::TRUE && clock2 == Tristate::TRUE) {
            if (getValue(8) == Tristate::TRUE)
                _q2 = Tristate::TRUE;
            else if (getValue(10) == Tristate::TRUE)
                _q2 = Tristate::FALSE;
            else
                _q2 = getValue(9);
        }
        _prevClock2 = clock2;
    }

    Tristate Component4013::compute(std::size_t pin) {
        if (pin < 1 || pin > 14)
            throw std::out_of_range("Invalid pin number for 4013");

        // First flip-flop outputs:
        if (pin == 1) return _q1;            // Q output (out_1_q).
        if (pin == 2) return tri_not(_q1);     // /Q output (out_1_qb).

        // Second flip-flop outputs:
        if (pin == 13) return _q2;           // Q output (out_2_q).
        if (pin == 12) return tri_not(_q2);    // /Q output (out_2_qb).

        return getValue(pin);
    }

    void Component4013::setLink(std::size_t pin, IComponent &other, std::size_t otherPin) {
        if (pin < 1 || pin > 14)
            throw std::out_of_range("Invalid pin number for 4013");
        _pins[pin - 1] = {&other, otherPin};
    }

    // Helper to retrieve the value of a given pin.
    Tristate Component4013::getValue(std::size_t pin) {
        Link link = _pins[pin - 1];
        if (link.comp != nullptr)
            return link.comp->compute(link.pin);
        return _values[pin - 1];
    }

}