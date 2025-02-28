/*
** EPITECH PROJECT, 2025
** B-OOP-400-LYN-4-1-tekspice-matis.taam
** File description:
** Component4013
*/

#pragma once
#include "AComponent.hpp"
#include <vector>

namespace nts {
    class Component4013 : public AComponent {
        public:
            Component4013();

            void simulate(std::size_t tick) override;
            Tristate compute(std::size_t pin) override;
            void setLink(std::size_t pin, IComponent &other, std::size_t otherPin) override;

        private:
            Tristate getValue(std::size_t pin);
            Tristate computeNot(Tristate a);

            struct Link {
                IComponent *comp;
                std::size_t pin;
            };
            std::vector<Link> _pins;
            std::vector<Tristate> _values;

            // Internal states for the two flip-flops.
            Tristate _q1;
            Tristate _q2;
            Tristate _prevClock1;
            Tristate _prevClock2;
        };
}