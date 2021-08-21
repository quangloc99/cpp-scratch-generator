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
    c = a op b op a op b op a op c;         \
    cout << c;
    
    gen_expressions(+);
    gen_expressions(-); 
    gen_expressions(*); 
    gen_expressions(/); 
    gen_expressions(%); 
    
#define gen_func_call(func)                       \
    c = func(a, b);                               \
    c = func(a, 100);                             \
    c = func(100, a);                             \
    c = func(func(a, b), a);                      \
    c = func(a, func(a, b));                      \
    c = func(func(a, b), 200);                    \
    c = func(300, func(a, b));                    \
    c = func(a, func(b, func(a, func(b, c))))
    // c = func(100, 100);                          

    
    // gen_func_call(random); 
    
    cout << a << b << c;
}
#include "../undef-macro.inc"

int main() {
    ofstream out("project.json");
    CppScratchGenerator::generate_project_json(out, my_program);
    return 0;
}
