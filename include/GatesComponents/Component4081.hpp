/*
** EPITECH PROJECT, 2025
** B-OOP-400-LYN-4-1-tekspice-matis.taam
** File description:
** Component4081
*/

#pragma once
#include "AComponent.hpp"

namespace nts {
    class Component4081 : public AComponent {
        public:
            Tristate compute(std::size_t pin) override;

        private:
            Tristate computeAnd(Tristate a, Tristate b);
    };
}
