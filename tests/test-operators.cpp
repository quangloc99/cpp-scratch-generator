#include <iostream>
#include <fstream>
#include "../cpp-scratch-generator.hpp"

using namespace std;

void my_program() {
#include "../def-macro.inc"
    dec_var(a, 0); 
    dec_var(b, 0); 
    dec_var(c, 0); 
    
    a = 1; 
    a = "a"; 
    a = b; 
    a = c + b; 
    
    auto x = a + b;
    dec_var(y, a * b);
    
    cin >> a >> b >> c;
    
    a += b;
    a -= b;
    a += 1;
    a += 0;
    a += 2;
    a += b + 2;
    a += 2 * b;
    a -= 0;
    a -= 1;
    a -= 2;
    a -= b + 2;
    a -= 2 * b;
    
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
    
#define gen_func_call_binary(func)                \
    c = func(a, b);                               \
    c = func(a, 100);                             \
    c = func(100, a);                             \
    c = func(func(a, b), a);                      \
    c = func(a, func(a, b));                      \
    c = func(func(a, b), 200);                    \
    c = func(300, func(a, b));                    \
    c = func(a, func(b, func(a, func(b, c))));    \
    c = func(100, 100);                           \
    cout << c;

    
    gen_func_call_binary(random); 
    gen_func_call_binary(join); 
    gen_func_call_binary(letter_of); 
    
#define gen_func_call_unary(func) \
    c = func(a);                    \
    c = func(1);                    \
    c = func(2 + 3);                \
    c = func("abc");                \
    c = func(a + a);                \
    c = func(a * a);                \
    c = func(a + b + 123);          \
    cout << c;
    
    gen_func_call_unary(length);
    gen_func_call_unary(round);
    gen_func_call_unary(abs);
    gen_func_call_unary(floor);
    gen_func_call_unary(ceil);
    gen_func_call_unary(sqrt);
    gen_func_call_unary(sin);
    gen_func_call_unary(cos);
    gen_func_call_unary(tan);
    gen_func_call_unary(asin);
    gen_func_call_unary(acos);
    gen_func_call_unary(atan);
    gen_func_call_unary(ln);
    gen_func_call_unary(log);
    gen_func_call_unary(expe);
    gen_func_call_unary(exp10);
    
    cout << a << b << c;
    
    
    // test join for multiple argument
    cout << join(a, b);
    cout << join(a, b, c); 
    cout << join(1, 2, 3); 
    cout << join("x", "y", "z"); 
    cout << join(a, " ", b, " ", c, " "); 
    cout << join(a, ' ', b, ' ', c, ' '); 
#include "../undef-macro.inc"
}

int main(int argc, char** argv) {
    std::string out_dir = argc <= 1 ? "." : argv[1];
    ofstream out((out_dir + "/project.json").c_str());
    CppScratchGenerator::generate_project_json(out, my_program);
    return 0;
}
