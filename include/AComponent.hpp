/*
** EPITECH PROJECT, 2025
** B-OOP-400-LYN-4-1-tekspice-matis.taam
** File description:
** AComponent
*/

#pragma once
#include "IComponent.hpp"
#include <map>

namespace nts {
    class AComponent : public IComponent {
        public:
            ~AComponent() = default;

            void simulate(std::size_t tick) override;
            virtual Tristate compute(std::size_t pin) = 0;

            Tristate getLink(std::size_t pin) const;

            void setLink(std::size_t pin, IComponent &other, std::size_t otherPin) override;

        protected:
            std::map<std::size_t, std::pair<IComponent *, std::size_t>> _links;
    };
}
