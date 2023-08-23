/*
** EPITECH PROJECT, 2022
** bootstrap
** File description:
** AndComponent.cpp
*/

#include "../../includes/IComponent.hpp"

enum AND_LAYOUT {
    INPUT1 = 1,
    INPUT2 = 2,
    OUTPUT = 3,
    AND_LAYOUT_MAX = OUTPUT
};

AndComponent::AndComponent(std::string name) : AComponent(name, "AndComponent") {
    _pins.push_back(nullptr);
    _pins.push_back(new Pin(name, UNDEFINED));
    _pins.push_back(new Pin(name, UNDEFINED));
    _pins.push_back(new Pin(name, UNDEFINED));
}

Tristate AndComponent::compute(std::size_t pin) {
    _pins[INPUT1]->compute(_pins[INPUT1]->getPin());
    _pins[INPUT2]->compute(_pins[INPUT2]->getPin());
    if (pin == OUTPUT) {
        if (_pins[INPUT1]->getState() == TRUE && _pins[INPUT2]->getState() == TRUE) {
            _pins[OUTPUT]->setState(TRUE);
            return TRUE;
        } else if (_pins[INPUT1]->getState() == FALSE || _pins[INPUT2]->getState() == FALSE) {
            _pins[OUTPUT]->setState(FALSE);
            return FALSE;
        } else {
            _pins[OUTPUT]->setState(UNDEFINED);
            return UNDEFINED;
        }
    }
    if (pin == INPUT1 || pin == INPUT2)
        return _pins[pin]->getState();
    return UNDEFINED;
}

void AndComponent::setLink(std::size_t pin, IComponent &other, std::size_t otherPin) {
    if (pin > AND_LAYOUT_MAX || pin <= 0) {
        std::cerr << "Pin " << pin << " doesn't exist for gate " << _name << std::endl;
        exit(84);
    }
    if (otherPin > other.getPins().size() - 1) {
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
