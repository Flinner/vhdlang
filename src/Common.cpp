#include "vhdlang/Common.hpp"

#include "vhdlang/GrammarRule.hpp"
#include "vhdlang/NodeIdentifier.hpp"
#include "vhdlang/Parser.hpp"
#include "vhdlang/Pattern.hpp"
#include "vhdlang/Terminal.hpp"
#include <memory>

using namespace vhdlang;
using namespace std;
using namespace Common;

int Common::parseIdentifier(vhdlang::Lexer& lexer, ASTree* parent) {
    unique_ptr<ASTree> tree(new ASTree(parent, GrammarRule::IDENTIFIER));
    TerminalName tok = lexer.peak().getName();
    if (tok == TerminalName::BASIC_IDENTIFIER ||
        tok == TerminalName::EXTENDED_IDENTIFIER) {
        Token id = lexer.pop();
        unique_ptr<ASTNode> newIdentifier(new NodeIdentifier(id.getValue()));
        tree->setNode(std::move(newIdentifier));
        parent->addChild(std::move(tree));
        return 0;
    }
    return PARSE_NOMATCH;
}

int Common::parsePackageDeclaration(vhdlang::Lexer& lexer, ASTree* parent) {
    if (!lexer.match(TerminalName::RES_PACKAGE)) {
        return PARSE_NOMATCH;
    }
    lexer.pop(); // package

    unique_ptr<ASTree> tree(
        new ASTree(parent, GrammarRule::PACKAGE_DECLARATION));
    int result = parseIdentifier(lexer, tree.get());

    if (result != 0) {
        return PARSE_ERROR;
    }

    if (!lexer.match(TerminalName::RES_IS)) {
        cerr << "Missing is " << endl;
        return PARSE_ERROR;
    }

    lexer.pop(); // is
    result = parsePackageDeclarativePart(lexer, tree.get());
    if (result != 0) {
        return PARSE_ERROR;
    }

    if (!lexer.match(TerminalName::RES_END)) {
        cerr << "Missing end " << endl;
        return PARSE_ERROR;
    }
    lexer.pop(); // end

    // optional
    if (lexer.match(TerminalName::RES_PACKAGE)) {
        lexer.pop();
    }

    // optional
    // package
    result = parseIdentifier(lexer, tree.get());

    if (result == PARSE_ERROR) {
        return PARSE_ERROR;
    }

    if (!lexer.match(TerminalName::SEMICOLON)) {
        cerr << "Missing ; after package declaration" << endl;
        return PARSE_ERROR;
    }
    lexer.pop(); // semicolon

    parent->addChild(std::move(tree));
    return 0;
}

int Common::parsePackageBody(vhdlang::Lexer& lexer, ASTree* parent) {
    if (!lexer.match(TerminalName::RES_PACKAGE)) {
        return PARSE_NOMATCH;
    }
    lexer.pop(); // package
    if (!lexer.match(TerminalName::RES_BODY)) {
        return PARSE_ERROR;
    }
    lexer.pop(); // body
    unique_ptr<ASTree> tree(new ASTree(parent, GrammarRule::PACKAGE_BODY));

    // package
    int result = parseIdentifier(lexer, tree.get());
    if (result != 0) {
        return PARSE_ERROR;
    }

    if (!lexer.match(TerminalName::RES_IS)) {
        cerr << "Missing is " << endl;
        return PARSE_ERROR;
    }

    result = parsePackageBodyDeclarativePart(lexer, tree.get());
    if (result != 0) {
        return PARSE_ERROR;
    }

    if (!lexer.match(TerminalName::RES_END)) {
        cerr << "Missing end " << endl;
        return PARSE_ERROR;
    }
    lexer.pop(); // end

    // optional
    if (lexer.match(TerminalName::RES_PACKAGE)) {
        lexer.pop();
        if (!lexer.match(TerminalName::RES_BODY)) {
            cerr << "Missing body " << endl;
            return PARSE_ERROR;
        }
        lexer.pop();
    }

    // optional
    // package
    result = parseIdentifier(lexer, tree.get());

    if (result == PARSE_ERROR) {
        return PARSE_ERROR;
    }

    if (!lexer.match(TerminalName::SEMICOLON)) {
        cerr << "Missing ; after package body" << endl;
        return PARSE_ERROR;
    }
    lexer.pop(); // semicolon

    parent->addChild(std::move(tree));
    return 0;
}

