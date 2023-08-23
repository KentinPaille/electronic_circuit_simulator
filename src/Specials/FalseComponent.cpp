/*
** EPITECH PROJECT, 2023
** TekSpice
** File description:
** FalseComponent
*/

#include "../../includes/IComponent.hpp"

enum FALSE_LAYOUT {
    INPUT = 1,
};

FalseComponent::FalseComponent(std::string name): AComponent(name, "FalseComponent")
{
    _pins.push_back(nullptr);
    _pins.push_back(new Pin(name, FALSE));
}

Tristate FalseComponent::compute(std::size_t pin)
{
    return FALSE;
}

void FalseComponent::setLink(std::size_t pin, IComponent &other, std::size_t otherPin)
{
    if (pin == INPUT) {
        _pins[INPUT]->setGate(&other);
        _pins[INPUT]->setState(FALSE);
        _pins[INPUT]->setPin(otherPin);
    }
}
