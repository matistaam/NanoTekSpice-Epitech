/*
** EPITECH PROJECT, 2025
** B-OOP-400-LYN-4-1-tekspice-matis.taam
** File description:
** Component4514
*/

#include "Component4514.hpp"
#include "NtsException.hpp"

namespace nts {
    Component4514::Component4514() : _pins(24, {nullptr, 0}), _values(24, Tristate::UNDEFINED), _latchedA(Tristate::UNDEFINED),
    _latchedB(Tristate::UNDEFINED), _latchedC(Tristate::UNDEFINED), _latchedD(Tristate::UNDEFINED), _prevLatchEnable(Tristate::UNDEFINED)
    {
    }

    // void Component4514::simulate(std::size_t tick)
    // {
    //     // To implement
    // }

    // Tristate Component4514::compute(std::size_t pin)
    // {
    //     // To implement
    // }

    void Component4514::setLink(std::size_t pin, IComponent &other, std::size_t otherPin)
    {
        if (pin < 1 || pin > 24)
            throw InvalidPinError("4514", pin);
        this->_pins[pin - 1] = {&other, otherPin};
    }

    Tristate Component4514::getValue(std::size_t pin)
    {
        Link link = {nullptr, 0};

        if (pin < 1 || pin > 24)
            throw InvalidPinError("4514", pin);
        link = this->_pins[pin - 1];
        if (link.comp != nullptr)
            return (link.comp->compute(link.pin));
        return (this->_values[pin - 1]);
    }
}
