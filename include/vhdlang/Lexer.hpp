#pragma once
#include <fstream>
#include <deque>
#include <string>
#include <vhdlang/Terminal.hpp>
#include <vhdlang/Token.hpp>

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

    // Fills the tokens vector with tokens from the file list
    int lexFile();

    // Print stored tokens
    void printTokens();
};
} // namespace vhdlang
