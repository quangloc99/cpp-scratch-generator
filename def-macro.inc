/**
* This file contains all macro/shorthand/magic for comfortably writing things
* in "C++"
*/
// must be in a function



using namespace CppScratchGenerator;



#define auto VariableHolder
#define var auto
#define dec_var(name, value) VariableHolder name(#name, value)

#define cin fake_cin
#define cout fake_cout

// vim: filetype=cpp
