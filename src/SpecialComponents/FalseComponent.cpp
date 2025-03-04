/*
** EPITECH PROJECT, 2025
** B-OOP-400-LYN-4-1-tekspice-matis.taam
** File description:
** FalseComponent
*/

#include "NtsException.hpp"
#include "FalseComponent.hpp"

namespace nts {
    Tristate FalseComponent::compute(std::size_t pin)
    {
        if (pin != 1)
            throw InvalidPinError("FalseComponent", pin);
        return (Tristate::FALSE);
    }
}
