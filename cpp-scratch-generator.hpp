#pragma once

// This is sort of "proof of concept", so the functions in this file are meant
// to be used in competition.  If you want to use this file in production,
// consider making a folk and change this file into a real header and a real
// cpp source file.  I do made the functions in this file static/inline though,
// it should be ok to link.

#include <cassert>
#include <iostream>
#include <functional>
#include <vector>
#include <set>
#include <unordered_map>
#include <string>
#include <stdexcept>
#include <sstream>
#include <iomanip>
#include <ios>


namespace CppScratchGenerator {
    
    
namespace Opcode {
    namespace Control {
        const std::string If = "control_if";
        const std::string IfElse = "control_if_else";
        const std::string Repeat = "control_repeat";
        const std::string RepeatUntil = "control_repeat_until";
    }
    namespace Data {
        const std::string SetVariableTo = "data_setvariableto";
        const std::string ChangeVariableBy = "data_changevariableby";
    }
    namespace Operator {
        const std::string Add = "operator_add";
        const std::string Subtract = "operator_subtract";
        const std::string Multiply = "operator_multiply";
        const std::string Divide = "operator_divide";
        const std::string Mod = "operator_mod";
        
        const std::string Gt = "operator_gt";
        const std::string Lt = "operator_lt";
        const std::string Equals = "operator_equals";
        const std::string Not = "operator_not";
        
        const std::string And = "operator_and";
        const std::string Or = "operator_or";
        
        const std::string Join = "operator_join";
        const std::string LetterOf = "operator_letter_of";
        const std::string Length = "operator_length";
        const std::string Contains = "operator_contains";
        const std::string Round = "operator_round";
        const std::string Mathop = "operator_mathop";
        const std::string Random = "operator_random";
        
        namespace MathOp {
            const std::string ABS = "abs";
            const std::string FLOOR = "floor";
            const std::string CEILING = "ceiling";
            const std::string SQRT = "sqrt";
            const std::string SIN = "sin";
            const std::string COS = "cos";
            const std::string TAN = "tan";
            const std::string ASIN = "asin";
            const std::string ACOS = "acos";
            const std::string ATAN = "atan";
            const std::string LN = "ln";
            const std::string LOG = "log";
            const std::string EXPE = "e ^";
            const std::string EXP10 = "10 ^";
        };
    }
    namespace Looks {
        const std::string Say = "looks_say";
    }
    namespace Event {
        const std::string WhenFlagClicked = "event_whenflagclicked";
    }
    namespace Sensing {
        const std::string AskAndWait = "sensing_askandwait";
        const std::string Answer = "sensing_answer";
    }
}

    
std::string double_to_string(double x) {
    static std::stringstream ss;
    ss.str("");
    ss << std::noshowpoint << x;
    return ss.str();
}
    
    
    
/**
 * A class for "more comfortable" writing json data.
 * 
 * This class does not really check validity.
 * It is created just for writing json easily, for example: no need to write
 * quoted string, adding colon, indentation...
 */
class StupidJsonWriter {
    struct Frame {
        enum Type { OBJECT, ARRAY };
        Type type;
        int item_count;
    };
    
    std::ostream& out;
    const std::string indent_string;
    std::vector<Frame> frames;
public:
    inline StupidJsonWriter(std::ostream& out_, const std::string& indent_str = "  ")
        : out(out_ << std::boolalpha)
        , indent_string(indent_str)
        { }
    
    inline StupidJsonWriter& writeIndent() {
        for (size_t i = 0; i < frames.size(); ++i) {
            out << indent_string;
        }
        return *this;
    }
    
    inline StupidJsonWriter& obj_begin() {
        check_array_indent();
        frames.push_back({Frame::Type::OBJECT, 0});
        out << "{";
        return *this;
    }
    
    inline StupidJsonWriter& arr_begin() {
        check_array_indent();
        frames.push_back({Frame::Type::ARRAY, 0});
        out << "[";
        return *this;
    }
    
    inline StupidJsonWriter& end() {
        out << std::endl;
        auto last = frames.back();
        frames.pop_back();
        writeIndent();
        if (last.type == Frame::Type::OBJECT) {
            out << "}";
        } else {
            out << "]";
        }
        inc_item_count();
        return *this;
    }
    
    inline StupidJsonWriter& p(const std::string& name) {  // property
        assert(frames.size() and frames.back().type == Frame::Type::OBJECT);
        if (frames.back().item_count > 0) {
            out << ",";
        }
        out << std::endl;
        writeIndent();
        out << '"' << name << '"' << ": ";
        return *this;
    }
    
    // write generic value, can be number, can be "null", or whatever
    template<class T>
    StupidJsonWriter& v(const T& value) {
        check_array_indent();
        out << value;
        inc_item_count();
        return *this;
    }
    
