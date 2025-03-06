/*
** EPITECH PROJECT, 2025
** B-OOP-400-LYN-4-1-tekspice-matis.taam
** File description:
** ClockComponent
*/

#include "ClockComponent.hpp"

namespace nts {
    ClockComponent::ClockComponent() : _Simulated(false)
    {
    }

    void ClockComponent::simulate(std::size_t tick)
    {
        (void)tick;

        if (this->_state != Tristate::UNDEFINED) {
            if (!this->_Simulated) {
                this->_Simulated = true;
            } else if (!this->_nextStateSet) {
                this->_state = (this->_state == Tristate::TRUE) ? Tristate::FALSE : Tristate::TRUE;
            }
            this->_nextStateSet = false;
        }
    }
}
