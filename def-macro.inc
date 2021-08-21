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
#define dec_var(name, ...) VariableHolder name(#name, ##__VA_ARGS__)

#define list CppScratchGenerator::ListHolder
#define dec_list(name, ...) list name(#name, ##__VA_ARGS__)

#define cin fake_cin
#define cout fake_cout


#define if(condition) \
    for (CppScratchGenerator::IfBlockGenerator __CSG_UNIQUE_NAME(ibg)(condition); \
        __CSG_UNIQUE_NAME(ibg).check_collecting(); )
        
#define else \
    for (CppScratchGenerator::ElseBlockGenerator __CSG_UNIQUE_NAME(ebg); \
        __CSG_UNIQUE_NAME(ebg).check_collecting(); )
        
#define repeat(times) \
    for (CppScratchGenerator::RepeatBlockGenerator __CSG_UNIQUE_NAME(rbg)(times); \
        __CSG_UNIQUE_NAME(rbg).check_collecting(); )
        
#define repeat_until(condition) \
    for (CppScratchGenerator::RepeatUntilBlockGenerator __CSG_UNIQUE_NAME(rubg)(condition); \
        __CSG_UNIQUE_NAME(rubg).check_collecting(); )
        
#define while(condition) repeat_until(!(condition))

#define return assert(("return is not supported in CppScratchGenerator", false))
#define continue assert(("continue is not supported in CppScratchGenerator", false))
#define break assert(("break is not supported in CppScratchGenerator", false))

// vim: filetype=cpp