    // write a quoted string value
    StupidJsonWriter& sv(const std::string& value) {
        return v('"' + value + '"');
    }
private:
    inline void check_array_indent() {
        if (frames.size() and frames.back().type == Frame::Type::ARRAY) {
            if (frames.back().item_count > 0) {
                out << ",";
            }
            out << std::endl;
            writeIndent();
        }
    }
    inline void inc_item_count() {
        if (frames.size()) {
            ++frames.back().item_count;
        }
    }
};


// Act like a simple database.
// I just don't want to name it database tho.
template<class T>
class AutoGeneratedNamedMap {
public:
    using map_type = std::unordered_map<std::string, T>;
    using value_type = typename map_type::value_type;
    using iterator = typename map_type::iterator;
    using const_iterator = typename map_type::const_iterator;
private:
    size_t auto_inc_key;
    std::string key_prefix;
    map_type mp;
public:
    AutoGeneratedNamedMap(std::string key_prefix_ = "")
        : auto_inc_key(0), key_prefix(key_prefix_) {}
    
    iterator insert(const T& u) {
        auto res = mp.emplace(generate_key(), u);
        assert(res.second);
        return res.first;
    }
    
    template <class... Args>
    iterator emplace(Args&&... args) {
        auto res = mp.emplace(std::piecewise_construct,
              std::forward_as_tuple(generate_key()),
              std::forward_as_tuple(args...)
              );
        assert(res.second);
        return res.first;
    }
    
    iterator register_value(const std::string& name, const T& u) {
        auto res = mp.emplace(name, u);
        if (!res.second) {
            throw std::invalid_argument('"' + name + '"' + " is already a key in the map. Use a different key.");
        }
        return res.first;
    }
    
    const_iterator find(const std::string& key) const {
        return mp.find(key);
    }
    iterator find(const std::string& key) {
        return mp.find(key);
    }
    
    void clear() {
        auto_inc_key = 0;
        mp.clear();
    }
    
    iterator begin() {
        return mp.begin();
    }
    iterator end() {
        return mp.end();
    }
    const_iterator begin() const {
        return mp.begin();
    }
    const_iterator end() const {
        return mp.end();
    }
    const_iterator cbegin() {
        return mp.cbegin();
    }
    const_iterator cend() {
        return mp.cend();
    }
private:
    std::string generate_key() {
        std::string cur_key;
        do {
            cur_key = key_prefix + std::to_string(auto_inc_key++);
        } while (mp.count(cur_key));
        return cur_key;
    }
};




class BlockInput {
public:
    enum ShadowType {
        // https://github.com/LLK/scratch-vm/blob/develop/src/serialization/sb3.js#L39-L41 
        INPUT_SAME_BLOCK_SHADOW = 1, // unobscured shadow
        // INPUT_BLOCK_NO_SHADOW = 2, // no shadow   // this type is not useful
                                                     // and seems like it will
                                                     // never be used.
                                                     // It is because it disable
                                                     // the ability to overwrite
                                                     // value if we want to remove
                                                     // the already made elements.
        INPUT_DIFF_BLOCK_SHADOW = 3, // obscured shadow
    };
    enum InputType {
        // Based on the table described here
        // https://en.scratch-wiki.info/wiki/Scratch_File_Format#Monitors 
        // the commented ones are not supported here
        ID = -1,  // this is the plain ID
        NUMBER = 4,
        // POSITIVE_NUMBER = 5, 
        // POSITIVE_INTEGER = 6, 
        // INTEGER = 7, 
        // ANGLE = 8, 
        // COLOR = 9, 
        STRING = 10,
        // BROADCAST = 11, 
        VARIABLE = 12,
        LIST = 13,
    };
    
    InputType type;
    std::string value;  // for the case of number, it will be casted to string.
    
    BlockInput(InputType type_, const std::string& value_)
        : type(type_)
        , value(value_)
    {}
    
    // Util functions in order not to add more keystrokes like InputType::*
    static BlockInput id(const std::string& value) {
        return BlockInput(InputType::ID, value);
    }
    static BlockInput number(const std::string& value) {
        return BlockInput(InputType::NUMBER, value);
    }
    static BlockInput number(double value) {
        return BlockInput(InputType::NUMBER, double_to_string(value));
    }
    static BlockInput string(const std::string& value) {
        return BlockInput(InputType::STRING, value);
    }
    static BlockInput variable(const std::string& value) {
        return BlockInput(InputType::VARIABLE, value);
    }
    static BlockInput list(const std::string& value) {
        return BlockInput(InputType::LIST, value);
    }
    
    bool is_scalar() const {
        return type == InputType::NUMBER || type == InputType::STRING;
    }
    
    StupidJsonWriter& write_json(StupidJsonWriter& json_writer) const {
        bool is_scalar_ = is_scalar();
        json_writer.arr_begin()
            .v(is_scalar_
                    ? ShadowType::INPUT_SAME_BLOCK_SHADOW 
                    : ShadowType::INPUT_DIFF_BLOCK_SHADOW
            );
            if (type == InputType::ID) {
                json_writer.sv(value);
            } else {
                json_writer.arr_begin().v(type).sv(value);
                if (type == InputType::VARIABLE || type == InputType::LIST) {
                    json_writer.sv(value);  // because the name is the same as id
                }
                json_writer.end();
            }
            if (!is_scalar_) {
                json_writer.arr_begin().v(InputType::STRING).sv("0").end();
            }
        return json_writer.end();
    }
};

// fields are just array of string, so meh
using BlockField = std::vector<std::string>;



class Block {
public:
    enum Type {
        CONTROL,
        BOOLEAN_EXPRESSION,
        SCALAR_EXPRESSION
    };
    
