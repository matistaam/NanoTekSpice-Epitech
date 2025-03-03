/*
** EPITECH PROJECT, 2025
** B-OOP-400-LYN-4-1-tekspice-matis.taam
** File description:
** Component4094
*/

#include "Component4094.hpp"
#include "NtsException.hpp"

namespace nts {
    Component4094::Component4094()
        : _pins(16, {nullptr, 0}),
          _values(16, Tristate::UNDEFINED),
          _shift(8, Tristate::UNDEFINED),
          _latch(8, Tristate::UNDEFINED),
          _out_qe(Tristate::UNDEFINED),
          _prevClock(Tristate::UNDEFINED),
          _prevStrobe(Tristate::UNDEFINED)
    {
    }

    void Component4094::simulate(std::size_t)
    {
        // Retrieve input values.
        Tristate clockVal   = getValue(3);
        Tristate strobeVal  = getValue(1);
        Tristate dataVal    = getValue(2);

        // On positive clock edge: shift the register.
        if (_prevClock != Tristate::TRUE && clockVal == Tristate::TRUE) {
            for (int i = 7; i > 0; --i) {
                _shift[i] = _shift[i - 1];
            }
            _shift[0] = dataVal;
        }

        // On negative clock edge: update the secondary output (out_qe).
        if (_prevClock == Tristate::TRUE && clockVal == Tristate::FALSE) {
            _out_qe = _shift[7];
        }

        // On negative strobe edge: latch the shift register contents.
        if (_prevStrobe == Tristate::TRUE && strobeVal == Tristate::FALSE) {
            for (size_t i = 0; i < 8; ++i) {
                _latch[i] = _shift[i];
            }
        }

        // Update previous state variables.
        _prevClock = clockVal;
        _prevStrobe = strobeVal;
    }

    Tristate Component4094::compute(std::size_t pin)
    {
        if (pin < 1 || pin > 16)
            throw InvalidPinError("4094", pin);

        // For input pins, delegate to linked components.
        switch (pin) {
            case 1:  return getValue(1);  // strobe input
            case 2:  return getValue(2);  // data input
            case 3:  return getValue(3);  // clock input
            case 15: return getValue(15); // enable input
            default:
                break;
        }
        // For power pins, return UNDEFINED.
        if (pin == 8 || pin == 16)
            return Tristate::UNDEFINED;

        // Check enable; if not enabled, outputs are undefined.
        Tristate enableVal = getValue(15);
        if (enableVal != Tristate::TRUE)
            return Tristate::UNDEFINED;

        switch (pin) {
            case 4:  return _latch[0];
            case 5:  return _latch[1];
            case 6:  return _latch[2];
            case 7:  return _latch[3];
            case 9:  return _shift[7];   // QS output (direct from shift register)
            case 10: return _out_qe;      // Secondary output
            case 11: return _latch[7];
            case 12: return _latch[6];
            case 13: return _latch[5];
            case 14: return _latch[4];
            default:
                return Tristate::UNDEFINED;
        }
    }

    void Component4094::setLink(std::size_t pin, IComponent &other, std::size_t otherPin)
    {
        if (pin < 1 || pin > 16)
            throw InvalidPinError("4094", pin);
        _pins[pin - 1] = { &other, otherPin };
    }

    Tristate Component4094::getValue(std::size_t pin)
    {
        Link link = _pins[pin - 1];
        if (link.comp != nullptr)
            return link.comp->compute(link.pin);
        return _values[pin - 1];
    }
}