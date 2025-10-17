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

// TODO: psl verification unit
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

int Parser::parseEntityDeclaration(ASTree* parent) {
    if (lexer.peak().getName() != TerminalName::RES_ENTITY) {
        return PARSE_NOMATCH;
    }
    lexer.pop(); // entity

    unique_ptr<ASTree> tree(
        new ASTree(parent, GrammarRule::ENTITY_DECLARATION));
    int result = parseIdentifier(tree.get());

    if (result != 0) {
        return PARSE_ERROR;
    }

    if (lexer.peak().getName() != TerminalName::RES_IS) {
        cerr << "Missing is " << endl;
        return PARSE_ERROR;
    }

    lexer.pop(); // is
    result = parseEntityHeader(tree.get());
    if (result != 0) {
        return PARSE_ERROR;
    }

    result = parseEntityDeclarativePart(tree.get());
    if (result != 0) {
        return PARSE_ERROR;
    }

    // optional part
    if (lexer.peak().getName() == TerminalName::RES_BEGIN) {
        lexer.pop(); // begin
        result = parseEntityStatementPart(tree.get());
        if (result != 0) {
            return PARSE_ERROR;
        }
    }

    if (lexer.peak().getName() != TerminalName::RES_END) {
        cerr << "Missing end " << endl;
        return PARSE_ERROR;
    }
    lexer.pop(); // end

    // optional
    if (lexer.peak().getName() == TerminalName::RES_ENTITY) {
        lexer.pop();
    }

    // optional
    // entity
    result = parseSimpleName(tree.get());

    if (result == PARSE_ERROR) {
        return PARSE_ERROR;
    }

    if (lexer.peak().getName() != TerminalName::SEMICOLON) {
        cerr << "Missing ; after entity declaration" << endl;
        return PARSE_ERROR;
    }
    lexer.pop(); // semicolon

    parent->addChild(std::move(tree));
    return 0;
}

// TODO: verification binding grammar
int Parser::parseConfigurationDeclaration(ASTree* parent) {
    if (lexer.peak().getName() != TerminalName::RES_CONFIGURATION) {
        return PARSE_NOMATCH;
    }
    lexer.pop(); // entity

    unique_ptr<ASTree> tree(
        new ASTree(parent, GrammarRule::CONFIGURATION_DECLARATION));
    int result = parseIdentifier(tree.get());

    if (result != 0) {
        return PARSE_ERROR;
    }

    if (lexer.peak().getName() != TerminalName::RES_OF) {
        cerr << "Missing of " << endl;
        return PARSE_ERROR;
    }
    lexer.pop(); // of

    // entity
    result = parseName(tree.get());
    if (result != 0) {
        return PARSE_ERROR;
    }

    if (lexer.peak().getName() != TerminalName::RES_IS) {
        cerr << "Missing is " << endl;
        return PARSE_ERROR;
    }
    lexer.pop(); // is

    result = parseConfigurationDeclarativePart(tree.get());
    if (result != 0) {
        return PARSE_ERROR;
    }

    if (lexer.peak().getName() != TerminalName::RES_END) {
        cerr << "Missing end " << endl;
        return PARSE_ERROR;
    }
    lexer.pop(); // end

    // optional
    if (lexer.peak().getName() == TerminalName::RES_CONFIGURATION) {
        lexer.pop();
    }

    // optional
    // configuration
    result = parseSimpleName(tree.get());
    if (result == PARSE_ERROR) {
        return PARSE_ERROR;
    }

    if (lexer.peak().getName() != TerminalName::SEMICOLON) {
        cerr << "Missing ; after entity declaration" << endl;
        return PARSE_ERROR;
    }
    lexer.pop(); // semicolon

    parent->addChild(std::move(tree));
    return 0;
}

