#pragma once

#include "vhdlang/ASTNode.hpp"
#include <string>

namespace vhdlang {
class NodeIdentifier : public ASTNode {
private:
    std::string identifier;

public:
    NodeIdentifier(std::string identifier) { this->identifier = identifier; }
    std::string getIdentifier() { return identifier; }
};
} // namespace vhdlang
