#ifndef CLI_H
#define CLI_H

#include <string>
#include <vector>
#include <map>
#include <functional>

class shell {
    std::map<std::string, std::function<void()>> command;
    std::string input;
    std::vector<std::string> arguments;


    void split_String();

public:
    shell() = default;

    void addStdCommands();
    void addCommand(const std::string &name, const std::function<void()> &func);
    bool arg(const std::string &name) const;
    bool arg_pos(int &pos, const std::string &name) const;
    std::string arg_atPos(const int &pos);
    int getArgAnz() const;

    void init();
};

#endif //CLI_H
