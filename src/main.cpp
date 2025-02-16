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

// int main(void)
// {
//     // Test components
//     std::unique_ptr<nts::IComponent> andGate = std::make_unique<nts::AndComponent>();
//     std::unique_ptr<nts::IComponent> orGate = std::make_unique<nts::OrComponent>();
//     std::unique_ptr<nts::IComponent> xorGate = std::make_unique<nts::XorComponent>();
//     std::unique_ptr<nts::IComponent> notGate = std::make_unique<nts::NotComponent>();

//     // Test inputs
//     std::unique_ptr<nts::IComponent> true1 = std::make_unique<nts::TrueComponent>();
//     std::unique_ptr<nts::IComponent> true2 = std::make_unique<nts::TrueComponent>();
//     std::unique_ptr<nts::IComponent> false1 = std::make_unique<nts::FalseComponent>();
//     std::unique_ptr<nts::IComponent> false2 = std::make_unique<nts::FalseComponent>();
//     std::unique_ptr<nts::IComponent> input = std::make_unique<nts::InputComponent>();

//     // Test AND gate combinations
//     std::cout << "=== AND Gate Tests ===" << std::endl;
//     andGate->setLink(1, *true1, 1);
//     andGate->setLink(2, *true2, 1);
//     std::cout << "TRUE && TRUE = " << andGate->compute(3) << std::endl;

//     andGate->setLink(2, *false1, 1);
//     std::cout << "TRUE && FALSE = " << andGate->compute(3) << std::endl;

//     andGate->setLink(1, *false2, 1);
//     std::cout << "FALSE && FALSE = " << andGate->compute(3) << std::endl;

//     // Test OR gate combinations
//     std::cout << "\n=== OR Gate Tests ===" << std::endl;
//     orGate->setLink(1, *true1, 1);
//     orGate->setLink(2, *true2, 1);
//     std::cout << "TRUE || TRUE = " << orGate->compute(3) << std::endl;

//     orGate->setLink(2, *false1, 1);
//     std::cout << "TRUE || FALSE = " << orGate->compute(3) << std::endl;

//     orGate->setLink(1, *false2, 1);
//     std::cout << "FALSE || FALSE = " << orGate->compute(3) << std::endl;

//     // Test XOR gate combinations
//     std::cout << "\n=== XOR Gate Tests ===" << std::endl;
//     xorGate->setLink(1, *true1, 1);
//     xorGate->setLink(2, *true2, 1);
//     std::cout << "TRUE ^ TRUE = " << xorGate->compute(3) << std::endl;

//     xorGate->setLink(2, *false1, 1);
//     std::cout << "TRUE ^ FALSE = " << xorGate->compute(3) << std::endl;

//     xorGate->setLink(1, *false2, 1);
//     std::cout << "FALSE ^ FALSE = " << xorGate->compute(3) << std::endl;

//     // Test NOT gate
//     std::cout << "\n=== NOT Gate Tests ===" << std::endl;
//     notGate->setLink(1, *true1, 1);
//     std::cout << "!TRUE = " << notGate->compute(2) << std::endl;

//     notGate->setLink(1, *false1, 1);
//     std::cout << "!FALSE = " << notGate->compute(2) << std::endl;

//     // Test undefined state with InputComponent
//     std::cout << "\n=== Undefined State Tests ===" << std::endl;
//     andGate->setLink(1, *input, 1);
//     andGate->setLink(2, *true1, 1);
//     std::cout << "UNDEFINED && TRUE = " << andGate->compute(3) << std::endl;

//     orGate->setLink(1, *input, 1);
//     orGate->setLink(2, *false1, 1);
//     std::cout << "UNDEFINED || FALSE = " << orGate->compute(3) << std::endl;

//     // Test Special Components
//     std::cout << "\n=== Special Components Tests ===" << std::endl;

//     // Test True/False Components
//     std::cout << "\n--- True/False Components ---" << std::endl;
//     std::unique_ptr<nts::IComponent> trueComp = std::make_unique<nts::TrueComponent>();
//     std::unique_ptr<nts::IComponent> falseComp = std::make_unique<nts::FalseComponent>();
//     std::cout << "True Component = " << trueComp->compute(1) << std::endl;
//     std::cout << "False Component = " << falseComp->compute(1) << std::endl;
//     std::cout << "True Component (invalid pin) = " << trueComp->compute(2) << std::endl;
//     std::cout << "False Component (invalid pin) = " << falseComp->compute(2) << std::endl;