int Common::parsePackageInstantiationDeclaration(vhdlang::Lexer& lexer,
                                                 ASTree* parent) {
    if (!lexer.match(TerminalName::RES_PACKAGE)) {
        return PARSE_NOMATCH;
    }
    lexer.pop(); // package

    unique_ptr<ASTree> tree(
        new ASTree(parent, GrammarRule::PACKAGE_INSTANTIATION_DECLARATION));
    int result = parseIdentifier(lexer, tree.get());
    if (result != 0) {
        return PARSE_ERROR;
    }
    if (!lexer.match(TerminalName::RES_IS)) {
        return PARSE_ERROR;
    }
    lexer.pop(); // is
    if (!lexer.match(TerminalName::RES_NEW)) {
        return PARSE_ERROR;
    }
    lexer.pop(); // new
    // uninstantiated_package
    result = parseName(lexer, tree.get());
    if (result != 0) {
        return PARSE_ERROR;
    }

    // optional
    result = parseGenericMapAspect(lexer, tree.get());

    if (result == PARSE_ERROR) {
        return PARSE_ERROR;
    }

    if (!lexer.match(TerminalName::SEMICOLON)) {
        cerr << "Missing ; in package instantiation" << endl;
        return PARSE_ERROR;
    }
    lexer.pop(); // semicolon

    parent->addChild(std::move(tree));
    return 0;
}

int Common::parseUseClause(vhdlang::Lexer& lexer, ASTree* parent) {
    if (!lexer.match(TerminalName::RES_USE)) {
        return PARSE_NOMATCH;
    }

    lexer.pop();
    unique_ptr<ASTree> tree(new ASTree(parent, GrammarRule::USE_CLAUSE));
    int result = parseSelectedName(lexer, tree.get());

    if (result != 0) {
        return PARSE_ERROR;
    }

    while (lexer.match(TerminalName::COMMA)) {
        lexer.pop(); // comma
        result = parseSelectedName(lexer, tree.get());
        if (result != 0) {
            return PARSE_ERROR;
        }
    }

    if (!lexer.match(TerminalName::SEMICOLON)) {
        cerr << "Missing ; after use clause" << endl;
        return PARSE_ERROR;
    }
    lexer.pop(); // semicolon
    parent->addChild(std::move(tree));
    return 0;
}

int Common::parseInterfaceList(vhdlang::Lexer& lexer, ASTree* parent) {
    return Pattern::parseSeparatedList(lexer, parent,
                                       GrammarRule::INTERFACE_LIST,
                                       TerminalName::SEMICOLON,
                                       parseInterfaceDeclaration);
}

// TODO: Incomplete, use switch instead
int Common::parseInterfaceDeclaration(vhdlang::Lexer& lexer, ASTree* parent) {
    unique_ptr<ASTree> tree(
        new ASTree(parent, GrammarRule::INTERFACE_DECLARATION));

    int result = parseInterfaceObjectDeclaration(lexer, tree.get());

    if (result == PARSE_NOMATCH) {
        result = parseInterfaceTypeDeclaration(lexer, tree.get());
    }

    if (result == PARSE_NOMATCH) {
        result = parseInterfaceSubprogramDeclaration(lexer, tree.get());
    }

    if (result == PARSE_NOMATCH) {
        result = parseInterfacePackageDeclaration(lexer, tree.get());
    }

    if (result == 0) {
        parent->addChild(std::move(tree));
    }

    return result;
}

// TODO: Incomplete, use switch instead
int Common::parseInterfaceObjectDeclaration(vhdlang::Lexer& lexer,
                                            ASTree* parent) {
    unique_ptr<ASTree> tree(
        new ASTree(parent, GrammarRule::INTERFACE_OBJECT_DECLARATION));

    int result = parseInterfaceConstantDeclaration(lexer, tree.get());

    if (result == PARSE_NOMATCH) {
        result = parseInterfaceSignalDeclaration(lexer, tree.get());
    }

    if (result == PARSE_NOMATCH) {
        result = parseInterfaceVariableDeclaration(lexer, tree.get());
    }

    if (result == PARSE_NOMATCH) {
        result = parseInterfaceFileDeclaration(lexer, tree.get());
    }

    if (result == 0) {
        parent->addChild(std::move(tree));
    }

    return result;
}

