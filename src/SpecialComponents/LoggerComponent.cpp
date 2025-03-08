/*
** EPITECH PROJECT, 2025
** B-OOP-400-LYN-4-1-tekspice-matis.taam
** File description:
** LoggerComponent
*/

#include "LoggerComponent.hpp"
#include "NtsException.hpp"
#include <iostream>
#include <fstream>

namespace nts {
    void LoggerComponent::simulate(std::size_t tick)
    {
        (void)tick;
        Tristate clock = getLink(9);
        Tristate inhibit = Tristate::UNDEFINED;
        Tristate bit = Tristate::UNDEFINED;
        char c = 0;

        if (clock != Tristate::TRUE)
            return;
        inhibit = getLink(10);
        if (inhibit != Tristate::FALSE)
            return;
        for (int i = 0; i < 7; i++) {
            bit = getLink(i + 1);
            if (bit == Tristate::UNDEFINED)
                return;
            if (bit == Tristate::TRUE)
                c |= (1 << i);
        }
        std::ofstream logFile("log.bin", std::ios::app | std::ios::binary);
        if (logFile.is_open()) {
            logFile.write(&c, 1);
            logFile.close();
        } else {
            std::cerr << "Error: Unable to open log.bin for writing." << std::endl;
        }
    }

    Tristate LoggerComponent::compute(std::size_t pin)
    {
        (void)pin;
        return (Tristate::UNDEFINED);
    }
}
