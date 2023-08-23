/*
** EPITECH PROJECT, 2022
** nanoTekSpice
** File description:
** Gate4081.cpp
*/

#include "../../includes/IComponent.hpp"

enum Gate4081_LAYOUT {
    INPUT1 = 1,
    INPUT2 = 2,
    OUTPUT1 = 3,
    OUTPUT2 = 4,
    INPUT3 = 5,
    INPUT4 = 6,
    INPUT5 = 8,
    INPUT6 = 9,
    OUTPUT3 = 10,
    OUTPUT4 = 11,
    INPUT7 = 12,
    INPUT8 = 13,
    Gate4081_LAYOUT_MAX = INPUT8
};

Gate4081::Gate4081(std::string name) : AComponent(name, "Gate4081") {
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

Tristate Gate4081::compute(std::size_t pin) {
    if (pin == OUTPUT1)
        return ANDLogic(OUTPUT1, INPUT1, INPUT2);
    if (pin == OUTPUT2)
        return ANDLogic(OUTPUT2, INPUT3, INPUT4);
    if (pin == OUTPUT3)
        return ANDLogic(OUTPUT3, INPUT5, INPUT6);
    if (pin == OUTPUT4)
        return ANDLogic(OUTPUT4, INPUT7, INPUT8);
    if (pin == INPUT1 || pin == INPUT2 || pin == INPUT3 || pin == INPUT4
     || pin == INPUT5 || pin == INPUT6 || pin == INPUT7 || pin == INPUT8)
        return _pins[pin]->getState();
    return UNDEFINED;
}

Tristate Gate4081::ANDLogic(std::size_t output, std::size_t input1, std::size_t input2) {
    _pins[input1]->compute(_pins[input1]->getPin());
    _pins[input2]->compute(_pins[input2]->getPin());
    if (_pins[input1]->getState() == TRUE && _pins[input2]->getState() == TRUE) {
        _pins[output]->setState(TRUE);
        return TRUE;
    } else if (_pins[input1]->getState() == FALSE || _pins[input2]->getState() == FALSE) {
        _pins[output]->setState(FALSE);
        return FALSE;
    } else {
        _pins[output]->setState(UNDEFINED);
        return UNDEFINED;
    }
}

void Gate4081::setLink(std::size_t pin, IComponent &other, std::size_t otherPin) {
    if (pin > Gate4081_LAYOUT_MAX || pin <= 0) {
        std::cerr << "Pin " << pin << " doesn't exist for gate " << _name << std::endl;
        exit(84);
    }
    if (otherPin > other.getPins().size() - 1) {
        std::cerr << "Pin " << otherPin << " doesn't exist for gate " << other.getType() << " with name: " << other.getName() << std::endl;
        exit(84);
    }
    if (pin != OUTPUT1 && pin != OUTPUT2 && pin != OUTPUT3 && pin != OUTPUT4) {
        _pins[pin] = other.getPins()[otherPin];
        _pins[pin]->setGate(&other);
        _pins[pin]->setState(other.compute(otherPin));
        _pins[pin]->setPin(otherPin);
    }
}
