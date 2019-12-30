//
// Created by shaiac on 17/12/2019.
//
#include "symbolTable.h"
#include <vector>
#include <zconf.h>
#include <iostream>

SymbolTables *SymbolTables::singelton = nullptr; //the single show of the obj

/** We initialize the symbol table. the symbol table is a map
 * the key is the name of the vars in the simulator
 * the value is the value of the var*/
void SymbolTables::initializeSimulator() {
    this->finish = false;
    this->simulatorVars["airspeed-indicator_indicated-speed-kt"] =
            {0.0, "/instrumentation/airspeed-indicator/indicated-speed-kt", "", false};
    this->simulatorVars["time_warp"] =
            {0.0, "/sim/time/warp", "", false};
    this->simulatorVars["switches_magnetos"] =
            {0.0, "/controls/switches/magnetos", "", false};
    this->simulatorVars["heading-indicator_offset-deg"] =
            {0.0, "/instrumentation/heading-indicator/offset-deg", "", false};
    this->simulatorVars["altimeter_indicated-altitude-ft"] =
            {0.0, "/instrumentation/altimeter/indicated-altitude-ft", "", false};
    this->simulatorVars["altimeter_pressure-alt-ft"] =
            {0.0, "/instrumentation/altimeter/pressure-alt-ft", "", false};
    this->simulatorVars["attitude-indicator_indicated-pitch-deg"] =
            {0.0, "/instrumentation/attitude-indicator/indicated-pitch-deg", "", false};
    this->simulatorVars["attitude-indicator_indicated-roll-deg"] =
            {0.0, "/instrumentation/attitude-indicator/indicated-roll-deg", "", false};
    this->simulatorVars["attitude-indicator_internal-pitch-deg"] =
            {0.0, "/instrumentation/attitude-indicator/internal-pitch-deg", "", false};
    this->simulatorVars["attitude-indicator_internal-roll-deg"] =
            {0.0, "/instrumentation/attitude-indicator/internal-roll-deg", "", false};
    this->simulatorVars["encoder_indicated-altitude-ft"] =
            {0.0, "/instrumentation/encoder/indicated-altitude-ft", "", false};
    this->simulatorVars["encoder_pressure-alt-ft"] =
            {0.0, "/instrumentation/encoder/pressure-alt-ft", "", false};
    this->simulatorVars["gps_indicated-altitude-ft"] =
            {0.0, "/instrumentation/gps/indicated-altitude-ft", "", false};
    this->simulatorVars["gps_indicated-ground-speed-kt"] =
            {0.0, "/instrumentation/gps/indicated-ground-speed-kt", "", false};
    this->simulatorVars["gps_indicated-vertical-speed"] =
            {0.0, "/instrumentation/gps/indicated-vertical-speed", "", false};
    this->simulatorVars["indicated-heading-deg"] =
            {0.0, "/instrumentation/heading-indicator/indicated-heading-deg", "", false};
    this->simulatorVars["magnetic-compass_indicated-heading-deg"] =
            {0.0, "/instrumentation/magnetic-compass/indicated-heading-deg", "", false};
    this->simulatorVars["slip-skid-ball_indicated-slip-skid"] =
            {0.0, "/instrumentation/slip-skid-ball/indicated-slip-skid", "", false};
    this->simulatorVars["turn-indicator_indicated-turn-rate"] =
            {0.0, "/instrumentation/turn-indicator/indicated-turn-rate", "", false};
    this->simulatorVars["vertical-speed-indicator_indicated-speed-fpm"] =
            {0.0, "/instrumentation/vertical-speed-indicator/indicated-speed-fpm", "", false};
    this->simulatorVars["flight_aileron"] =
            {0.0, "/controls/flight/aileron", "", false};
    this->simulatorVars["flight_elevator"] =
            {0.0, "/controls/flight/elevator", "", false};
    this->simulatorVars["flight_rudder"] =
            {0.0, "/controls/flight/rudder", "", false};
    this->simulatorVars["flight_flaps"] =
            {0.0, "/controls/flight/flaps", "", false};
    this->simulatorVars["engine_throttle"] =
            {0.0, "/controls/engines/engine/throttle", "", false};
    this->simulatorVars["current-engine_throttle"] =
            {0.0, "/controls/engines/current-engine/throttle", "", false};
    this->simulatorVars["switches_master-avionics"] =
            {0.0, "/controls/switches/master-avionics", "", false};
    this->simulatorVars["switches_starter"] =
            {0.0, "/controls/switches/starter", "", false};
    this->simulatorVars["active-engine_auto-start"] =
            {0.0, "/engines/active-engine/auto-start", "", false};
    this->simulatorVars["flight_speedbrake"] =
            {0.0, "/controls/flight/speedbrake", "", false};
    this->simulatorVars["c172p_brake-parking"] =
            {0.0, "/sim/model/c172p/brake-parking", "", false};
    this->simulatorVars["engine_primer"] =
            {0.0, "/controls/engines/engine/primer", "", false};
    this->simulatorVars["current-engine_mixture"] =
            {0.0, "/controls/engines/current-engine/mixture", "", false};
    this->simulatorVars["switches_master-bat"] =
            {0.0, "/controls/switches/master-bat", "", false};
    this->simulatorVars["switches_master-alt"] =
            {0.0, "/controls/switches/master-alt", "", false};
    this->simulatorVars["engine_rpm"] =
            {0.0, "/engines/engine/rpm", "", false};
}

