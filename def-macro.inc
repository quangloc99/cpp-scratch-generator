/**
* This file contains all macro/shorthand/magic for comfortably writing things
* in "C++"
*/

#include<functional>
#include<exception>

// https://newbedev.com/is-it-possible-to-iterate-over-arguments-in-variadic-macros 
#ifndef __FOREACH_MACROS__
#define __FOREACH_MACROS__

// Make a FOREACH macro
#define GET_MACRO(_0,_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,_15,_16,NAME,...) NAME 

  
#define FE_0(WHAT, data, sep)
#define FE_1(WHAT, data, sep, X) WHAT(data, X) 
#define FE_2(WHAT, data, sep, X, ...) WHAT(data, X)sep FE_1(WHAT, data, sep, __VA_ARGS__)
#define FE_3(WHAT, data, sep, X, ...) WHAT(data, X)sep FE_2(WHAT, data, sep, __VA_ARGS__)
#define FE_4(WHAT, data, sep, X, ...) WHAT(data, X)sep FE_3(WHAT, data, sep, __VA_ARGS__)
#define FE_5(WHAT, data, sep, X, ...) WHAT(data, X)sep FE_4(WHAT, data, sep, __VA_ARGS__)
#define FE_6(WHAT, data, sep, X, ...) WHAT(data, X)sep FE_5(WHAT, data, sep, __VA_ARGS__)
#define FE_7(WHAT, data, sep, X, ...) WHAT(data, X)sep FE_6(WHAT, data, sep, __VA_ARGS__)
#define FE_8(WHAT, data, sep, X, ...) WHAT(data, X)sep FE_7(WHAT, data, sep, __VA_ARGS__)
#define FE_9(WHAT, data, sep, X, ...) WHAT(data, X)sep FE_8(WHAT, data, sep, __VA_ARGS__)
#define FE_10(WHAT, data, sep, X, ...) WHAT(data, X)sep FE_9(WHAT, data, sep, __VA_ARGS__)
#define FE_11(WHAT, data, sep, X, ...) WHAT(data, X)sep FE_10(WHAT, data, sep, __VA_ARGS__)
#define FE_12(WHAT, data, sep, X, ...) WHAT(data, X)sep FE_11(WHAT, data, sep, __VA_ARGS__)
#define FE_13(WHAT, data, sep, X, ...) WHAT(data, X)sep FE_12(WHAT, data, sep, __VA_ARGS__)
#define FE_14(WHAT, data, sep, X, ...) WHAT(data, X)sep FE_13(WHAT, data, sep, __VA_ARGS__)
#define FE_15(WHAT, data, sep, X, ...) WHAT(data, X)sep FE_14(WHAT, data, sep, __VA_ARGS__)
#define FE_16(WHAT, data, sep, X, ...) WHAT(data, X)sep FE_15(WHAT, data, sep, __VA_ARGS__)
//... repeat as needed

