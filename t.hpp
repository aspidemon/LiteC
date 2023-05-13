#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <fstream>
#include <map>
#include "exp.hpp"
#include "ast.hpp"

#define _and &&
#define _or ||

using namespace std;

enum tokens {WORD, NUMBER, CHAR, STRING, OPERATION, OPERATIONLOGIC, OPERATIONSYS, CALL, ARGSBEGGIN, ARGSEND, ARGSDATA, CONTENTBEGGIN, CONTENTEND, CONTENTDATA, QUOTESBEGGIN, QUOTESEND, QUOTESDATA, DOT, COMMA, END, NEWLINE};

string tokenToString(tokens t) {
    switch (t)
    {
    case WORD:
        return "WORD";
        break;
    case NUMBER:
        return "NUMBER";
        break;
    case CHAR:
        return "CHAR";
        break;
    case STRING:
        return "STRING";
        break;
    case OPERATION:
        return "OPERATION";
        break;
    case OPERATIONLOGIC:
        return "OPERATIONLOGIC";
        break;
    case OPERATIONSYS:
        return "OPERATIONSYS";
        break;
    case CALL:
        return "CALL";
        break;
    case ARGSBEGGIN:
        return "ARGSBEGGIN";
        break;
    case ARGSDATA:
        return "ARGSDATA";
        break;
    case ARGSEND:
        return "ARGSEND";
        break;
    case CONTENTBEGGIN:
        return "CONTENTBEGGIN";
        break;
    case CONTENTDATA:
        return "CONTENTDATA";
        break;
    case CONTENTEND:
        return "CONTENTEND";
        break;
    case DOT:
        return "DOT";
        break;
    case COMMA:
        return "COMMA";
        break;
    case END:
        return "END";
        break;
    case QUOTESBEGGIN:
        return "QUOTESBEGGIN";
        break;
    case QUOTESDATA:
        return "QUOTESDATA";
        break;
    case QUOTESEND:
        return "QUOTESEND";
        break;
    default:
        return "!none";
        break;
    }
}

class tokendetect {
public:

    bool isMathOp(char l) {
        if (l == '=') {
            return true;
        } else if (l == '+') {
            return true;
        }
        else if (l == '-') {
            return true;
        }
        else if (l == '/') {
            return true;
        }
        else if (l == '*') {
            return true;
        }
        return false;
    }

    bool isLogicOp(char l) {
        if (l == '>') {
            return true;
        } else if (l == '<') {
            return true;
        } else if (l == '!') {
            return true;
        }
        return false;
    }

    bool isSysOp(char l) {
        if (l == ':') {
            return true;
        } else if (l == '?') {
            return true;
        }
        else if (l == '$') {
            return true;
        }
        else if (l == '&') {
            return true;
        }
        else if (l == '@') {
            return true;
        }
        return false;
    }

    bool isDelimetr(char l) {
        if (isspace(l) _or isMathOp(l) _or isLogicOp(l) _or isSysOp(l)) {
            return true;
        }
        return false;
    }

    int isSpecial(char l) {
        if (l == '.') {
            return 1;
        }
        else if (l == ',') {
            return 2;
        }
        return 0;
    }

    string delSpace(string l) {
        string t;
        int ii = 0;
        for (int i = 0; i < l.length(); i++) {
            if (isspace(l[i])){}
            else {t += l[i]; ii++;}
        }
        return t;
    }
};

