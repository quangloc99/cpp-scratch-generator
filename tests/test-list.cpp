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
    
    cout << a[1];
    cout << a[2];
    cout << a[3];
    cout << d[2];
    cout << d[1] + a[2];
    cout << a[1] * b[2] + d[3] + c[4];
    a[1] = 1 + 2;
    a[1] = b[2];
    b[2] = a.size();
    a[x + y] = 100;
    a[x * x] = 434;
    
#include "../undef-macro.inc"
}

int main(int argc, char** argv) {
    std::string out_dir = argc <= 1 ? "." : argv[1];
    ofstream out((out_dir + "/project.json").c_str());
    CppScratchGenerator::generate_project_json(out, my_program);
    return 0;
}