//     // Test Input Component
//     std::cout << "\n--- Input Component ---" << std::endl;
//     std::unique_ptr<nts::InputComponent> inputComp = std::make_unique<nts::InputComponent>();
//     std::cout << "Input (default) = " << inputComp->compute(1) << std::endl;
//     inputComp->setState(nts::Tristate::TRUE);
//     std::cout << "Input (set to TRUE) = " << inputComp->compute(1) << std::endl;
//     inputComp->setState(nts::Tristate::FALSE);
//     std::cout << "Input (set to FALSE) = " << inputComp->compute(1) << std::endl;
//     std::cout << "Input (invalid pin) = " << inputComp->compute(2) << std::endl;

//     // Test Output Component
//     std::cout << "\n--- Output Component ---" << std::endl;
//     std::unique_ptr<nts::OutputComponent> outputComp = std::make_unique<nts::OutputComponent>();
//     outputComp->setLink(1, *trueComp, 1);
//     std::cout << "Output (linked to TRUE) = " << outputComp->compute(1) << std::endl;
//     outputComp->setLink(1, *falseComp, 1);
//     std::cout << "Output (linked to FALSE) = " << outputComp->compute(1) << std::endl;
//     std::cout << "Output (invalid pin) = " << outputComp->compute(2) << std::endl;

//     // Test Clock Component
//     std::cout << "\n--- Clock Component ---" << std::endl;
//     std::unique_ptr<nts::ClockComponent> clockComp = std::make_unique<nts::ClockComponent>();
//     std::cout << "Clock (initial) = " << clockComp->compute(1) << std::endl;
//     clockComp->setState(nts::Tristate::TRUE);
//     std::cout << "Clock (set to TRUE) = " << clockComp->compute(1) << std::endl;
//     clockComp->simulate(1);
//     std::cout << "Clock (after simulate) = " << clockComp->compute(1) << std::endl;
//     clockComp->simulate(2);
//     std::cout << "Clock (after second simulate) = " << clockComp->compute(1) << std::endl;
//     std::cout << "Clock (invalid pin) = " << clockComp->compute(2) << std::endl;

//     // Test Circuit
//     std::cout << "\n=== Circuit Tests ===" << std::endl;
//     nts::Circuit circuit;

//     // Test component addition and finding
//     std::cout << "\n--- Component Management ---" << std::endl;
//     circuit.addComponent("input1", std::make_unique<nts::InputComponent>());
//     circuit.addComponent("input2", std::make_unique<nts::InputComponent>());
//     circuit.addComponent("output1", std::make_unique<nts::OutputComponent>());
//     circuit.addComponent("and1", std::make_unique<nts::AndComponent>());

//     auto found = circuit.findComponent("input1");
//     std::cout << "Find existing component: " << (found != nullptr ? "Found" : "Not found") << std::endl;
//     found = circuit.findComponent("nonexistent");
//     std::cout << "Find non-existent component: " << (found != nullptr ? "Found" : "Not found") << std::endl;

//     // Test circuit linking and computation
//     std::cout << "\n--- Circuit Computation ---" << std::endl;
//     auto input1 = dynamic_cast<nts::InputComponent*>(circuit.findComponent("input1"));
//     auto input2 = dynamic_cast<nts::InputComponent*>(circuit.findComponent("input2"));
//     auto and1 = circuit.findComponent("and1");
//     auto output1 = circuit.findComponent("output1");

//     // Link components
//     and1->setLink(1, *input1, 1);
//     and1->setLink(2, *input2, 1);
//     output1->setLink(1, *and1, 3);

//     // Test different input combinations
//     std::cout << "Initial state:" << std::endl;
//     circuit.display();

//     input1->setState(nts::Tristate::TRUE);
//     input2->setState(nts::Tristate::TRUE);
//     std::cout << "\nAfter setting inputs to TRUE:" << std::endl;
//     circuit.display();

//     input2->setState(nts::Tristate::FALSE);
//     std::cout << "\nAfter setting input2 to FALSE:" << std::endl;
//     circuit.display();

//     // Test simulation
//     std::cout << "\n--- Circuit Simulation ---" << std::endl;
//     circuit.addComponent("clock1", std::make_unique<nts::ClockComponent>());
//     auto clock1 = dynamic_cast<nts::ClockComponent*>(circuit.findComponent("clock1"));
//     clock1->setState(nts::Tristate::TRUE);

//     std::cout << "Initial clock state:" << std::endl;
//     circuit.display();

//     circuit.simulate(1);
//     std::cout << "\nAfter first simulation:" << std::endl;
//     circuit.display();

//     circuit.simulate(2);
//     std::cout << "\nAfter second simulation:" << std::endl;
//     circuit.display();
//     return 0;
// }
