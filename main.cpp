/*
** EPITECH PROJECT, 2022
** nanoTekSpice
** File description:
** main.cpp
*/

#include "./includes/IComponent.hpp"
#include "./includes/Shell.hpp"

int main(int ac, char **av)
{
    if (ac != 2) {
        std::cout << "Usage: ./nts configFile" << std::endl;
       return 84;
    }

    sh::Shell shell(av[1]);
    try {
        shell.takeInputs();
    } catch (sh::Shell::ShellException &e) {
        std::cerr << e.what() << std::endl;
        return 84;
    }

    return 0;
}
