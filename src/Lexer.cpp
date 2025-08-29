#include "vhdlang/Lexer.hpp"

#include <iostream>
#include <regex>

using namespace vhdlang;

Lexer::Lexer(std::fstream* sourceFile) : sourceFile(sourceFile) {
}
Lexer::Lexer(std::string inputText) : sourceFile(NULL), fileContents(inputText) {
}

void Lexer::printTokens() {
    for (auto token : tokens) {
        std::cout << token.toString() << " ";
    }
    std::cout << std::endl;
}

int Lexer::lexFile() {
    int line = 1;
    int column = 1;
    std::smatch tokenResults;

    // Read file and put a pointer to track end of regex matches
    if (sourceFile != NULL) {
        fileContents = std::string((std::istreambuf_iterator<char>(*sourceFile)),
                                   std::istreambuf_iterator<char>());
    }
    std::string currentPosition = fileContents;

    while (!currentPosition.empty()) {
        bool matched = false;
        for (auto& potentialTerminal : vhdlTerminals) {
            if (std::regex_search(currentPosition, tokenResults, potentialTerminal.getRegex(),
                                  std::regex_constants::match_continuous)) {
                matched = true;
                // std::cout << "Matched: " << tokenResults[0] << std::endl;
                // std::cout << "Suffix: " << tokenResults.suffix() << std::endl;

                // Create Token
                Token newToken(tokenResults[0], potentialTerminal);
                newToken.setColumn(column);
                newToken.setLine(line);
                this->tokens.push_back(newToken);

                // Update positions
                currentPosition = tokenResults.suffix();
                if (newToken.getId().getName() == TerminalName::NEWLINE) {
                    line += tokenResults[0].length();
                    column = 1;
                }
                else {
                    column += tokenResults[0].length();
                }

                break;
            }
        }
        if (!matched) {
            std::cerr << "Unrecognized symbol at " << line << ", " << column << std::endl;
            std::cerr << currentPosition.substr(0, currentPosition.find('\n')) << std::endl;
            return 1;
        }
    }
    return 0;
}

