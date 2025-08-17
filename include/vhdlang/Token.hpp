#pragma once
#include <string>
#include <vhdlang/Terminal.hpp>

namespace vhdlang {
class Token {
private:
    std::string value;
    const Terminal& id;

public:
    Token(std::string value, const Terminal& id) : value(value), id(id) {};
    std::string toString() { return "[Type: " + id.getNameString() + ", value: " + value + "]"; }
};

} // namespace vhdlang
