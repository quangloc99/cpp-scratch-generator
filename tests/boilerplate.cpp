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
    
    a = a + b + 1;
    b = b + (a + 100);
    a = (100 + b) + (200 + a);
}
#include "../undef-macro.inc"

int main() {
    ofstream out("project.json");
    CppScratchGenerator::generate_project_json(out, my_program);
    return 0;
}
