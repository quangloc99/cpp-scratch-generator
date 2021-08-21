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
#define gen_expressions(op)                 \
    c = a op b;                             \
    c = a op 100;                           \
    c = 100 op a;                           \
    c = 100 op 100;                         \
    c = (a op b) op a;                      \
    c = a op (a op b);                      \
    c = (a op b) op 200;                    \
    c = 300 op (a op b);                    \
    c = a op b op a op b op a op c; 

    gen_expressions(+);
    gen_expressions(-);
    gen_expressions(*);
    gen_expressions(/);
    gen_expressions(%);
    
    cout << a << b << c;
}
#include "../undef-macro.inc"

int main() {
    ofstream out("project.json");
    CppScratchGenerator::generate_project_json(out, my_program);
    return 0;
}
