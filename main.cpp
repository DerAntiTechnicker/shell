#include <iostream>

#include "shell.h"

int main() {
    shell test;
    test.addStdCommands();
    test.addCommand("bool", [&test]() {
        if (test.getArgAnz() > 1 || test.getArgAnz() < 1) std::cout << "Must have ONE argument..." << std::endl;
        else {
            if (test.arg_atPos(1) == "1") std::cout << "true" << std::endl;
            else if (test.arg_atPos(1) == "0") std::cout << "false" << std::endl;
            else std::cout << "\"" << test.arg_atPos(1) << "\" not found..." << std::endl;
        }
    });
    test.init();
    return 0;
}