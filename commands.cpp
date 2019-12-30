#include <netinet/in.h>
#include <zconf.h>
#include <sstream>
#include <map>
#include "commands.h"
#include "symbolTable.h"
#include "sys/socket.h"
#include "ex1.h"
#include <arpa/inet.h>
#include <thread>
#include "commandsControl.h"
#include "singeltonInter.h"

#define PORT 5402

//
// Created by shaiac on 16/12/2019.
//
OpenServerCommand::OpenServerCommand() : Command() {}

ConnectCommand::ConnectCommand() : Command() {}

DefineVarCommand::DefineVarCommand() : Command() {}

ChangeVar::ChangeVar() : Command() {}

PrintCommand::PrintCommand() : Command() {}

SleepCommand::SleepCommand() : Command() {}

ConditionParser::ConditionParser() : Command() {
    this->status = false;
}

IfCommand::IfCommand() : ConditionParser() {}

LoopCommand::LoopCommand() : ConditionParser() {}

Command::Command() {
    this->symbolTable = SymbolTables::getSymbolT();
    this->interpreter = SingeltonInter::GetInterpreter();
}
/**
 * Destructor to the class.
 */
Command::~Command() {
    delete (this->symbolTable);
    delete (this->interpreter);
}

/**
 * All the methods that initializing the commands, saving all the values and things
 * that we need to execute the command.
 * each command has different initialize
 */
int OpenServerCommand::initializeCommand(list<string>::iterator begin) {
    this->commandValues.clear();
    this->commandValues.push_front(begin.operator*());
    return 1;
}

int ConnectCommand::initializeCommand(list<string>::iterator begin) {
    this->commandValues.clear();
    this->commandValues.push_back(begin.operator*());
    begin++;
    this->commandValues.push_back(begin.operator*());
    begin++;
    return 2;
}

int DefineVarCommand::initializeCommand(list<string>::iterator begin) {
    this->commandValues.clear();
    this->commandValues.push_back(begin.operator*());
    begin++;
    int j = 3;
    if ((begin.operator*()) == "=") {
        j = 2;
    }
    for (int i = 0; i < j; i++) {
        this->commandValues.push_back(begin.operator*());
        begin++;
    }
    return 1 + j;
}

int ChangeVar::initializeCommand(list<string>::iterator begin) {
    this->commandValues.clear();
    for (int i = 0; i < 3; i++) {
        this->commandValues.push_back(begin.operator*());
        begin++;
    }
    return 3;

}

int PrintCommand::initializeCommand(list<string>::iterator begin) {
    this->commandValues.clear();
    this->commandValues.push_front(begin.operator*());
    return 1;
}

int SleepCommand::initializeCommand(list<string>::iterator begin) {
    this->commandValues.clear();
    this->commandValues.push_front(begin.operator*());
    return 1;
}

int ConditionParser::initializeCommand(list<string>::iterator begin) {
    this->commandValues.clear();
    this->status = true;
    int count = 0;
    bool lor = true;
    while (begin.operator*() != "{") {
        count++;
        string tmp = begin.operator*();
        if (tmp == ">" || tmp == ">=" || tmp == "<" || tmp == "<=" || tmp == "==" || tmp == "!=") {
            this->condition = tmp;
            lor = false;
            begin++;
            continue;
        }
        if (lor) {
            this->left = tmp;
        } else {
            this->right = tmp;
        }
        begin++;
    }
    begin++;
    count++;
    while (begin.operator*() != "}") {
        this->commandValues.push_back(begin.operator*());
        count++;
        begin++;
    }
    count++;
    return count;
}

/**
 * Adding vars to from the symbol table to the interpeter.
 */
void Command::AddVarsFromSymbol(string exp) {
    int i = 0;
    while (exp[i] != '\000' && exp[i] != '\n') {
        if (isalpha(exp[i])) {
            string var = "";
            while (isalpha(exp[i]) || isdigit(exp[i]) || exp[i] == '_') {
                var += exp[i];
                i++;
            }
            if (this->symbolTable->isInProgramMap(var)) {
                float value = this->symbolTable->getVarValue(var);
                string exp = var + " = " + to_string(value);
                this->interpreter->setVariables(exp);
                continue;
            }
        }
        i++;
    }
}

SymbolTables *Command::getSymTab() {
    return this->symbolTable;
}

/**
 * Checking for the loop and if commands if the condition is tru ot false.
 */