#define FOR_EACH(action, data, separator,...) \
  GET_MACRO(_0,##__VA_ARGS__,FE_16,FE_15,FE_14,FE_13,FE_12,FE_11,FE_10,FE_9,FE_8,FE_7,FE_6,FE_5,FE_4,FE_3,FE_2,FE_1,FE_0)(action, data, separator,##__VA_ARGS__)

#define FE_COMMA_0(WHAT, data)
#define FE_COMMA_1(WHAT, data, X) WHAT(data, X) 
#define FE_COMMA_2(WHAT, data, X, ...) WHAT(data, X), FE_COMMA_1(WHAT, data, __VA_ARGS__)
#define FE_COMMA_3(WHAT, data, X, ...) WHAT(data, X), FE_COMMA_2(WHAT, data, __VA_ARGS__)
#define FE_COMMA_4(WHAT, data, X, ...) WHAT(data, X), FE_COMMA_3(WHAT, data, __VA_ARGS__)
#define FE_COMMA_5(WHAT, data, X, ...) WHAT(data, X), FE_COMMA_4(WHAT, data, __VA_ARGS__)
#define FE_COMMA_6(WHAT, data, X, ...) WHAT(data, X), FE_COMMA_5(WHAT, data, __VA_ARGS__)
#define FE_COMMA_7(WHAT, data, X, ...) WHAT(data, X), FE_COMMA_6(WHAT, data, __VA_ARGS__)
#define FE_COMMA_8(WHAT, data, X, ...) WHAT(data, X), FE_COMMA_7(WHAT, data, __VA_ARGS__)
#define FE_COMMA_9(WHAT, data, X, ...) WHAT(data, X), FE_COMMA_8(WHAT, data, __VA_ARGS__)
#define FE_COMMA_10(WHAT, data, X, ...) WHAT(data, X), FE_COMMA_9(WHAT, data, __VA_ARGS__)
#define FE_COMMA_11(WHAT, data, X, ...) WHAT(data, X), FE_COMMA_10(WHAT, data, __VA_ARGS__)
#define FE_COMMA_12(WHAT, data, X, ...) WHAT(data, X), FE_COMMA_11(WHAT, data, __VA_ARGS__)
#define FE_COMMA_13(WHAT, data, X, ...) WHAT(data, X), FE_COMMA_12(WHAT, data, __VA_ARGS__)
#define FE_COMMA_14(WHAT, data, X, ...) WHAT(data, X), FE_COMMA_13(WHAT, data, __VA_ARGS__)
#define FE_COMMA_15(WHAT, data, X, ...) WHAT(data, X), FE_COMMA_14(WHAT, data, __VA_ARGS__)
#define FE_COMMA_16(WHAT, data, X, ...) WHAT(data, X), FE_COMMA_15(WHAT, data, __VA_ARGS__)
//... repeat as needed

#define FOR_EACH_COMMA(action, data, ...) \
  GET_MACRO(_0,##__VA_ARGS__,FE_COMMA_16,FE_COMMA_15,FE_COMMA_14,FE_COMMA_13,FE_COMMA_12,FE_COMMA_11,FE_COMMA_10,FE_COMMA_9,FE_COMMA_8,FE_COMMA_7,FE_COMMA_6,FE_COMMA_5,FE_COMMA_4,FE_COMMA_3,FE_COMMA_2,FE_COMMA_1,FE_COMMA_0)(action, data, ##__VA_ARGS__)
#endif



using namespace CppScratchGenerator;

#define __CSG_CONCAT(a, b) __CSG_CONCAT_INNER(a, b)
#define __CSG_CONCAT_INNER(a, b) a ## b

#define __CSG_UNIQUE_NAME(base) __CSG_CONCAT(base, __LINE__)
#define __CSG_STR0(x) #x
#define __CSG_STR(x) __CSG_STR0(x)

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

#define do          CppScratchGenerator::throw_if(true, std::logic_error("`do` keyword is not supported in CppScratchGenerator"))
#define return      CppScratchGenerator::throw_if(true, std::logic_error("`return` keyword is not supported in CppScratchGenerator"))
#define continue    CppScratchGenerator::throw_if(true, std::logic_error("`continue` keyword is not supported in CppScratchGenerator"))
#define break       CppScratchGenerator::throw_if(true, std::logic_error("`break` keyword is not supported in CppScratchGenerator"))


#define __procedure_arg_proccode(_, x) " %s"
#define __procedure_arg_id(proc_name, x) #proc_name "#arg_" #x 
#define __procedure_arg_id_quoted(proc_name, x) "\\\"" __procedure_arg_id(proc_name, x) "\\\""
#define __procedure_arg_name(_, x) "\\\""#x"\\\""
#define __procedure_arg_default(_, x) "\\\"\\\""

#define __procedure_arg_lambda_arg(_, x) const CppScratchGenerator::ProcedureArgument& x
#define __procedure_arg_lambda_passing_arg(_, x) CppScratchGenerator::ProcedureArgument(#x)

#define __procedure_arg_call_arg(_, x) const CppScratchGenerator::Operand& x
#define __procedure_arg_call_check(_, x) \
    CppScratchGenerator::throw_if(                                              \
        x.get_value_type() != CppScratchGenerator::Operand::ValueType::SCALAR,  \
        std::invalid_argument("Argument for procedure should be scalar")        \
    )
#define __procedure_arg_call_mount(name, x) {__procedure_arg_id(name, x), x.to_input() }
    
#define __procedure_arg_init_block(name, x) \
    {__procedure_arg_id(name, x), CppScratchGenerator::BlockInput::noshadow_id(     \
            CppScratchGenerator::BlockHolder(                                       \
                CppScratchGenerator::Opcode::Procedures::ScalarArgumentReporter,    \
                {}, {{"VALUE", {#x}}},                                              \
                CppScratchGenerator::Block::Type::SCALAR_EXPRESSION,                \
                false, false                                                        \
            ).id()                                                                  \
    ) }
    

#define procedure(name, ...) \
    class procedure_ ## name {                                                                  \
        CppScratchGenerator::BlockHolder proc_proto, proc_def;                                  \
        bool body_set;                                                                          \
    public:                                                                                     \
        procedure_ ## name()                                                                    \
            : proc_proto(Opcode::Procedures::Prototype, {                                       \
                    FOR_EACH_COMMA(__procedure_arg_init_block, name, ##__VA_ARGS__)             \
            }, {}, Block::Type::CONTROL, false, false)                                          \
            , proc_def(Opcode::Procedures::Definition, { {"custom_block",                       \
                        CppScratchGenerator::BlockInput::noshadow_id(proc_proto.id())}          \
                }, {}, Block::Type::CONTROL, true, false)                                       \
            , body_set(0)                                                                       \
        {                                                                                       \
            proc_proto->write_additional = write_mutation;                                      \
        }                                                                                       \
        static void write_mutation(CppScratchGenerator::StupidJsonWriter& json_writer) {        \
            json_writer.p("mutation").obj_begin()                                               \
                .p("tagName").sv("mutation")                                                    \
                .p("children").arr_begin().end()                                                \
                .p("proccode").sv(                                                              \
                    #name FOR_EACH(__procedure_arg_proccode,,, ##__VA_ARGS__)                   \
                )                                                                               \
                .p("argumentids").sv(                                                           \
                    "[" FOR_EACH(__procedure_arg_id_quoted, name, ",", ##__VA_ARGS__) "]"       \
                )                                                                               \
                .p("argumentnames").sv(                                                         \
                    "[" FOR_EACH(__procedure_arg_name,, ",", ##__VA_ARGS__) "]"                 \
                )                                                                               \
                .p("argumentdefaults").sv(                                                      \
                    "[" FOR_EACH(__procedure_arg_default,, ",", ##__VA_ARGS__) "]"              \
                )                                                                               \
                .p("warp").sv("false")                                                          \
            .end();                                                                             \
        }                                                                                       \
        void operator=(const std::function<void(                                                \
                FOR_EACH_COMMA(__procedure_arg_lambda_arg,, ##__VA_ARGS__)                      \
        )>& gen_body) {                                                                         \
            CppScratchGenerator::throw_if(                                                      \
                body_set, std::invalid_argument("must not set procedure's body twice")          \
            );                                                                                  \
            gen_body(                                                                           \
                FOR_EACH_COMMA(__procedure_arg_lambda_passing_arg,, ##__VA_ARGS__)              \
            );                                                                                  \
            CppScratchGenerator::BlockHolder::pop_stack_til<true>(proc_def.id());               \
            CppScratchGenerator::BlockHolder::block_holder_stack.pop_back();                    \
        }                                                                                       \
        void operator()(FOR_EACH_COMMA(__procedure_arg_call_arg,, ##__VA_ARGS__)) {             \
            /*std::cerr << "calling " << #name << endl;*/                                       \
            FOR_EACH(__procedure_arg_call_check,,;,##__VA_ARGS__);                              \
            CppScratchGenerator::BlockHolder call_block(                                        \
                CppScratchGenerator::Opcode::Procedures::Call, {                                \
                    FOR_EACH_COMMA(__procedure_arg_call_mount, name, ##__VA_ARGS__)             \
                }, {}, CppScratchGenerator::Block::Type::CONTROL, true, true);                  \
            call_block->write_additional = write_mutation;                                      \
        }                                                                                       \
    } name;                                                                                     \
    name = [&](                                                                                 \
                FOR_EACH_COMMA(__procedure_arg_lambda_arg,, ##__VA_ARGS__)                      \
    )  /* expecting the user to use braces to define the body  */

// vim: filetype=cpp
