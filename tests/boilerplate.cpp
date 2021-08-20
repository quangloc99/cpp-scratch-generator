#include <iostream>
#include <fstream>
#include "../cpp-scratch-generator.hpp"

using namespace std;

int main() {
    ofstream out("project.json");
    generate_project_json(out, []{
            VariableDeclaration v("my var", 1);
            VariableDeclaration a = 2;
            });
    return 0;
}
