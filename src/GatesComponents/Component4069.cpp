/*
** EPITECH PROJECT, 2025
** B-OOP-400-LYN-4-1-tekspice-matis.taam
** File description:
** Component4069
*/

#include "Component4069.hpp"
#include "NtsException.hpp"

namespace nts {
    Tristate Component4069::computeNot(Tristate a)
    {
        if (a == Tristate::UNDEFINED)
            return (Tristate::UNDEFINED);
        if (a == Tristate::TRUE)
            return (Tristate::FALSE);
        return (Tristate::TRUE);
    }

    Tristate Component4069::compute(std::size_t pin)
    {
        if (pin < 1 || pin > 14)
            throw InvalidPinError("4069", pin);
        switch (pin) {
            case 2:
                return (computeNot(getLink(1)));
            case 4:
                return (computeNot(getLink(3)));
            case 6:
                return (computeNot(getLink(5)));
            case 8:
                return (computeNot(getLink(9)));
            case 10:
                return (computeNot(getLink(11)));
            case 12:
                return (computeNot(getLink(13)));
            default:
                return (Tristate::UNDEFINED);
        }
    }
}
