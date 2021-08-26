#include <iostream>
#include <fstream>
#include <string>
#include "../cpp-scratch-generator.hpp"

using namespace std;

void my_program() {
#include "../def-macro.inc"
    auto a = 0;
    dec_var(b, ""); 
    dec_var(very_long_variable_name, ""); 
    dec_var(foo, ""); 
    dec_var(bar, ""); 
    
    cin >> a >> b >> very_long_variable_name >> foo >> bar; 
#include "../undef-macro.inc"
}

void gen_to_file(const std::string& json_fname, const std::string& zip_fname) {
    ofstream out(json_fname.c_str());
    CppScratchGenerator::generate_project_json(out, my_program);
    out.close();
    system(("cp " + json_fname + " project.json").c_str());
    system(("zip " + zip_fname + " project.json").c_str());
    system("rm project.json");
}

int main() {
    gen_to_file("default-cin-prompt.json", "default-cin-prompt.sb3");
    CppScratchGenerator::FakeIstream::prompt_format = "Enter %s please! "; 
    gen_to_file("cin-prompt-polite.json", "cin-prompt-polite.sb3"); 
    CppScratchGenerator::FakeIstream::prompt_format = "read_token"; 
    gen_to_file("cin-prompt_read_token.json", "default-cin_read_token.sb3"); 
    return 0;
}

