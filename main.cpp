#include <iostream>

#include "shell.h"

int main() {
    shell test;
    test.addStdCommands();
    test.addCommand("bool", [&test]() {
        if (test.getArgAnz() == 1) {
            if (test.arg("0")) std::cout << "false" << std::endl;
            else if (test.arg("1")) std::cout << "true" << std::endl;
            else std::cout << "invalid input - type \"0\" or \"1\"" << std::endl;
        }
        else std::cout << "must have ONE argument..." << std::endl;
    });
    test.init();
    return 0;
}
