/*
** EPITECH PROJECT, 2025
** B-OOP-400-LYN-4-1-tekspice-matis.taam
** File description:
** TrueComponent
*/

#pragma once
#include "AComponent.hpp"

namespace nts {
    class TrueComponent : public AComponent {
        public:
            Tristate compute(std::size_t pin) override;
    };
}
