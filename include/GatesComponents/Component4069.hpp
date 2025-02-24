/*
** EPITECH PROJECT, 2025
** B-OOP-400-LYN-4-1-tekspice-matis.taam
** File description:
** Component4069
*/

#pragma once
#include "AComponent.hpp"

namespace nts {
    class Component4069 : public AComponent {
        public:
            Tristate compute(std::size_t pin) override;

        private:
            Tristate computeNot(Tristate a);
    };
}
