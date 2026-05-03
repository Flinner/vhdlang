#pragma once
#include "vhdlang/Terminal.hpp"
#include "vhdlang/Token.hpp"
#include <deque>
#include <fstream>
#include <string>

namespace vhdlang {

class Lexer {
private:
    static const std::vector<Terminal> vhdlTerminals;
    std::fstream* sourceFile;
    std::string fileContents;
    std::deque<Token> tokens;

public:
    Lexer(std::fstream* sourceFile);
    Lexer(std::string inputText);

    bool empty() { return tokens.empty(); }
    // Peak while ignoring whitespace tokens
    const Token peak();

    const Token peakN(int n);

    // Pop while ignoring whitespace tokens
    Token pop();

    // Fills the tokens vector with tokens from the file list
    int lexFile();

    // Print stored tokens
    void printTokens();

    // Match the first non-whitespace token
    bool match(TerminalName name);
};
} // namespace vhdlang
