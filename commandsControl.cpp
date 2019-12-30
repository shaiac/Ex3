#include "commandsControl.h"
#include "lexer.h"

//
// Created by shaiac on 17/12/2019.
//
CommandsControl::CommandsControl() {
    this->initializeCommandsMap();
}

void CommandsControl::ReadLexer(const char *file_path) {
    lexer l;
    l.ReadFile(file_path);
    this->comAsString = l.GetList();
}

void CommandsControl::SetLexer(list<string> full) {
    this->comAsString = full;
}

void CommandsControl::initializeCommandsMap() {
    this->commandsMap["openDataServer"] = new OpenServerCommand;
    this->commandsMap["connectControlClient"] = new ConnectCommand;
    this->commandsMap["var"] = new DefineVarCommand;
    this->commandsMap["Print"] = new PrintCommand;
    this->commandsMap["Sleep"] = new SleepCommand;
    this->commandsMap["while"] = new LoopCommand;
    this->commandsMap["if"] = new IfCommand;
}

void CommandsControl::Praser() {
    list<string>::iterator iter = this->comAsString.begin();
    bool alive = true;
    int forward;
    Command *command;
    while (alive) {
        string tmp = iter.operator*();
        if (this->commandsMap.find(tmp) != this->commandsMap.end()) {
            pair<string, Command *> pair = this->commandsMap.find(tmp).operator*();
            command = pair.second;
            iter++;
        } else {
            command = new ChangeVar();
        }
        forward = command->initializeCommand(iter);
        for (int i = 0; i < forward; i++) {
            iter++;
            if (iter == this->comAsString.end()) {
                alive = false;
                break;
            }
        }
        command->execute();

    }
}
