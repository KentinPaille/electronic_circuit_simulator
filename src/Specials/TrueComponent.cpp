/*
** EPITECH PROJECT, 2023
** TekSpice
** File description:
** TrueComponent
*/

#include "../../includes/IComponent.hpp"

enum TRUE_LAYOUT {
    INPUT = 1,
};

TrueComponent::TrueComponent(std::string name): AComponent(name, "TrueComponent")
{
    _pins.push_back(nullptr);
    _pins.push_back(new Pin(name, TRUE));
}

Tristate TrueComponent::compute(std::size_t pin)
{
    return TRUE;
}

void TrueComponent::setLink(std::size_t pin, IComponent &other, std::size_t otherPin)
{
    if (pin == INPUT) {
        _pins[INPUT]->setGate(&other);
        _pins[INPUT]->setState(TRUE);
        _pins[INPUT]->setPin(otherPin);
    }
}

