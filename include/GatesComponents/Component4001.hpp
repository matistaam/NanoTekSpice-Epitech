/*
** EPITECH PROJECT, 2025
** B-OOP-400-LYN-4-1-tekspice-matis.taam
** File description:
** Component4001
*/

#pragma once
#include "AComponent.hpp"

namespace nts {
    class Component4001 : public AComponent {
        public:
            Component4001();

            Tristate compute(std::size_t pin) override;

        private:
            Tristate computeNor(Tristate a, Tristate b);
            Tristate _q;
            Tristate _qb;
            bool _isComputingRS = false;
    };
}
