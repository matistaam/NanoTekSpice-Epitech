/*
** EPITECH PROJECT, 2025
** B-OOP-400-LYN-4-1-tekspice-matis.taam
** File description:
** Component4001
*/

#include "Component4001.hpp"
#include "NtsException.hpp"
#include <set>

namespace nts {
    Component4001::Component4001() : _q(Tristate::UNDEFINED), _qb(Tristate::UNDEFINED)
    {
    }

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
        Tristate R = Tristate::UNDEFINED;
        Tristate S = Tristate::UNDEFINED;
        Tristate Q = Tristate::UNDEFINED;
        Tristate Qb = Tristate::UNDEFINED;
        Tristate newQ = Tristate::UNDEFINED;
        Tristate newQb = Tristate::UNDEFINED;
        bool changed = true;

        if (pin < 1 || pin > 14)
            throw InvalidPinError("4001", pin);
        if (pin == 3 || pin == 4) {
            if (this->_isComputingRS)
                return (Tristate::UNDEFINED);
            this->_isComputingRS = true;
            R = getLink(1);
            S = getLink(6);
            if (R == Tristate::FALSE && S == Tristate::FALSE) {
                Q  = Tristate::TRUE;
                Qb = Tristate::FALSE;
            } else {
                Q  = this->_q;
                Qb = this->_qb;
            }
            std::set<std::pair<Tristate, Tristate>> visited;
            while (changed) {
                if (visited.find({Q, Qb}) != visited.end())
                    break;
                visited.insert({Q, Qb});
                newQ  = computeNor(R, Qb);
                newQb = computeNor(S, Q);
                changed = (newQ != Q || newQb != Qb);
                Q = newQ;
                Qb = newQb;
            }
            this->_q = Q;
            this->_qb = Qb;
            this->_isComputingRS = false;
            if (pin == 3)
                return (Q);
            else
                return (Qb);
        }
        if (pin == 10)
            return computeNor(getLink(8), getLink(9));
        if (pin == 11)
            return computeNor(getLink(12), getLink(13));
        return (Tristate::UNDEFINED);
    }
}