void ConditionParser::CheckCondition() {
    if (isalpha(this->left[0])) {
        this->AddVarsFromSymbol(this->left);
    }
    float left = this->interpreter->interpret(this->left)->calculate();
    if (isalpha(this->right[0])) {
        this->AddVarsFromSymbol(this->right);
    }
    float right = this->interpreter->interpret(this->right)->calculate();
    string cond = this->condition;
    this->status = false;
    if (condition == "==") {
        if (left == right) {
            this->status = true;
        }
    }
    if (condition == "!=") {
        if (left != right) {
            this->status = true;
        }
    }
    if (condition == ">") {
        if (left > right) {
            this->status = true;
        }
    }
    if (condition == ">=") {
        if (left >= right) {
            this->status = true;
        }
    }
    if (condition == "<") {
        if (left < right) {
            this->status = true;
        }
    }
    if (condition == "<=") {
        if (left <= right) {
            this->status = true;
        }
    }
}

/**
 * spliting a string by "," returning a vector.
 */
vector<string> split(string s) {
    vector<string> values;
    string str = "";
    int i;
    for (i = 0; i < s.length(); i++) {
        if (s[i] == ',' || s[i] == '\n') {
            values.push_back(str);
            str = "";
            if (s[i] == '\n') {
                return values;
            }
        } else {
            str += s[i];
        }
    }
    return values;
}

/**
 * After Opening the server we running in another thread this method that reads data
 * from the simulator and updating the values of the right vars.
 * @param client_socket the socket
 */
void OpenServerCommand::loopThread(int client_socket) {
    int valread;
    int i = 0;
    char buffer1[1024] = {0};
    string *array = this->symbolTable->getArray();
    while (!this->symbolTable->isFinish()) {
        valread = read(client_socket, buffer1, 1024);
        vector<string> v = split(buffer1);
        unordered_map<string, var>::iterator it;
        unordered_map<string, var> *symap = this->symbolTable->getSymap();
        while (!v.empty()) {
            it = symap->find(array[i]);
            var check = it->second;
            if (check.condition.compare("get") == 0) {
                if (!isdigit(v.front()[0])) {
                    v.erase(v.begin());
                    i++;
                    continue;
                }
                check.value = stof(v.front());
                this->symbolTable->updateSimulatorVars('g', it, check);
            }
            v.erase(v.begin());
            i++;
        }
        i = 0;
    }
    close(client_socket);
}

/**
 * Opening the server, waiting to a connection from the client (the simulator).
 */
void OpenServerCommand::execute() {
    int client_socket;
    int socketfd = socket(AF_INET, SOCK_STREAM, 0);
    if (socketfd == -1) {
        exit(-1);
    }
    sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    string sp = this->commandValues.front();
    this->commandValues.pop_front();
    int port = this->interpreter->interpret(sp)->calculate();
    address.sin_port = htons(port);
    if (bind(socketfd, (struct sockaddr *) &address, sizeof(address)) < 0) {
        cerr << "Error, couldn't bind the socket to an IP" << endl;
        exit(-2);
    }
    if (listen(socketfd, 5) < 0) {
        cerr << "Error, during the listening command" << endl;
        exit(-3);
    }
    if ((client_socket = accept(socketfd, (struct sockaddr *) &address,
                                (socklen_t *) &address)) < 0) {
        cerr << "Error, during accepting client" << endl;
        exit(-4);
    }
    std::cout << "Server is now connected to Client" << std::endl;
    thread server([this, client_socket] { this->loopThread(client_socket); });
    server.detach();
}

/**
 * Running on the symbol table map if there are vars that we need to set in the simulator
 * sending to the simulator the right message.
 * @param client_socket the socket.
 */
void ConnectCommand::loopThread(int client_socket) {
    unordered_map<string, var>::iterator it;
    unordered_map<string, var> *symbolTables = this->symbolTable->getSymap();
    while (!this->symbolTable->isFinish()) {
        for (it = symbolTables->begin(); it != symbolTables->end(); it++) {
            var check = it->second;
            if (check.condition.compare("set") == 0 && check.readyToSet) {
                var toChange;
                toChange.value = client_socket;
                this->symbolTable->updateSimulatorVars('s', it, toChange);
            }
        }
    }
    close(client_socket);
}

/**
 * Opening a client that connecting to the server (the simulator).
 */
