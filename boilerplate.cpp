#include <iostream>
#include <fstream>
#include "cpp-scratch-generator.hpp"

using namespace std;

void my_program() {
#include "def-macro.inc"
    // your code here
#include "undef-macro.inc"
}

int main() {
    ofstream out("project.json");
    CppScratchGenerator::generate_project_json(out, my_program);
    return 0;
}
