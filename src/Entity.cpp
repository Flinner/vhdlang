#include "vhdlang/Entity.hpp"

#include "vhdlang/Common.hpp"
#include "vhdlang/GrammarRule.hpp"
#include "vhdlang/Parser.hpp"
#include "vhdlang/Pattern.hpp"
#include "vhdlang/Terminal.hpp"
#include <memory>

using namespace vhdlang;
using namespace std;
using namespace Entity;

int Entity::parseEntityDeclaration(vhdlang::Lexer& lexer, ASTree* parent) {
    if (!lexer.match(TerminalName::RES_ENTITY)) {
        return PARSE_NOMATCH;
    }
    lexer.pop(); // entity

    unique_ptr<ASTree> tree(
        new ASTree(parent, GrammarRule::ENTITY_DECLARATION));
    int result = Common::parseIdentifier(lexer, tree.get());

    if (result != 0) {
        return PARSE_ERROR;
    }

    if (!lexer.match(TerminalName::RES_IS)) {
        cerr << "Missing is " << endl;
        return PARSE_ERROR;
    }

    lexer.pop(); // is
    result = parseEntityHeader(lexer, tree.get());
    if (result != 0) {
        return PARSE_ERROR;
    }

    // TODO: implement
    // result = parseEntityDeclarativePart(lexer, tree.get());
    // if (result != 0) {
    //     return PARSE_ERROR;
    // }

    // optional part
    if (lexer.match(TerminalName::RES_BEGIN)) {
        lexer.pop(); // begin
        result = parseEntityStatementPart(lexer, tree.get());
        if (result != 0) {
            return PARSE_ERROR;
        }
    }

    if (!lexer.match(TerminalName::RES_END)) {
        cerr << "Missing end " << endl;
        return PARSE_ERROR;
    }
    lexer.pop(); // end

    // optional
    if (lexer.match(TerminalName::RES_ENTITY)) {
        lexer.pop();
    }

    // optional
    // entity
    result = Common::parseIdentifier(lexer, tree.get());

    if (result == PARSE_ERROR) {
        return PARSE_ERROR;
    }

    if (!lexer.match(TerminalName::SEMICOLON)) {
        cerr << "Missing ; after entity declaration" << endl;
        return PARSE_ERROR;
    }
    lexer.pop(); // semicolon

    parent->addChild(std::move(tree));
    return 0;
}

int Entity::parseEntityHeader(vhdlang::Lexer& lexer, ASTree* parent) {
    unique_ptr<ASTree> tree(new ASTree(parent, GrammarRule::ENTITY_HEADER));
    int result = Common::parseGenericClause(lexer, tree.get());
    if (result == PARSE_ERROR) {
        return PARSE_ERROR;
    }

    result = parsePortClause(lexer, tree.get());
    if (result == PARSE_ERROR) {
        return PARSE_ERROR;
    }

    // TODO: check if empty
    parent->addChild(std::move(tree));

    return 0;
}

int Entity::parseEntityDeclarativePart(vhdlang::Lexer& lexer, ASTree* parent) {
    return Pattern::parseWhile(lexer, parent,
                               GrammarRule::ENTITY_DECLARATIVE_PART,
                               parseEntityDeclarativeItem);
}

int Entity::parseEntityStatementPart(vhdlang::Lexer& lexer, ASTree* parent) {
    return PARSE_NOMATCH;
}

int Entity::parsePortClause(vhdlang::Lexer& lexer, ASTree* parent) {
    if (!lexer.match(TerminalName::RES_PORT)) {
        return PARSE_NOMATCH;
    }
    lexer.pop(); // PORT

    unique_ptr<ASTree> tree(new ASTree(parent, GrammarRule::PORT_CLAUSE));

    if (!lexer.match(TerminalName::LEFT_PARENTHESIS)) {
        cerr << "Missing (" << endl;
        return PARSE_ERROR;
    }
    lexer.pop();

    int result = parsePortList(lexer, tree.get());
    if (result != 0) {
        cerr << "Error in parsing port list" << endl;
        return PARSE_ERROR;
    }

    if (!lexer.match(TerminalName::RIGHT_PARENTHESIS)) {
        cerr << "Missing ) in port clause" << endl;
        return PARSE_ERROR;
    }
    lexer.pop();

    if (!lexer.match(TerminalName::SEMICOLON)) {
        cerr << "Missing ;" << endl;
        return PARSE_ERROR;
    }
    lexer.pop();

    parent->addChild(std::move(tree));

    return 0;
}

int Entity::parsePortList(vhdlang::Lexer& lexer, ASTree* parent) {
    unique_ptr<ASTree> tree(new ASTree(parent, GrammarRule::PORT_LIST));
    int result = Common::parseInterfaceList(lexer, tree.get());
    if (result != 0) {
        return PARSE_ERROR;
    }
    parent->addChild(std::move(tree));
    return 0;
}

int Entity::parseEntityDeclarativeItem(vhdlang::Lexer& lexer, ASTree* parent) {
    return PARSE_NOMATCH;
}

int Entity::parseEntityStatement(vhdlang::Lexer& lexer, ASTree* parent) {
    return PARSE_NOMATCH;
}

int Entity::parseInterfaceConstantDeclaration(vhdlang::Lexer& lexer,
                                              ASTree* parent) {
    return PARSE_NOMATCH;
}
