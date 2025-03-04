/*
** EPITECH PROJECT, 2025
** B-OOP-400-LYN-4-1-tekspice-matis.taam
** File description:
** Shell
*/

#pragma once
#include "Circuit.hpp"

namespace nts {
    class Shell {
        public:
            Shell(Circuit &circuit);

            void run();

        private:
            void handleCommand(const std::string &command);
            void display() const;
            void setInput(const std::string &name, const std::string &value);
            void simulate();
            void loop();
            Circuit &_circuit;
            bool _running;
            std::size_t _tick;
            std::map<std::string, Tristate> _pendingInputs;
    };
}
