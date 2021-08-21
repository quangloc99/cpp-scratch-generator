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
            json_writer.v(value);
        } else {
            json_writer.arr_begin().v(type).v(value);
        }
        if (!is_scalar_) {
            json_writer.arr_begin().v(InputType::NUMBER).v(0);
        }
        return json_writer.end();
    }
};




class Block {
public:
    std::string opcode;
    std::string next, parent;
    std::unordered_map<std::string, BlockInput> inputs;
    std::unordered_map<std::string, std::vector<std::string>> fields;  // fields are just array of string, so meh
    
    inline Block(const std::string& opcode_)
        : opcode(opcode_)
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
        
        // TODO
        json_writer.p("inputs").obj_begin().end();
        json_writer.p("fields").obj_begin().end();
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
    BlockHolder(const std::string& opcode)
        : it(__block_map.emplace(opcode))
    { }
};



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
        , value(std::to_string(double_value_))
    {}  
}; 

AutoGeneratedNamedMap<Variable> __variable_map; 

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
    std::vector<std::string> to_field() const {
        return {key(), key()};  // the name and the id. In this code, they are the same.
    }
    
    
    // magic operator
    
}; 



void __reset_all() {
    __variable_map.clear(); 
    __block_map.clear();
    BlockHolder("event_whenflagclicked");
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
                .p("lists").obj_begin()
                .end()
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