int Parser::parsePackageDeclaration(ASTree* parent) {
    if (lexer.peak().getName() != TerminalName::RES_PACKAGE) {
        return PARSE_NOMATCH;
    }
    lexer.pop(); // package

    unique_ptr<ASTree> tree(
        new ASTree(parent, GrammarRule::PACKAGE_DECLARATION));
    int result = parseIdentifier(tree.get());

    if (result != 0) {
        return PARSE_ERROR;
    }

    if (lexer.peak().getName() != TerminalName::RES_IS) {
        cerr << "Missing is " << endl;
        return PARSE_ERROR;
    }

    lexer.pop(); // is
    result = parsePackageHeader(tree.get());
    if (result != 0) {
        return PARSE_ERROR;
    }

    result = parsePackageDeclarativePart(tree.get());
    if (result != 0) {
        return PARSE_ERROR;
    }

    if (lexer.peak().getName() != TerminalName::RES_END) {
        cerr << "Missing end " << endl;
        return PARSE_ERROR;
    }
    lexer.pop(); // end

    // optional
    if (lexer.peak().getName() == TerminalName::RES_PACKAGE) {
        lexer.pop();
    }

    // optional
    // package
    result = parseSimpleName(tree.get());

    if (result == PARSE_ERROR) {
        return PARSE_ERROR;
    }

    if (lexer.peak().getName() != TerminalName::SEMICOLON) {
        cerr << "Missing ; after package declaration" << endl;
        return PARSE_ERROR;
    }
    lexer.pop(); // semicolon

    parent->addChild(std::move(tree));
    return 0;
}

int Parser::parsePackageInstantiationDeclaration(ASTree* parent) {
    if (lexer.peak().getName() != TerminalName::RES_PACKAGE) {
        return PARSE_NOMATCH;
    }
    lexer.pop(); // package

    unique_ptr<ASTree> tree(
        new ASTree(parent, GrammarRule::PACKAGE_INSTANTIATION_DECLARATION));
    int result = parseIdentifier(tree.get());
    if (result != 0) {
        return PARSE_ERROR;
    }
    if (lexer.peak().getName() != TerminalName::RES_IS) {
        return PARSE_ERROR;
    }
    lexer.pop(); // is
    if (lexer.peak().getName() != TerminalName::RES_NEW) {
        return PARSE_ERROR;
    }
    lexer.pop(); // new
    // uninstantiated_package
    result = parseName(tree.get());
    if (result != 0) {
        return PARSE_ERROR;
    }

    // optional
    result = parseGenericMapAspect(tree.get());

    if (result == PARSE_ERROR) {
        return PARSE_ERROR;
    }

    if (lexer.peak().getName() != TerminalName::SEMICOLON) {
        cerr << "Missing ; in package instantiation" << endl;
        return PARSE_ERROR;
    }

    parent->addChild(std::move(tree));
    return 0;
}

int Parser::parseContextDeclaration(ASTree* parent) {
    if (lexer.peak().getName() != TerminalName::RES_CONTEXT) {
        return PARSE_NOMATCH;
    }
    lexer.pop(); // context

    unique_ptr<ASTree> tree(
        new ASTree(parent, GrammarRule::CONTEXT_DECLARATION));
    int result = parseIdentifier(tree.get());

    if (result != 0) {
        return PARSE_ERROR;
    }

    if (lexer.peak().getName() != TerminalName::RES_IS) {
        cerr << "Missing is " << endl;
        return PARSE_ERROR;
    }

    lexer.pop(); // is

    result = parseContextClause(tree.get());
    if (result != 0) {
        return PARSE_ERROR;
    }

    if (lexer.peak().getName() != TerminalName::RES_END) {
        cerr << "Missing end " << endl;
        return PARSE_ERROR;
    }
    lexer.pop(); // end

    // optional
    if (lexer.peak().getName() == TerminalName::RES_CONTEXT) {
        lexer.pop();
    }

    // optional
    // context
    result = parseSimpleName(tree.get());

    if (result == PARSE_ERROR) {
        return PARSE_ERROR;
    }

    if (lexer.peak().getName() != TerminalName::SEMICOLON) {
        cerr << "Missing ; after context declaration" << endl;
        return PARSE_ERROR;
    }
    lexer.pop(); // semicolon

    parent->addChild(std::move(tree));
    return 0;
}

