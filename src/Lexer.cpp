#include <iostream>
#include <regex>
#include <vhdlang/Lexer.hpp>

using namespace vhdlang;

Lexer::Lexer(std::vector<Terminal>& vhdlTerminals, std::fstream& sourceFile) :
    vhdlTerminals(vhdlTerminals), sourceFile(sourceFile) {
}

void Lexer::printTokens() {
    for (auto token : tokens) {
        std::cout << token.toString() << "\n";
    }
    std::cout << std::endl;
}

int Lexer::lexFile() {
    std::string line;
    int row = 0;
    int column = 0;
    std::smatch tokenResults;

    while (std::getline(sourceFile, line)) {
        std::string restLine = line;
        while (!restLine.empty()) {
            bool matched = false;
            for (auto& potentialTerminal : this->vhdlTerminals) {
                if (std::regex_search(restLine, tokenResults, potentialTerminal.getRegex(),
                                      std::regex_constants::match_continuous)) {
                    matched = true;
                    // std::cout << "Matched: " << tokenResults[0] << std::endl;
                    // std::cout << "Suffix: " << tokenResults.suffix() << std::endl;
                    Token newToken(tokenResults[0], potentialTerminal);
                    newToken.setColumn(column);
                    column += tokenResults[0].length();
                    newToken.setRow(row);
                    this->tokens.push_back(newToken);
                    restLine = tokenResults.suffix();
                    break;
                }
            }
            if (!matched) {
                std::cout << "Unrecognized symbol at " << row << ", " << column << std::endl;
                std::cout << "Problem in: " << line << std::endl;
                return 1;
            }
        }

        row++;
    }
    return 0;
}
