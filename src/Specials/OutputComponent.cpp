/*
** EPITECH PROJECT, 2023
** TekSpice
** File description:
** Output
*/

#include "../../includes/IComponent.hpp"

enum OUTPUT_LAYOUT {
    OUTPUT = 1,
};

OutputComponent::OutputComponent(std::string name): AComponent(name, "OutputComponent")
{
    _pins.push_back(nullptr);
    _pins.push_back(new Pin(name, UNDEFINED));
}

OutputComponent::~OutputComponent()
{
}

Tristate OutputComponent::compute(std::size_t pin)
{
    return _pins[OUTPUT]->compute(_pins[OUTPUT]->getPin());
}

void OutputComponent::setLink(std::size_t pin, IComponent &other, std::size_t otherPin)
{
    if (pin == OUTPUT) {
        _pins[OUTPUT]->setGate(&other);
        _pins[OUTPUT]->setState(other.compute(otherPin));
        _pins[OUTPUT]->setPin(otherPin);
    }
}

