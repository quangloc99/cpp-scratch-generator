#include <iostream>
#include <fstream>
#include "../cpp-scratch-generator.hpp"

using namespace std;

void my_program() {
#include "../def-macro.inc"
    dec_var(n, 0);
    cin >> n;
    
    dec_var(ans, 0);
    dec_var(x, 1);
    repeat(11) {
        // cout << join("x = ", x); 
        auto i = 0;
        i = 0;
        repeat(9) {
            i += 1;
            // cout << join("i * x = ", i * x); 
            // cout << join("n = ", n); 
            if (i * x <= n) {
                // cout << join("i = ", i); 
                // cout << join("x = ", x); 
                ans += 1;
            }
        }
        x = x * 10 + 1;
    }
    cout << ans;
    
#include "../undef-macro.inc"
}

int main() {
    ofstream out("project.json");
    try { 
        CppScratchGenerator::generate_project_json(out, my_program);
    } catch (const std::exception& e) { 
        cout << "=== ERROR ===" << endl << e.what() << endl; 
    } 
    return 0;
}

