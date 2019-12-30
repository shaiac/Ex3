//
// Created by shaiac on 16/12/2019.
//

#ifndef EX3_COMMANDS_H
#define EX3_COMMANDS_H
using namespace std;

#include "iostream"
#include "symbolTable.h"
#include <vector>
#include <list>
#include "ex1.h"
#include <mutex>

class Command {
protected:
    SymbolTables *symbolTable;
    list <string> commandValues;
    Interpreter *interpreter;
public:
    Command();

    SymbolTables *getSymTab();

    void AddVarsFromSymbol(string exp);

    void AddVarsFromValue(string varName, float value);


    virtual void execute() = 0;

    virtual int initializeCommand(list<string>::iterator begin) = 0;

    ~Command();
};

class OpenServerCommand : public Command {
protected:
public:
    void execute();

    OpenServerCommand();

    int initializeCommand(list<string>::iterator begin);

    void loopThread(int);

};

class ConnectCommand : public Command {
protected:
public:
    void execute();

    ConnectCommand();

    int initializeCommand(list<string>::iterator begin);

    void loopThread(int);

};

class DefineVarCommand : public Command {
public:
    DefineVarCommand();

    void execute();

    int initializeCommand(list<string>::iterator begin);

};

class ChangeVar : public Command {
public:
    ChangeVar();

    void execute();

    int initializeCommand(list<string>::iterator begin);

};

class PrintCommand : public Command {
public:
    void execute();

    PrintCommand();

    int initializeCommand(list<string>::iterator begin);

};

class SleepCommand : public Command {
public:
    void execute();

    SleepCommand();

    int initializeCommand(list<string>::iterator begin);

};

class ConditionParser : public Command {
protected:
    bool status;
    string left;
    string right;
    string condition;

public:
    ConditionParser();

    virtual void execute() = 0;

    void CheckCondition();

    int initializeCommand(list<string>::iterator begin);

};

class IfCommand : public ConditionParser {
protected:

public:
    IfCommand();

    void execute();

};

class LoopCommand : public ConditionParser {
protected:

public:
    LoopCommand();

    void execute();

};

#endif //EX3_COMMANDS_H
