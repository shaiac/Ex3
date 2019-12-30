//
// Created by omer on 16.12.2019.
//

#ifndef FILGHTGEAR_LEXER_H
#define FILGHTGEAR_LEXER_H

#include <string>
#include <list>

using namespace std;

class lexer {

private:
    list <string> cmdAndPr;
public:
    void ReadFile(const char *file_path);

    void SepALine(string line);

    list <string> GetList() {
        return this->cmdAndPr;
    }

};

#endif //FILGHTGEAR_LEXER_H
