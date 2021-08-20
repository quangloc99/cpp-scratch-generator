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
#include <string>


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




class NameGenerator {
    std::set<std::string> name_pool;
    std::string name_prefix;
    int count;
public:
    NameGenerator(const std::string& prefix = ""): name_prefix(prefix), count(0) {
    }
    std::string generate() {
        std::string res;
        do {
            res = name_prefix + std::to_string(count++);
        }  while (name_pool.count(res));
        return res;
    }
    void register_name(const std::string& name) {
        auto t = name_pool.insert(name);
        assert(t.second);
    }
    void reset() {
        name_pool.clear();
        count = 0;
    }
};



class Variable {
public:
    static NameGenerator var_name_generator;
    static std::vector<Variable> variable_list;
    static void reset() {
        var_name_generator.reset();
        variable_list.clear();
    }
    
    const std::string name;
    std::string value;
    
    inline Variable(const std::string& name_, const std::string& value_)
        : name(name_)
        , value(value_)
    {
        variable_list.push_back(*this);
    }
    inline Variable()
        : Variable(var_name_generator.generate(), "0") {}
    
    inline Variable(const std::string& value_)
        : Variable(var_name_generator.generate(), value_) {}
    inline Variable(const char*  value_)
        : Variable(var_name_generator.generate(), value_) {}
    inline Variable(int value_)
        : Variable(std::to_string(value_)) {}
    inline Variable(long long value_)
        : Variable(std::to_string(value_)) {}
    inline Variable(float value_)
        : Variable(std::to_string(value_)) {}
    inline Variable(double value_)
        : Variable(std::to_string(value_)) {}
    
    inline Variable(const std::string& name_, int value_)
        : Variable(name_, std::to_string(value_)) {}
    inline Variable(const std::string& name_, long long value_)
        : Variable(name_, std::to_string(value_)) {}
    inline Variable(const std::string& name_, float value_)
        : Variable(name_, std::to_string(value_)) {}
    inline Variable(const std::string& name_, double value_)
        : Variable(name_, std::to_string(value_)) {}
};

NameGenerator Variable::var_name_generator("var_");
std::vector<Variable> Variable::variable_list;

void __reset_all() {
    Variable::reset();
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
                
                for (auto& var: Variable::variable_list) {
                    json_writer.p(var.name).arr_begin()
                        .sv(var.name).sv(var.value)
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
                .p("name").sv("NeverGonnaGiveYouUp")
                .p("variables").obj_begin()
                .end()
                .p("lists").obj_begin()
                .end()
                .p("broadcasts").obj_begin()
                .end()
                .p("blocks").obj_begin()
                .end()
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
