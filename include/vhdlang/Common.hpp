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

// clang-format off
inline int parseSuffix(vhdlang::Lexer& lexer, ASTree* parent) { return PARSE_NOMATCH; }
// already in Parser.hpp
inline int parseGenericMapAspect(vhdlang::Lexer& lexer, ASTree* parent) { return PARSE_NOMATCH; }
inline int parsePackageDeclarativePart(vhdlang::Lexer& lexer, ASTree* parent) { return PARSE_NOMATCH; }
inline int parseSelectedName(vhdlang::Lexer& lexer, ASTree* parent) { return PARSE_NOMATCH; }
inline int parsePackageBodyDeclarativePart(vhdlang::Lexer& lexer, ASTree* parent) { return PARSE_NOMATCH; }
// to implement
inline int parseSubprogramDeclaration(vhdlang::Lexer& lexer, ASTree* parent) { return PARSE_NOMATCH; }
inline int parseSubprogramBody(vhdlang::Lexer& lexer, ASTree* parent) { return PARSE_NOMATCH; }
inline int parseSubprogramInstantiationDeclaration(vhdlang::Lexer& lexer, ASTree* parent) { return PARSE_NOMATCH; }
inline int parseTypeDeclaration(vhdlang::Lexer& lexer, ASTree* parent) { return PARSE_NOMATCH; }
inline int parseSubtypeDeclaration(vhdlang::Lexer& lexer, ASTree* parent) { return PARSE_NOMATCH; }
inline int parseConstantDeclaration(vhdlang::Lexer& lexer, ASTree* parent) { return PARSE_NOMATCH; }
inline int parseSignalDeclaration(vhdlang::Lexer& lexer, ASTree* parent) { return PARSE_NOMATCH; }
inline int parseVariableDeclaration(vhdlang::Lexer& lexer, ASTree* parent) { return PARSE_NOMATCH; }
inline int parseFileDeclaration(vhdlang::Lexer& lexer, ASTree* parent) { return PARSE_NOMATCH; }
inline int parseAliasDeclaration(vhdlang::Lexer& lexer, ASTree* parent) { return PARSE_NOMATCH; }
inline int parseAttributeDeclaration(vhdlang::Lexer& lexer, ASTree* parent) { return PARSE_NOMATCH; }
inline int parseAttributeSpecification(vhdlang::Lexer& lexer, ASTree* parent) { return PARSE_NOMATCH; }
inline int parseDisconnectionSpecification(vhdlang::Lexer& lexer, ASTree* parent) { return PARSE_NOMATCH; }
inline int parseGroupTemplateDeclaration(vhdlang::Lexer& lexer, ASTree* parent) { return PARSE_NOMATCH; }
inline int parseGroupDeclaration(vhdlang::Lexer& lexer, ASTree* parent) { return PARSE_NOMATCH; }
inline int parseConcurrentAssertionStatement(vhdlang::Lexer& lexer, ASTree* parent) { return PARSE_NOMATCH; }
inline int parseProcessStatement(vhdlang::Lexer& lexer, ASTree* parent) { return PARSE_NOMATCH; }
inline int parseConcurrentProcedureCallStatement(vhdlang::Lexer& lexer, ASTree* parent) { return PARSE_NOMATCH; }
inline int parseExpression(vhdlang::Lexer& lexer, ASTree* parent) { return PARSE_NOMATCH; }
inline int parseGenericClause(vhdlang::Lexer& lexer, ASTree* parent) { return PARSE_NOMATCH; }
inline int parseGenericList(vhdlang::Lexer& lexer, ASTree* parent) { return PARSE_NOMATCH; }
inline int parseInterfaceTypeDeclaration(vhdlang::Lexer& lexer, ASTree* parent) { return PARSE_NOMATCH; }
inline int parseInterfaceSubprogramDeclaration(vhdlang::Lexer& lexer, ASTree* parent) { return PARSE_NOMATCH; }
inline int parseInterfacePackageDeclaration(vhdlang::Lexer& lexer, ASTree* parent) { return PARSE_NOMATCH; }
inline int parseInterfaceConstantDeclaration(vhdlang::Lexer& lexer, ASTree* parent) { return PARSE_NOMATCH; }
inline int parseInterfaceVariableDeclaration(vhdlang::Lexer& lexer, ASTree* parent) { return PARSE_NOMATCH; }
inline int parseInterfaceFileDeclaration(vhdlang::Lexer& lexer, ASTree* parent) { return PARSE_NOMATCH; }
inline int parseResolutionIndication(vhdlang::Lexer& lexer, ASTree* parent) { return PARSE_NOMATCH; }
inline int parseActualParameterPart(vhdlang::Lexer& lexer, ASTree* parent) { return PARSE_NOMATCH; }
inline int parseDiscreteRange(vhdlang::Lexer& lexer, ASTree* parent) { return PARSE_NOMATCH; }
inline int parseAttributeDesignator(vhdlang::Lexer& lexer, ASTree* parent) { return PARSE_NOMATCH; }
} // namespace Common
} // namespace vhdlang
