#pragma once
#include "vhdlang/ASTree.hpp"
#include "vhdlang/Lexer.hpp"
#include <memory>

// Takes as input a lexer and parses it to create an AST.
// For now the idea is 1 parser per file

namespace vhdlang {
class Parser {
private:
    vhdlang::Lexer& lexer;
    std::unique_ptr<ASTree> astree;

    // Gramar rules
    int parseDesignFile(ASTree* root);
    int parseDesignUnit(ASTree* parent);
    int parseContextClause(ASTree* parent);
    int parseLibraryUnit(ASTree* parent);
    int parseContextItem(ASTree* parent);
    int parsePrimaryUnit(ASTree* parent);
    int parseSecondaryUnit(ASTree* parent);
    int parseLibraryClause(ASTree* parent);
    int parseUseClause(ASTree* parent);
    int parseContextReference(ASTree* parent);

public:
    Parser(vhdlang::Lexer& lexer) : lexer(lexer) {}
    int parse();
};
} // namespace vhdlang
