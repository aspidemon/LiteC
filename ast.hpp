#pragma once

#include <vector>
#include "t.hpp"

class ExpressionNode {

};

class StatementsNode {
private:   
    vector<ExpressionNode> code;

public:
    addNode(ExpressionNode node) {
        this->code.push_back(node);
    };

};

class VariableNode {
private:
    tokens variable;

public:
    VariableNode(tokens variable) {
        this->variable = variable;
    };

};

class NumberNode {
private:
    tokens number;

public:
    NumberNode(tokens number) {
        this->number = number;
    }

}

class BinOperation {
private:
    tokens operator;
    ExpressionNode left;
    ExpressionNode right;

public:
    BinOperation(tokens operator, ExpressionNode left, ExpressionNode right) {
        this->operator = operator;
        this->left = left;
        this->right = right;
    }

}

class UnarOperation {
private:
    tokens operation;
    ExpressionNode operand;

public:
    UnarOperation(tokens operation, ExpressionNode operand) {
        this->operation;
        this->operand;
    }

}