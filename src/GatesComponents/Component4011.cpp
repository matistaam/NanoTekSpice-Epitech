/*
** EPITECH PROJECT, 2025
** B-OOP-400-LYN-4-1-tekspice-matis.taam
** File description:
** Component4011
*/

#include "Component4011.hpp"

namespace nts {
    Tristate Component4011::computeNand(Tristate a, Tristate b)
    {
        if (a == Tristate::FALSE || b == Tristate::FALSE)
            return (Tristate::TRUE);
        if (a == Tristate::UNDEFINED || b == Tristate::UNDEFINED)
            return (Tristate::UNDEFINED);
        return (Tristate::FALSE);
    }

    Tristate Component4011::compute(std::size_t pin)
    {
        switch (pin) {
            case 3:
                return (computeNand(getLink(1), getLink(2)));
            case 4:
                return (computeNand(getLink(5), getLink(6)));
            case 10:
                return (computeNand(getLink(8), getLink(9)));
            case 11:
                return (computeNand(getLink(12), getLink(13)));
            default:
                return (Tristate::UNDEFINED);
        }
    }
}
