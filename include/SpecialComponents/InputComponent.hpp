/*
** EPITECH PROJECT, 2025
** B-OOP-400-LYN-4-1-tekspice-matis.taam
** File description:
** InputComponent
*/

#pragma once
#include "AComponent.hpp"

namespace nts {
    class InputComponent : public AComponent {
        public:
            InputComponent();

            Tristate compute(std::size_t pin) override;

            void setState(Tristate state);

        private:
            Tristate _state;
    };
}
