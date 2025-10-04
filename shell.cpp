#include "shell.h"
#include <iostream>
#include <limits>

int convstring(const std::string &text) {
    const char *test = text.c_str();
    for (int i = 0; i < text.size(); i++) if (test[i] < 48 || test[i] > 57) return 0;
    return std::stoi(test);
}

/****************************************/

void shell::split_String() {
    std::string buffer;
    for (int i = 0; i < input.size(); i++) {
        if (input.at(i) != ' ') {
            while (i < input.size() && input.at(i) != ' ') {
                buffer += input.at(i);
                i++;
            }
            arguments.push_back(buffer);
            buffer.clear();
        }
    }
}
/****************************************/
void shell::addStdCommands() {
    addCommand("exit", [this] { loop = false; });
    addCommand("clear", [] { printf("\033[2J\033[3J\033[H"); });    // erase screen, saved lines, set cursor to home pos. (0|0)
    addCommand("help", [this] {
        if (!command.empty()) {
            for (const auto &pair : command) {
                std::cout << pair.first << std::endl;
            }
        }
        else std::cout << "No commands to Display..." << std::endl;
    });
}
/****************************************/
void shell::addCommand(const std::string &name, const std::function<void()> &func) {
    command.insert({name, func});
}
/****************************************/
void shell::init() {
    auto input_buffer = std::cin.rdbuf();       // pointer "test" to input stream
    if (input_buffer->sputbackc('\n') == EOF) std::cout << "ERROR" << std::endl;      // push '\n' to input stream in case it is empty, to not let the cin.ignore wait until something is in the input stream in case it is empty
    std::cin.ignore(std::numeric_limits<std::streamsize>::max() ,'\n');      // incase something is left inside the input - buffer from a previous input
    std::cout.flush();
    while (loop) {
        std::cout << "> ";
        std::getline(std::cin, input);
        split_String();
        if (!arguments.empty()) {
            if (command.count(arguments[0]) == 1) command.at(arguments[0])();
            else if (arguments[0].empty()) {}
            else std::cout << "Command \"" << arguments[0] << "\" not found..." << std::endl;
        }
        input.clear();
        arguments.clear();
    }
}
/****************************************/
bool shell::arg(const std::string &name) const {
    for (int i = 1; i < arguments.size(); i++) {
        if (arguments[i] == name) return true;
    }
    return false;
}
/****************************************/
bool shell::arg_pos(int &pos, const std::string &name) const {
    for (int i = 1; i < arguments.size(); i++) {
        if (arguments.at(i) == name) {
            pos = i;
            return true;
        }
    }
    return false;
}
/****************************************/
std::string shell::arg_atPos(const int &pos) {
    if (pos < 0) return arguments.front();
    if (pos >= arguments.size()) return arguments.back();
    return arguments.at(pos);
}

unsigned long long shell::getArgAnz() const {
    return arguments.size() - 1;
}