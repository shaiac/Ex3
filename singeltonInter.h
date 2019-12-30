//
// Created by shaiac on 26/12/2019.
//

#ifndef EX3_SINGELTONINTER_H
#define EX3_SINGELTONINTER_H

#include "ex1.h"

class SingeltonInter {
private:
    static Interpreter *interpreter;

    SingeltonInter();

public:

    static Interpreter *GetInterpreter();

};

#endif //EX3_SINGELTONINTER_H
