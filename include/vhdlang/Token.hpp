#pragma once
#include "vhdlang/Terminal.hpp"
#include <string>

namespace vhdlang {
class Token {
private:
    std::string value;
    const Terminal& id;
    int column = 0;
    int line = 0;

public:
    Token(std::string value, const Terminal& id) : value(value), id(id) {};
    std::string toString() const {
        if (this->getName() == TerminalName::EOF_VHDL) {
            return "[EOF]";
        }
        return "[Type: " + id.getNameString() +
               ", pos: " + std::to_string(line) + ", " +
               std::to_string(column) + "] " + value;
    }
    Terminal getId() { return id; }

    // Redundant kinda but keeps the abstraction barrier
    TerminalName getName() const { return id.getName(); }

    std::string getValue() const { return value; }
    int getLine() { return line; }
    int getColumn() { return column; }
    void setLine(int newLine) { line = newLine; }
    void setColumn(int newColumn) { column = newColumn; }
};

const Token eofToken = Token("", vhdlang::eofTerminal);

inline std::ostream& operator<<(std::ostream& os, const Token& token) {
    os << token.toString();
    return os;
}

inline bool operator==(const Token& lhs, const Token& rhs) {
    return lhs.getName() == rhs.getName() && lhs.getValue() == rhs.getValue();
}

} // namespace vhdlang
