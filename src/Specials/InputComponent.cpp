/*
** EPITECH PROJECT, 2023
** TekSpice
** File description:
** Input
*/

#include "../../includes/IComponent.hpp"

enum INPUT_LAYOUT {
    INPUT1 = 1,
};

InputComponent::InputComponent(std::string name): AComponent(name, "InputComponent")
{
    _pins.push_back(nullptr);
    _pins.push_back(new Pin(name, UNDEFINED));
}

InputComponent::~InputComponent()
{
}

Tristate InputComponent::compute(std::size_t pin)
{
    return _pins[1]->getState();
}

void InputComponent::setLink(std::size_t pin, IComponent &other, std::size_t otherPin)
{
    if (pin == INPUT1) {
        _pins[INPUT1]->setGate(&other);
        _pins[INPUT1]->setState(other.compute(otherPin));
        _pins[INPUT1]->setPin(otherPin);
    }
}