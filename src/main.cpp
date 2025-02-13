/*
** EPITECH PROJECT, 2025
** B-OOP-400-LYN-4-1-tekspice-matis.taam
** File description:
** main
*/

#include <iostream>
#include <memory>
#include "IComponent.hpp"
#include "AndComponent.hpp"
#include "OrComponent.hpp"
#include "XorComponent.hpp"
#include "NotComponent.hpp"
#include "TrueComponent.hpp"
#include "FalseComponent.hpp"
#include "InputComponent.hpp"
#include "OutputComponent.hpp"
#include "ClockComponent.hpp"
#include "Circuit.hpp"

std::ostream &operator<<(std::ostream &s, nts::Tristate v)
{
    switch (v) {
        case nts::Tristate::UNDEFINED:
            s << "Undefined";
            break;
        case nts::Tristate::TRUE:
            s << "True";
            break;
        case nts::Tristate::FALSE:
            s << "False";
            break;
    }
    return (s);
}

int main(void)
{
    std::unique_ptr<nts::IComponent> gate = std::make_unique<nts::AndComponent>();
    std::unique_ptr<nts::IComponent> input1 = std::make_unique<nts::FalseComponent>();
    std::unique_ptr<nts::IComponent> input2 = std::make_unique<nts::TrueComponent>();
    std::unique_ptr<nts::IComponent> inverter = std::make_unique<nts::NotComponent>();
    gate->setLink(1, *input1, 1);
    gate->setLink(2, *input2, 1);
    inverter->setLink(1, *gate, 3);
    std::cout << "!(" << input1->compute(1) << " && " << input2->compute(1) << ") -> " << inverter->compute(2) << std::endl;
}
