/*
** EPITECH PROJECT, 2025
** B-OOP-400-LYN-4-1-tekspice-matis.taam
** File description:
** NotComponent
*/

#include "NtsException.hpp"
#include "NotComponent.hpp"

namespace nts {
    Tristate NotComponent::compute(std::size_t pin)
    {
        Tristate a = Tristate::UNDEFINED;

        if (pin != 2)
            return (Tristate::UNDEFINED);
        a = getLink(1);
        if (a == Tristate::UNDEFINED)
            return (Tristate::UNDEFINED);
        if (a == Tristate::TRUE)
            return (Tristate::FALSE);
        return (Tristate::TRUE);
    }
}
