#include "commandsControl.h"
#include "lexer.h"

//
// Created by shaiac on 17/12/2019.
//
CommandsControl::CommandsControl() {
    this->initializeCommandsMap();
}

/**
 * Inserting the strings that the lexer read from the the text into comAsString.
 * @param file_path the file path.
 */
void CommandsControl::ReadLexer(const char *file_path) {
    lexer l;
    l.ReadFile(file_path);
    this->comAsString = l.GetList();
}

void CommandsControl::SetLexer(list<string> full) {
    this->comAsString = full;
}

/**
 * Initializing the commands map, with all the possible commands.
 */
void CommandsControl::initializeCommandsMap() {
    this->commandsMap["openDataServer"] = new OpenServerCommand;
    this->commandsMap["connectControlClient"] = new ConnectCommand;
    this->commandsMap["var"] = new DefineVarCommand;
    this->commandsMap["Print"] = new PrintCommand;
    this->commandsMap["Sleep"] = new SleepCommand;
    this->commandsMap["while"] = new LoopCommand;
    this->commandsMap["if"] = new IfCommand;
}

/**
 * Running on the strings list that we get from the file, if the string is command
 * executing that matching command.
 */
void CommandsControl::Praser() {
    list<string>::iterator iter = this->comAsString.begin();
    bool alive = true;
    int forward;
    Command *command;
    while (alive) {
        string tmp = iter.operator*();
        //If the string is command
        if (this->commandsMap.find(tmp) != this->commandsMap.end()) {
            pair<string, Command *> pair = this->commandsMap.find(tmp).operator*();
            command = pair.second;
            iter++;
            //if not specific command only var name
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
        //execute the command
        command->execute();

    }
}
