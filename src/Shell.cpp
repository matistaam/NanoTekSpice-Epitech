/*
** EPITECH PROJECT, 2025
** B-OOP-400-LYN-4-1-tekspice-matis.taam
** File description:
** Shell
*/

#include <iostream>
#include <csignal>
#include "Shell.hpp"
#include "InputComponent.hpp"
#include "ClockComponent.hpp"

namespace nts {
    volatile std::sig_atomic_t g_looping = true;

    static void signalHandler(int)
    {
        g_looping = false;
    }

    Shell::Shell(Circuit &circuit) : _circuit(circuit), _running(true), _tick(0)
    {
    }

    void Shell::run()
    {
        std::string command;

        std::cout << "> ";
        while (this->_running && std::getline(std::cin, command)) {
            if (!command.empty())
                handleCommand(command);
            if (this->_running)
                std::cout << "> ";
        }
    }

    void Shell::handleCommand(const std::string &command)
    {
        std::string name = "";
        std::string value = "";

        if (command == "exit")
            this->_running = false;
        else if (command == "simulate")
            simulate();
        else if (command == "display")
            display();
        else if (command == "loop")
            loop();
        else if (command.find('=') != std::string::npos) {
            name = command.substr(0, command.find('='));
            value = command.substr(command.find('=') + 1);
            setInput(name, value);
        }
    }

    void Shell::display() const
    {
        std::cout << "tick: " << this->_tick << std::endl;
        this->_circuit.display();
    }

    void Shell::setInput(const std::string &name, const std::string &value)
    {
        auto *component = dynamic_cast<InputComponent*>(this->_circuit.findComponent(name));

        if (!component)
            return;
        if (value == "1")
            this->_pendingInputs[name] = Tristate::TRUE;
        else if (value == "0")
            this->_pendingInputs[name] = Tristate::FALSE;
        else if (value == "U")
            this->_pendingInputs[name] = Tristate::UNDEFINED;
    }

    void Shell::simulate()
    {
        for (const auto &[name, state] : this->_pendingInputs) {
            auto *component = dynamic_cast<InputComponent*>(this->_circuit.findComponent(name));
            if (component)
                component->setState(state);
        }
        this->_pendingInputs.clear();
        this->_circuit.simulate(this->_tick++);
    }

    void Shell::loop()
    {
        signal(SIGINT, signalHandler);
        g_looping = true;
        while (g_looping) {
            simulate();
            display();
        }
        signal(SIGINT, SIG_DFL);
    }
}
