/*
** EPITECH PROJECT, 2025
** B-OOP-400-LYN-4-1-tekspice-matis.taam
** File description:
** LoggerComponent
*/

#pragma once
#include "AComponent.hpp"

namespace nts {
    class LoggerComponent : public AComponent {
        public:
            void simulate(std::size_t tick = 1) override;
            Tristate compute(std::size_t pin = 1) override;
    };
}
