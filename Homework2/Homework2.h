//
// Created by tao on 2019/11/22.
//

#ifndef USTCCOMPILER_HOMEWORK2_H
#define USTCCOMPILER_HOMEWORK2_H

#define KEY 0
#define STRING 1

//在这部分中，你将使用图转移算法手工实现一个小型的词法分析器。
//* 分析器的输入：存储在文本文件中的字符序列，字符取自ASCII字符集。文件中可能包括四种记号：关键字if、符合C语言标准的标识符、空格符、回车符\n。
//* 分析器的输出：打印出所识别的标识符的种类、及行号、列号信息。

//【示例】对于下面的文本文件：
//ifx if iif       if
//iff     if

//你的输出应该是：
//ID(ifx) (1, 1)
//IF        (1, 4)
//ID(iif)  (1, 8)
//IF       (1, 13)
//ID(iff) (2, 1)
//IF       (2, 8)


#include <string>
#include <vector>


enum class StateType {
    Start,
    Identifier,
    Done
};

struct Token {
    int column;
    int row;
    int type;
    std::string value;
};


class Homework2 {
private:
    std::string readData();
    std::vector<Token*>& parse(const std::string& str);
    void log(std::vector<Token*>);
public:
    void main();
};


#endif //USTCCOMPILER_HOMEWORK2_H
