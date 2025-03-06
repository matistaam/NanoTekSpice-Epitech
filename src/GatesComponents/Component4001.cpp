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
        static bool computing = false;
        Tristate result = Tristate::UNDEFINED;

        if (pin < 1 || pin > 14)
            throw InvalidPinError("4001", pin);
        if (computing)
            return (Tristate::UNDEFINED);
        computing = true;
        result = Tristate::UNDEFINED;
        switch (pin) {
            case 3:
                result = computeNor(getLink(1), getLink(2));
                break;
            case 4:
                result = computeNor(getLink(5), getLink(6));
                break;
            case 10:
                result = computeNor(getLink(8), getLink(9));
                break;
            case 11:
                result = computeNor(getLink(12), getLink(13));
                break;
            default:
                result = Tristate::UNDEFINED;
        }
        computing = false;
        return (result);
    }
}
