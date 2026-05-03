#pragma once
#include "vhdlang/ASTree.hpp"
#include "vhdlang/Lexer.hpp"
#include <memory>

// Different return values to indicate if we took the wrong option or actual
// error
#define PARSE_NOMATCH 1
#define PARSE_ERROR 2

// Takes as input a lexer and parses it to create an AST.
// For now the idea is 1 parser per file

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
    int parseName(ASTree* parent);
    int parseConfigurationDeclarativePart(ASTree* parent);
    int parseBlockConfiguration(ASTree* parent);
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
    int parseEntityStatement(ASTree* parent);
    int parseNamePart(ASTree* parent);
    int parseConfigurationDeclarativeItem(ASTree* parent);
    int parseBlockSpecification(ASTree* parent);
    int parseConfigurationItem(ASTree* parent);
    int parsePackageDeclarativeItem(ASTree* parent);
    int parseAssociationList(ASTree* parent);
    int parseBlockDeclarativeItem(ASTree* parent);
    int parseArchitectureStatement(ASTree* parent);
    int parseBodyDeclarativeItem(ASTree* parent);

    int parseBlockStatement(ASTree* parent);

public:
    Parser(vhdlang::Lexer& lexer) : lexer(lexer) {}
    int parse();
};
} // namespace vhdlang
