#include <iostream>
#include <fstream>
#include "../cpp-scratch-generator.hpp"

using namespace std;

void my_program() {
#include "../def-macro.inc"
    var x;
    var y;
    list a;
    list b = {1, 2, 3};
    list c = {"a", "b", "c"};
    
    dec_list (d, {10, 20, 30});
    dec_list (t);
    
    a.push_back("a");
    b.push_back("b");
    c.push_back("c");
    d.push_back("d");
    
    a.clear();
    d.clear();
    
    a.push_back(x);
    b.push_back(y);
    c.erase_at(1);
    d.erase_at(x + y);
    
    a.insert_at(x, y);
    a.insert_at(1, x);
    a.insert_at(y, 200);
    
    y = a.first_index_of(x); 
    cout << a.first_index_of(x) << a.first_index_of(y) << a.first_index_of(1); 
    if (b.contains(x)) { 
        cout << "B contains x"; 
    } 
    if (b.contains(100)) { 
        cout << "B contains 100"; 
    } 
    
    cout << (a.size() + b.size());
    cout << ((a.size() * b.size()) + x * y);
    
#include "../undef-macro.inc"
}

int main() {
    ofstream out("project.json");
    CppScratchGenerator::generate_project_json(out, my_program);
    return 0;
}