int run(string data) {
    tokendetect tkd;
    vector<tokens> datt;
    vector<string> dat;
    string tmpdat, emptyline = "";
    int argslvl, colp = 0;
    int contlvl = 0;
    int skipTo = -1;
    bool isString, ignore = false;
    int line = 1;
    for (int i = 0; i < data.length(); i++) {
        
        if (skipTo >= i) continue;
        colp++;
        if (isString _and data[i] == '\\' _and !ignore) {
            //skipTo = i + 1;
            tmpdat += data[i];
        }
        else if (data[i] == '"' _and !ignore) {
            
            if (isString) {
                datt.push_back(tokens::QUOTESDATA);
                dat.push_back(tmpdat);
                tmpdat="";
                datt.push_back(tokens::QUOTESEND);
                dat.push_back(emptyline+data[i]);
                
            }
            else {
                tmpdat="";
                datt.push_back(tokens::QUOTESBEGGIN);
                dat.push_back(emptyline+data[i]);
                
            }
            isString = !isString;
            
        }
        if (data[i] == '\n') {
            line++;
            tmpdat+='\n';
            colp = 0;
            datt.push_back(tokens::NEWLINE);
            dat.push_back(emptyline+data[i]);
            tmpdat="";
        }
        else if(data[i] == ';' _and !isString _and !ignore) {
            if (!tkd.delSpace(tmpdat).empty()) {
                datt.push_back(tokens::WORD);
                dat.push_back(tkd.delSpace(tmpdat));
            } cout << tmpdat << "<\n";
            datt.push_back(tokens::END);
            dat.push_back(emptyline+data[i]);
            tmpdat="";
        }
        else if (isspace(data[i]) _and !isString _and !ignore) {
            if (!tkd.delSpace(tmpdat).empty()) {
                datt.push_back(tokens::WORD);
                dat.push_back(tkd.delSpace(tmpdat));
            } cout << tmpdat << "<\n";
            tmpdat="";
        }
        else if (tkd.isSysOp(data[i]) _and !isString _and !ignore) {
            if (!tkd.delSpace(tmpdat).empty()) {
                datt.push_back(tokens::WORD);
                dat.push_back(tkd.delSpace(tmpdat));
            } cout << tmpdat << "<\n";
            datt.push_back(tokens::OPERATIONSYS);
            dat.push_back(emptyline+data[i]);
            tmpdat="";
            continue;
        } else if (tkd.isMathOp(data[i]) _and !isString _and !ignore) {
            if (!tkd.delSpace(tmpdat).empty()) {
                datt.push_back(tokens::WORD);
                dat.push_back(tkd.delSpace(tmpdat));
            } cout << tmpdat << "<\n";
            datt.push_back(tokens::OPERATION);
            dat.push_back(emptyline+data[i]);
            tmpdat="";
            continue;
        }
        else if (tkd.isLogicOp(data[i]) _and !isString _and !ignore) {
            if (!tkd.delSpace(tmpdat).empty()) {
                datt.push_back(tokens::WORD);
                dat.push_back(tkd.delSpace(tmpdat));
            } cout << ">" << tmpdat << "<\n";
            datt.push_back(tokens::OPERATIONLOGIC);
            dat.push_back(emptyline+data[i]);
            tmpdat="";
            continue;
        }
        else if (isdigit(data[i])_and !isString _and !ignore) {
            datt.push_back(tokens::NUMBER);
            dat.push_back(emptyline+data[i]);
            tmpdat="";
        }
        else if (tkd.isSpecial(data[i]) _and !isString _and !ignore) {
            if (!tkd.delSpace(tmpdat).empty()) {
                datt.push_back(tokens::WORD);
                dat.push_back(tkd.delSpace(tmpdat));
            }
            if (tkd.isSpecial(data[i]) == 1) {
                datt.push_back(tokens::DOT);
                dat.push_back(emptyline+data[i]);          
            }
            else {
                datt.push_back(tokens::COMMA);
                dat.push_back(emptyline+data[i]);
            }
            tmpdat="";
            continue;
        }
        else if ((data[i] == '(' _or data[i] == ')') _and (!isString _and !ignore)) {
            
            if (data[i] == '(' _and argslvl >= 0) {
                if (!tkd.delSpace(tmpdat).empty()) {
                    datt.push_back(tokens::WORD);
                    dat.push_back(tkd.delSpace(tmpdat));
                }
                datt.push_back(tokens::ARGSBEGGIN);
                dat.push_back(emptyline+data[i]);
                argslvl++;
                tmpdat="";
                continue;
            }
            else if (data[i] == ')' _and argslvl >=1) {
                datt.push_back(tokens::ARGSEND);
                dat.push_back(emptyline+data[i]);
                argslvl--;
                tmpdat="";
                continue;
            }
            if (argslvl <= -1 _or (data[i] == ')' _and argslvl == 0)) {
                expnow(GET_VARIABLE_NAME(exceptions::ParenthesisClosedButNotOpened), line, colp, 'j');
                return -1;
            }
        }
        else if ((data[i] == '{' _or data[i] == '}') _and (!isString _and !ignore)) {
            if (data[i] == '{' _and contlvl >= 0) {
                if (!tkd.delSpace(tmpdat).empty()) {
                    datt.push_back(tokens::WORD);
                    dat.push_back(tkd.delSpace(tmpdat));
                }
                datt.push_back(tokens::CONTENTBEGGIN);
                dat.push_back(emptyline+data[i]);
                contlvl++;
                tmpdat="";
                continue;
            }
            else if (data[i] == '}' _and contlvl >=1) {
                datt.push_back(tokens::CONTENTEND);
                dat.push_back(emptyline+data[i]);
                contlvl--;
                tmpdat="";
                continue;
            }
            if (contlvl <= -1 _or (data[i] == '}' _and contlvl == 0)) {
                expnow(GET_VARIABLE_NAME(exceptions::ContainerClosedButNotOpened), line, colp, 'j');
                return -1;
            }
        }
        else if(!isString _and !ignore) {
            tmpdat+=data[i];
        }
        else if(isString _and !ignore _and data[i] != '"') {tmpdat+=data[i];}
    }
    
    for (tokens tkk : datt)
    cout << tokenToString(tkk) << " , "; 
    for (string lll : dat)
    cout << lll << "<>"; 
    cout << "\n"<< datt.size() <<":"<< dat.size();
    if (argslvl != 0) {
        expnow(GET_VARIABLE_NAME(exceptions::ParenthesisNotClosed), -1, -1, 'j');
        return -1;
    }
    else if (contlvl != 0) {
        expnow(GET_VARIABLE_NAME(exceptions::ContainerNotClosed), contlvl, -1, 'j');
        return -1;
    }
    //return i_run(datt, dat);
}

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

int mainggg() {
    int retval = run("int var = 0;\npb int main(\"ggg\") {\nv.call(\"kkkk\", =999);\n}");
    if (retval == -2) {
        expnow(GET_VARIABLE_NAME(exceptions::UnknownError), -1, -1, 'n');
        return -1;
    }
    return retval;
}