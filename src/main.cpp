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
#include "NtsException.hpp"
#include "Component4001.hpp"
#include "Component4011.hpp"
#include "Component4030.hpp"
#include "Component4069.hpp"
#include "Component4071.hpp"
#include "Component4081.hpp"
#include "Shell.hpp"

int main(int ac, char **av)
{
    if (ac != 2) {
        std::cerr << "Usage: " << av[0] << " <circuit_file>" << std::endl;
        return (84);
    }
    nts::Circuit circuit;
    nts::Shell shell(circuit);
    shell.run();
    return (0);
}
