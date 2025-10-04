#ifndef CLI_H
#define CLI_H

#include <string>
#include <vector>
#include <map>
#include <functional>

int convstring(const std::string &text);

class shell {
    std::map<std::string, std::function<void()>> command;
    std::string input;
    std::vector<std::string> arguments;
    bool loop;      // set false to stop CLI

    void split_String();

public:
    shell() {
        loop = true;
    };

    void addStdCommands();
    void addCommand(const std::string &name, const std::function<void()> &func);
    bool arg(const std::string &name) const;
    bool arg_pos(int &pos, const std::string &name) const;
    std::string arg_atPos(const int &pos);
    unsigned long long getArgAnz() const;

    void init();
};

#endif //CLI_H