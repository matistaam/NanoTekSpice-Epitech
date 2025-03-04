/*
** EPITECH PROJECT, 2025
** B-OOP-400-LYN-4-1-tekspice-matis.taam
** File description:
** Component4001
*/

#include "Component4001.hpp"
#include "NtsException.hpp"

namespace nts {
    Tristate Component4001::computeNor(Tristate a, Tristate b)
    {
        if (a == Tristate::TRUE || b == Tristate::TRUE)
            return (Tristate::FALSE);
        if (a == Tristate::UNDEFINED || b == Tristate::UNDEFINED)
            return (Tristate::UNDEFINED);
        return (Tristate::TRUE);
    }

    Tristate Component4001::compute(std::size_t pin)
    {
        if (pin < 1 || pin > 14)
            throw InvalidPinError("4001", pin);
        switch (pin) {
            case 3:
                return (computeNor(getLink(1), getLink(2)));
            case 4:
                return (computeNor(getLink(5), getLink(6)));
            case 10:
                return (computeNor(getLink(8), getLink(9)));
            case 11:
                return (computeNor(getLink(12), getLink(13)));
            default:
                return (Tristate::UNDEFINED);
        }
    }
}
