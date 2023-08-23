/*
** EPITECH PROJECT, 2023
** TekSpice
** File description:
** Clock
*/

#include "../../includes/IComponent.hpp"

enum CLOCK_LAYOUT {
    INPUT = 1,
};

ClockComponent::ClockComponent(std::string name): AComponent(name, "ClockComponent")
{
    _pins.push_back(nullptr);
    _pins.push_back(new Pin(name, UNDEFINED));
}

Tristate ClockComponent::compute(std::size_t pin)
{
    return _pins[1]->getState();
}

void ClockComponent::setLink(std::size_t pin, IComponent &other, std::size_t otherPin)
{
    if (pin == INPUT) {
        _pins[INPUT]->setGate(&other);
        _pins[INPUT]->setState(other.compute(otherPin));
        _pins[INPUT]->setPin(otherPin);
    }
}