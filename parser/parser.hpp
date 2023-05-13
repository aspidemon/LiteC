#pragma once

#include <vector>
#include "exp.hpp"
#include "ast.hpp"

class Parser {
private:
    vector<tokens> datt;
    int pos = 0;

public:
    Parser(vector<tokens> datt) {
        this->datt = datt;
    };

    template <typename T>
    T match(tokens tok) {
        if (this->pos < this->datt.length()) {
            tokens currentt = this->datt[this->pos];
            for (tokens t : tok) {
                if (tok == t) {
                    this->pos += 1;
                    return currentt;
                }
            }
        }
        return 0;
    };

    tokens require(tokens tok) {
        tokens token = this->match(tokens);
        //сюды вызов ошибки
        return token;
    };

    ExpressionNode parseExpression() {
        if (this->match(tokens::WORD) == 0) {
            printNode = parsePrint();
            return printNode;
        }
        this->pos -= 1;
        //varNode = parseVarOrNumber();
        //assignOperator = this->match(tokens::OPERATION);

    };

    ExpressionNode parse() {
        StatementsNode root();
        while (this->pos < this->datt.length()) {
            ExpressionNode stringNode = this->parseExpression();
            this->require(tokens::END);
            root.addNode(stringNode);
        }
        return root;
    };

};
