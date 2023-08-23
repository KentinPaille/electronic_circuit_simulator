/*
** EPITECH PROJECT, 2023
** TekSpice
** File description:
** Not
*/

#include "../../includes/IComponent.hpp"

enum NOT_LAYOUT {
    INPUT = 1,
    OUTPUT = 2,
    NOT_LAYOUT_MAX = OUTPUT
};

NotComponent::NotComponent(std::string name) : AComponent(name, "NotComponent")
{
    _pins.push_back(nullptr);
    _pins.push_back(new Pin(name, UNDEFINED));
    _pins.push_back(new Pin(name, UNDEFINED));
}

Tristate NotComponent::compute(std::size_t pin)
{
    _pins[INPUT]->compute(_pins[INPUT]->getPin());
    if (_pins[INPUT]->getState() == FALSE) {
        _pins[OUTPUT]->setState(TRUE);
        return TRUE;
    } else if (_pins[INPUT]->getState() == TRUE) {
        _pins[OUTPUT]->setState(FALSE);
        return FALSE;
    } else if (pin == INPUT)
        return _pins[pin]->getState();
    else {
        _pins[OUTPUT]->setState(UNDEFINED);
        return UNDEFINED;
    }
}

void NotComponent::setLink(std::size_t pin, IComponent &other, std::size_t otherPin)
{
    if (pin > OUTPUT || pin <= 0) {
        std::cerr << "Pin " << pin << " doesn't exist for gate " << _name << std::endl;
        exit(84);
    }
    if (otherPin > other.getPins().size() - 1) {
        std::cerr << "Pin " << otherPin << " doesn't exist for gate " << other.getType() << " with name: " << other.getName() << std::endl;
        exit(84);
    }
    if (pin == INPUT) {
        _pins[INPUT] = other.getPins()[otherPin];
        _pins[INPUT]->setGate(&other);
        _pins[INPUT]->setState(other.compute(otherPin));
        _pins[INPUT]->setPin(otherPin);
    }
}