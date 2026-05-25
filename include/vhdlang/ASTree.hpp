#pragma once
#include "vhdlang/ASTNode.hpp"
#include "vhdlang/GrammarRule.hpp"
#include <memory>
#include <vector>

namespace vhdlang {
class ASTree {
private:
    std::vector<std::unique_ptr<ASTree>> children;
    const ASTree* parent;
    std::unique_ptr<ASTNode> node;
    const GrammarRule rule;

public:
    ASTree();
    ASTree(ASTree* parent, GrammarRule rule) : parent(parent), rule(rule) {}

    void addChild(std::unique_ptr<ASTree> child) {
        children.push_back(std::move(child));
    }
    const ASTree* getParent() { return parent; }
    const GrammarRule getRule() { return rule; }
    void setNode(std::unique_ptr<ASTNode> node) {
        this->node = std::move(node);
    }
    const ASTNode& getNode() { return *node; }

    // Prints the current tree and its subtrees
    void print(std::string prefix);

    // class ASTIterator {
    // private:
    //     // non-owning pointers, should I make them constant to force a read
    //     // only? Maybe the iterator would also to be to modify things.
    //     std::vector<const ASTree*> content;
    //
    // public:
    //     void init() {
    //     }
    // };
};
} // namespace vhdlang
