#include <iostream>
#include <string>

int nbOccurences(std::string str, char c)
{
    int count = 0;
    for (int i = 0; i < str.length(); i++)
        if (str[i] == c)
            count++;
    return count;
}

void removeWhiteSpaces(std::string &str)
{
    int count = 0;
    for (int i = 0; i < str.length(); i++) {
        if (str[i] != ' ') {
            str[count++] = str[i];
        }
    }
    str.erase(count, str.length());
}
