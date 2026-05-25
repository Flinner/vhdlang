#include "vhdlang/GrammarRule.hpp"

using namespace vhdlang;

std::string vhdlang::grammarRuleName(GrammarRule rule) {
    // clang-format off
    switch (rule) {
    case GrammarRule::DESIGN_FILE: return "DESIGN_FILE";
    case GrammarRule::DESIGN_UNIT: return "DESIGN_UNIT";
    case GrammarRule::CONTEXT_CLAUSE: return "CONTEXT_CLAUSE";
    case GrammarRule::LIBRARY_UNIT: return "LIBRARY_UNIT";
    case GrammarRule::CONTEXT_ITEM: return "CONTEXT_ITEM";
    case GrammarRule::PRIMARY_UNIT: return "PRIMARY_UNIT";
    case GrammarRule::SECONDARY_UNIT: return "SECONDARY_UNIT";
    case GrammarRule::LIBRARY_CLAUSE: return "LIBRARY_CLAUSE";
    case GrammarRule::USE_CLAUSE: return "USE_CLAUSE";
    case GrammarRule::CONTEXT_REFERENCE: return "CONTEXT_REFERENCE";
    case GrammarRule::ENTITY_DECLARATION: return "ENTITY_DECLARATION";
    case GrammarRule::CONFIGURATION_DECLARATION: return "CONFIGURATION_DECLARATION";
    case GrammarRule::PACKAGE_DECLARATION: return "PACKAGE_DECLARATION";
    case GrammarRule::PACKAGE_INSTANTIATION_DECLARATION: return "PACKAGE_INSTANTIATION_DECLARATION";
    case GrammarRule::CONTEXT_DECLARATION: return "CONTEXT_DECLARATION";
    case GrammarRule::ARCHITECTURE_BODY: return "ARCHITECTURE_BODY";
    case GrammarRule::PACKAGE_BODY: return "PACKAGE_BODY";
    case GrammarRule::LOGICAL_NAME_LIST: return "LOGICAL_NAME_LIST";
    case GrammarRule::SELECTED_NAME: return "SELECTED_NAME";
    case GrammarRule::IDENTIFIER: return "IDENTIFIER";
    case GrammarRule::ENTITY_HEADER: return "ENTITY_HEADER";
    case GrammarRule::ENTITY_DECLARATIVE_PART: return "ENTITY_DECLARATIVE_PART";
    case GrammarRule::ENTITY_STATEMENT_PART: return "ENTITY_STATEMENT_PART";
    case GrammarRule::NAME: return "NAME";
    case GrammarRule::CONFIGURATION_DECLARATIVE_PART: return "CONFIGURATION_DECLARATIVE_PART";
    case GrammarRule::BLOCK_CONFIGURATION: return "BLOCK_CONFIGURATION";
    case GrammarRule::PACKAGE_DECLARATIVE_PART: return "PACKAGE_DECLARATIVE_PART";
    case GrammarRule::GENERIC_MAP_ASPECT: return "GENERIC_MAP_ASPECT";
    case GrammarRule::ARCHITECTURE_DECLARATIVE_PART: return "ARCHITECTURE_DECLARATIVE_PART";
    case GrammarRule::ARCHITECTURE_STATEMENT_PART: return "ARCHITECTURE_STATEMENT_PART";
    case GrammarRule::PACKAGE_BODY_DECLARATIVE_PART: return "PACKAGE_BODY_DECLARATIVE_PART";
    case GrammarRule::LOGICAL_NAME: return "LOGICAL_NAME";
    case GrammarRule::SUFFIX: return "SUFFIX";
    case GrammarRule::GENERIC_CLAUSE: return "GENERIC_CLAUSE";
    case GrammarRule::ARCHITECTURE_STATEMENT: return "ARCHITECTURE_STATEMENT";
    case GrammarRule::PORT_CLAUSE: return "PORT_CLAUSE";
    case GrammarRule::PORT_LIST: return "PORT_LIST";
    case GrammarRule::INTERFACE_LIST: return "INTERFACE_LIST";
    case GrammarRule::INTERFACE_DECLARATION: return "INTERFACE_DECLARATION";
    case GrammarRule::INTERFACE_OBJECT_DECLARATION: return "INTERFACE_OBJECT_DECLARATION";
    case GrammarRule::INTERFACE_SIGNAL_DECLARATION: return "INTERFACE_SIGNAL_DECLARATION";
    case GrammarRule::IDENTIFIER_LIST: return "IDENTIFIER_LIST";
    case GrammarRule::MODE_RULE: return "MODE_RULE";
    case GrammarRule::SUBTYPE_DECLARATION: return "SUBTYPE_DECLARATION";
    case GrammarRule::NAME_PART: return "NAME_PART";
    default: return "NOT IMPLEMENTED YET";
            // clang-format on
    }
}
