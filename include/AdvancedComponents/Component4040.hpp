/*
** EPITECH PROJECT, 2025
** B-OOP-400-LYN-4-1-tekspice-matis.taam
** File description:
** Component4040
*/

#pragma once
#include "AComponent.hpp"
#include <vector>

namespace nts {
    class Component4040 : public AComponent {
        public:
            Component4040();

            void simulate(std::size_t tick) override;
            Tristate compute(std::size_t pin) override;

            void setLink(std::size_t pin, IComponent &other, std::size_t otherPin) override;

        private:
            Tristate getValue(std::size_t pin);
            struct Link {
                IComponent *comp;
                std::size_t pin;
            };
            std::vector<Link> _pins;
            std::vector<Tristate> _values;
            unsigned int _counter; // Internal state: 12-bit counter (values from 0 to 4095)
            Tristate _prevClock; // Previous clock state (for detecting a falling edge on pin 10)
    };
}
