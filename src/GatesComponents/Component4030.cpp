/*
** EPITECH PROJECT, 2025
** B-OOP-400-LYN-4-1-tekspice-matis.taam
** File description:
** Component4030
*/

#include "Component4030.hpp"

namespace nts {
    Tristate Component4030::computeXor(Tristate a, Tristate b)
    {
        if (a == Tristate::UNDEFINED || b == Tristate::UNDEFINED)
            return (Tristate::UNDEFINED);
        if ((a == Tristate::TRUE && b == Tristate::FALSE) ||
            (a == Tristate::FALSE && b == Tristate::TRUE))
            return (Tristate::TRUE);
        return (Tristate::FALSE);
    }

    Tristate Component4030::compute(std::size_t pin)
    {
        switch (pin) {
            case 3:
                return (computeXor(getLink(1), getLink(2)));
            case 4:
                return (computeXor(getLink(5), getLink(6)));
            case 10:
                return (computeXor(getLink(8), getLink(9)));
            case 11:
                return (computeXor(getLink(12), getLink(13)));
            default:
                return (Tristate::UNDEFINED);
        }
    }
}
