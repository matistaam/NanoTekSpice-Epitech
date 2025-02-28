/*
** EPITECH PROJECT, 2025
** B-OOP-400-LYN-4-1-tekspice-matis.taam
** File description:
** Component4512
*/

#include "Component4512.hpp"
#include "NtsException.hpp"

namespace nts {
    Component4512::Component4512() : _pins(24, {nullptr, 0}), _values(24, Tristate::UNDEFINED), _prevLatchEnable(Tristate::UNDEFINED)
    {
    }

    // void Component4512::simulate(std::size_t tick)
    // {
    //     // To implement
    // }

    // Tristate Component4512::compute(std::size_t pin)
    // {
    //     // To implement
    // }

    void Component4512::setLink(std::size_t pin, IComponent &other, std::size_t otherPin)
    {
        if (pin < 1 || pin > 24)
            throw InvalidPinError("4512", pin);
        this->_pins[pin - 1] = {&other, otherPin};
    }

    Tristate Component4512::getValue(std::size_t pin)
    {
        Link link = this->_pins[pin - 1];

        if (link.comp != nullptr)
            return (link.comp->compute(link.pin));
        return (this->_values[pin - 1]);
    }
}
