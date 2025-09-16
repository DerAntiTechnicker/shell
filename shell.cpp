#include "shell.h"

#include <iostream>

void shell::split_String() {
    std::string buffer;
    for (int i = 0; i < input.size(); i++) {
        if (input[i] != ' ') buffer += input[i];
        else if (input[i] == ' ' && input[i - 1] != ' ' && i > 0) {
            arguments.push_back(buffer);
            buffer.clear();
        }
    }
    arguments.push_back(buffer);     // write the buffer to the vector "argument"
}



void shell::addStdCommands() {
    addCommand("clear", [] { printf("\033[2J\033[3J\033[H"); });    // erase screen, saved lines, set cursor to home pos. (0|0)
    addCommand("help", [this] {
        if (!command.empty()) {
            for (const auto &pair : command) {
                std::cout << pair.first << std::endl;
            }
        }
    });
}




void shell::addCommand(const std::string &name, const std::function<void()> &func) {
    command.insert({name, func});
}



void shell::init() {
    while (true) {
        std::cout << "> ";
        std::getline(std::cin, input);
        split_String();
        if (arguments[0] == "exit") break;
        if (!arguments.empty()) {
            if (command.count(arguments[0]) == 1) command.at(arguments[0])();
            else if (arguments[0].empty()) {}
            else std::cout << "Command \"" << arguments[0] << "\" not found..." << std::endl;
        }
        input.clear();
        arguments.clear();
    }
}



bool shell::arg(const std::string &name) const {
    for (int i = 1; i < arguments.size(); i++) {
        if (arguments[i] == name) return true;
    }
    return false;
}



bool shell::arg_pos(int &pos, const std::string &name) const {
    for (int i = 1; i < arguments.size(); i++) {
        if (arguments.at(i) == name) {
            pos = i;
            return true;
        }
    }
    return false;
}



std::string shell::arg_atPos(const int &pos) {
    std::cout << pos << std::endl;

    if (pos < 0) return arguments.front();
    if (pos >= arguments.size()) return arguments.back();
    return arguments.at(pos);
}



int shell::getArgAnz() const {
    return arguments.size() - 1;
}