/**We initialize the list varsArray.
 * The program send the values of the vars in the same order every time.
 * this list build on the same order and with this list we know
 * which vars we need to set his value*/
void SymbolTables::initializeArray() {
    this->varsArray[0] = "airspeed-indicator_indicated-speed-kt";
    this->varsArray[1] = "time_warp";
    this->varsArray[2] = "switches_magnetos";
    this->varsArray[3] = "heading-indicator_offset-deg";
    this->varsArray[4] = "altimeter_indicated-altitude-ft";
    this->varsArray[5] = "altimeter_pressure-alt-ft";
    this->varsArray[6] = "attitude-indicator_indicated-pitch-deg";
    this->varsArray[7] = "attitude-indicator_indicated-roll-deg";
    this->varsArray[8] = "attitude-indicator_internal-pitch-deg";
    this->varsArray[9] = "attitude-indicator_internal-roll-deg";
    this->varsArray[10] = "encoder_indicated-altitude-ft";
    this->varsArray[11] = "encoder_pressure-alt-ft";
    this->varsArray[12] = "gps_indicated-altitude-ft";
    this->varsArray[13] = "gps_indicated-ground-speed-kt";
    this->varsArray[14] = "gps_indicated-vertical-speed";
    this->varsArray[15] = "indicated-heading-deg";
    this->varsArray[16] = "magnetic-compass_indicated-heading-deg";
    this->varsArray[17] = "slip-skid-ball_indicated-slip-skid";
    this->varsArray[18] = "turn-indicator_indicated-turn-rate";
    this->varsArray[19] = "vertical-speed-indicator_indicated-speed-fpm";
    this->varsArray[20] = "flight_aileron";
    this->varsArray[21] = "flight_elevator";
    this->varsArray[22] = "flight_rudder";
    this->varsArray[23] = "flight_flaps";
    this->varsArray[24] = "engine_throttle";
    this->varsArray[25] = "current-engine_throttle";
    this->varsArray[26] = "switches_master-avionics";
    this->varsArray[27] = "switches_starter";
    this->varsArray[28] = "active-engine_auto-start";
    this->varsArray[29] = "flight_speedbrake";
    this->varsArray[30] = "c172p_brake-parking";
    this->varsArray[31] = "engine_primer";
    this->varsArray[32] = "current-engine_mixture";
    this->varsArray[33] = "switches_master-bat";
    this->varsArray[34] = "switches_master-alt";
    this->varsArray[35] = "engine_rpm";
}

/**return the order of the vars in the simulator*/
string *SymbolTables::getArray() {
    return this->varsArray;
}

/**the constructor is private*/
SymbolTables::SymbolTables() {
    this->initializeSimulator();
    this->initializeArray();
}

/**here we use the singelton design pattern
 * we have only one show of this class,
 * every obj who used this class, use the same show*/
