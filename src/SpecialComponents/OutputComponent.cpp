/*
** EPITECH PROJECT, 2025
** B-OOP-400-LYN-4-1-tekspice-matis.taam
** File description:
** OutputComponent
*/

#include "NtsException.hpp"
#include "OutputComponent.hpp"

namespace nts {
    Tristate OutputComponent::compute(std::size_t pin)
    {
        if (pin != 1)
            throw InvalidPinError("OutputComponent", pin);
        return (getLink(1));
    }
}
