/*
** EPITECH PROJECT, 2023
** TekSpice
** File description:
** Pin
*/

#include "../../includes/IComponent.hpp"

Tristate Pin::compute(std::size_t pin)
{
    if (_gate == nullptr || _gate->getType() == "OutputComponent") {
        return _state;
    }
    _state = _gate->compute(_pin);
    return _gate->compute(_pin);
}

void Pin::setGate(IComponent *gate)
{
    _gate = gate;
    return;
}

IComponent *Pin::getGate() const
{
    return _gate;
}

void Pin::setState(Tristate state)
{
    _state = state;
}

Tristate Pin::getState() const
{
    return _state;
}

std::string Pin::getName() const
{
    return _name;
}

void Pin::setPin(std::size_t pin)
{
    _pin = pin;
}

std::size_t Pin::getPin() const
{
    return _pin;
}