int Parser::parseArchitectureBody(ASTree* parent) {
    if (lexer.peak().getName() != TerminalName::RES_ARCHITECTURE) {
        return PARSE_NOMATCH;
    }
    lexer.pop(); // architecture

    unique_ptr<ASTree> tree(new ASTree(parent, GrammarRule::ARCHITECTURE_BODY));
    int result = parseIdentifier(tree.get());

    if (result != 0) {
        return PARSE_ERROR;
    }
    if (lexer.peak().getName() != TerminalName::RES_OF) {
        return PARSE_ERROR;
    }
    lexer.pop(); // of

    // entity
    result = parseName(tree.get());

    if (result != 0) {
        return PARSE_ERROR;
    }
    if (lexer.peak().getName() != TerminalName::RES_IS) {
        return PARSE_ERROR;
    }
    lexer.pop(); // is

    result = parseArchitectureDeclarativePart(tree.get());
    if (result != 0) {
        return PARSE_ERROR;
    }

    if (lexer.peak().getName() != TerminalName::RES_BEGIN) {
        return PARSE_ERROR;
    }
    lexer.pop(); // begin

    result = parseArchitectureStatementPart(tree.get());
    if (result != 0) {
        return PARSE_ERROR;
    }
    if (lexer.peak().getName() != TerminalName::RES_END) {
        cerr << "Missing end " << endl;
        return PARSE_ERROR;
    }
    lexer.pop(); // end

    // optional
    if (lexer.peak().getName() == TerminalName::RES_ARCHITECTURE) {
        lexer.pop();
    }

    // optional
    // architecture
    result = parseSimpleName(tree.get());

    if (result == PARSE_ERROR) {
        return PARSE_ERROR;
    }

    if (lexer.peak().getName() != TerminalName::SEMICOLON) {
        cerr << "Missing ; after architecture body" << endl;
        return PARSE_ERROR;
    }
    lexer.pop(); // semicolon

    parent->addChild(std::move(tree));
    return 0;
}

int Parser::parsePackageBody(ASTree* parent) {
    if (lexer.peak().getName() != TerminalName::RES_PACKAGE) {
        return PARSE_NOMATCH;
    }
    lexer.pop(); // package
    if (lexer.peak().getName() != TerminalName::RES_BODY) {
        return PARSE_ERROR;
    }
    lexer.pop(); // body
    unique_ptr<ASTree> tree(new ASTree(parent, GrammarRule::PACKAGE_BODY));

    // package
    int result = parseSimpleName(tree.get());
    if (result != 0) {
        return PARSE_ERROR;
    }

    if (lexer.peak().getName() != TerminalName::RES_IS) {
        cerr << "Missing is " << endl;
        return PARSE_ERROR;
    }

    result = parsePackageBodyDeclarativePart(tree.get());
    if (result != 0) {
        return PARSE_ERROR;
    }

    if (lexer.peak().getName() != TerminalName::RES_END) {
        cerr << "Missing end " << endl;
        return PARSE_ERROR;
    }
    lexer.pop(); // end

    // optional
    if (lexer.peak().getName() == TerminalName::RES_PACKAGE) {
        lexer.pop();
        if (lexer.peak().getName() != TerminalName::RES_BODY) {
            cerr << "Missing body " << endl;
            return PARSE_ERROR;
        }
        lexer.pop();
    }

    // optional
    // package
    result = parseSimpleName(tree.get());

    if (result == PARSE_ERROR) {
        return PARSE_ERROR;
    }

    if (lexer.peak().getName() != TerminalName::SEMICOLON) {
        cerr << "Missing ; after package body" << endl;
        return PARSE_ERROR;
    }
    lexer.pop(); // semicolon

    parent->addChild(std::move(tree));
    return 0;
}

int Parser::parseLogicalNameList(ASTree* parent) {
    unique_ptr<ASTree> tree(new ASTree(parent, GrammarRule::LOGICAL_NAME_LIST));
    int result = parseLogicalName(tree.get());

    if (result != 0) {
        return PARSE_ERROR;
    }

    while (lexer.peak().getName() == TerminalName::COMMA) {
        lexer.pop(); // comma
        result = parseLogicalName(tree.get());
        if (result != 0) {
            return PARSE_ERROR;
        }
    }

    parent->addChild(std::move(tree));
    return 0;
}

int Parser::parseSelectedName(ASTree* parent) {
}
