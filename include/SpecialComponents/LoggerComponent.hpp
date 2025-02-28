/*
** EPITECH PROJECT, 2025
** B-OOP-400-LYN-4-1-tekspice-matis.taam
** File description:
** LoggerComponent
*/

#pragma once
#include "AComponent.hpp"
#include <fstream>

namespace nts {
    class LoggerComponent : public AComponent {
        public:
            LoggerComponent();
            ~LoggerComponent() override;

            void simulate(std::size_t tick) override;
            Tristate compute(std::size_t pin) override;

        private:
            char computeChar() const;
            std::ofstream _file;
            bool _lastClock;
    };
}
