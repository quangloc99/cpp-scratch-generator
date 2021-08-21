#include <iostream>
#include <fstream>
#include "../cpp-scratch-generator.hpp"

using namespace std;

#include "../def-macro.inc"
void my_program() {
    var a = 1;
    var b = 2;
    auto x = 1.2;
    auto y = 3.14159265358;
    var s = "abcxyz";
    dec_var(abcd, 123);
    dec_var(xyzt, "nice");
    
    a = b; 
    x = y;
    abcd = xyzt;
}
#include "../undef-macro.inc"

int main() {
    ofstream out("project.json");
    generate_project_json(out, my_program);
    return 0;
}
