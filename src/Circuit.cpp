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
#include "ClockComponent.hpp"
#include "TrueComponent.hpp"
#include "FalseComponent.hpp"
#include "Component4001.hpp"
#include "Component4011.hpp"
#include "Component4030.hpp"
#include "Component4069.hpp"
#include "Component4071.hpp"
#include "Component4081.hpp"
#include "NtsException.hpp"

namespace nts {
    void Circuit::addComponent(const std::string &name, std::unique_ptr<IComponent> component)
    {
        if (this->_components.find(name) != this->_components.end())
            throw DuplicateComponentError(name);
        this->_components[name] = std::move(component);
    }

    IComponent *Circuit::findComponent(const std::string &name)
    {
        auto it = this->_components.find(name);

        if (it == this->_components.end())
            throw UnknownComponentError(name);
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

    void Circuit::checkEmpty() const
    {
        if (this->_components.empty())
            throw EmptyCircuitError();
    }

    std::unique_ptr<IComponent> Circuit::createComponent(const std::string& type)
    {
        if (type == "input")
            return std::make_unique<InputComponent>();
        if (type == "output")
            return std::make_unique<OutputComponent>();
        if (type == "clock")
            return std::make_unique<ClockComponent>();
        if (type == "true")
            return std::make_unique<TrueComponent>();
        if (type == "false")
            return std::make_unique<FalseComponent>();
        if (type == "4001")
            return std::make_unique<Component4001>();
        if (type == "4011")
            return std::make_unique<Component4011>();
        if (type == "4030")
            return std::make_unique<Component4030>();
        if (type == "4069")
            return std::make_unique<Component4069>();
        if (type == "4071")
            return std::make_unique<Component4071>();
        if (type == "4081")
            return std::make_unique<Component4081>();
        throw UnknownComponentError(type);
    }
}

std::ostream &operator<<(std::ostream &s, nts::Tristate v)
{
    switch (v) {
        case nts::Tristate::UNDEFINED:
            s << "U";
            break;
        case nts::Tristate::TRUE:
            s << "1";
            break;
        case nts::Tristate::FALSE:
            s << "0";
            break;
    }
    return (s);
}
