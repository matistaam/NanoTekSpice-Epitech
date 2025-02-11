/*
** EPITECH PROJECT, 2025
** B-OOP-400-LYN-4-1-tekspice-matis.taam
** File description:
** AComponent
*/

#include "AComponent.hpp"

namespace nts {
    Tristate AComponent::getLink(std::size_t pin) const
    {
        auto it = this->_links.find(pin);

        if (it == this->_links.end())
            return (Tristate::UNDEFINED);
        return (it->second.first->compute(it->second.second));
    }

    void AComponent::setLink(std::size_t pin, IComponent &other, std::size_t otherPin)
    {
        this->_links[pin] = std::make_pair(&other, otherPin);
    }
}
