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
        if (!token) {
            //сюды вызов ошибки
        }
        return token;
    };

    ExpressionNode parseVariableNumber() {
        tokens number = this->match(tokens::NUMBER);
        if (number != 0) {
            return NumberNode(number);
        }
        tokens variable = this->match(tokens::WORD);
        if (variable != 0) {
            return VariableNode(variable);
        }
        //вызов ошибки
    };

    ExpressionNode parseParentheses() {
        if (this->match(tokens::ARGSBEGGIN) != 0) {
            ExpressionNode node = this->parseFormula();
            this->require(tokens::ARGSEND);
            return node;
        } else {
            return this->parseVariableNumber();
        }
    };

    ExpressionNode parseFormula() {
        ExpressionNode leftNode = this->parseParentheses();
        tokens operator = match(tokens::OPERATION);
        while (operator != 0) {
            rightNode = ;
            BinOperation leftNode(operator, leftNode, rightNode); 
        }
        return leftNode;
    };
    
    ExpressionNode parseExpression() {
        if (this->match(tokens::WORD) == 0) {
            printNode = parsePrint();
            return printNode;
        }
        this->pos -= 1;
        EpressionNode varNode = this->parseVarOrNumber();
        tokens assignOperator = this->match(tokens::OPERATION);
        if (assignOperator != 0) {
            ExpressionNode rightFormulaNode = this->parseFormula();
            BinOperation binaryNode(assignOperator, varNode, rightFormulaNode);
            return binaryNode;
        }
        //вызов ошибки
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

    template <typename T>
    T run(ExpressionNode node) {

    };

};
