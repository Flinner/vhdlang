#pragma once

// Contains common parsing patterns

#include "vhdlang/ASTree.hpp"
#include "vhdlang/Lexer.hpp"
#include "vhdlang/Parser.hpp"

namespace vhdlang {
namespace Common {

// already implemented
int parseIdentifier(vhdlang::Lexer& lexer, ASTree* parent);
int parsePackageDeclaration(vhdlang::Lexer& lexer, ASTree* parent);
int parsePackageBody(vhdlang::Lexer& lexer, ASTree* parent);
int parsePackageInstantiationDeclaration(vhdlang::Lexer& lexer, ASTree* parent);
int parseUseClause(vhdlang::Lexer& lexer, ASTree* parent);
int parseInterfaceList(vhdlang::Lexer& lexer, ASTree* parent);
int parseInterfaceDeclaration(vhdlang::Lexer& lexer, ASTree* parent);
int parseInterfaceObjectDeclaration(vhdlang::Lexer& lexer, ASTree* parent);
int parseInterfaceSignalDeclaration(vhdlang::Lexer& lexer, ASTree* parent);
int parseIdentifierList(vhdlang::Lexer& lexer, ASTree* parent);
int parseModeRule(vhdlang::Lexer& lexer, ASTree* parent);
int parseSubtypeIndication(vhdlang::Lexer& lexer, ASTree* parent);
int parseName(vhdlang::Lexer& lexer, ASTree* parent);

int parseNamePart(vhdlang::Lexer& lexer, ASTree* parent);
int parseSuffix(vhdlang::Lexer& lexer, ASTree* parent);
// to implement
// clang-format off
int parseSubprogramDeclaration(vhdlang::Lexer& lexer, ASTree* parent) { return PARSE_NOMATCH; }
int parseSubprogramBody(vhdlang::Lexer& lexer, ASTree* parent) { return PARSE_NOMATCH; }
int parseSubprogramInstantiationDeclaration(vhdlang::Lexer& lexer, ASTree* parent) { return PARSE_NOMATCH; }
int parseTypeDeclaration(vhdlang::Lexer& lexer, ASTree* parent) { return PARSE_NOMATCH; }
int parseSubtypeDeclaration(vhdlang::Lexer& lexer, ASTree* parent) { return PARSE_NOMATCH; }
int parseConstantDeclaration(vhdlang::Lexer& lexer, ASTree* parent) { return PARSE_NOMATCH; }
int parseSignalDeclaration(vhdlang::Lexer& lexer, ASTree* parent) { return PARSE_NOMATCH; }
int parseVariableDeclaration(vhdlang::Lexer& lexer, ASTree* parent) { return PARSE_NOMATCH; }
int parseFileDeclaration(vhdlang::Lexer& lexer, ASTree* parent) { return PARSE_NOMATCH; }
int parseAliasDeclaration(vhdlang::Lexer& lexer, ASTree* parent) { return PARSE_NOMATCH; }
int parseAttributeDeclaration(vhdlang::Lexer& lexer, ASTree* parent) { return PARSE_NOMATCH; }
int parseAttributeSpecification(vhdlang::Lexer& lexer, ASTree* parent) { return PARSE_NOMATCH; }
int parseDisconnectionSpecification(vhdlang::Lexer& lexer, ASTree* parent) { return PARSE_NOMATCH; }
int parseGroupTemplateDeclaration(vhdlang::Lexer& lexer, ASTree* parent) { return PARSE_NOMATCH; }
int parseGroupDeclaration(vhdlang::Lexer& lexer, ASTree* parent) { return PARSE_NOMATCH; }
int parseConcurrentAssertionStatement(vhdlang::Lexer& lexer, ASTree* parent) { return PARSE_NOMATCH; }
int parseProcessStatement(vhdlang::Lexer& lexer, ASTree* parent) { return PARSE_NOMATCH; }
int parseConcurrentProcedureCallStatement(vhdlang::Lexer& lexer, ASTree* parent) { return PARSE_NOMATCH; }
int parseExpression(vhdlang::Lexer& lexer, ASTree* parent) { return PARSE_NOMATCH; }
int parseGenericClause(vhdlang::Lexer& lexer, ASTree* parent) { return PARSE_NOMATCH; }
int parseGenericList(vhdlang::Lexer& lexer, ASTree* parent) { return PARSE_NOMATCH; }
int parseInterfaceTypeDeclaration(vhdlang::Lexer& lexer, ASTree* parent) { return PARSE_NOMATCH; }
int parseInterfaceSubprogramDeclaration(vhdlang::Lexer& lexer, ASTree* parent) { return PARSE_NOMATCH; }
int parseInterfacePackageDeclaration(vhdlang::Lexer& lexer, ASTree* parent) { return PARSE_NOMATCH; }
int parseInterfaceConstantDeclaration(vhdlang::Lexer& lexer, ASTree* parent) { return PARSE_NOMATCH; }
int parseInterfaceVariableDeclaration(vhdlang::Lexer& lexer, ASTree* parent) { return PARSE_NOMATCH; }
int parseInterfaceFileDeclaration(vhdlang::Lexer& lexer, ASTree* parent) { return PARSE_NOMATCH; }
int parseResolutionIndication(vhdlang::Lexer& lexer, ASTree* parent) { return PARSE_NOMATCH; }
} // namespace Common
} // namespace vhdlang
