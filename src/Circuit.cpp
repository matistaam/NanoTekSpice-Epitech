/*
** EPITECH PROJECT, 2025
** B-OOP-400-LYN-4-1-tekspice-matis.taam
** File description:
** Circuit
*/

#include <iostream>
#include "Circuit.hpp"
#include "InputComponent.hpp"
#include "OutputComponent.hpp"

namespace nts {
    void Circuit::addComponent(const std::string &name, std::unique_ptr<IComponent> component)
    {
        this->_components[name] = std::move(component);
    }

    IComponent *Circuit::findComponent(const std::string &name)
    {
        auto it = this->_components.find(name);

        if (it == this->_components.end())
            return (nullptr);
        return (it->second.get());
    }

    void Circuit::display() const
    {
        for (const auto &[name, component] : this->_components) {
            if (dynamic_cast<InputComponent*>(component.get()))
                std::cout << name << "=" << component->compute(1) << std::endl;
        }
        for (const auto &[name, component] : this->_components) {
            if (dynamic_cast<OutputComponent*>(component.get()))
                std::cout << name << "=" << component->compute(1) << std::endl;
        }
    }

    void Circuit::simulate(std::size_t tick)
    {
        for (auto &[name, component] : this->_components)
            component->simulate(tick);
    }

    Tristate Circuit::compute(std::size_t pin)
    {
        (void)pin;
        return (Tristate::UNDEFINED);
    }

    void Circuit::setLink(std::size_t pin, IComponent &other, std::size_t otherPin)
    {
        (void)pin;
        (void)other;
        (void)otherPin;
    }
}
