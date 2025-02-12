/*
** EPITECH PROJECT, 2025
** B-OOP-400-LYN-4-1-tekspice-matis.taam
** File description:
** TrueComponent
*/

#include "TrueComponent.hpp"

namespace nts {
    Tristate TrueComponent::compute(std::size_t pin)
    {
        if (pin != 1)
            return (Tristate::UNDEFINED);
        return (Tristate::TRUE);
    }
}
