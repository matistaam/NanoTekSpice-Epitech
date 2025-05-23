/*
** EPITECH PROJECT, 2025
** B-OOP-400-LYN-4-1-tekspice-matis.taam
** File description:
** Component4094
*/

#include "NtsException.hpp"
#include "Component4094.hpp"

namespace nts {
    Component4094::Component4094() : _pins(16, {nullptr, 0}), _values(16, Tristate::UNDEFINED), _shift(8, Tristate::UNDEFINED),
    _latch(8, Tristate::UNDEFINED), _out_qe(Tristate::UNDEFINED), _prevClock(Tristate::UNDEFINED), _prevStrobe(Tristate::UNDEFINED)
    {
        this->_values[15 - 1] = Tristate::TRUE;
    }

    void Component4094::simulate(std::size_t tick)
    {
        (void)tick;
        Tristate clockVal = getValue(3);
        Tristate strobeVal = getValue(1);
        Tristate dataVal = getValue(2);

        if (this->_prevClock != Tristate::TRUE && clockVal == Tristate::TRUE) {
            for (int i = 7; i > 0; --i)
                this->_shift[i] = this->_shift[i - 1];
            this->_shift[0] = dataVal;
        }
        if (this->_prevClock == Tristate::TRUE && clockVal == Tristate::FALSE)
            this->_out_qe = this->_shift[7];
        if (this->_prevStrobe != Tristate::TRUE && strobeVal == Tristate::TRUE) {
            for (size_t i = 0; i < 8; ++i)
                this->_latch[i] = this->_shift[i];
        }
        this->_prevClock = clockVal;
        this->_prevStrobe = strobeVal;
    }

    Tristate Component4094::compute(std::size_t pin)
    {
        Tristate enableVal = Tristate::UNDEFINED;

        if (pin < 1 || pin > 16)
            throw InvalidPinError("4094", pin);
        switch (pin) {
            case 1:
                return (getValue(1));
            case 2:
                return (getValue(2));
            case 3:
                return (getValue(3));
            case 15:
                return (getValue(15));
            default:
                break;
        }
        if (pin == 8 || pin == 16)
            return (Tristate::UNDEFINED);
        enableVal = getValue(15);
        if (enableVal != Tristate::TRUE)
            return (Tristate::UNDEFINED);
        switch (pin) {
            case 4:
                return (this->_latch[0]);
            case 5:
                return (this->_latch[1]);
            case 6:
                return (this->_latch[2]);
            case 7:
                return (this->_latch[3]);
            case 9:
                return (this->_shift[7]);
            case 10:
                return (this->_out_qe);
            case 11:
                return (this->_latch[7]);
            case 12:
                return (this->_latch[6]);
            case 13:
                return (this->_latch[5]);
            case 14:
                return (this->_latch[4]);
            default:
                return (Tristate::UNDEFINED);
        }
    }

    void Component4094::setLink(std::size_t pin, IComponent &other, std::size_t otherPin)
    {
        if (pin < 1 || pin > 16)
            throw InvalidPinError("4094", pin);
        this->_pins[pin - 1] = {&other, otherPin};
    }

    Tristate Component4094::getValue(std::size_t pin)
    {
        Link link = {nullptr, 0};

        if (pin < 1 || pin > 16)
            throw InvalidPinError("4094", pin);
        link = this->_pins[pin - 1];
        if (link.comp != nullptr)
            return (link.comp->compute(link.pin));
        return (this->_values[pin - 1]);
    }
}
