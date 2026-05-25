#include "vhdlang/Pattern.hpp"

#include "vhdlang/GrammarRule.hpp"
#include "vhdlang/Parser.hpp"
#include "vhdlang/Terminal.hpp"

using namespace vhdlang;
using namespace std;

int Pattern::parseWhile(
    vhdlang::Lexer& lexer, ASTree* parent, GrammarRule rule,
    std::function<int(vhdlang::Lexer&, ASTree*)> parseRule) {

    unique_ptr<ASTree> tree(new ASTree(parent, rule));
    int result = parseRule(lexer, tree.get());
    bool match = false; // Matched at least once
    while (result == 0) {
        result = parseRule(lexer, tree.get());
        match = true;
    }
    if (result == PARSE_NOMATCH && match) {
        parent->addChild(std::move(tree));
        return 0;
    }
    return result;
}

int Pattern::parseSeparatedList(
    vhdlang::Lexer& lexer, ASTree* parent, GrammarRule rule,
    TerminalName separator,
    std::function<int(vhdlang::Lexer&, ASTree*)> parseRule) {

    unique_ptr<ASTree> tree(new ASTree(parent, rule));
    int result = parseRule(lexer, tree.get());

    if (result != 0) {
        return PARSE_ERROR;
    }

    // cout << "Before pop from separated list" << endl;
    // cout << lexer.peak() << endl;
    while (lexer.match(separator)) {
        lexer.pop();
        // cout << "Popped from separated list" << endl;
        result = parseRule(lexer, tree.get());
        if (result != 0) {
            return PARSE_ERROR;
        }
    }

    parent->addChild(std::move(tree));
    return 0;
}

bool Pattern::matchWALRUS(vhdlang::Lexer& lexer) {
    TerminalName tok = lexer.peak().getName();
    TerminalName tok1 = lexer.peakN(1).getName();
    return (tok == TerminalName::COLON && tok1 == TerminalName::EQUAL);
}
