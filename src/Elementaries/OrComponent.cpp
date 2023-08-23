/*
** EPITECH PROJECT, 2022
** bootstrap
** File description:
** OrComponent.cpp
*/

#include "../../includes/IComponent.hpp"

enum OR_LAYOUT {
    INPUT1 = 1,
    INPUT2 = 2,
    OUTPUT = 3,
    Or_LAYOUT_MAX = OUTPUT
};

OrComponent::OrComponent(std::string name) : AComponent(name, "OrComponent") {
    _pins.push_back(nullptr);
    _pins.push_back(new Pin(name, UNDEFINED));
    _pins.push_back(new Pin(name, UNDEFINED));
    _pins.push_back(new Pin(name, UNDEFINED));
}

Tristate OrComponent::compute(std::size_t pin) {
    _pins[INPUT1]->compute(_pins[INPUT1]->getPin());
    _pins[INPUT2]->compute(_pins[INPUT2]->getPin());
    if (pin == OUTPUT) {
        if (_pins[INPUT1]->getState() == FALSE && _pins[INPUT2]->getState() == FALSE) {
            _pins[OUTPUT]->setState(FALSE);
            return FALSE;
        } else if (_pins[INPUT1]->getState() == TRUE || _pins[INPUT2]->getState() == TRUE) {
            _pins[OUTPUT]->setState(TRUE);
            return TRUE;
        } else {
            _pins[OUTPUT]->setState(UNDEFINED);
            return UNDEFINED;
        }
    }
    if (pin == INPUT1 || pin == INPUT2)
        return _pins[pin]->getState();
    return UNDEFINED;
}

void OrComponent::setLink(std::size_t pin, IComponent &other, std::size_t otherPin) {
    if (pin > Or_LAYOUT_MAX || pin <= 0) {
        std::cerr << "Pin " << pin << " doesn't exist for gate " << _name << std::endl;
        exit(84);
    }
    if (otherPin > other.getPins().size() - 1 ) {
        std::cerr << "Pin " << otherPin << " doesn't exist for gate " << other.getType() << " with name: " << other.getName() << std::endl;
        exit(84);
    }
    if (pin == INPUT1) {
        _pins[INPUT1] = other.getPins()[otherPin];
        _pins[INPUT1]->setGate(&other);
        _pins[INPUT1]->setState(other.compute(otherPin));
        _pins[INPUT1]->setPin(otherPin);
    }
    else if (pin == INPUT2) {
        _pins[INPUT2] = other.getPins()[otherPin];
        _pins[INPUT2]->setGate(&other);
        _pins[INPUT2]->setState(other.compute(otherPin));
        _pins[INPUT2]->setPin(otherPin);
    }
}
