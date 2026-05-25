#include "vhdlang/ASTree.hpp"

#include <iostream>
#include "vhdlang/GrammarRule.hpp"

using namespace vhdlang;

void ASTree::print(std::string prefix) {
    std::cout << prefix << grammarRuleName(this->getRule()) << std::endl;;

    for (auto it = children.begin(); it != children.end(); it++) {
        (*it)->print(prefix + "|  ");
    }
}
