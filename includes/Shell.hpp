/*
** EPITECH PROJECT, 2022
** nanoTekSpice
** File description:
** Shell.hpp
*/

#pragma once

#include "IComponent.hpp"
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <tuple>
#include <map>
#include <functional>
#include <memory>
#include <thread>
#include <chrono>

namespace sh {
    class Shell {
        public:
            Shell(std::string configFilePath);
            ~Shell();

            void checkConfigFile();
            void getChipsets();
            void getLinks();

            Tristate getTristateFromStr(std::string str);

            void setupCircuit();

            typedef struct input_s {
                std::string name;
                Tristate value;
            } input_t;
            void takeInputs();

            void display();
            void simulate();
            void loop();

            class ShellException : public std::exception {
                public:
                    ShellException(std::string const &message) throw();
                    ~ShellException() throw();
                    const char *what() const throw();
                private:
                    std::string _message;
            };
        private:
            std::vector<std::string> _configFileContent;

            typedef struct chip_s {
                std::string type;
                std::string name;
            } chip_t;
            std::vector<chip_t> _chips;

            typedef struct links_s {
                std::string name1;
                int pin1;
                std::string name2;
                int pin2;
            } links_t;
            std::vector<links_t> _links;

            std::vector<std::shared_ptr<IComponent>> _circuit;

            bool _active = true;

            size_t _tick = 0;

            std::vector<input_t> _inputs;
    };
};

int nbOccurences(std::string str, char c);
void removeWhiteSpaces(std::string &str);
