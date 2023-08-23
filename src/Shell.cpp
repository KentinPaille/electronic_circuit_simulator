/*
** EPITECH PROJECT, 2022
** nanoTekSpice
** File description:
** Shell.cpp
*/

#include "../includes/Shell.hpp"

//* Constructors & Destructors
sh::Shell::Shell(std::string configFilePath)
{
    try {
        std::ifstream file(configFilePath);
        if (!file.is_open()) {
            throw ShellException("Error: config file not found");
        }
        std::string line;
        while (std::getline(file, line)) {
            _configFileContent.push_back(line);
        }
        checkConfigFile();
        setupCircuit();
    } catch (ShellException &e) {
        std::cerr << e.what() << std::endl;
        exit(84);
    }
}

sh::Shell::~Shell()
{
}

//* Shell exceptions
sh::Shell::ShellException::ShellException(std::string const &message) throw() : _message(message)
{
}

sh::Shell::ShellException::~ShellException() throw()
{
}

const char *sh::Shell::ShellException::what() const throw()
{
    return _message.c_str();
}

//* Shell functions
void sh::Shell::takeInputs()
{
    while (_active) {
        std::cout << "> ";
        std::string input;
        std::getline(std::cin, input);
        if (std::cin.eof()) {
            // std::cout << std::endl;
            exit(0);
        }
        if (nbOccurences(input, '=') == 1) {
            std::string inputName = input.substr(0, input.find("="));
            std::string value = input.substr(input.find("=") + 1, input.length());
            removeWhiteSpaces(inputName);
            removeWhiteSpaces(value);

            bool validInputName = false;
            for (auto &chip : _chips) {
                if (chip.name == inputName) {
                    validInputName = true;
                    break;
                }
            }

            if (!validInputName) {
                std::cout << "Error: " << inputName << " is not part of the chipset" << std::endl;
                continue;
            } else if (value != "1" && value != "0" && value != "U") {
                std::cerr << "Error: invalid value" << std::endl;
                continue;
            } else {
                input_t input;
                input.name = inputName;
                input.value = getTristateFromStr(value);
                _inputs.push_back(input);
            }
        }
        if (input == "exit")
            _active = false;
        if (input == "display")
            display();
        if (input == "simulate")
            simulate();
        if (input == "loop")
            loop();
    }
}

// TODO: replace getThirdPin by this
char printPin(Tristate pin)
{
    char res;

    if (pin == TRUE) {
        res = '1';
        return res;
    }
    if (pin == FALSE) {
        res = '0';
        return res;
    }
    if (pin == UNDEFINED) {
        res = 'U';
        return res;
    }
    res = 'F';
    return res;
}

void sh::Shell::display()
{
    std::cout << "tick:" << " " << _tick << std::endl;
    std::cout << "input(s):" << std::endl;
    for (auto &chip : _circuit) {
        if (chip->getType() == "InputComponent" || chip->getType() == "ClockComponent")
            std::cout << "  " << chip->getName() << ": " << printPin(chip->getThirdPin(1)) << std::endl;
    }
    std::cout << "output(s):" << std::endl;
    for (auto &chip : _circuit) {
        if (chip->getType() == "OutputComponent")
            std::cout << "  " << chip->getName() << ": " << printPin(chip->getThirdPin(1)) << std::endl;
    }
}

void sh::Shell::simulate()
{
    for (auto &chip : _circuit) {
        if (chip->getType() == "ClockComponent") {
            if (chip->getThirdPin(1) != UNDEFINED)
                chip->setState(chip->compute(1) == TRUE ? FALSE : TRUE);
        }
    }
    if (_inputs.size() > 0) {
        for (auto &input : _inputs) {
            for (auto &chip : _circuit) {
                if (chip->getName() == input.name) {
                    chip->setState(input.value);
                }
            }
        }
    }
    _inputs.clear();
    for (auto &chip : _circuit) {
        if (chip->getType() == "OutputComponent")
            chip->compute(1);
    }
    _tick++;
}

void sh::Shell::loop()
{
    while (true) {
        simulate();
        display();
        // std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

Tristate sh::Shell::getTristateFromStr(std::string value)
{
    if (value == "1")
        return TRUE;
    if (value == "0")
        return FALSE;
    if (value == "U")
        return UNDEFINED;
    return UNDEFINED;
}

void sh::Shell::setupCircuit()
{
    std::map<std::string, std::function<std::shared_ptr<IComponent>(std::string)>> createComp = {
        {"input", [](std::string name) { return std::make_shared<InputComponent>(name); }},
        {"output", [](std::string name) { return std::make_shared<OutputComponent>(name); }},
        {"clock", [](std::string name) { return std::make_shared<ClockComponent>(name); }},
        {"true", [](std::string name) { return std::make_shared<TrueComponent>(name); }},
        {"false", [](std::string name) { return std::make_shared<FalseComponent>(name); }},
        {"and", [](std::string name) { return std::make_shared<AndComponent>(name); }},
        {"or", [](std::string name) { return std::make_shared<OrComponent>(name); }},
        {"xor", [](std::string name) { return std::make_shared<XorComponent>(name); }},
        {"not", [](std::string name) { return std::make_shared<NotComponent>(name); }},
        {"4001", [](std::string name) { return std::make_shared<Gate4001>(name); }},
        {"4011", [](std::string name) { return std::make_shared<Gate4011>(name); }},
        {"4030", [](std::string name) { return std::make_shared<Gate4030>(name); }},
        {"4069", [](std::string name) { return std::make_shared<Gate4069>(name); }},
        {"4071", [](std::string name) { return std::make_shared<Gate4071>(name); }},
        {"4081", [](std::string name) { return std::make_shared<Gate4081>(name); }},
        {"4008", [](std::string name) { return nullptr; }},
        {"4013", [](std::string name) { return nullptr; }},
        {"4017", [](std::string name) { return nullptr; }},
        {"4040", [](std::string name) { return nullptr; }},
        {"4094", [](std::string name) { return nullptr; }},
        {"4512", [](std::string name) { return nullptr; }},
        {"4514", [](std::string name) { return nullptr; }},
        {"4801", [](std::string name) { return nullptr; }},
        {"2716", [](std::string name) { return nullptr; }},
    };

    for (int i = 0; i < _chips.size(); i++) {
        std::shared_ptr<IComponent> component;
        if (component = createComp[_chips[i].type](_chips[i].name)) {
            _circuit.push_back(component);
        } else {
            throw ShellException("Error: component unavailable");
        }
    }

    for (int i = 0; i < _links.size(); i++) {
        for (int j = 0; j < _circuit.size(); j++) {
            if (_circuit[j]->getName() == _links[i].name1) {
                for (int k = 0; k < _circuit.size(); k++) {
                    if (_circuit[k]->getName() == _links[i].name2) {
                        if (_circuit[k]->getType() == "OutputComponent" || _circuit[j]->getType() == "OutputComponent") {
                            _circuit[j]->setLink(_links[i].pin1, *_circuit[k], _links[i].pin2);
                            _circuit[k]->setLink(_links[i].pin2, *_circuit[j], _links[i].pin1);
                        } else {
                            _circuit[k]->setLink(_links[i].pin2, *_circuit[j], _links[i].pin1);
                        }
                    }
                }
            }
        }
    }
}
