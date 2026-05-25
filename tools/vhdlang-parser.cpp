#include "vhdlang/Lexer.hpp"
#include "vhdlang/Parser.hpp"
#include <fstream>
#include <iostream>

using namespace vhdlang;

int main(int argc, char** argv) {

    // Current test
    std::string filename = argv[1];
    std::fstream file(filename);
    if (!file.is_open()) {
        std::cout << "Unable to open " << filename << std::endl;
        return 1;
    }
    Lexer testLexer(&file);
    testLexer.lexFile();
    testLexer.printTokens();
    std::cout << "Lexing complete" << std::endl;
    // while (!testLexer.empty()) {
    //     std::cout << testLexer.pop();
    // }
    // std::cout << std::endl;

    Parser testParser(testLexer);
    testParser.parse();
    testParser.printAST();
    return 0;
}
