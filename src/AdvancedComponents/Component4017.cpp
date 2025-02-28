/*
** EPITECH PROJECT, 2025
** B-OOP-400-LYN-4-1-tekspice-matis.taam
** File description:
** Component4017
*/

#include "Component4017.hpp"

namespace nts {
    Component4017::Component4017() : _counter(0), _prevCP0(Tristate::UNDEFINED), _prevCP1(Tristate::UNDEFINED)
    {
    }

    void Component4017::simulate(std::size_t tick)
    {
        (void)tick; // Unused parameter

        // Retrieve input values for the clock and reset pins.
        // CP0 is on pin 14, CP1 is on pin 13, and MR (reset) is on pin 15.
        Tristate cp0 = Tristate::UNDEFINED;
        Tristate cp1 = Tristate::UNDEFINED;
        Tristate mr  = Tristate::UNDEFINED;

        if (this->_links.find(14) != this->_links.end())
            cp0 = this->_links[14].first->compute(this->_links[14].second);
        if (this->_links.find(13) != this->_links.end())
            cp1 = this->_links[13].first->compute(this->_links[13].second);
        if (this->_links.find(15) != this->_links.end())
            mr  = this->_links[15].first->compute(this->_links[15].second);

        // If master reset (MR) is high, counter reset to 0.
        if (mr == Tristate::TRUE) {
            this->_counter = 0;
        } else {
            // Detect clock edge to advance the counter.
            bool advance = false;
            // Condition 1 A LOW-to-HIGH transition on CP0 while CP1 is LOW.
            if (this->_prevCP0 == Tristate::FALSE && cp0 == Tristate::TRUE && cp1 == Tristate::FALSE)
                advance = true;
            // Condition 2 A HIGH-to-LOW transition on CP1 while CP0 is HIGH.
            if (this->_prevCP1 == Tristate::TRUE && cp1 == Tristate::FALSE && cp0 == Tristate::TRUE)
                advance = true;
            if (advance)
                this->_counter = (this->_counter + 1) % 10;
        }
        // Update previous clock values for edge detection in the next simulate.
        this->_prevCP0 = cp0;
        this->_prevCP1 = cp1;
    }

    Tristate Component4017::compute(std::size_t pin)
    {
        // For input pins (CP0, CP1, MR), delegate to the linked component if present.
        if (pin == 13 || pin == 14 || pin == 15) {
            if (this->_links.find(pin) != this->_links.end())
                return (this->_links[pin].first->compute(this->_links[pin].second));
            return (Tristate::UNDEFINED);
        }
        // Check the reset condition. If MR is high, output the reset state:
        // According to the pdf, on reset:
        //   Q0 (pin 3) and Q5–Q9 (pins 1, 5, 6, 9, 11) and the group output (pin 12) are HIGH,
        //   while Q1–Q4 (pins 2, 4, 7, 10) are LOW.
        Tristate mr = Tristate::UNDEFINED;
        if (this->_links.find(15) != this->_links.end())
            mr = this->_links[15].first->compute(this->_links[15].second);
        if (mr == Tristate::TRUE) {
            if (pin == 3 || pin == 1 || pin == 5 || pin == 6 || pin == 9 || pin == 11 || pin == 12)
                return (Tristate::TRUE);
            if (pin == 2 || pin == 4 || pin == 7 || pin == 10)
                return (Tristate::FALSE);
            return (Tristate::UNDEFINED);
        } else {
            // Normal operation:
            // It is HIGH if the counter is in states 0–4, and LOW if in states 5–9.
            int count = this->_counter;
            // One-hot output: only the output corresponding to the counter value is HIGH.
            if ((count == 0 && pin == 3) ||
                (count == 1 && pin == 2) ||
                (count == 2 && pin == 4) ||
                (count == 3 && pin == 7) ||
                (count == 4 && pin == 10) ||
                (count == 5 && pin == 1) ||
                (count == 6 && pin == 5) ||
                (count == 7 && pin == 6) ||
                (count == 8 && pin == 9) ||
                (count == 9 && pin == 11))
                return (Tristate::TRUE);
            // For the group output on pin 12, output HIGH if the counter is less than 5.
            if (pin == 12) {
                if (count < 5)
                    return (Tristate::TRUE);
                return (Tristate::FALSE);
            }
            // All other outputs remain LOW.
            return (Tristate::FALSE);
        }
    }
}
