/*
** EPITECH PROJECT, 2025
** B-OOP-400-LYN-4-1-tekspice-matis.taam
** File description:
** InputComponent
*/

#include "InputComponent.hpp"

namespace nts {
    InputComponent::InputComponent() : _state(Tristate::UNDEFINED)
    {
    }

    Tristate InputComponent::compute(std::size_t pin)
    {
        if (pin != 1)
            return (Tristate::UNDEFINED);
        return (this->_state);
    }

    void InputComponent::setState(Tristate state)
    {
        this->_state = state;
    }
}
