//
// Created by omer on 16.12.2019.
//
#include <fstream>
#include <iostream>
#include "lexer.h"

using namespace std;
/**
 * take a line and break it to commands and obj
 */
void lexer::SepALine(string line) {
    int i = 0;
    string single = "";
    bool isequal = false; // if we in the middle of the right side =
    bool isgeresh = false; // if we in the middle of apostrophes
    bool isoger = false; // if we in the middle of brackets
    while (true) {
        char check = line[i];
        if (check == '!') { //check if we in oper with the char !
            if (line[i + 1] == '=') { // if the oper is !=
                if (single != "") {
                    this->cmdAndPr.push_back(single);
                }
                this->cmdAndPr.push_back("!=");
                i += 2;
                single = "";
                continue;
            }
        }
        if (line[i + 1] == '{' || line[i + 1] == '}') { // when we see { } we always stop our obj/command
            if (single != "") {
                if (check != ' ') {
                    single += check;
                }
                this->cmdAndPr.push_back(single);
            }
            single = "";
            i++;
            continue;
        }
        if (check == '>' || check == '<') {
            if (line[i - 1] != '-' && line[i + 1] != '-') { // if its not a sign of an arrow
                if (single != "") {
                    this->cmdAndPr.push_back(single);
                }
                single = line[i];
                if (line[i + 1] == '=') { // if its a sign of oper <= >=
                    single += '=';
                    i++;
                }
                this->cmdAndPr.push_back(single);
                isequal = true; // we in the middle of an equation
            } else {
                if (line[i - 1] == '-') { // if its a sign of an arrow
                    if (single != "" && single != "-") {
                        single.erase(single.size() - 1);
                        this->cmdAndPr.push_back(single);
                    }
                    single = "->";
                    this->cmdAndPr.push_back(single);
                } else if (line[i + 1] == '-') {
                    if (single != "") {
                        this->cmdAndPr.push_back(single);
                    }
                    i++;
                    single = "<-";
                    this->cmdAndPr.push_back(single);
                }
            }
            single = "";
            i++;
            continue;
        }
        if (check == '=') { // if we have oper of =
            if (single != "") {
                this->cmdAndPr.push_back(single);
            }
            single = "=";
            if (line[i + 1] == '=') { //if its in oper ==
                single += '=';
                i++;
            }
            this->cmdAndPr.push_back(single);
            single = "";
            isequal = true; // we in the middle of an equation
            i++;
            continue;
        }
        if (check == '"') {
            if (isgeresh) { // if its the end of the apostrophes
                single += 34;
                this->cmdAndPr.push_back(single);
                isgeresh = false;
                single = "";
            } else if (!isgeresh) { // if its the start of apostrophes
                if (single != "") {
                    this->cmdAndPr.push_back(single);
                }
                single = "";
                single += 34;
                isgeresh = true;
            }
            i++;
            continue;
        }
        if (check == '\n' || check == '\000') { // if its the end of the line
            if (single != "") {
                this->cmdAndPr.push_back(single);
            }
            break;
        }
        if (check == '(' && (!isequal) && (!isgeresh)) { // if we in new comma
            if (single != "") {
                this->cmdAndPr.push_back(single);
            }
            single = "";
            isoger = true; // we in the middle of coma
            i++;
            continue;
        }
        if (check == ')' && (!isequal) && (!isgeresh)) { // if we in the end of comma
            if (single != "") {
                this->cmdAndPr.push_back(single);
            }
            single = "";
            isoger = false; // close the coma
            i++;
            continue;
        }
        if ((check == ',') && (!isequal) && (!isgeresh)) { // ',' is beyond coma, we can have ',' in coma
            if (single != "") {
                this->cmdAndPr.push_back(single);
            }
            single = "";
            i++;
            continue;
        }
        if ((check == ' ' || check == '\t') && (!isequal) && (!isgeresh) && (!isoger)) {
            if (single != "") {
                this->cmdAndPr.push_back(single);
            }
            single = "";
            i++;
            continue;
        }
        if (single == "" && check == ' ') { // to avoid space in the start of obj
            i++;
            continue;
        }
        single += line[i];
        i++;
    }
}
/**
 * take the full file and break it to command and obj
 */
void lexer::ReadFile(const char *file_path) {
    ifstream file;
    file.open(file_path);
    if (!file.is_open()) {
        throw "bad file";
    }
    string line;
    string sep = "";
    while (getline(file, line)) {
        this->SepALine(line);
    }
    file.close();
}
