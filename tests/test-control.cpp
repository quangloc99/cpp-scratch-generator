#include <iostream>
#include <fstream>
#include "../cpp-scratch-generator.hpp"

using namespace std;

void my_program() {
#include "../def-macro.inc"
    dec_var(a, 1);
    dec_var(b, 10);
    
    if (a == 1) {
        cout << "Nice";
        if (a > b) {
            cout << "Nested";
            if (a + 10 > b) {
                cout << "More nested" ;
            }
        } else {
            a = a * 1000;
            cout << a;
            cout << "Else here";
        }
        if (length(a) == 10) {
            cout << "Still nesting";
        }
        cout << "Cool";
    } else {
        a = 2;
        cout << "Wow here is an else";
    }
    
    if (a == a) cout << "a == a"; else cout << "not a == a";
    if (a != a) cout << "a != a"; else cout << "not a != a";
    if (a > a) cout << "a > a"; else cout << "not a > a";
    if (a < a) cout << "a < a"; else cout << "not a < a";
    if (a >= a) cout << "a >= a"; else cout << "not a >= a";
    if (a <= a) cout << "a <= a"; else cout << "not a <= a";
    
    if (a > 1) {
    } else {
        cout << "Blank substack";
    }
    
    if (a < 1) {
        cout << "Blank substack 2";
    } else ;
    
    repeat(11) {
        cout << "Hello";
    }
    
    repeat(a) {
        cout << "Hi";
    }
    
    repeat(a)
        repeat(a) {
            cout << "Bye";
        }
    
    dec_var(i, 0);
    
    repeat(a) {
        i = i + 1;
        if (i % 2 == 1) {
            cout << i;
        }
    }
    
    repeat_until(a == i) {
        cout << "a is still not b";
    }
    
    repeat_until(a > i) {
        repeat_until(a < i) {
            repeat_until(a == i) {
                repeat_until(a != i) {
                    cout << "WHAT";
                }
            }
        }
    }
    
    while (a >= i) {
        while (a <= i) {
            while (a != i) {
                while (a == i) {
                    cout << "AGAIN???";
                }
            }
        }
    }
    
    
    cout << "OK";
    
#include "../undef-macro.inc"
}

int main(int argc, char** argv) {
    std::string out_dir = argc <= 1 ? "." : argv[1];
    ofstream out((out_dir + "/project.json").c_str());
    CppScratchGenerator::generate_project_json(out, my_program);
    return 0;
}
