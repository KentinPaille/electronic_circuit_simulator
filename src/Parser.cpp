/*
** EPITECH PROJECT, 2022
** nanoTekSpice
** File description:
** Parser.cpp
*/

#include "../includes/Shell.hpp"

void sh::Shell::checkConfigFile()
{
    bool chipset = false;
    bool links = false;
    for (auto &line : _configFileContent) {
        if (line.find(".chipsets:") != std::string::npos) {
            chipset = true;
            getChipsets();
            continue;
        }
        if (line.find(".links:") != std::string::npos) {
            links = true;
            getLinks();
            continue;
        }
    }
    if (!chipset || !links) {
        throw ShellException("Error: invalid config file");
    }
}

std::vector<std::string> chipTypes = {
    "input",
    "output",
    "clock",
    "true",
    "false",
    "and",
    "or",
    "xor",
    "not",
    "4001",
    "4011",
    "4030",
    "4069",
    "4071",
    "4081",
    "4008",
    "4013",
    "4017",
    "4040",
    "4094",
    "4512",
    "4514",
    "4801",
    "2716"
};

void sh::Shell::getChipsets()
{
    for (auto &line : _configFileContent) {
        if (line.find("#") != std::string::npos)
            line = line.substr(0, line.find("#"));
        if (line.empty())
            continue;
        if (line.find(".links:") != std::string::npos)
            break;
        if (line.find(".chipsets:") == std::string::npos) {
            std::istringstream iss(line);
            std::string type, name, err;
            iss >> type >> name >> err;

            if (type.empty() || name.empty())
                throw ShellException("Error: you must provide a type and a name for every chip");

            if (!err.empty())
                throw ShellException("Error: too many arguments for " + type + " " + name);

            bool found = false;
            for (auto &chipType : chipTypes) {
                if (type == chipType) {
                    found = true;
                    break;
                }
            }
            if (!found)
                throw ShellException("Error: " + type + " is not a valid chipset type");

            for (auto &chip : _chips) {
                if (name == chip.name)
                    throw ShellException("Error: " + name + " is already used");
            }

            chip_t chip;
            chip.type = type;
            chip.name = name;
            _chips.push_back(chip);
        }
    }

    //! Delete
    // std::cout << "CHIPSETS:" << std::endl;
    // for (auto &chip : _chips) {
    //     std::cout << "--> " << chip.type << " " << chip.name << std::endl;
    // }
}

void sh::Shell::getLinks()
{
    bool checkLinks = false;
    for (auto &line : _configFileContent) {
        if (line.find("#") != std::string::npos)
            line = line.substr(0, line.find("#"));
        if (line.empty())
            continue;
        if (line.find(".links:") != std::string::npos) {
            checkLinks = true;
            continue;
        }
        if (checkLinks) {
            std::istringstream iss(line);
            std::string link1, link2, err;
            iss >> link1 >> link2 >> err;

            if (link1.empty() || link2.empty())
                throw ShellException("Error: you must provide two links");

            if (!err.empty())
                throw ShellException("Error: too many arguments for " + link1 + " " + link2);

            size_t pos1 = link1.find(":");
            size_t pos2 = link2.find(":");
            if (pos1 == std::string::npos || pos2 == std::string::npos)
                throw ShellException("Error: invalid link");

            size_t err1 = link1.find(":", pos1 + 1);
            size_t err2 = link2.find(":", pos2 + 1);
            if (err1 != std::string::npos || err2 != std::string::npos)
                throw ShellException("Error: too many elements in link");

            links_t link;
            link.name1 = link1.substr(0, pos1);
            link.name2 = link2.substr(0, pos2);

            try {
                link.pin1 = std::stoi(link1.substr(pos1 + 1, link1.size()).c_str());
                link.pin2 = std::stoi(link2.substr(pos2 + 1, link2.size()).c_str());
            } catch (std::exception &e) {
                throw ShellException("Error: provided pin is not an integer");
            }

            _links.push_back(link);
        }
    }

    //! Delete
    // std::cout << "LINKS:" << std::endl;
    // for (auto &link : _links) {
    //     std::cout << "--> " << link.name1 << "-" << link.pin1 << " " << link.name2 << "-" << link.pin2 << std::endl;
    // }
    // std::cout << std::endl;
}