const std::vector<Terminal> Lexer::vhdlTerminals = {
    Terminal(TerminalName::WHITESPACE, "Whitespace", "[ \\t]+"),
    Terminal(TerminalName::NEWLINE, "NEWLINE", "[\\n\\r]+"),
    Terminal(TerminalName::BIT_STRING_BINARY, "BIT_STRING_BINARY", "B\"[01_]+\""),
    Terminal(TerminalName::BIT_STRING_OCTAL, "BIT_STRING_OCTAL", "O\"[0-7_]+\""),
    Terminal(TerminalName::BIT_STRING_HEX, "BIT_STRING_HEX", "X\"[_[:xdigit:]]\""),
    Terminal(TerminalName::REAL_NUMBER, "REAL_NUMBER", "\\d+\\.\\d+"), // TODO add exponent support
    Terminal(TerminalName::CHARACTER_LITERAL, "CHARACTER_LITERAL", "'.'"),
    Terminal(TerminalName::STRING_LITERAL, "STRING_LITERAL", "\"[^\\n\"]*\"(\"[^\\n\"]*\")*"),
    Terminal(TerminalName::COMMENT, "Comment", "--[^\\n]*"),
    Terminal(TerminalName::DOT, "DOT", "\\."),
    Terminal(TerminalName::COMMA, "COMMA", ","),
    Terminal(TerminalName::SEMICOLON, "SEMICOLON", ";"),
    Terminal(TerminalName::COLON, "COLON", ":"),
    Terminal(TerminalName::PLUS, "PLUS", "\\+"),
    Terminal(TerminalName::MINUS, "MINUS", "-"),
    Terminal(TerminalName::STAR, "STAR", "\\*"),
    Terminal(TerminalName::CARET, "CARET", "\\^"),
    Terminal(TerminalName::EQUALS, "EQUALS", "="),
    Terminal(TerminalName::EXCLAMATION, "EXCLAMATION", "!"),
    Terminal(TerminalName::QUESTION, "QUESTION", "\\?"),
    Terminal(TerminalName::LEFT_PARENTHESIS, "LEFT_PARENTHESIS", "\\("),
    Terminal(TerminalName::RIGHT_PARENTHESIS, "RIGHT_PARENTHESIS", "\\)"),
    Terminal(TerminalName::LEFT_BRACKET, "LEFT_BRACKET", "\\["),
    Terminal(TerminalName::RIGHT_BRACKET, "RIGHT_BRACKET", "\\]"),
    Terminal(TerminalName::LEFT_CURLY, "LEFT_CURLY", "\\{"),
    Terminal(TerminalName::RIGHT_CURLY, "RIGHT_CURLY", "\\}"),
    Terminal(TerminalName::GREATER_THAN, "GREATER_THAN", ">"),
    Terminal(TerminalName::LESS_THAN, "LESS_THAN", "<"),
    Terminal(TerminalName::SINGLE_QUOTE, "SINGLE_QUOTE", "'"),
    Terminal(TerminalName::DOUBLE_QUOTE, "DOUBLE_QUOTE", "\""),
    Terminal(TerminalName::BACKSLASH, "BACKSLASH", "\\\\"),
    Terminal(TerminalName::INTEGER, "Integer", "\\d+"),
    Terminal(TerminalName::AMPERSAND, "AMPERSAND", "&"),
    Terminal(TerminalName::SLASH, "SLASH", "/"),
    Terminal(TerminalName::TILDE, "TILDE", "~"),
    Terminal(TerminalName::BACKTICK, "BACKTICK", "`"),
    Terminal(TerminalName::VERTICAL_BAR, "VERTICAL_BAR", "\\|"),
    Terminal(TerminalName::RES_ABS, "ABS", "\\bABS\\b"),
    Terminal(TerminalName::RES_ACCESS, "ACCESS", "\\bACCESS\\b"),
    Terminal(TerminalName::RES_AFTER, "AFTER", "\\bAFTER\\b"),
    Terminal(TerminalName::RES_ALIAS, "ALIAS", "\\bALIAS\\b"),
    Terminal(TerminalName::RES_ALL, "ALL", "\\bALL\\b"),
    Terminal(TerminalName::RES_AND, "AND", "\\bAND\\b"),
    Terminal(TerminalName::RES_ARCHITECTURE, "ARCHITECTURE", "\\bARCHITECTURE\\b"),
    Terminal(TerminalName::RES_ARRAY, "ARRAY", "\\bARRAY\\b"),
    Terminal(TerminalName::RES_ASSERT, "ASSERT", "\\bASSERT\\b"),
    Terminal(TerminalName::RES_ATTRIBUTE, "ATTRIBUTE", "\\bATTRIBUTE\\b"),
    Terminal(TerminalName::RES_BEGIN, "BEGIN", "\\bBEGIN\\b"),
    Terminal(TerminalName::RES_BLOCK, "BLOCK", "\\bBLOCK\\b"),
    Terminal(TerminalName::RES_BODY, "BODY", "\\bBODY\\b"),
    Terminal(TerminalName::RES_BUFFER, "BUFFER", "\\bBUFFER\\b"),
    Terminal(TerminalName::RES_BUS, "BUS", "\\bBUS\\b"),
    Terminal(TerminalName::RES_CASE, "CASE", "\\bCASE\\b"),
    Terminal(TerminalName::RES_COMPONENT, "COMPONENT", "\\bCOMPONENT\\b"),
    Terminal(TerminalName::RES_CONFIGURATION, "CONFIGURATION", "\\bCONFIGURATION\\b"),
    Terminal(TerminalName::RES_CONSTANT, "CONSTANT", "\\bCONSTANT\\b"),
    Terminal(TerminalName::RES_DISCONNECT, "DISCONNECT", "\\bDISCONNECT\\b"),
    Terminal(TerminalName::RES_DOWNTO, "DOWNTO", "\\bDOWNTO\\b"),
    Terminal(TerminalName::RES_ELSE, "ELSE", "\\bELSE\\b"),
    Terminal(TerminalName::RES_ELSIF, "ELSIF", "\\bELSIF\\b"),
    Terminal(TerminalName::RES_END, "END", "\\bEND\\b"),
    Terminal(TerminalName::RES_ENTITY, "ENTITY", "\\bENTITY\\b"),
    Terminal(TerminalName::RES_EXIT, "EXIT", "\\bEXIT\\b"),
    Terminal(TerminalName::RES_FILE, "FILE", "\\bFILE\\b"),
    Terminal(TerminalName::RES_FOR, "FOR", "\\bFOR\\b"),
    Terminal(TerminalName::RES_FUNCTION, "FUNCTION", "\\bFUNCTION\\b"),
    Terminal(TerminalName::RES_GENERATE, "GENERATE", "\\bGENERATE\\b"),
    Terminal(TerminalName::RES_GENERIC, "GENERIC", "\\bGENERIC\\b"),
    Terminal(TerminalName::RES_GROUP, "GROUP", "\\bGROUP\\b"),
    Terminal(TerminalName::RES_GUARDED, "GUARDED", "\\bGUARDED\\b"),
    Terminal(TerminalName::RES_IF, "IF", "\\bIF\\b"),
    Terminal(TerminalName::RES_IMPURE, "IMPURE", "\\bIMPURE\\b"),
    Terminal(TerminalName::RES_IN, "IN", "\\bIN\\b"),
    Terminal(TerminalName::RES_INERTIAL, "INERTIAL", "\\bINERTIAL\\b"),
    Terminal(TerminalName::RES_INOUT, "INOUT", "\\bINOUT\\b"),
    Terminal(TerminalName::RES_IS, "IS", "\\bIS\\b"),
    Terminal(TerminalName::RES_LABEL, "LABEL", "\\bLABEL\\b"),
    Terminal(TerminalName::RES_LIBRARY, "LIBRARY", "\\bLIBRARY\\b"),
    Terminal(TerminalName::RES_LINKAGE, "LINKAGE", "\\bLINKAGE\\b"),
    Terminal(TerminalName::RES_LITERAL, "LITERAL", "\\bLITERAL\\b"),
    Terminal(TerminalName::RES_LOOP, "LOOP", "\\bLOOP\\b"),
    Terminal(TerminalName::RES_MAP, "MAP", "\\bMAP\\b"),
    Terminal(TerminalName::RES_MOD, "MOD", "\\bMOD\\b"),
    Terminal(TerminalName::RES_NAND, "NAND", "\\bNAND\\b"),
    Terminal(TerminalName::RES_NEW, "NEW", "\\bNEW\\b"),
    Terminal(TerminalName::RES_NEXT, "NEXT", "\\bNEXT\\b"),
    Terminal(TerminalName::RES_NOR, "NOR", "\\bNOR\\b"),
    Terminal(TerminalName::RES_NOT, "NOT", "\\bNOT\\b"),
    Terminal(TerminalName::RES_NULL, "NULL", "\\bNULL\\b"),
    Terminal(TerminalName::RES_OF, "OF", "\\bOF\\b"),
    Terminal(TerminalName::RES_ON, "ON", "\\bON\\b"),
    Terminal(TerminalName::RES_OPEN, "OPEN", "\\bOPEN\\b"),
    Terminal(TerminalName::RES_OR, "OR", "\\bOR\\b"),
    Terminal(TerminalName::RES_OTHERS, "OTHERS", "\\bOTHERS\\b"),
    Terminal(TerminalName::RES_OUT, "OUT", "\\bOUT\\b"),
    Terminal(TerminalName::RES_PACKAGE, "PACKAGE", "\\bPACKAGE\\b"),
    Terminal(TerminalName::RES_PORT, "PORT", "\\bPORT\\b"),
    Terminal(TerminalName::RES_POSTPONED, "POSTPONED", "\\bPOSTPONED\\b"),
    Terminal(TerminalName::RES_PROCEDURE, "PROCEDURE", "\\bPROCEDURE\\b"),
    Terminal(TerminalName::RES_PROCESS, "PROCESS", "\\bPROCESS\\b"),
    Terminal(TerminalName::RES_PURE, "PURE", "\\bPURE\\b"),
    Terminal(TerminalName::RES_RANGE, "RANGE", "\\bRANGE\\b"),
    Terminal(TerminalName::RES_RECORD, "RECORD", "\\bRECORD\\b"),
    Terminal(TerminalName::RES_REGISTER, "REGISTER", "\\bREGISTER\\b"),
    Terminal(TerminalName::RES_REJECT, "REJECT", "\\bREJECT\\b"),
    Terminal(TerminalName::RES_REM, "REM", "\\bREM\\b"),
    Terminal(TerminalName::RES_REPORT, "REPORT", "\\bREPORT\\b"),
    Terminal(TerminalName::RES_RETURN, "RETURN", "\\bRETURN\\b"),
    Terminal(TerminalName::RES_ROL, "ROL", "\\bROL\\b"),
    Terminal(TerminalName::RES_ROR, "ROR", "\\bROR\\b"),
    Terminal(TerminalName::RES_SELECT, "SELECT", "\\bSELECT\\b"),
    Terminal(TerminalName::RES_SEVERITY, "SEVERITY", "\\bSEVERITY\\b"),
    Terminal(TerminalName::RES_SIGNAL, "SIGNAL", "\\bSIGNAL\\b"),
    Terminal(TerminalName::RES_SHARED, "SHARED", "\\bSHARED\\b"),
    Terminal(TerminalName::RES_SLA, "SLA", "\\bSLA\\b"),
    Terminal(TerminalName::RES_SLL, "SLL", "\\bSLL\\b"),
    Terminal(TerminalName::RES_SRA, "SRA", "\\bSRA\\b"),
    Terminal(TerminalName::RES_SRL, "SRL", "\\bSRL\\b"),
    Terminal(TerminalName::RES_SUBTYPE, "SUBTYPE", "\\bSUBTYPE\\b"),
    Terminal(TerminalName::RES_THEN, "THEN", "\\bTHEN\\b"),
    Terminal(TerminalName::RES_TO, "TO", "\\bTO\\b"),
    Terminal(TerminalName::RES_TRANSPORT, "TRANSPORT", "\\bTRANSPORT\\b"),
    Terminal(TerminalName::RES_TYPE, "TYPE", "\\bTYPE\\b"),
    Terminal(TerminalName::RES_UNAFFECTED, "UNAFFECTED", "\\bUNAFFECTED\\b"),
    Terminal(TerminalName::RES_UNITS, "UNITS", "\\bUNITS\\b"),
    Terminal(TerminalName::RES_UNTIL, "UNTIL", "\\bUNTIL\\b"),
    Terminal(TerminalName::RES_USE, "USE", "\\bUSE\\b"),
    Terminal(TerminalName::RES_VARIABLE, "VARIABLE", "\\bVARIABLE\\b"),
    Terminal(TerminalName::RES_WAIT, "WAIT", "\\bWAIT\\b"),
    Terminal(TerminalName::RES_WHEN, "WHEN", "\\bWHEN\\b"),
    Terminal(TerminalName::RES_WHILE, "WHILE", "\\bWHILE\\b"),
    Terminal(TerminalName::RES_WITH, "WITH", "\\bWITH\\b"),
    Terminal(TerminalName::RES_XNOR, "XNOR", "\\bXNOR\\b"),
    Terminal(TerminalName::RES_XOR, "XOR", "\\bXOR\\b"),
    Terminal(TerminalName::BASIC_IDENTIFIER, "BASIC_IDENTIFIER", "[a-zA-Z](_\\w|\\w)*"),
    Terminal(TerminalName::EXTENDED_IDENTIFIER, "EXTENDED_IDENTIFIER", "\\\\[^\\\\\\n]+\\\\"),
    Terminal(TerminalName::IDENTIFIER, "Identifier", "\\w+")};
