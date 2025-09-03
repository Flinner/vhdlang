#include "vhdlang/Parser.hpp"

#include "vhdlang/GrammarRule.hpp"

// Different return values to indicate if we took the wrong option or actual
// error
#define PARSE_NOMATCH 1
#define PARSE_ERROR 2

using namespace vhdlang;
using namespace std;

// Starting grammar rule is design file
int Parser::parse() {
    this->astree = unique_ptr<ASTree>(
        new ASTree(nullptr, GrammarRule::DESIGN_UNIT));
    return parseDesignFile(this->astree.get());
}

int Parser::parseDesignFile(ASTree* root) {
    int result = parseDesignUnit(root);
    while (result == 0) {
        result = parseDesignUnit(root);
    }
    return (result == PARSE_NOMATCH) ? 0 : PARSE_ERROR;
}

int Parser::parseDesignUnit(ASTree* parent) {
    unique_ptr<ASTree> tree(new ASTree(parent, GrammarRule::DESIGN_UNIT));
    int result = parseContextClause(tree.get());
    if (result != 0) {
        return result;
    }
    result = parseLibraryUnit(tree.get());

    if (result != 0) {
        return PARSE_ERROR;
    }
    parent->addChild(std::move(tree));
    return 0;
}

int Parser::parseContextClause(ASTree* parent) {
    unique_ptr<ASTree> tree(new ASTree(parent, GrammarRule::CONTEXT_CLAUSE));
    int result = parseContextItem(tree.get());
    bool match = false; // Matched at least once
    while (result == 0) {
        result = parseContextItem(tree.get());
        match = true;
    }
    if (result == PARSE_NOMATCH && match) {
        parent->addChild(std::move(tree));
        return 0;
    }
    return result;
}

int Parser::parseLibraryUnit(ASTree* parent) {
    unique_ptr<ASTree> tree(new ASTree(parent, GrammarRule::LIBRARY_UNIT));
    int result = parsePrimaryUnit(tree.get());

    if (result == PARSE_NOMATCH) {
        result = parseSecondaryUnit(tree.get());
    }

    if (result == 0) {
        parent->addChild(std::move(tree));
    }
    return result;
}

int Parser::parseContextItem(ASTree* parent) {
    unique_ptr<ASTree> tree(new ASTree(parent, GrammarRule::CONTEXT_ITEM));
    int result = parseLibraryClause(tree.get());

    if (result == PARSE_NOMATCH) {
        result = parseUseClause(tree.get());
    }

    if (result == PARSE_NOMATCH) {
        result = parseContextReference(tree.get());
    }

    if (result == 0) {
        parent->addChild(std::move(tree));
    }
    return result;
}
