#pragma once

#include "vhdlang/ASTree.hpp"
#include "vhdlang/Lexer.hpp"

namespace vhdlang {
namespace Entity {
int parseEntityDeclaration(vhdlang::Lexer& lexer, ASTree* parent);
int parseEntityHeader(vhdlang::Lexer& lexer, ASTree* parent);
int parseEntityDeclarativePart(vhdlang::Lexer& lexer, ASTree* parent);
int parseEntityStatementPart(vhdlang::Lexer& lexer, ASTree* parent);
int parsePortClause(vhdlang::Lexer& lexer, ASTree* parent);
int parseEntityDeclarativeItem(vhdlang::Lexer& lexer, ASTree* parent);
int parseEntityStatement(vhdlang::Lexer& lexer, ASTree* parent);
int parsePortList(vhdlang::Lexer& lexer, ASTree* parent);
int parseInterfaceConstantDeclaration(vhdlang::Lexer& lexer, ASTree* parent);
} // namespace Entity
} // namespace vhdlang
