#include <iostream>
#include <fstream>
#include "../cpp-scratch-generator.hpp"

using namespace std;

void test_do() {
#include "../def-macro.inc"
    do;
#include "../undef-macro.inc"
}
void test_return() {
#include "../def-macro.inc"
    return;
#include "../undef-macro.inc"
}
void test_break() {
#include "../def-macro.inc"
    break;
#include "../undef-macro.inc"
}
void test_continue() {
#include "../def-macro.inc"
    continue;
#include "../undef-macro.inc"
}

int main(int argc, char** argv) {
    std::string out_dir = argc <= 1 ? "." : argv[1];
    ofstream out((out_dir + "/project.json").c_str());
    for (auto func: {test_do, test_return, test_break, test_continue}) {
        try {
            func();
        } catch (const std::exception& e) {
            cout << e.what() << endl;
        }
    }
    cout << "OK" << endl;
    return 0;
}