    std::string opcode;
    Type type;
    std::string next, parent;
    std::unordered_map<std::string, BlockInput> inputs;
    std::unordered_map<std::string, BlockField> fields;
    
    inline Block(const std::string& opcode_, Type type_ = Type::CONTROL)
        : opcode(opcode_)
        , type(type_)
    { }
    
    inline bool is_top_level() const {
        return parent.empty();
    }
    
    inline void write_json(StupidJsonWriter& json_writer) const {
        json_writer.obj_begin();
        json_writer.p("opcode").sv(opcode);
        json_writer.p("next");
        if (next.empty()) {
            json_writer.v("null");
        } else {
            json_writer.sv(next);
        }
        json_writer.p("parent");
        if (parent.empty()) {
            json_writer.v("null");
        } else {
            json_writer.sv(parent);
        }
        
        json_writer.p("inputs").obj_begin();
        for (const auto& it: inputs) {  
            json_writer.p(it.first);  
            it.second.write_json(json_writer);  
        }  
        json_writer.end();
        json_writer.p("fields").obj_begin();
        for (const auto& it: fields) { 
            json_writer.p(it.first).arr_begin(); 
            for (const auto& x: it.second) { 
                json_writer.sv(x); 
            } 
            json_writer.end(); 
        } 
        json_writer.end();
        json_writer.p("shadow").v(false);
        
        if (is_top_level()) {
            json_writer
                .p("topLevel").v(true)
                // we don't really care about the position
                .p("x").v(0)
                .p("y").v(0);
        }
        json_writer.end();
    }
};


AutoGeneratedNamedMap<Block> __block_map("block_");

class BlockHolder {
    AutoGeneratedNamedMap<Block>::iterator it;
public:
    static std::vector<BlockHolder> block_holder_stack;
    static std::string pop_stack_til(const std::string& id) {
        std::string res;
        while (true) {
            assert(!block_holder_stack.empty());
            auto last_id = block_holder_stack.back().id();
            if (last_id == id) {
                break;
            }
            res = last_id;
            block_holder_stack.pop_back();
        }
        block_holder_stack.back()->next = "";
        return res;
    }
    static void make_substack(BlockHolder& block_holder, const std::string& substack_name) {
        auto last = pop_stack_til(block_holder.id());
        if (!last.empty()) {
            block_holder->inputs.emplace(substack_name, BlockInput::id(last));
        }
    }
    
    BlockHolder() = default;
    
    BlockHolder(
            const std::string& opcode,
            Block::Type type = Block::Type::CONTROL,
            bool push_to_stack = true,
            bool do_linking = true
    ) : it(__block_map.emplace(opcode, type))
    {
        if (do_linking and !block_holder_stack.empty()) {
            auto& last = block_holder_stack.back();
            last->next = id();
            operator*().parent = last.id();
        }
        if (push_to_stack) {
            block_holder_stack.push_back(*this);
        }
    }
    
    BlockHolder(
            const std::string& opcode,
            const std::unordered_map<std::string, BlockInput>& inputs,
            const std::unordered_map<std::string, BlockField>& fields,
            Block::Type type = Block::Type::CONTROL,
            bool push_to_stack = true,
            bool do_linking = true
    ) : BlockHolder(opcode, type, push_to_stack, do_linking) {
        operator*().inputs = inputs;
        operator*().fields = fields;
        for (const auto & inp_it: inputs) {
            if (inp_it.second.type == BlockInput::InputType::ID) {
                auto block_it = __block_map.find(inp_it.second.value);
                assert(block_it != __block_map.end());
                block_it->second.parent = id();
            }
        }
    }
    
    const std::string& id() const {
        return it->first;
    }
    
    Block& operator*() { 
        return it->second; 
    } 
    const Block& operator*() const { 
        return it->second; 
    } 
    Block* operator->() const { 
        return &it->second; 
    } 
};

std::vector<BlockHolder> BlockHolder::block_holder_stack;



class Variable { 
public: 
    std::string name; 
    std::string value; 
    inline Variable() = default;  
    inline Variable(const std::string& name_, const std::string& value_)  
        : name(name_)  
        , value(value_)  
    {}  
    
    inline Variable(const std::string name_, double double_value_)  
        : name(name_)  
        , value(double_to_string(double_value_))
    {}  
}; 

AutoGeneratedNamedMap<Variable> __variable_map("var_");


class Operand;

class VariableHolder { 
    AutoGeneratedNamedMap<Variable>::iterator it; 
public:  
    inline VariableHolder(const std::string& name_, const std::string& value_) 
        : it(__variable_map.register_value(name_, Variable(name_, value_))) 
    { } 
    inline VariableHolder(const std::string& name_, double value_) 
        : it(__variable_map.register_value(name_, Variable(name_, value_))) 
    {} 
    
    inline VariableHolder(const std::string& value_) 
        : it(__variable_map.emplace("", value_))
    { 
        it->second.name = it->first; 
    } 
    inline VariableHolder(const char*  value_) 
        : it(__variable_map.emplace("", value_))
    { 
        it->second.name = it->first; 
    } 
    
    inline VariableHolder(double value_) 
        : it(__variable_map.emplace("", value_))
    { 
        it->second.name = it->first; 
    } 
    
    inline VariableHolder(): VariableHolder("") {} 
    
