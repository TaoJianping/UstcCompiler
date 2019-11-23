//
// Created by tao on 2019/11/22.
//

#include <fstream>
#include <sstream>
#include <iostream>
#include "Homework2.h"

void Homework2::main() {
    std::string data = readData();
    auto ts = parse(data);
    log(ts);
}

std::string Homework2::readData() {
    std::string path = "/home/tao/Documents/projects/UstcCompiler/Homework2/test.txt";
    std::ifstream infile;
    infile.open(path);
    std::stringstream buffer;
    buffer << infile.rdbuf();
    std::string contents(buffer.str());
    return contents;
}

std::vector<Token *> &Homework2::parse(const std::string &str) {
    StateType state = StateType::Start;
    auto ts = new std::vector<Token *>();
    int pointer = 0;
    int index = 0;
    int line = 1;
    int column = 1;
    for (char c : str) {
        if (state == StateType::Start) {
            switch (c) {
                case '\n':
                    line += 1;
                    column = 0;
                    index += 1;
                    break;
                case ' ':
                    index += 1;
                    column += 1;
                    break;
                default:
                    if (isalpha(c)) {
                        state = StateType::Identifier;
                    }
            }
        }
        if (state == StateType::Identifier) {
            column += 1;
            if (c == ' ' || c == '\n' || c == '\0' || pointer == str.length()-1) {
                if (c == '\n') {
                    line += 1;
                    column = 0;
                }
                state = StateType::Done;
            }
        }
        if (state == StateType::Done) {
            int count = pointer - index;
            if (pointer == str.length()-1) {
                count += 1;
            }
            std::string value = str.substr(index, count);
            auto token = new Token();
            token->value = value;
            token->column = column;
            token->row = line;
            if (value == "if") {
                token->type = KEY;
            } else {
                token->type = STRING;
            }
            ts->push_back(token);
            state = StateType::Start;
            index = pointer + 1;
        }
        pointer += 1;
    }
    return *ts;
}

void Homework2::log(std::vector<Token *> ts) {
    for (auto t : ts) {
        if (t->type == STRING) {
            std::cout << "ID(" << t->value << ")" << "  (" << t->row << ", " << t->column << ")" << std::endl;
        } else {
            std::cout << "IF" << "(" << t->row << ", " << t->column << ")" << std::endl;
        }
    }
}
