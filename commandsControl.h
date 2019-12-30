//
// Created by shaiac on 17/12/2019.
//

#ifndef EX3_COMMANDSCONTROL_H
#define EX3_COMMANDSCONTROL_H

#include "commands.h"

class CommandsControl {
protected:
    list<string> comAsString;
    unordered_map<string, Command *> commandsMap;
public:
    CommandsControl();

    void ReadLexer(const char *file_path);

    void SetLexer(list<string> full);

    void Praser();

    void initializeCommandsMap();

    void runCommands();
};

#endif //EX3_COMMANDSCONTROL_H
