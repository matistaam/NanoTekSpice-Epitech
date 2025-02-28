/*
** EPITECH PROJECT, 2025
** B-OOP-400-LYN-4-1-tekspice-matis.taam
** File description:
** Component4081
*/

#include "Component4081.hpp"
#include "NtsException.hpp"

namespace nts {
    Tristate Component4081::computeAnd(Tristate a, Tristate b)
    {
        if (a == Tristate::FALSE || b == Tristate::FALSE)
            return (Tristate::FALSE);
        if (a == Tristate::UNDEFINED || b == Tristate::UNDEFINED)
            return (Tristate::UNDEFINED);
        return (Tristate::TRUE);
    }

    Tristate Component4081::compute(std::size_t pin)
    {
        if (pin < 1 || pin > 14)
            throw InvalidPinError("4081", pin);
        switch (pin) {
            case 3:
                return (computeAnd(getLink(1), getLink(2)));
            case 4:
                return (computeAnd(getLink(5), getLink(6)));
            case 10:
                return (computeAnd(getLink(8), getLink(9)));
            case 11:
                return (computeAnd(getLink(12), getLink(13)));
            default:
                return (Tristate::UNDEFINED);
        }
    }
}
