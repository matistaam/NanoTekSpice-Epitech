/*
** EPITECH PROJECT, 2025
** B-OOP-400-LYN-4-1-tekspice-matis.taam
** File description:
** ClockComponent
*/

#include "ClockComponent.hpp"

namespace nts {
    void ClockComponent::simulate(std::size_t tick)
    {
        (void)tick;
        Tristate current = compute(1);

        if (current == Tristate::TRUE)
            setState(Tristate::FALSE);
        else if (current == Tristate::FALSE)
            setState(Tristate::TRUE);
    }
}
