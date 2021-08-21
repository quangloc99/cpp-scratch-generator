#include <iostream>
#include <fstream>
#include "../cpp-scratch-generator.hpp"

using namespace std;

#include "../def-macro.inc"
void my_program() {
    auto a;
    auto b;
    cin >> a >> b;
    cout << b << a;
    cout << "mot con vit";
    cout << "xoe ra " << 2 << " cai canh";
    
    cout << 3.1415926535;
}
#include "../undef-macro.inc"

int main() {
    ofstream out("project.json");
    CppScratchGenerator::generate_project_json(out, my_program);
    return 0;
}
