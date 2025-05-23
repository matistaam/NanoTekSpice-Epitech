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
        std::string trimmedCommand = command;

        trimmedCommand.erase(trimmedCommand.find_last_not_of(" \t") + 1);
        trimmedCommand.erase(0, trimmedCommand.find_first_not_of(" \t"));
        if (trimmedCommand == "exit")
            this->_running = false;
        else if (trimmedCommand == "simulate")
            simulate();
        else if (trimmedCommand == "display")
            display();
        else if (trimmedCommand == "loop")
            loop();
        else if (trimmedCommand.find('=') != std::string::npos) {
            name = trimmedCommand.substr(0, trimmedCommand.find('='));
            value = trimmedCommand.substr(trimmedCommand.find('=') + 1);
            name.erase(name.find_last_not_of(" \t") + 1);
            name.erase(0, name.find_first_not_of(" \t"));
            value.erase(value.find_last_not_of(" \t") + 1);
            value.erase(0, value.find_first_not_of(" \t"));
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
