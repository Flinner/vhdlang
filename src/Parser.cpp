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

int Parser::parsePrimaryUnit(ASTree* parent) {
    unique_ptr<ASTree> tree(new ASTree(parent, GrammarRule::PRIMARY_UNIT));
    int result = parseEntityDeclaration(tree.get());

    if (result == PARSE_NOMATCH) {
        result = parseConfigurationDeclaration(tree.get());
    }

    if (result == PARSE_NOMATCH) {
        result = parsePackageDeclaration(tree.get());
    }

    if (result == PARSE_NOMATCH) {
        result = parsePackageInstantiationDeclaration(tree.get());
    }

    if (result == PARSE_NOMATCH) {
        result = parseContextDeclaration(tree.get());
    }

    if (result == 0) {
        parent->addChild(std::move(tree));
    }

    return result;
}

int Parser::parseSecondaryUnit(ASTree* parent) {
    unique_ptr<ASTree> tree(new ASTree(parent, GrammarRule::SECONDARY_UNIT));
    int result = parseArchitectureBody(tree.get());

    if (result == PARSE_NOMATCH) {
        result = parsePackageBody(tree.get());
    }

    if (result == 0) {
        parent->addChild(std::move(tree));
    }

    return result;
}

int Parser::parseLibraryClause(ASTree* parent) {
    Token tok = lexer.peak();
    if (tok.getName() != TerminalName::RES_LIBRARY) {
        return PARSE_NOMATCH;
    }

    lexer.pop(); // library
    unique_ptr<ASTree> tree(new ASTree(parent, GrammarRule::LIBRARY_CLAUSE));
    int result = parseLogicalNameList(tree.get());

    if (result != 0) {
        return PARSE_ERROR;
    }

    if (lexer.peak().getName() != TerminalName::SEMICOLON) {
        cerr << "Missing ; after library" << endl;
        return PARSE_ERROR;
    }
    lexer.pop(); // semicolon
    parent->addChild(std::move(tree));
    return 0;
}

int Parser::parseUseClause(ASTree* parent) {
    Token tok = lexer.peak();
    if (tok.getName() != TerminalName::RES_USE) {
        return PARSE_NOMATCH;
    }

    lexer.pop();
    unique_ptr<ASTree> tree(new ASTree(parent, GrammarRule::USE_CLAUSE));
    int result = parseSelectedName(tree.get());

    if (result != 0) {
        return PARSE_ERROR;
    }

    while (lexer.peak().getName() == TerminalName::COMMA) {
        lexer.pop(); // comma
        result = parseSelectedName(tree.get());
        if (result != 0) {
            return PARSE_ERROR;
        }
    }

    if (lexer.peak().getName() != TerminalName::SEMICOLON) {
        cerr << "Missing ; after use clause" << endl;
        return PARSE_ERROR;
    }
    lexer.pop(); // semicolon
    parent->addChild(std::move(tree));
    return 0;
}

int Parser::parseContextReference(ASTree* parent) {
    Token tok = lexer.peak();
    if (tok.getName() != TerminalName::RES_CONTEXT) {
        return PARSE_NOMATCH;
    }

    lexer.pop();
    unique_ptr<ASTree> tree(new ASTree(parent, GrammarRule::CONTEXT_REFERENCE));
    int result = parseSelectedName(tree.get());

    if (result != 0) {
        return PARSE_ERROR;
    }

    while (lexer.peak().getName() == TerminalName::COMMA) {
        lexer.pop(); // comma
        result = parseSelectedName(tree.get());
        if (result != 0) {
            return PARSE_ERROR;
        }
    }

    if (lexer.peak().getName() != TerminalName::SEMICOLON) {
        cerr << "Missing ; after use clause" << endl;
        return PARSE_ERROR;
    }
    lexer.pop(); // semicolon
    parent->addChild(std::move(tree));
    return 0;
}
