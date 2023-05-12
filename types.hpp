#pragma once
#include <string>

enum l_types {
        l_byte,
        l_int,
        l_long,
        l_float,
        l_double,
        l_char,
        l_string,
        l_bool,
        l_void,
        l_NULL,
        l_class,
        l_type,
        l_none_type
};

std::string StringToTypes(l_types t) {
    switch (t)
    {
    case l_byte:
        return "byte";
        break;
    case l_int:
        return "int";
        break;
    case l_long:
        return "long";
        break;
    case l_float:
        return "float";
        break;
    case l_double:
        return "double";
        break;
    case l_char:
        return "char";
        break;
    case l_string:
        return "string";
        break;
    case l_bool:
        return "bool";
        break;
    case l_void:
        return "void";
        break;
    case l_NULL:
        return "NULL";
        break;
    case l_class:
        return "class";
        break;
    case l_type:
        return "type";
        break;
    default:
        return "!None";
        break;
    }
}

l_types typesToString(std::string t) {
    if (t == "byte")
        return l_byte;
    else if (t == "int")
        return l_int;
    else if (t == "long")
        return l_long;
    else if (t == "float")
        return l_float;
    else if (t ==  "double")
        return l_double;
    else if (t ==  "char")
        return l_char;
    else if (t ==  "string")
        return l_string;
    else if (t ==  "bool")
        return l_bool;
    else if (t ==  "void")
        return l_void;
    else if (t ==  "NULL")
        return l_NULL;
    else if (t ==  "class")
        return l_class;
    else if (t ==  "type")
        return l_type;
    else
        return l_none_type;
}

enum l_keywords {
    l_public,
    l_private,
    l_naked,
    l_inline,
    l_thread,
    l_static,
    l_unsafe,
    l_import,
    l_export,
    l_new
};

std::string keywordToString(l_keywords k) {
    switch(k) {
    case l_public:
            return "public";
    case l_private:
            return "private";
    case l_naked:
            return "naked";
    case l_inline:
            return "inline";
    case l_thread:
            return "thread";
    case l_static:
            return "static";
    case l_unsafe:
            return "unsafe";
    case l_import:
            return "import";
    case l_export:
            return "export";
    case l_new:
            return "new";
            }
}

l_keywords StringToKeyword(std::string k) {
    if (k == "public") {
        return l_keywords::l_public;
    }else if (k == "private") {
        return l_keywords::l_private;
    }else if (k == "naked") {
        return l_keywords::l_naked;
    }else if (k == "inline") {
        return l_keywords::l_inline;
    }else if (k == "thread") {
        return l_keywords::l_thread;
    }else if (k == "static") {
        return l_keywords::l_static;
    }else if (k == "unsafe") {
        return l_keywords::l_unsafe;
    }else if (k == "import") {
        return l_keywords::l_import;
    }else if (k == "export") {
        return l_keywords::l_export;
    }else if (k == "new") {
        return l_keywords::l_new;
    }
}