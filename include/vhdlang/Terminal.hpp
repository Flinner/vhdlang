#pragma once
#include <regex>
#include <string>

namespace vhdlang {

enum class TerminalName { INTEGER, IDENTIFIER };

class Terminal {
private:
    const TerminalName name;
    const std::string nameString;
    const std::regex terminalRegex;

public:
    Terminal(TerminalName name, const std::string& nameString, const std::string& regexText) :
        name(name), nameString(nameString),
        terminalRegex(std::regex(regexText, std::regex::icase)) {};
    const TerminalName& getName() const { return name; }
    const std::string& getNameString() const { return nameString; }
    const std::regex& getRegex() const { return terminalRegex; }
};

// Huge list of terminals, order matter, lower index => matches first
static std::vector<Terminal> vhdlTerminals = {Terminal(TerminalName::INTEGER, "Integer", "\\d+"),
                                              Terminal(TerminalName::IDENTIFIER, "Identifier",
                                                       "\\w+")};
} // namespace vhdlang
