#include <iostream>
#include <fstream>
#include "../cpp-scratch-generator.hpp"

using namespace std;

void my_program() {
#include "../def-macro.inc"
    dec_var(a, 0);
    dec_var(b, 0);
    procedure(x) {
        a = a + b;
        if (a > b) {
            cout << a << " is bigger than " << b;
        }
    };
    // x();  
#include "../undef-macro.inc"
}

int main() {
    ofstream out("project.json");
    try { 
        CppScratchGenerator::generate_project_json(out, my_program);
    } catch (const std::exception& e) { 
        cout << "=== ERROR ===" << endl << e.what() << endl; 
    } 
    return 0;
}

