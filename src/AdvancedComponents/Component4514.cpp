#include "Component4514.hpp"
#include "NtsException.hpp"

namespace nts {
    Component4514::Component4514() : _pins(24, {nullptr, 0}), _values(24, Tristate::UNDEFINED),
        _latchedA(Tristate::UNDEFINED), _latchedB(Tristate::UNDEFINED), _latchedC(Tristate::UNDEFINED),
        _latchedD(Tristate::UNDEFINED), _prevLatchEnable(Tristate::UNDEFINED)
    {
    }

    void Component4514::simulate(std::size_t tick)
    {
        (void)tick;
        Tristate strobeVal = getValue(1);

        if (this->_prevLatchEnable == Tristate::UNDEFINED && strobeVal != Tristate::UNDEFINED)
            this->_prevLatchEnable = strobeVal;
        if (this->_prevLatchEnable == Tristate::FALSE && strobeVal == Tristate::TRUE) {
            this->_latchedA = getValue(2);
            this->_latchedB = getValue(3);
            this->_latchedC = getValue(21);
            this->_latchedD = getValue(22);
        }
        this->_prevLatchEnable = strobeVal;
    }

    Tristate Component4514::compute(std::size_t pin)
    {
        int value = 0;

        if (pin < 1 || pin > 24)
            throw InvalidPinError("4514", pin);
        if (pin == 1 || pin == 2 || pin == 3 || pin == 21 || pin == 22 || pin == 23)
            return (getValue(pin));
        if (pin == 12 || pin == 24)
            return (Tristate::UNDEFINED);
        if (getValue(23) == Tristate::TRUE) {
            if (this->_latchedA == Tristate::UNDEFINED || this->_latchedB == Tristate::UNDEFINED ||
            this->_latchedC == Tristate::UNDEFINED || this->_latchedD == Tristate::UNDEFINED)
                return (Tristate::UNDEFINED);
            return (Tristate::FALSE);
        }
        if (getValue(23) == Tristate::UNDEFINED)
            return (Tristate::UNDEFINED);
        if (this->_latchedA == Tristate::UNDEFINED || this->_latchedB == Tristate::UNDEFINED ||
            this->_latchedC == Tristate::UNDEFINED || this->_latchedD == Tristate::UNDEFINED)
            return (Tristate::FALSE);
        value |= (this->_latchedA == Tristate::TRUE ? 1 : 0);
        value |= (this->_latchedB == Tristate::TRUE ? 2 : 0);
        value |= (this->_latchedC == Tristate::TRUE ? 4 : 0);
        value |= (this->_latchedD == Tristate::TRUE ? 8 : 0);
        switch (pin) {
            case 11: return (value == 0 ? Tristate::TRUE : Tristate::FALSE);
            case 9: return (value == 1 ? Tristate::TRUE : Tristate::FALSE);
            case 10: return (value == 2 ? Tristate::TRUE : Tristate::FALSE);
            case 8: return (value == 3 ? Tristate::TRUE : Tristate::FALSE);
            case 7: return (value == 4 ? Tristate::TRUE : Tristate::FALSE);
            case 6: return (value == 5 ? Tristate::TRUE : Tristate::FALSE);
            case 5: return (value == 6 ? Tristate::TRUE : Tristate::FALSE);
            case 4: return (value == 7 ? Tristate::TRUE : Tristate::FALSE);
            case 18: return (value == 8 ? Tristate::TRUE : Tristate::FALSE);
            case 17: return (value == 9 ? Tristate::TRUE : Tristate::FALSE);
            case 20: return (value == 10 ? Tristate::TRUE : Tristate::FALSE);
            case 19: return (value == 11 ? Tristate::TRUE : Tristate::FALSE);
            case 14: return (value == 12 ? Tristate::TRUE : Tristate::FALSE);
            case 13: return (value == 13 ? Tristate::TRUE : Tristate::FALSE);
            case 16: return (value == 14 ? Tristate::TRUE : Tristate::FALSE);
            case 15: return (value == 15 ? Tristate::TRUE : Tristate::FALSE);
            default: return (Tristate::UNDEFINED);
        }
    }

    void Component4514::setLink(std::size_t pin, IComponent &other, std::size_t otherPin)
    {
        if (pin < 1 || pin > 24)
            throw InvalidPinError("4514", pin);
        this->_pins[pin - 1] = {&other, otherPin};
    }

    Tristate Component4514::getValue(std::size_t pin)
    {
        Link link = {nullptr, 0};

        if (pin < 1 || pin > 24)
            throw InvalidPinError("4514", pin);
        link = this->_pins[pin - 1];
        if (link.comp != nullptr)
            return (link.comp->compute(link.pin));
        return (this->_values[pin - 1]);
    }
}