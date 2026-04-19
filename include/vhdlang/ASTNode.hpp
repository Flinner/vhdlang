#pragma once

///===----------------------------------------------------------------------===//
/// @brief Base class for all AST nodes.
///===----------------------------------------------------------------------===//
class ASTNode {
private:
    int line, column;

protected:
    // virtual ~ASTNode() = default;
    int getLine() { return line; }
    int getColumn() { return column; }
};

