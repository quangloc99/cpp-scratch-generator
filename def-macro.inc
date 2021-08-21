/**
* This file contains all macro/shorthand/magic for comfortably writing things
* in "C++"
*/
// must be in a function



using namespace CppScratchGenerator;

#define __CSG_CONCAT(a, b) __CSG_CONCAT_INNER(a, b)
#define __CSG_CONCAT_INNER(a, b) a ## b

#define __CSG_UNIQUE_NAME(base) __CSG_CONCAT(base, __LINE__)

#define auto VariableHolder
#define var auto
#define dec_var(name, value) VariableHolder name(#name, value)

#define cin fake_cin
#define cout fake_cout


#define if(condition) \
    for (CppScratchGenerator::IfBlockGenerator __CSG_UNIQUE_NAME(ibg)(condition); \
        __CSG_UNIQUE_NAME(ibg).check_collecting(); )
        
#define else \
    for (CppScratchGenerator::ElseBlockGenerator __CSG_UNIQUE_NAME(ebg); \
        __CSG_UNIQUE_NAME(ebg).check_collecting(); )

// vim: filetype=cpp
