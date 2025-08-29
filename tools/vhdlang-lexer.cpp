#include "vhdlang/Lexer.hpp"
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
    return 0;
}
