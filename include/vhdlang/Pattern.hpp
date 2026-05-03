#pragma once

#include "vhdlang/ASTree.hpp"
#include "vhdlang/Lexer.hpp"
#include "vhdlang/Terminal.hpp"
#include <functional>

namespace vhdlang {
namespace Pattern {
int parseWhile(vhdlang::Lexer& lexer, ASTree* parent, GrammarRule rule,
               std::function<int(vhdlang::Lexer&, ASTree*)> parseRule);
int parseSeparatedList(vhdlang::Lexer& lexer, ASTree* parent, GrammarRule rule,
                       TerminalName separator,
                       std::function<int(vhdlang::Lexer&, ASTree*)> parseRule);
bool matchWALRUS(vhdlang::Lexer& lexer);
} // namespace Pattern
} // namespace vhdlang
