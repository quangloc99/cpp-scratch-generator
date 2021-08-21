/**
* This file contains all macro/shorthand/magic for comfortably writing things
* in "C++"
*/

#define var VariableHolder
#define auto VariableHolder
#define dec_var(name, value) VariableHolder name(#name, value)

#define cin fake_cin

// vim: filetype=cpp
