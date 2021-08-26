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
        x();
        x();
    };
    
    x();
    x();
    x();
    x();
    cout << "done x definition";  
    
    procedure(check_divide, a, b, c) { 
        if (a % b == 0) {  
            cout << b << " divides " << a;   
        }  
    }; 
    cout << "done check_divide definition"; 
    
    check_divide(1, 2, 3); 
    check_divide("a", "b", "c"); 
    
#include "../undef-macro.inc"
}

int main(int argc, char** argv) {
    std::string out_dir = argc <= 1 ? "." : argv[1];
    ofstream out((out_dir + "/project.json").c_str());
    try { 
        CppScratchGenerator::generate_project_json(out, my_program);
    } catch (const std::exception& e) { 
        cout << "=== ERROR ===" << endl << e.what() << endl; 
    } 
    return 0;
}

