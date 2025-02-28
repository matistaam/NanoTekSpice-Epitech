/*
** EPITECH PROJECT, 2025
** B-OOP-400-LYN-4-1-tekspice-matis.taam
** File description:
** Component4017
*/

#pragma once
#include "AComponent.hpp"
#include <map>
#include <utility>
#include <vector>

namespace nts {
    class Component4017 : public AComponent {
        public:
            Component4017();
            ~Component4017() override = default;

            void simulate(std::size_t tick) override;
            Tristate compute(std::size_t pin) override;

        private:
            // Internal counter: values 0 to 9
            int _counter;

            // Previous clock values for edge detection (CP0 on pin 14, CP1 on pin 13)
            Tristate _prevCP0;
            Tristate _prevCP1;
    };
}