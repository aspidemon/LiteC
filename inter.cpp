#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "t.hpp"
#include "exp.hpp"
#include "types.hpp"

using namespace std;



class i_runtime {
private:
    map<string, int> var_int;
    map<string, long> var_long;
    map<string, float> var_float;
    map<string, string> var_string;
    map<string, bool> var_bool;
    map<string, string> var_types;
    string temp;

    bool crv(string name, string data, l_types __type, int ln) {
        if (__type == l_types::l_int) {
            var_int[name] = stoi(data);
        }
        else if (__type == l_types::l_long) {
            var_long[name] = stol(data);
        }
        else if (__type == l_types::l_float) {
            var_float[name] = stof(data);
        }
        else if (__type == l_types::l_string) {
            var_string[name] = data;
        }
        else if (__type == l_types::l_bool) {
            if (data == "true") {
                var_bool[name] = true;
            } else if (data == "false") {
                var_bool[name] = false;
            }
            else {
                expnowbyln(GET_VARIABLE_NAME(exceptions::TypeConversionError), ln, "the value `"+data+"` is not a type<types:bool>");
                return false;
            }
        }
    }
public:
    i_runtime() {

    }
    bool create_var(string var_name, l_types var_type, string var_data, vector<l_keywords> var_keywords, int line) {
        if (var_types[var_name].empty()) {
            crv(var_name, var_data, var_type, line);
        } else {
            temp = "The \""+var_name+"\" name is already registered, you cannot use it in the current context.";
            expnowbyln(GET_VARIABLE_NAME(exceptions::NameAlreadyRegistered), line, temp);
            return false;
        }
    }
};

int i_run(const vector<tokens> e_tokens, const vector<string> e_names) {

}

int main() {
    i_runtime runtime;
    //int retval = run("int var = 0;\npb int main(\"ggg\") {\nv.call(\"kkkk\", =999);\n}");
    //if (retval == -2) {
        expnow(GET_VARIABLE_NAME(exceptions::UnknownError), -1, -1, 'n');
        //return -1;
    //}
    vector<l_keywords> f;
    runtime.create_var("test", l_types::l_bool, "truee", f, 999);
    //return retval;
}
