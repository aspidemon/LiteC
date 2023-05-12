#pragma once

#include <iostream>
#include <string>

#define GET_VARIABLE_NAME(Variable) (#Variable)
#define gvnc0(Variable) (#Variable)

enum exceptions {
    UnknownError,
    UnknownKeyword,
    UnknownType,
    UnknownName,
    UnknownVariable,
    UnknownFunction,
    FileRaedError,
    FileWriteError,
    FileOpenError,
    TypeConversionError,
    InvalidCall,
    InvalidKeyword,
    InvalidName,
    NameAlreadyRegistered,
    ParenthesisNotClosed,
    ParenthesisClosedButNotOpened,
    QuotesNotClosed,
    ContainerNotClosed,
    ContainerClosedButNotOpened
};

void expnow(std::string exp, int line, int _char, char __) {
    if (line != -1)
    std::cout << exp << " : in ln:" << line << ", col:" <<  _char << "\n";
    else
    std::cout << exp << " : in ln:" << "?" << ", col:" <<  "?" << "\n";
}

void expnowbyln(std::string exp, int line, std::string msg) {
    if (line != -1)
    std::cout << exp << " : in ln(" << line  << ") : " << msg;
    else
    std::cout << exp << " : in ln(" << "?" << ") : " << msg;
}

std::string expToString(exceptions e) {
    switch (e)
    {
    case exceptions::UnknownError :
        return "UnknownError";
        break;
    case exceptions::UnknownKeyword :
        return "UnknownKeyword";
        break;
    case exceptions::UnknownType :
        return "UnknownKeyword";
        break;
    case exceptions::UnknownName :
        return "UnknownKeyword";
        break;
    case exceptions::UnknownVariable :
        return "UnknownKeyword";
        break;
    case exceptions::UnknownFunction :
        return "UnknownKeyword";
        break;
    case exceptions::FileRaedError :
        return "UnknownKeyword";
        break;
    default:
        break;
    }
}