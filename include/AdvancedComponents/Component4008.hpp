/*
** EPITECH PROJECT, 2025
** B-OOP-400-LYN-4-1-tekspice-matis.taam
** File description:
** Component4008
*/

#pragma once
#include "AComponent.hpp"
#include <vector>

namespace nts {
    class Component4008 : public AComponent {
        public:
            Component4008();

            void simulate(std::size_t tick) override;
            Tristate compute(std::size_t pin) override;
            void setLink(std::size_t pin, IComponent &other, std::size_t otherPin) override;

        private:
            Tristate getValue(std::size_t pin);
            Tristate computeAnd(Tristate a, Tristate b);
            Tristate computeOr(Tristate a, Tristate b);
            Tristate computeXor(Tristate a, Tristate b);
            std::pair<Tristate, Tristate> fullAdder(Tristate a, Tristate b, Tristate carry);
            struct Link {
                IComponent *comp;
                std::size_t pin;
            };
            std::vector<Link> _pins;
            std::vector<Tristate> _values;
    };
}
