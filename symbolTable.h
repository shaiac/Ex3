//
// Created by shaiac on 17/12/2019.
//

#ifndef EX3_SYMBOLTABLE_H
#define EX3_SYMBOLTABLE_H

#include <string>
#include <unordered_map>
#include <mutex>

using namespace std;
struct var {
    float value;
    string sim;
    string condition;
    bool readyToSet;
};

class SymbolTables {
private:
    unordered_map<string, var> simulatorVars; // vars with thier name in the simulator table
    unordered_map<string, string> programVars; // matching vars in the program to vars in the simulator
    string varsArray[36]; // the order of the list is the order of the string the simulator send to us
    mutex mutex_string_var;
    bool finish;

    SymbolTables();

    static SymbolTables *singelton;
public:

    static SymbolTables *getSymbolT();

    void initializeSimulator();

    float getVarValue(string name);

    void setCondition(string, string, string);

    void updateSimulatorVars(char setOget, unordered_map<string, var>::iterator it, var variable);

    void setValueInSimulator(string name, float newVal);

    void turnOnSetVar(string name);

    unordered_map<string, var>* getSymap();

    void done();

    bool isFinish();

    void addProgramvar(string,string);

    void initializeArray();

    string* getArray();

    bool isInProgramMap(string name);

    bool isExsistInSymap(string name);

};

#endif //EX3_SYMBOLTABLE_H
