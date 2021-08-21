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
    
}
#include "../undef-macro.inc"

int main() {
    ofstream out("project.json");
    CppScratchGenerator::generate_project_json(out, my_program);
    return 0;
}
