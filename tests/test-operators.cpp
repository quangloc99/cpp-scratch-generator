#include <iostream>
#include <fstream>
#include "../cpp-scratch-generator.hpp"

using namespace std;

#include "../def-macro.inc"
void my_program() {
    dec_var(a, 0);
    dec_var(b, 0);
    dec_var(c, 0);
    
    cin >> a >> b >> c;
    
    // all combination
    c = a + b;
    c = a + 100; 
    c = 100 + a; 
    c = 100 + 100; 
    c = (a + b) + a; 
    c = a + (a + b); 
    c = (a + b) + 200; 
    c = 300 + (a + b); 
    
    c = a + b + a + b + a + c; 
    
    cout << a << b << c;
}
#include "../undef-macro.inc"

int main() {
    ofstream out("project.json");
    CppScratchGenerator::generate_project_json(out, my_program);
    return 0;
}
