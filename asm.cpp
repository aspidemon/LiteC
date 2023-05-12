#include <string>
#include <iostream>

class asm_gen {
private:
    std::string asm_format, asm_entry, asm_data, asm_code_fn, asm_code, asm_inc, asm_import = "";
public:
    asm_gen() {
        asm_format = "format PE Console";
        asm_entry = "entry start";
        asm_inc = "include 'win32a.inc'\ninclude 'win32ax.inc'";
    }
    void add_data(std::string l) {
        asm_data += l+"\n";
    }
    void add_code(std::string l) {
        asm_code += l+"\n";
    }
    void add_fn(std::string l) {
        asm_code_fn += l+"\n";
    }
    void add_inc(std::string l) {
        asm_inc += l+"\n";
    }
    void add_import(std::string l) {
        asm_import += l+"\n";
    }

    std::string COMPILER() {
        return asm_format+"\n"+asm_entry+"\n"+asm_inc+"\nsection '.data' data readable writeable\n"+asm_data+"\nsection '.code' code readable writeable executable\n"+asm_code_fn+"\n"+asm_code+"\nsection '.idata' data import readable\n"+asm_import;
    }
};

int main() {
    asm_gen a = asm_gen();
    std::cout<< a.COMPILER();
}