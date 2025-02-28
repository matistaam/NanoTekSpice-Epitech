/*
** EPITECH PROJECT, 2025
** B-OOP-400-LYN-4-1-tekspice-matis.taam
** File description:
** Component4071
*/

#include "Component4071.hpp"
#include "NtsException.hpp"

namespace nts {
    Tristate Component4071::computeOr(Tristate a, Tristate b)
    {
        if (a == Tristate::TRUE || b == Tristate::TRUE)
            return (Tristate::TRUE);
        if (a == Tristate::UNDEFINED || b == Tristate::UNDEFINED)
            return (Tristate::UNDEFINED);
        return (Tristate::FALSE);
    }

    Tristate Component4071::compute(std::size_t pin)
    {
        if (pin < 1 || pin > 14)
            throw InvalidPinError("4071", pin);
        switch (pin) {
            case 3:
                return (computeOr(getLink(1), getLink(2)));
            case 4:
                return (computeOr(getLink(5), getLink(6)));
            case 10:
                return (computeOr(getLink(8), getLink(9)));
            case 11:
                return (computeOr(getLink(12), getLink(13)));
            default:
                return (Tristate::UNDEFINED);
        }
    }
}