int Common::parseInterfaceSignalDeclaration(vhdlang::Lexer& lexer,
                                            ASTree* parent) {
    unique_ptr<ASTree> tree(
        new ASTree(parent, GrammarRule::INTERFACE_SIGNAL_DECLARATION));

    if (lexer.match(TerminalName::RES_SIGNAL)) {
        lexer.pop();
    }

    int result = parseIdentifierList(lexer, tree.get());

    if (result != 0) {
        return PARSE_ERROR;
    }

    if (!lexer.match(TerminalName::COLON)) {
        cerr << "Missing :" << endl;
        return PARSE_ERROR;
    }
    lexer.pop(); // :

    // TODO: work with the result
    result = parseModeRule(lexer, tree.get());

    result = parseSubtypeIndication(lexer, tree.get());

    if (result == PARSE_ERROR) {
        return PARSE_ERROR;
    }

    // optional
    if (lexer.match(TerminalName::RES_BUS)) {
        lexer.pop();
    }

    // optional
    // if (Pattern::matchWALRUS(lexer)) {
    //     lexer.pop();
    //     result = parseExpression(lexer, tree.get());
    //     if (result != 0) {
    //         return PARSE_ERROR;
    //     }
    // }

    parent->addChild(std::move(tree));
    return 0;
}

int Common::parseIdentifierList(vhdlang::Lexer& lexer, ASTree* parent) {
    return Pattern::parseSeparatedList(lexer, parent,
                                       GrammarRule::IDENTIFIER_LIST,
                                       TerminalName::COMMA, parseIdentifier);
}

int Common::parseModeRule(vhdlang::Lexer& lexer, ASTree* parent) {
    unique_ptr<ASTree> tree(new ASTree(parent, GrammarRule::MODE_RULE));

    TerminalName tok = lexer.peak().getName();

    switch (tok) {
        case TerminalName::RES_IN:
        case TerminalName::RES_OUT:
        case TerminalName::RES_INOUT:
        case TerminalName::RES_BUFFER:
        case TerminalName::RES_LINKAGE:
            lexer.pop();
            break;
        default:
            return PARSE_NOMATCH;
    }
    return 0;
}

// TODO: incomplete
int Common::parseSubtypeIndication(vhdlang::Lexer& lexer, ASTree* parent) {
    unique_ptr<ASTree> tree(
        new ASTree(parent, GrammarRule::SUBTYPE_INDICATION));

    // int result = parseResolutionIndication(lexer, tree.get());
    //
    // if (result == PARSE_ERROR) {
    //     return PARSE_ERROR;
    // }

    int result = parseName(lexer, tree.get());

    if (result != 0) {
        cerr << "Error in parsing subtype" << endl;
        return PARSE_ERROR;
    }

    parent->addChild(std::move(tree));
    return 0;
}

int Common::parseName(vhdlang::Lexer& lexer, ASTree* parent) {
    unique_ptr<ASTree> tree(new ASTree(parent, GrammarRule::NAME));
    int result = parseIdentifier(lexer, tree.get());
    if (result == PARSE_NOMATCH) {
        if (lexer.match(TerminalName::STRING_LITERAL)) {
            // TODO String literal node
            lexer.pop();
        }
        else if (lexer.match(TerminalName::CHARACTER_LITERAL)) {
            // TODO character literal node
            lexer.pop();
        }
        else {
            return PARSE_NOMATCH;
        }
    }

    result = Pattern::parseWhile(lexer, tree.get(), GrammarRule::NAME_PART,
                                 parseNamePart);

    if (result == PARSE_ERROR) {
        return PARSE_ERROR;
    }

    parent->addChild(std::move(tree));

    return 0;
}

int Common::parseNamePart(vhdlang::Lexer& lexer, ASTree* parent) {

    unique_ptr<ASTree> tree(new ASTree(parent, GrammarRule::NAME_PART));
    TerminalName tok = lexer.peak().getName();
    int result;

    switch (tok) {
        case TerminalName::DOT:
            lexer.pop();
            return Pattern::parseSeparatedList(lexer, parent,
                                               GrammarRule::SUFFIX,
                                               TerminalName::DOT, parseSuffix);
            break;
        case TerminalName::LEFT_PARENTHESIS:
            lexer.pop();
            result = parseActualParameterPart(lexer, tree.get());
            if (result == PARSE_NOMATCH) {
                result = parseDiscreteRange(lexer, tree.get());
            }
            if (result != 0) {
                cerr << "Error in parsing name" << endl;
                return PARSE_ERROR;
            }

            if (!lexer.match(TerminalName::RIGHT_PARENTHESIS)) {
                cerr << "Missing ) in Name Part" << endl;
                return PARSE_ERROR;
            }
            break;
        case TerminalName::SINGLE_QUOTE:
            lexer.pop();
            result = parseAttributeDesignator(lexer, tree.get());
            if (result != 0) {
                cerr << "Missing attribute designator" << endl;
                return PARSE_ERROR;
            }
            // TODO: add optional expression parsing rule here
            break;

        default:
            return PARSE_NOMATCH;
    }

    if (result == 0) {
        parent->addChild(std::move(tree));
    }

    return 0;
}
