/*
** EPITECH PROJECT, 2023
** TekSpice
** File description:
** Gate4069
*/

#include "../../includes/IComponent.hpp"

enum Gate4069_LAYOUT {
    INPUT1 = 1,
    OUTPUT1 = 2,
    INPUT2 = 3,
    OUTPUT2 = 4,
    INPUT3 = 5,
    OUTPUT3 = 6,
    OUTPUT4 = 8,
    INPUT4 = 9,
    OUTPUT5 = 10,
    INPUT5 = 11,
    OUTPUT6 = 12,
    INPUT6 = 13,
    Gate4069_LAYOUT_MAX = INPUT6
};

Gate4069::Gate4069(std::string name) : AComponent(name, "Gate4069")
{
    _pins.push_back(nullptr);
    _pins.push_back(new Pin(name, UNDEFINED));
    _pins.push_back(new Pin(name, UNDEFINED));
    _pins.push_back(new Pin(name, UNDEFINED));
    _pins.push_back(new Pin(name, UNDEFINED));
    _pins.push_back(new Pin(name, UNDEFINED));
    _pins.push_back(new Pin(name, UNDEFINED));
    _pins.push_back(nullptr);
    _pins.push_back(new Pin(name, UNDEFINED));
    _pins.push_back(new Pin(name, UNDEFINED));
    _pins.push_back(new Pin(name, UNDEFINED));
    _pins.push_back(new Pin(name, UNDEFINED));
    _pins.push_back(new Pin(name, UNDEFINED));
    _pins.push_back(new Pin(name, UNDEFINED));
    _pins.push_back(nullptr);
}

Tristate Gate4069::compute(std::size_t pin)
{
    if (pin == OUTPUT1)
        return NOTLogic(OUTPUT1, INPUT1);
    if (pin == OUTPUT2)
        return NOTLogic(OUTPUT2, INPUT2);
    if (pin == OUTPUT3)
        return NOTLogic(OUTPUT3, INPUT3);
    if (pin == OUTPUT4)
        return NOTLogic(OUTPUT4, INPUT4);
    if (pin == OUTPUT5)
        return NOTLogic(OUTPUT5, INPUT5);
    if (pin == OUTPUT6)
        return NOTLogic(OUTPUT6, INPUT6);
    if (pin == INPUT1 || pin == INPUT2 || pin == INPUT3 || pin == INPUT4
        || pin == INPUT5 || pin == INPUT6)
        return _pins[pin]->getState();
    return UNDEFINED;
}

Tristate Gate4069::NOTLogic(std::size_t output, std::size_t input)
{
    _pins[input]->compute(_pins[input]->getPin());
    if (_pins[input]->getState() == FALSE) {
        _pins[output]->setState(TRUE);
        return TRUE;
    } else if (_pins[input]->getState() == TRUE) {
        _pins[output]->setState(FALSE);
        return FALSE;
    } else {
        _pins[output]->setState(UNDEFINED);
        return UNDEFINED;
    }
}

void Gate4069::setLink(std::size_t pin, IComponent &other, std::size_t otherPin)
{
    if (pin > Gate4069_LAYOUT_MAX || pin <= 0) {
        std::cerr << "Pin " << pin << " doesn't exist for gate " << _name << std::endl;
        exit(84);
    }
    if (otherPin > other.getPins().size() - 1) {
        std::cerr << "Pin " << otherPin << " doesn't exist for gate " << other.getType() << " with name: " << other.getName() << std::endl;
        exit(84);
    }
    if (pin != OUTPUT1 && pin != OUTPUT2 && pin != OUTPUT3 && pin != OUTPUT4 && pin != OUTPUT5 && pin != OUTPUT6) {
        _pins[pin] = other.getPins()[otherPin];
        _pins[pin]->setGate(&other);
        _pins[pin]->setState(other.compute(otherPin));
        _pins[pin]->setPin(otherPin);
    }
}
