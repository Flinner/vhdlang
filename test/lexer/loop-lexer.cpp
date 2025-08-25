#include <fstream>
#include <iostream>
#include <vhdlang/Lexer.hpp>
#include <vhdlang/Terminal.hpp>
#include <vhdlang/Token.hpp>

using namespace vhdlang;

// Loops through the entire files and print only the paths that fail

int main(int argc, char** argv) {

    for (int i = 1; i < argc; i++) {
        // Current test
        std::string filename = argv[i];
        std::fstream file(filename);
        if (!file.is_open()) {
            std::cerr << "Unable to open " << filename << std::endl;
            return 1;
        }
        Lexer testLexer(file);
        int result = testLexer.lexFile();
        if (result != 0) {
            std::cerr << "Error in " << filename << std::endl;
        } else {
            std::cout << "Success for " << filename << std::endl;
        }
        // testLexer.printTokens();
    }
    return 0;
}
