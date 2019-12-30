#include "singeltonInter.h"

//
// Created by shaiac on 26/12/2019.
//
Interpreter * SingeltonInter::interpreter = nullptr; // the single show of the boj
/**
 * private constructor
 */
SingeltonInter::SingeltonInter(){
}

/**
 * return the single show of the obj
 */
Interpreter *SingeltonInter::GetInterpreter() {
    if (interpreter == nullptr) {
        interpreter = new Interpreter();
    }
    return interpreter;
}