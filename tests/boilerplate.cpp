#include <iostream>
#include <fstream>
#include "../cpp-scratch-generator.hpp"

using namespace std;

int main() {
    ofstream out("project.json");
    generate_project_json(out, []{});
    return 0;
}
