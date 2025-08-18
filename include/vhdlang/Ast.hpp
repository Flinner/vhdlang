/// @file Ast.hpp
/// @brief VHDL-{93,2002,2008,2019} AST hierarchy for hand-rolled parser.
/// @details
/// This file defines all AST nodes for declarations, statements, expressions,
/// and type specifications in VHDL.
/// ASTNode
///  ├── Decl                   (declarations)
///  │    ├── EntityDecl
///  │    ├── ArchDecl
///  │    ├── SignalDecl
///  │    ├── VarDecl
///  │    ├── ConstDecl
///  │    └── TypeDecl
///  │
///  ├── Stmt                   (statements inside processes, arch, etc.)
///  │    ├── SeqStmt           (sequential)
///  │    │     ├── SeqAssign
///  │    │     ├── IfStmt
///  │    │     ├── CaseStmt
///  │    │     ├── LoopStmt
///  │    │     └── WaitStmt
///  │    │
///  │    └── ConcurStmt        (concurrent)
///  │          ├── ConcurAssign
///  │          └── ProcessStmt
///  │
///  ├── Expr                   (expressions)
///  │    ├── NameExpr
///  │    ├── LiteralExpr
///  │    │     ├── IntLiteral
///  │    │     ├── RealLiteral
///  │    │     └── StringLiteral
///  │    ├── BinaryExpr
///  │    ├── UnaryExpr
///  │    ├── CallExpr           (function call / array index)
///  │    └── AggregateExpr
///  │
///  └── TypeSpec
///       ├── SubtypeIndication
///       ├── ArrayType
///       ├── RecordType
///       └── EnumType

#pragma once

/// \TODO: Remove from this file.
class SourceRange {
    /// @TODO: use the lexer's end_{line,column}
    int begLine{}, begCol{}; //, endLine{}, endCol{};
};

///===----------------------------------------------------------------------===//
/// @brief Base class for all AST nodes.
///===----------------------------------------------------------------------===//
class ASTNode {
private:
    SourceRange loc;

protected:
    virtual ~ASTNode() = default;
};

///===----------------------------------------------------------------------===//
/// @defgroup Declarations VHDL Declarations
/// Base class: Decl
/// Subclasses: EntityDecl, ArchDecl, SignalDecl, VarDecl, ConstDecl, TypeDecl
///@{
///===----------------------------------------------------------------------===//

/// @brief Base class for all declarations.
class Decl : public ASTNode {};

class EntityDecl : public Decl { /* ... */
};
class ArchDecl : public Decl { /* ... */
};
class SignalDecl : public Decl { /* ... */
};
class VarDecl : public Decl { /* ... */
};
class ConstDecl : public Decl { /* ... */
};
class TypeDecl : public Decl { /* ... */
};

///@} // end of Declarations

///===----------------------------------------------------------------------===//
/// @defgroup Statements VHDL Statements
/// Base class: Stmt
/// Sequential: SeqStmt, SeqAssign, IfStmt, CaseStmt, LoopStmt, WaitStmt
/// Concurrent: ConcurStmt, ConcurAssign, ProcessStmt
///@{
///===----------------------------------------------------------------------===//

/// @brief Base class for all statements.
class Stmt : public ASTNode {};

class SeqStmt : public Stmt {};
class SeqAssign : public SeqStmt { /* ... */
};
class IfStmt : public SeqStmt { /* ... */
};
class CaseStmt : public SeqStmt { /* ... */
};
class LoopStmt : public SeqStmt { /* ... */
};
class WaitStmt : public SeqStmt { /* ... */
};

class ConcurStmt : public Stmt {};
class ConcurAssign : public ConcurStmt { /* ... */
};
class ProcessStmt : public ConcurStmt { /* ... */
};

///@} // end of Statements

///===----------------------------------------------------------------------===//
/// @defgroup Expressions VHDL Expressions
/// Base class: Expr
/// Literals: IntLiteral, RealLiteral, StringLiteral
/// Operations: BinaryExpr, UnaryExpr
/// Calls: CallExpr
/// Aggregates: AggregateExpr
///@{
///===----------------------------------------------------------------------===//

/// @brief Base class for all expressions.
class Expr : public ASTNode {};

class NameExpr : public Expr { /* ... */
};

class LiteralExpr : public Expr {};
class IntLiteral : public LiteralExpr { /* ... */
};
class RealLiteral : public LiteralExpr { /* ... */
};
class StringLiteral : public LiteralExpr { /* ... */
};

class BinaryExpr : public Expr { /* ... */
};
class UnaryExpr : public Expr { /* ... */
};
class CallExpr : public Expr { /* ... */
};
class AggregateExpr : public Expr { /* ... */
};

///@} // end of Expressions

///===----------------------------------------------------------------------===//
/// @defgroup TypeSpecs VHDL Type Specifications
/// Base class: TypeSpec
/// Subtype: SubtypeIndication
/// ArrayType, RecordType, EnumType
///@{
///===----------------------------------------------------------------------===//

/// @brief Base class for all type specifications.
class TypeSpec : public ASTNode {};

class SubtypeIndication : public TypeSpec { /* ... */
};
class ArrayType : public TypeSpec { /* ... */
};
class RecordType : public TypeSpec { /* ... */
};
class EnumType : public TypeSpec { /* ... */
};

///@} // end of TypeSpecs