SymbolTables *SymbolTables::getSymbolT() {
    if (singelton == nullptr) {
        singelton = new SymbolTables();
    }
    return singelton;
}

/**
 * for every change we want to do in the symbol table we used this func.
 * this func protected by mutex to avoid threads collapse
 */
void SymbolTables::updateSimulatorVars(char setOget, unordered_map<string, var>::iterator it, var variable) {
    this->mutex_string_var.lock();
    if (setOget == 'g') { //when we changed our simulator by the values the simulator send
        unordered_map<string, var>::iterator update = this->simulatorVars.find(it->first);
        update->second = variable;
    }
    if (setOget == 's') { //when we send command to change the vars in the simulator
        var check = it->second;
        string message = "set " + check.sim + " " + to_string(check.value) + "\r\n"; //build the command
        ssize_t return_val;
        // Send message to the server
        return_val = write(int(variable.value), message.c_str(), message.length());
        check.readyToSet = false;
        unordered_map<string, var>::iterator update = this->simulatorVars.find(it->first);
        update->second = check;
    }
    mutex_string_var.unlock();
}
/**
 * the function match between the name of the var in simulator
 * and the new var we want to define
 */
void SymbolTables::addProgramvar(string name, string sim) {
    this->programVars[name] = sim;
    unordered_map<string, var>::iterator it;
    for (it = this->simulatorVars.begin(); it != this->simulatorVars.end(); it++) {
        if (it->second.sim.compare(sim) == 0) {
            this->programVars[name] = it->first;
            break;
        }
    }
}
/**
 * the function update condition on a specific var
 */
void SymbolTables::setCondition(string name, string sim, string condition) {
    unordered_map<string, var>::iterator it;
    for (it = this->simulatorVars.begin(); it != this->simulatorVars.end(); it++) {
        if (it->second.sim.compare(sim) == 0) {
            var toChange = it->second;
            toChange.condition = condition;
            this->updateSimulatorVars('g', it, toChange);
            break;
        }
    }
}
/**
 * the function return the value of the var
 */
float SymbolTables::getVarValue(string name) {
    string simulatorName = this->programVars.find(name)->second; //find the name of the var in the simulator
    unordered_map<string, var>::iterator itr;
    itr = this->simulatorVars.find(simulatorName);
    pair<string, var> p = itr.operator*();
    var v = p.second;
    return p.second.value;
}
/**
 * the function set the value of the var in the simulator table
 */
void SymbolTables::setValueInSimulator(string name, float newVal) {
    unordered_map<string, string>::iterator iterator;
    iterator = this->programVars.find(name);
    string simulatorName = iterator->second;
    unordered_map<string, var>::iterator itr;
    itr = this->simulatorVars.find(simulatorName);
    var toChange = itr->second;
    toChange.value = newVal; // create the new var
    this->updateSimulatorVars('g', itr, toChange);
}
/**
 * return the simulator table
 */
unordered_map<string, var> *SymbolTables::getSymap() {
    return &this->simulatorVars;
}
/**
 * the function turn on the ready to set, if the ready to set
 * is on the algorithm know that we need to send command to the simulator
 * to change his value
 */
void SymbolTables::turnOnSetVar(string name) {
    string simulatorName = this->programVars.find(name)->second;
    unordered_map<string, var>::iterator itr;
    itr = this->simulatorVars.find(simulatorName);
    var toChange = itr->second;
    toChange.readyToSet = true;
    this->updateSimulatorVars('g', itr, toChange);
}
/**
 * symbol that we end our program and we need to stop the run
 */
void SymbolTables::done() {
    this->finish = true;
}
/**
 * check if we need to stop the program
 */
bool SymbolTables::isFinish() {
    return this->finish;
}
/**
 * if this var represnt var in the simulator table
 */
bool SymbolTables::isInProgramMap(string name) {
    if (this->programVars.find(name) != this->programVars.end()) {
        return true;
    }
    return false;
}
/**
 * if this var represnt var in the simulator table
 */
bool SymbolTables::isExsistInSymap(string name) {
    unordered_map<string, string>::iterator itr = this->programVars.find(name);
    if (itr != this->programVars.end()) {
        return true;
    }
    return false;
}