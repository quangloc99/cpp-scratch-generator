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

int main(int argc, char** argv) {
    std::string out_folder = argc == 1 ? "." : argv[1];
    out_folder += "/";
    gen_to_file(out_folder + "default-cin-prompt.json", out_folder + "default-cin-prompt.sb3");
    CppScratchGenerator::FakeIstream::prompt_format = "Enter %s please! "; 
    gen_to_file(out_folder + "cin-prompt-polite.json", out_folder + "cin-prompt-polite.sb3"); 
    CppScratchGenerator::FakeIstream::prompt_format = "read_token"; 
    gen_to_file(out_folder + "cin-prompt_read_token.json", out_folder + "default-cin_read_token.sb3"); 
    return 0;
}

