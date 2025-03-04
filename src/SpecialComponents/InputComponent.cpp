/*
** EPITECH PROJECT, 2025
** B-OOP-400-LYN-4-1-tekspice-matis.taam
** File description:
** InputComponent
*/

#include "NtsException.hpp"
#include "InputComponent.hpp"

namespace nts {
    InputComponent::InputComponent() : _state(Tristate::UNDEFINED)
    {
    }

    void InputComponent::simulate(std::size_t tick)
    {
        (void)tick;
    }

    Tristate InputComponent::compute(std::size_t pin)
    {
        if (pin != 1)
            throw InvalidPinError("InputComponent", pin);
        return (this->_state);
    }

    void InputComponent::setState(Tristate state)
    {
        this->_state = state;
    }
}
