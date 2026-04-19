#pragma once
#include "vhdlang/ASTree.hpp"
#include "vhdlang/Lexer.hpp"
#include <memory>

// Takes as input a lexer and parses it to create an AST.
// For now the idea is 1 parser per file

// Changes from 2008 grammar
//
//   name
//     : simple_name
//     | operator_symbol
//     | selected_name
//     | indexed_name
//     | slice_name
//     | attribute_name
//     ;
//     and replace with the antlr vhdl grammar version which is
//
// name
//     : (identifier | STRING_LITERAL) (name_part)*
//     ;
//
// name_part
//     : selected_name_part
//     | function_call_or_indexed_name_part
//     | slice_name_part
//     | attribute_name_part
//     ;
//
// selected_name
//     : identifier (DOT suffix)*
//     ;
//
// selected_name_part
//     : (DOT suffix)+
//     ;
//
// function_call_or_indexed_name_part
//     : LPAREN actual_parameter_part RPAREN
//     ;
//
// slice_name_part
//     : LPAREN discrete_range RPAREN
//     ;

namespace vhdlang {
class Parser {
private:
    vhdlang::Lexer& lexer;
    std::unique_ptr<ASTree> astree;

    // Gramar rules
    int parseDesignFile(ASTree* root);
    int parseDesignUnit(ASTree* parent);
    int parseContextClause(ASTree* parent);
    int parseLibraryUnit(ASTree* parent);
    int parseContextItem(ASTree* parent);
    int parsePrimaryUnit(ASTree* parent);
    int parseSecondaryUnit(ASTree* parent);
    int parseLibraryClause(ASTree* parent);
    int parseUseClause(ASTree* parent);
    int parseContextReference(ASTree* parent);
    int parseEntityDeclaration(ASTree* parent);
    int parseConfigurationDeclaration(ASTree* parent);
    int parsePackageDeclaration(ASTree* parent);
    int parsePackageInstantiationDeclaration(ASTree* parent);
    int parseContextDeclaration(ASTree* parent);
    int parseArchitectureBody(ASTree* parent);
    int parsePackageBody(ASTree* parent);
    int parseLogicalNameList(ASTree* parent);
    int parseSelectedName(ASTree* parent);
    int parseIdentifier(ASTree* parent);
    int parseEntityHeader(ASTree* parent);
    int parseEntityDeclarativePart(ASTree* parent);
    int parseEntityStatementPart(ASTree* parent);
    int parseSimpleName(ASTree* parent);
    int parseName(ASTree* parent);
    int parseConfigurationDeclarativePart(ASTree* parent);
    int parseBlockConfiguration(ASTree* parent);
    int parsePackageHeader(ASTree* parent);
    int parsePackageDeclarativePart(ASTree* parent);
    int parseGenericMapAspect(ASTree* parent);
    int parseArchitectureDeclarativePart(ASTree* parent);
    int parseArchitectureStatementPart(ASTree* parent);
    int parsePackageBodyDeclarativePart(ASTree* parent);
    int parseLogicalName(ASTree* parent);
    int parseSuffix(ASTree* parent);

    int parseGenericClause(ASTree* parent);
    int parsePortClause(ASTree* parent);
    int parseEntityDeclarativeItem(ASTree* parent);

public:
    Parser(vhdlang::Lexer& lexer) : lexer(lexer) {}
    int parse();
};
} // namespace vhdlang