    inline VariableHolder(int value_) 
        : VariableHolder((double)value_) {} 
    inline VariableHolder(long long value_) 
        : VariableHolder((double)value_) {} 
    inline VariableHolder(float value_) 
        : VariableHolder((double)value_) {} 
    
    inline VariableHolder(const std::string& name_, int value_) 
        : VariableHolder(name_, (double)value_) {} 
    inline VariableHolder(const std::string& name_, long long value_) 
        : VariableHolder(name_, (double)value_) {} 
    inline VariableHolder(const std::string& name_, float value_) 
        : VariableHolder(name_, (double)value_) {} 
    
    const std::string& key() const { 
        return it->first; 
    } 
    Variable& operator*() { 
        return it->second; 
    } 
    const Variable& operator*() const { 
        return it->second; 
    } 
    Variable* operator->() const { 
        return &it->second; 
    } 
    BlockField to_field() const {
        return {key(), key()};  // the name and the id. In this code, they are the same.
    }
    
    
    // magic operator
    //all operator= return void in order not to have chain assignement.
    void operator=(const VariableHolder& other) {
        BlockHolder(Opcode::Data::SetVariableTo, {
                {"VALUE", BlockInput::variable(other.key())}
        }, {
                {"VARIABLE", to_field()}
        });
    }
    
    void operator=(const std::string& s) {
        BlockHolder(Opcode::Data::SetVariableTo, {
                {"VALUE", BlockInput::string(s) }
        }, {
                {"VARIABLE", to_field()}
        });
    }
    
    void operator=(const char* s) {
        BlockHolder(Opcode::Data::SetVariableTo, {
                {"VALUE", BlockInput::string(s) }
        }, {
                {"VARIABLE", to_field()}
        });
    }
    
    void operator=(double num) {
        BlockHolder(Opcode::Data::SetVariableTo, {
                {"VALUE", BlockInput::number(num) }
        }, {
                {"VARIABLE", to_field()}
        });
    }
    
    void operator=(const BlockHolder& other) {
        if (other->type != Block::Type::SCALAR_EXPRESSION) {
            throw std::logic_error("only scalar expression can be assigned to variable");
        }
        BlockHolder(Opcode::Data::SetVariableTo, {
                {"VALUE", BlockInput::id(other.id()) }
        }, {
                {"VARIABLE", to_field()}
        });
    }
    
    void operator+=(const Operand& operand);
    void operator-=(const Operand& operand);
}; 



class List { 
public: 
    std::string name; 
    std::vector<std::string> value; 
    inline List() = default;  
    inline List(const std::string& name_) : name(name_) {}
    inline List(const std::string& name_, std::initializer_list<std::string> value_) 
        : name(name_)
        , value(value_)  
    {}  
    
    inline List(const std::string name_, std::initializer_list<double> double_value_)  
        : name(name_)  
    {
        for (auto it: double_value_) {
            value.push_back(double_to_string(it));
        }
    } 
}; 

AutoGeneratedNamedMap<List> __list_map("list_");


class ListHolder { 
    AutoGeneratedNamedMap<List>::iterator it; 
public:  
    inline ListHolder(const std::string& name_, std::initializer_list<std::string> value_) 
        : it(__list_map.register_value(name_, List(name_, value_))) 
    { } 
    inline ListHolder(const std::string& name_, std::initializer_list<double> value_)
        : it(__list_map.register_value(name_, List(name_, value_))) 
    {} 
    inline ListHolder(const std::string& name_)
        : it(__list_map.register_value(name_, List(name_)))
    {}
    
    inline ListHolder(std::initializer_list<std::string> value_)
        : it(__list_map.emplace("", value_))
    { 
        it->second.name = it->first; 
    } 
    inline ListHolder(std::initializer_list<double> value_) 
        : it(__list_map.emplace("", value_))
    { 
        it->second.name = it->first; 
    } 
    
    inline ListHolder(): it(__list_map.emplace("")) {
        it->second.name = it->first; 
    }
    
    const std::string& key() const { 
        return it->first; 
    } 
    List& operator*() { 
        return it->second; 
    } 
    const List& operator*() const { 
        return it->second; 
    } 
    List* operator->() const { 
        return &it->second; 
    } 
    BlockField to_field() const {
        return {key(), key()};  // the name and the id. In this code, they are the same.
    }
}; 

class Operand {
public:
    enum InnerType {
        NUMBER_LITERAL,
        STRING_LITERAL,
        VARIABLE,
        BLOCK,
    };
    
    enum ValueType {
        SCALAR, BOOLEAN
    };
    
    InnerType inner_type;
    union {
        std::string string_value;
        double number_value;
        VariableHolder variable_holder;
        BlockHolder block_holder;
    };
    
