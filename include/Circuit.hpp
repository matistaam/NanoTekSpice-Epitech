/*
** EPITECH PROJECT, 2025
** B-OOP-400-LYN-4-1-tekspice-matis.taam
** File description:
** Circuit
*/

#pragma once
#include "IComponent.hpp"
#include <map>
#include <memory>
#include <functional>

namespace nts {
    class Circuit : public IComponent {
        public:
            Circuit();

            void addComponent(const std::string &name, std::unique_ptr<IComponent> component);
            IComponent *findComponent(const std::string &name);
            void display() const;

            void simulate(std::size_t tick) override;
            Tristate compute(std::size_t pin) override;

            void setLink(std::size_t pin, IComponent &other, std::size_t otherPin) override;

            void checkEmpty() const;

            std::unique_ptr<IComponent> createComponent(const std::string &type);
        private:
            std::map<std::string, std::function<std::unique_ptr<IComponent>()>> _factories;
            std::map<std::string, std::unique_ptr<IComponent>> _components;
    };
}

std::ostream &operator<<(std::ostream &s, nts::Tristate v);
