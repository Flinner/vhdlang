#pragma once
#include <string>
#include <vhdlang/Terminal.hpp>

namespace vhdlang {
class Token {
private:
    std::string value;
    const Terminal& id;
    int column;
    int row;

public:
    Token(std::string value, const Terminal& id) : value(value), id(id) {};
    std::string toString() { return "[Type: " + id.getNameString() + ", value: " + value + "]"; }
    int getRow() { return row; }
    int getColumn() { return column; }
    void setRow(int newRow) { row = newRow; }
    void setColumn(int newColumn) { column = newColumn; }
};

} // namespace vhdlang
