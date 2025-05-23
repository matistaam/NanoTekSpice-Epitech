/*
** EPITECH PROJECT, 2025
** B-OOP-400-LYN-4-1-tekspice-matis.taam
** File description:
** Component4512
*/

#pragma once
#include "AComponent.hpp"
#include <vector>

namespace nts {
    class Component4512 : public AComponent {
        public:
            Component4512();

            // void simulate(std::size_t tick) override;
            // Tristate compute(std::size_t pin) override;

            void setLink(std::size_t pin, IComponent &other, std::size_t otherPin) override;

        private:
            Tristate getValue(std::size_t pin);
            struct Link {
                IComponent *comp;
                std::size_t pin;
            };
            std::vector<Link> _pins;
            std::vector<Tristate> _values;
            Tristate _prevLatchEnable;
    };
}
