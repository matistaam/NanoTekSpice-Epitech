/*
** EPITECH PROJECT, 2025
** B-OOP-400-LYN-4-1-tekspice-matis.taam
** File description:
** ClockComponent
*/

#pragma once
#include "InputComponent.hpp"
#include <stdbool.h>

namespace nts {
    class ClockComponent : public InputComponent {
        public:
            ClockComponent();

            void simulate(std::size_t tick) override;

            bool _Simulated;
    };
}
