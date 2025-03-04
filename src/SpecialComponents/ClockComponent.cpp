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

        if (this->_state != Tristate::UNDEFINED && (this->_Simulated == false)) {
            this->_Simulated = true;
        } else if (this->_state != Tristate::UNDEFINED) {
            if (this->_state == Tristate::TRUE) {
                this->_state = Tristate::FALSE;
            } else {
                this->_state = Tristate::TRUE;
            }
        }
    }
}
