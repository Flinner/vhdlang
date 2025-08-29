#pragma once
#include "vhdlang/Terminal.hpp"
#include <string>

namespace vhdlang {
class Token {
private:
    std::string value;
    const Terminal& id;
    int column;
    int line;

public:
    Token(std::string value, const Terminal& id) : value(value), id(id) {};
    std::string toString() {
        return "[Type: " + id.getNameString() + ", pos: " + std::to_string(line) + ", " +
               std::to_string(column) + "] " + value;
    }
    Terminal getId() { return id; }
    int getLine() { return line; }
    int getColumn() { return column; }
    void setLine(int newLine) { line = newLine; }
    void setColumn(int newColumn) { column = newColumn; }
};

} // namespace vhdlang