    Operand(const char* s) 
        : inner_type(InnerType::STRING_LITERAL) 
        , string_value(s) 
    { } 
    Operand(const std::string& s)
        : inner_type(InnerType::STRING_LITERAL)
        , string_value(s)
    { }
    Operand(double num)
        : inner_type(InnerType::NUMBER_LITERAL)
        , number_value(num)
    { }
    Operand(int num)
        : inner_type(InnerType::NUMBER_LITERAL)
        , number_value(num)
    { }
    Operand(long long num)
        : inner_type(InnerType::NUMBER_LITERAL)
        , number_value(num)
    { }
    Operand(const VariableHolder& u)
        : inner_type(InnerType::VARIABLE)
        , variable_holder(u)
    { }
    Operand(const BlockHolder& u)
        : inner_type(InnerType::BLOCK)
        , block_holder(u)
    { }
    ~Operand() {
        switch (inner_type) {
            case NUMBER_LITERAL: break;
            case STRING_LITERAL: string_value.~basic_string(); break;
            case VARIABLE: variable_holder.~VariableHolder(); break;
            case BLOCK: block_holder.~BlockHolder(); break;
        }
    }
    ValueType get_value_type() const {
        if (inner_type == STRING_LITERAL || inner_type == NUMBER_LITERAL || inner_type == VARIABLE) {
            return ValueType::SCALAR;
        }
        if (block_holder->type == Block::Type::SCALAR_EXPRESSION) {
            return ValueType::SCALAR;
        }
        if (block_holder->type == Block::Type::BOOLEAN_EXPRESSION) {
            return ValueType::BOOLEAN;
        }
        throw std::logic_error("Operand must be either scalar or boolean");
    }
    BlockInput to_input() const {
        switch (inner_type) {
            case NUMBER_LITERAL: return BlockInput::number(number_value);
            case STRING_LITERAL: return BlockInput::string(string_value);
            case VARIABLE: return BlockInput::variable(variable_holder.key());
            case BLOCK: return BlockInput::id(block_holder.id());
        }
        assert(false);
    }
};



BlockHolder operator+(const Operand& lhs, const Operand& rhs) {                
    if (lhs.get_value_type() != Operand::ValueType::SCALAR ||
        rhs.get_value_type() != Operand::ValueType::SCALAR) {
        throw std::logic_error("operands of arithmetic operation must be a scalar expression"); 
    }
    return BlockHolder(Opcode::Operator::Add, {
            {"NUM1", lhs.to_input()},
            {"NUM2", rhs.to_input()},
    }, {}, Block::Type::SCALAR_EXPRESSION, false, false);
}

BlockHolder operator-(const Operand& lhs, const Operand& rhs) {                
    if (lhs.get_value_type() != Operand::ValueType::SCALAR ||
        rhs.get_value_type() != Operand::ValueType::SCALAR) {
        throw std::logic_error("operands of arithmetic operation must be a scalar expression"); 
    }
    return BlockHolder(Opcode::Operator::Subtract, {
            {"NUM1", lhs.to_input()},
            {"NUM2", rhs.to_input()},
    }, {}, Block::Type::SCALAR_EXPRESSION, false, false);
}

BlockHolder operator*(const Operand& lhs, const Operand& rhs) {                
    if (lhs.get_value_type() != Operand::ValueType::SCALAR ||
        rhs.get_value_type() != Operand::ValueType::SCALAR) {
        throw std::logic_error("operands of arithmetic operation must be a scalar expression"); 
    }
    return BlockHolder(Opcode::Operator::Multiply, {
            {"NUM1", lhs.to_input()},
            {"NUM2", rhs.to_input()},
    }, {}, Block::Type::SCALAR_EXPRESSION, false, false);
}

BlockHolder operator/(const Operand& lhs, const Operand& rhs) {                
    if (lhs.get_value_type() != Operand::ValueType::SCALAR ||
        rhs.get_value_type() != Operand::ValueType::SCALAR) {
        throw std::logic_error("operands of arithmetic operation must be a scalar expression"); 
    }
    return BlockHolder(Opcode::Operator::Divide, {
            {"NUM1", lhs.to_input()},
            {"NUM2", rhs.to_input()},
    }, {}, Block::Type::SCALAR_EXPRESSION, false, false);
}

BlockHolder operator%(const Operand& lhs, const Operand& rhs) {                
    if (lhs.get_value_type() != Operand::ValueType::SCALAR ||
        rhs.get_value_type() != Operand::ValueType::SCALAR) {
        throw std::logic_error("operands of arithmetic operation must be a scalar expression"); 
    }
    return BlockHolder(Opcode::Operator::Mod, {
            {"NUM1", lhs.to_input()},
            {"NUM2", rhs.to_input()},
    }, {}, Block::Type::SCALAR_EXPRESSION, false, false);
}

void VariableHolder::operator+=(const Operand& operand) {
    BlockHolder(Opcode::Data::ChangeVariableBy, {
        {"VALUE", operand.to_input()},
    }, {
        {"VARIABLE", to_field() }
    });
}

void VariableHolder::operator-=(const Operand& operand) {
    operator+=(Operand(0) - operand);
}

BlockHolder random(const Operand& lhs, const Operand& rhs) {
    if (lhs.get_value_type() != Operand::ValueType::SCALAR ||
        rhs.get_value_type() != Operand::ValueType::SCALAR) {
        throw std::logic_error("operands in function random must be a scalar expression"); 
    }
    return BlockHolder(Opcode::Operator::Random, {
            {"FROM", lhs.to_input()},
            {"TO", rhs.to_input()},
    }, {}, Block::Type::SCALAR_EXPRESSION, false, false);
}

BlockHolder join(const Operand& lhs, const Operand& rhs) {
    if (lhs.get_value_type() != Operand::ValueType::SCALAR ||
        rhs.get_value_type() != Operand::ValueType::SCALAR) {
        throw std::logic_error("operands in function join must be a scalar expression"); 
    }
    return BlockHolder(Opcode::Operator::Join, {
            {"STRING1", lhs.to_input()},
            {"STRING2", rhs.to_input()},
    }, {}, Block::Type::SCALAR_EXPRESSION, false, false);
}

BlockHolder letter_of(const Operand& lhs, const Operand& rhs) {
    if (lhs.get_value_type() != Operand::ValueType::SCALAR ||
        rhs.get_value_type() != Operand::ValueType::SCALAR) {
        throw std::logic_error("operands in function letter of must be a scalar expression"); 
    }
    return BlockHolder(Opcode::Operator::LetterOf, {
            {"LETTER", lhs.to_input()},
            {"STRING", rhs.to_input()},
    }, {}, Block::Type::SCALAR_EXPRESSION, false, false);
}

BlockHolder length(const Operand& value) {
    if (value.get_value_type() != Operand::ValueType::SCALAR) {
        throw std::logic_error("operands in function length must be a scalar expression"); 
    }
    return BlockHolder(Opcode::Operator::Length, {
            {"STRING", value.to_input()},
    }, {}, Block::Type::SCALAR_EXPRESSION, false, false);
}

BlockHolder contains(const Operand& lhs, const Operand& rhs) {
    if (lhs.get_value_type() != Operand::ValueType::SCALAR ||
        rhs.get_value_type() != Operand::ValueType::SCALAR) {
        throw std::logic_error("operands in function contains must be a scalar expression"); 
    }
    return BlockHolder(Opcode::Operator::Contains, {
            {"STRING1", lhs.to_input()},
            {"STRING2", rhs.to_input()},
    }, {}, Block::Type::BOOLEAN_EXPRESSION, false, false);
}

BlockHolder round(const Operand& value) {
    if (value.get_value_type() != Operand::ValueType::SCALAR) {
        throw std::logic_error("operands in function round must be a scalar expression"); 
    }
    return BlockHolder(Opcode::Operator::Round, {
            {"NUM", value.to_input()},
    }, {}, Block::Type::SCALAR_EXPRESSION, false, false);
}

BlockHolder operator<(const Operand& lhs, const Operand& rhs) {
    if (lhs.get_value_type() != Operand::ValueType::SCALAR ||
        rhs.get_value_type() != Operand::ValueType::SCALAR) {
        throw std::logic_error("operands of arithmetic operation must be a scalar expression"); 
    }
    return BlockHolder(Opcode::Operator::Lt, {
            {"OPERAND1", lhs.to_input()},
            {"OPERAND2", rhs.to_input()},
    }, {}, Block::Type::BOOLEAN_EXPRESSION, false, false);
}

BlockHolder operator>(const Operand& lhs, const Operand& rhs) {
    if (lhs.get_value_type() != Operand::ValueType::SCALAR ||
        rhs.get_value_type() != Operand::ValueType::SCALAR) {
        throw std::logic_error("operands of arithmetic operation must be a scalar expression"); 
    }
    return BlockHolder(Opcode::Operator::Gt, {
            {"OPERAND1", lhs.to_input()},
            {"OPERAND2", rhs.to_input()},
    }, {}, Block::Type::BOOLEAN_EXPRESSION, false, false);
}

BlockHolder operator==(const Operand& lhs, const Operand& rhs) {
    if (lhs.get_value_type() != Operand::ValueType::SCALAR ||
        rhs.get_value_type() != Operand::ValueType::SCALAR) {
        throw std::logic_error("operands of arithmetic operation must be a scalar expression"); 
    }
    return BlockHolder(Opcode::Operator::Equals, {
            {"OPERAND1", lhs.to_input()},
            {"OPERAND2", rhs.to_input()},
    }, {}, Block::Type::BOOLEAN_EXPRESSION, false, false);
}

BlockHolder operator!(const Operand& value) {
    if (value.get_value_type() != Operand::ValueType::BOOLEAN) {
        throw std::logic_error("operands of arithmetic operation must be a scalar expression"); 
    }
    return BlockHolder(Opcode::Operator::Not, {
            {"OPERAND", value.to_input()},
    }, {}, Block::Type::BOOLEAN_EXPRESSION, false, false);
}

BlockHolder operator!=(const Operand& lhs, const Operand& rhs) {
    return !(lhs == rhs);
}
BlockHolder operator<=(const Operand& lhs, const Operand& rhs) {
    return !(lhs > rhs);
}

BlockHolder operator>=(const Operand& lhs, const Operand& rhs) {
    return !(lhs < rhs);
}

BlockHolder operator||(const Operand& lhs, const Operand& rhs) {
    if (lhs.get_value_type() != Operand::ValueType::BOOLEAN ||
        rhs.get_value_type() != Operand::ValueType::BOOLEAN) {
        throw std::logic_error("operands of a logic operation must be a boolean expression"); 
    }
    return BlockHolder(Opcode::Operator::Or, {
            {"OPERAND1", lhs.to_input()},
            {"OPERAND2", rhs.to_input()},
    }, {}, Block::Type::BOOLEAN_EXPRESSION, false, false);
}

BlockHolder operator&&(const Operand& lhs, const Operand& rhs) {
    if (lhs.get_value_type() != Operand::ValueType::BOOLEAN ||
        rhs.get_value_type() != Operand::ValueType::BOOLEAN) {
        throw std::logic_error("operands of a logic operation must be a boolean expression"); 
    }
    return BlockHolder(Opcode::Operator::And, {
            {"OPERAND1", lhs.to_input()},
            {"OPERAND2", rhs.to_input()},
    }, {}, Block::Type::BOOLEAN_EXPRESSION, false, false);
}

#define DEFINE_MATHOP_FUNCTION(func_name, op_name) \
    BlockHolder func_name(const Operand& value) {                                                       \
        if (value.get_value_type() != Operand::ValueType::SCALAR) {                                     \
            throw std::logic_error("operands in mathop function must be a scalar expression");          \
        }                                                                                               \
        return BlockHolder(Opcode::Operator::Mathop, {                                                  \
                {"NUM", value.to_input()},                                                              \
        }, {                                                                                            \
                {"OPERATOR", {op_name}}                                                                 \
        }, Block::Type::SCALAR_EXPRESSION, false, false);                                               \
    }

DEFINE_MATHOP_FUNCTION(abs, Opcode::Operator::MathOp::ABS)
DEFINE_MATHOP_FUNCTION(floor, Opcode::Operator::MathOp::FLOOR)
DEFINE_MATHOP_FUNCTION(ceiling, Opcode::Operator::MathOp::CEILING)
DEFINE_MATHOP_FUNCTION(sqrt, Opcode::Operator::MathOp::SQRT)
DEFINE_MATHOP_FUNCTION(sin, Opcode::Operator::MathOp::SIN)
DEFINE_MATHOP_FUNCTION(cos, Opcode::Operator::MathOp::COS)
DEFINE_MATHOP_FUNCTION(tan, Opcode::Operator::MathOp::TAN)
DEFINE_MATHOP_FUNCTION(asin, Opcode::Operator::MathOp::ASIN)
DEFINE_MATHOP_FUNCTION(acos, Opcode::Operator::MathOp::ACOS)
DEFINE_MATHOP_FUNCTION(atan, Opcode::Operator::MathOp::ATAN)
DEFINE_MATHOP_FUNCTION(ln, Opcode::Operator::MathOp::LN)
DEFINE_MATHOP_FUNCTION(log, Opcode::Operator::MathOp::LOG)
DEFINE_MATHOP_FUNCTION(expe, Opcode::Operator::MathOp::EXPE)
DEFINE_MATHOP_FUNCTION(exp10, Opcode::Operator::MathOp::EXP10)
    
#undef DEFINE_MATHOP_FUNCTION

    
    
class ControlBlockGenerator {
    bool collecting;
public:
    ControlBlockGenerator(): collecting(0) {}
    bool check_collecting() {
        collecting ^= 1;
        return collecting;
    }
};
    
class IfBlockGenerator: public ControlBlockGenerator {
    BlockHolder if_block;
public:
    IfBlockGenerator(const Operand& condition)
        : ControlBlockGenerator()
        , if_block(Opcode::Control::If, {
            {"CONDITION", condition.to_input()}
        }, {})
    {
        if (condition.get_value_type() != Operand::ValueType::BOOLEAN) {
            throw std::logic_error("Condition must be a boolean expression");
        }
    }
    ~IfBlockGenerator() {
        BlockHolder::make_substack(if_block, "SUBSTACK");
    }
};


class ElseBlockGenerator: public ControlBlockGenerator {
    BlockHolder if_block;
public:
    ElseBlockGenerator(): ControlBlockGenerator() {
        auto& stack = BlockHolder::block_holder_stack;
        if (stack.empty() or stack.back()->opcode != Opcode::Control::If) {
            throw std::logic_error("The last block should be If in order to use Else.");
        }
        if_block = stack.back();
        if_block->opcode = Opcode::Control::IfElse;
    }
    ~ElseBlockGenerator() {
        BlockHolder::make_substack(if_block, "SUBSTACK2");
    }
};

class RepeatBlockGenerator: public ControlBlockGenerator {
    BlockHolder repeat_block;
public:
    RepeatBlockGenerator(const Operand& times)
        : ControlBlockGenerator()
        , repeat_block(Opcode::Control::Repeat, {
            {"TIMES", times.to_input()}
        }, { })
    {
        if (times.get_value_type() != Operand::ValueType::SCALAR) {
            throw std::logic_error("The TIMES argument for repeat block should be a scalar");
        }
    }
    ~RepeatBlockGenerator() {
        BlockHolder::make_substack(repeat_block, "SUBSTACK");
    }
};
    

class RepeatUntilBlockGenerator : public ControlBlockGenerator {
    BlockHolder repeat_until_block;
public:
    RepeatUntilBlockGenerator(const Operand& condition)
        : ControlBlockGenerator()
        , repeat_until_block(Opcode::Control::RepeatUntil, {
            {"CONDITION", condition.to_input()}
        }, {})
    {
        if (condition.get_value_type() != Operand::ValueType::BOOLEAN) {
            throw std::logic_error("Condition must be a boolean expression");
        }
    }
    ~RepeatUntilBlockGenerator() {
        BlockHolder::make_substack(repeat_until_block, "SUBSTACK");
    }
};
    



    
struct FakeIstream {
};

// magic reading operator
FakeIstream& operator>>(FakeIstream& cin, VariableHolder& var) {
    BlockHolder(Opcode::Sensing::AskAndWait, {
            {"QUESTION", BlockInput::string(var.key() + " = ?")}
    }, {
    });
    BlockHolder answer(Opcode::Sensing::Answer, Block::Type::SCALAR_EXPRESSION, false, false);
    BlockHolder set_answer(Opcode::Data::SetVariableTo, {
            {"VALUE", BlockInput::id(answer.id())},
    }, {
            {"VARIABLE", var.to_field()}
    });
    
    answer->parent = set_answer.id();
    
    return cin;
}



struct FakeOstream {
};

FakeOstream& operator<<(FakeOstream& cout, const VariableHolder& var) {
    BlockHolder(Opcode::Looks::Say, {
            {"MESSAGE", BlockInput::variable(var.key())}
    }, {
    });
    return cout;
}

FakeOstream& operator<<(FakeOstream& cout, const char* s) {
    BlockHolder(Opcode::Looks::Say, {
            {"MESSAGE", BlockInput::string(s)}
    }, {
    });
    return cout;
}

FakeOstream& operator<<(FakeOstream& cout, const std::string& s) {
    BlockHolder(Opcode::Looks::Say, {
            {"MESSAGE", BlockInput::string(s)}
    }, {
    });
    return cout;
}

FakeOstream& operator<<(FakeOstream& cout, double num) {
    BlockHolder(Opcode::Looks::Say, {
            {"MESSAGE", BlockInput::number(num)}
    }, {
    });
    return cout;
}


FakeIstream fake_cin;
FakeOstream fake_cout;

void __reset_all() {
    __variable_map.clear(); 
    __block_map.clear();
    __list_map.clear();
    BlockHolder(Opcode::Event::WhenFlagClicked, Block::Type::CONTROL, true, false);
}

using BlocklyGenerator = std::function<void()>;
inline void generate_project_json(std::ostream& out, const BlocklyGenerator& generator) {
    __reset_all();
    generator();
    StupidJsonWriter json_writer(out);
    json_writer.obj_begin()
        .p("targets").arr_begin()
            // the stage
            .obj_begin()
                .p("isStage").v(true)
                .p("name").sv("Stage")
                .p("variables").obj_begin();
                
                for (const auto& var: __variable_map) {
                    json_writer.p(var.first).arr_begin() 
                        .sv(var.second.name).sv(var.second.value) 
                    .end(); 
                } 
    
                json_writer.end()
                .p("lists").obj_begin();
                
                for (const auto& list: __list_map) {
                    json_writer.p(list.first).arr_begin()
                        .sv(list.second.name).arr_begin();
                        for (auto x: list.second.value) {
                            json_writer.sv(x);
                        }
                        json_writer.end();
                    json_writer.end();
                }
                
                json_writer.end()
                .p("broadcasts").obj_begin().end()
                .p("blocks").obj_begin().end()
                .p("comments").obj_begin().end()
                .p("currentCustume").v(0)
                .p("costumes").arr_begin()
                    // the default costume
                    .obj_begin()
                       .p("assetId").sv("cd21514d0531fdffb22204e0ec5ed84a")
                       .p("name").sv("backdrop1")
                       .p("md5ext").sv("cd21514d0531fdffb22204e0ec5ed84a.svg")
                       .p("dataFormat").sv("svg")
                       .p("rotationCenterX").v(240)
                       .p("rotationCenterY").v(180)
                    .end()
                .end()
                .p("sounds").arr_begin().end()
                .p("layerOrder").v(0)
            .end()
            
            // the only sprite
            .obj_begin()
                .p("isStage").v(false)
                .p("name").sv("Sprite1")
                .p("variables").obj_begin()
                .end()
                .p("lists").obj_begin()
                .end()
                .p("broadcasts").obj_begin()
                .end()
                .p("blocks").obj_begin();
                
                for (const auto& it: __block_map) {
                    json_writer.p(it.first);
                    it.second.write_json(json_writer);
                }
                
                json_writer.end()
                .p("comments").obj_begin().end()
                .p("currentCostume").v(0)
                .p("costumes").arr_begin()
                    // the default costome
                    .obj_begin()
                       .p("assetId").sv("bcf454acf82e4504149f7ffe07081dbc")
                       .p("name").sv("costume1")
                       .p("bitmapResolution").v(1)
                       .p("md5ext").sv("bcf454acf82e4504149f7ffe07081dbc.svg")
                       .p("dataFormat").sv("svg")
                       .p("rotationCenterX").v(48)
                       .p("rotationCenterY").v(50)
                    .end()
                .end()
                .p("sounds").arr_begin().end()
                .p("layerOrder").v(1)
            .end()
        .end()
        .p("monitors").arr_begin().end()
        .p("extensions").arr_begin().end()
        .p("meta").obj_begin()
            // these are the default values
            // except for agent, because I don't use any browser for this
            .p("semver").sv("3.0.0")
            .p("vm").sv("0.2.0-prerelease.20210812043817")
            .p("agent").sv("")
        .end()
    .end();
}




}