void ConnectCommand::execute() {
    //create socket
    int client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket == -1) {
        //error
        std::cerr << "Could not create a socket" << std::endl;
        exit(-1);
    }
    //We need to create a sockaddr obj to hold address of server
    sockaddr_in address; //in means IP4
    address.sin_family = AF_INET;//IP4
    string addrfromC = this->commandValues.front();
    this->commandValues.pop_front();
    addrfromC = addrfromC.substr(1, addrfromC.length() - 2);
    const char *aDr = (const char *) &addrfromC[0];
    address.sin_addr.s_addr = inet_addr(aDr);  //the localhost address
    string sp = this->commandValues.front();
    this->commandValues.pop_front();
    int port = this->interpreter->interpret(sp)->calculate();
    address.sin_port = htons(port);
    while (!this->symbolTable->isFinish()) {
        int is_connect = connect(client_socket, (struct sockaddr *) &address, sizeof(address));
        if (is_connect == -1) {
            continue;
        } else {
            std::cout << "Client is now connected to server" << std::endl;
            break;
        }
    }
    thread client([this, client_socket] { this->loopThread(client_socket); });
    client.detach();
}
/**
 * When we get an command that starting with var we need to define the var
 * according to the data (set or get var, the sim).
 */
void DefineVarCommand::execute() {
    string sim;
    string name = this->commandValues.front();
    this->commandValues.pop_front();
    if (this->commandValues.front().compare("<-") == 0) {
        commandValues.pop_front();
        commandValues.pop_front();
        sim = this->commandValues.front();
        sim = sim.substr(1, sim.length() - 2);
        this->symbolTable->setCondition(name, sim, "get");
        this->symbolTable->addProgramvar(name, sim);
    } else if (this->commandValues.front().compare("->") == 0) {
        commandValues.pop_front();
        commandValues.pop_front();
        sim = this->commandValues.front();
        sim = sim.substr(1, sim.length() - 2);
        this->symbolTable->setCondition(name, sim, "set");
        this->symbolTable->addProgramvar(name, sim);
    } else if (this->commandValues.front().compare("=") == 0) {
        commandValues.pop_front();
        string valueAsString = this->commandValues.front();
        if (this->symbolTable->isExsistInSymap(valueAsString)) {
            float value = this->symbolTable->getVarValue(valueAsString);
            this->interpreter->setVariables(name + "=" + to_string(value));
        } else {
            this->interpreter->setVariables(name + "=" + valueAsString);
        }
    }
    this->commandValues.pop_front();
}

/**
 * Command that changes a existing var value according to the data that given.
 */
void ChangeVar::execute() {
    string varToChanged = this->commandValues.front();
    this->commandValues.pop_front();
    this->commandValues.pop_front();
    string exp = this->commandValues.front();
    this->AddVarsFromSymbol(exp);
    float value = this->interpreter->interpret(exp)->calculate();
    this->symbolTable->setValueInSimulator(varToChanged, value);
    this->symbolTable->turnOnSetVar(varToChanged);
}

/**
 * Printing the data that given us to print.
 */
void PrintCommand::execute() {
    string top = this->commandValues.front();
    if (top[0] == '"') {
        top = top.substr(1, top.length() - 2);
        cout << top << endl;
        //if need to print done, tell the program that we done and exit.
        if (top == "done") {
            this->symbolTable->done();
            sleep(5);
            exit(0);
        }
    } else {
        if (this->symbolTable->isInProgramMap(top)) {
            float f = this->symbolTable->getVarValue(top);
            cout << f << endl;
        } else {
            cout << this->interpreter->interpret(top)->calculate() << endl;
        }
    }
}

/**
 * Command that make the thread that call it to sleep.
 */
void SleepCommand::execute() {
    string sp = this->commandValues.front();
    int num = this->interpreter->interpret(sp)->calculate();
    sleep(num / 1000);
}

/**
 * If command, checking if the condition is true or false.
 */
void IfCommand::execute() {
    this->CheckCondition();
    if (this->status) {
        CommandsControl *coco = new CommandsControl();
        coco->SetLexer(this->commandValues);
        coco->Praser();
    }
}

/**
 * Running a loop until the condition is false.
 */
void LoopCommand::execute() {
    this->CheckCondition();
    CommandsControl *coco = new CommandsControl();
    coco->SetLexer(this->commandValues);
    while (this->status) {
        coco->Praser();
        this->CheckCondition();
    }
}
