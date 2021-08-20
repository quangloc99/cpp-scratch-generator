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




std::vector<int> __scratch_global_variables;
std::vector<int> __scratch_global_lists;

using BlocklyGenerator = std::function<void()>;
inline void generate_project_json(std::ostream& out, const BlocklyGenerator& generator) {
    generator();
    StupidJsonWriter(out)
        .obj_begin()
            .p("targets").arr_begin()
                // the stage
                .obj_begin()
                    .p("isStage").v(true)
                    .p("name").sv("Stage")
                    .p("variables").obj_begin()
                    .end()
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
