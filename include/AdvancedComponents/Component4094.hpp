/*
** EPITECH PROJECT, 2025
** B-OOP-400-LYN-4-1-tekspice-matis.taam
** File description:
** Component4094
*/

#pragma once
#include "AComponent.hpp"
#include <vector>

namespace nts {
    class Component4094 : public AComponent {
        public:
            Component4094();

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
            // Internal 8-bit shift register and latch (index 0 is the first stage)
            std::vector<Tristate> _shift; // size 8
            std::vector<Tristate> _latch; // size 8
            Tristate _out_qe; // Secondary output from the shift register, updated on negative clock edge
            Tristate _prevClock; // Previous input states for edge detection
            Tristate _prevStrobe;
    };
}
