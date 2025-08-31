#pragma once
#include "vhdlang/ASTree.hpp"
#include "vhdlang/GrammarRule.hpp"
#include "vhdlang/Lexer.hpp"

// Takes as input a lexer and parses it to create an AST.
// For now the idea is 1 parser per file

namespace vhdlang {
class Parser {
private:
    vhdlang::Lexer& lexer;
    vhdlang::ASTree tree;

public:
    Parser(vhdlang::Lexer& lexer) : lexer(lexer), tree(ASTree(nullptr, GrammarRule::DESIGN_FILE)) {}
    int parse();
};
} // namespace vhdlang
