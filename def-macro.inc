/**
* This file contains all macro/shorthand/magic for comfortably writing things
* in "C++"
*/

#include<functional>
#include<exception>

// https://github.com/swansontec/map-macro/blob/master/map.h 
/*
 * Created by William Swanson in 2012.
 *
 * I, William Swanson, dedicate this work to the public domain.
 * I waive all rights to the work worldwide under copyright law,
 * including all related and neighboring rights,
 * to the extent allowed by law.
 *
 * You can copy, modify, distribute and perform the work,
 * even for commercial purposes, all without asking permission.
 */

#ifndef MAP_H_INCLUDED
#define MAP_H_INCLUDED

#define EVAL0(...) __VA_ARGS__
#define EVAL1(...) EVAL0(EVAL0(EVAL0(__VA_ARGS__)))
#define EVAL2(...) EVAL1(EVAL1(EVAL1(__VA_ARGS__)))
#define EVAL3(...) EVAL2(EVAL2(EVAL2(__VA_ARGS__)))
#define EVAL4(...) EVAL3(EVAL3(EVAL3(__VA_ARGS__)))
#define EVAL(...)  EVAL4(EVAL4(EVAL4(__VA_ARGS__)))

#define MAP_END(...)
#define MAP_OUT
#define MAP_COMMA ,

#define MAP_GET_END2() 0, MAP_END
#define MAP_GET_END1(...) MAP_GET_END2
#define MAP_GET_END(...) MAP_GET_END1
#define MAP_NEXT0(test, next, ...) next MAP_OUT
#define MAP_NEXT1(test, next) MAP_NEXT0(test, next, 0)
#define MAP_NEXT(test, next)  MAP_NEXT1(MAP_GET_END test, next)

#define MAP0(f, x, peek, ...) f(x) MAP_NEXT(peek, MAP1)(f, peek, __VA_ARGS__)
#define MAP1(f, x, peek, ...) f(x) MAP_NEXT(peek, MAP0)(f, peek, __VA_ARGS__)

#define MAP_LIST_NEXT1(test, next) MAP_NEXT0(test, MAP_COMMA next, 0)
#define MAP_LIST_NEXT(test, next)  MAP_LIST_NEXT1(MAP_GET_END test, next)

#define MAP_LIST0(f, x, peek, ...) f(x) MAP_LIST_NEXT(peek, MAP_LIST1)(f, peek, __VA_ARGS__)
#define MAP_LIST1(f, x, peek, ...) f(x) MAP_LIST_NEXT(peek, MAP_LIST0)(f, peek, __VA_ARGS__)

/**
 * Applies the function macro `f` to each of the remaining parameters.
 */
#define MAP(f, ...) EVAL(MAP1(f, __VA_ARGS__, ()()(), ()()(), ()()(), 0))

/**
 * Applies the function macro `f` to each of the remaining parameters and
 * inserts commas between the results.
 */
#define MAP_LIST(f, ...) EVAL(MAP_LIST1(f, __VA_ARGS__, ()()(), ()()(), ()()(), 0))

#endif



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
#define do assert(("do is not supported in CppScratchGenerator", false))


#define procedure(name, ...) \
    class procedure ## name {                                                                   \
        CppScratchGenerator::BlockHolder proc_proto, proc_def;                                  \
        bool body_set;                                                                          \
    public:                                                                                     \
        procedure ## name()                                                                     \
            : proc_proto(Opcode::Procedures::Prototype, Block::Type::CONTROL, false, false)     \
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
                .p("proccode").sv(#name)                                                        \
                .p("argumentids").sv("[]")                                                      \
                .p("argumentnames").sv("[]")                                                    \
                .p("argumentdefaults").sv("[]")                                                 \
                .p("warp").sv("false")                                                          \
            .end();                                                                             \
        }                                                                                       \
        void operator=(const std::function<void()>& gen_body) {                                 \
            CppScratchGenerator::throw_if(                                                      \
                body_set, std::invalid_argument("must not set procedure's body twice")          \
            );                                                                                  \
            gen_body();                                                                         \
            CppScratchGenerator::BlockHolder::pop_stack_til<true>(proc_def.id());               \
            CppScratchGenerator::BlockHolder::block_holder_stack.pop_back();                    \
        }                                                                                       \
        void operator()() {                                                                     \
        }                                                                                       \
    } name;                                                                                     \
    name = [&]()  /* expecting the user to use braces to define the body  */

// vim: filetype=cpp
