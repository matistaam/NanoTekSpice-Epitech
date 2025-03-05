/*
** EPITECH PROJECT, 2025
** B-OOP-400-LYN-4-1-tekspice-matis.taam
** File description:
** XorComponent
*/

#include "NtsException.hpp"
#include "XorComponent.hpp"

namespace nts {
    Tristate XorComponent::compute(std::size_t pin)
    {
        Tristate a = Tristate::UNDEFINED;
        Tristate b = Tristate::UNDEFINED;

        if (pin != 3)
            return (Tristate::UNDEFINED);
        a = getLink(1);
        b = getLink(2);
        if (a == Tristate::UNDEFINED || b == Tristate::UNDEFINED)
        return (Tristate::UNDEFINED);
        if ((a == Tristate::TRUE && b == Tristate::FALSE) ||
        (a == Tristate::FALSE && b == Tristate::TRUE))
            return (Tristate::TRUE);
        return (Tristate::FALSE);
    }
}
