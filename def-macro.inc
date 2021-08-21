/**
* This file contains all macro/shorthand/magic for comfortably writing things
* in "C++"
*/

#define auto CppScratchGenerator::VariableHolder
#define var auto
#define dec_var(name, value) CppScratchGenerator::VariableHolder name(#name, value)

#define cin CppScratchGenerator::fake_cin
#define cout CppScratchGenerator::fake_cout

#define random CppScratchGenerator::random

// vim: filetype=cpp
