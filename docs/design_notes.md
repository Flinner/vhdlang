# Design Notes

This document will explain the design choices that were taken during the construction of this
project. The main conventions are presented here as well as why.

## Parsing

It's better to divide the parser into main blocks (architecture, entity, etc.) for the sake of
easier testing.

For now I see the following is the most appropriate idea: a main parser class that contains the
lexer and the AST. This class will call multiple (static?) classes to help with parsing.

Current "main block":
- [ ] Architecture body
- [ ] Package body
- [ ] Entity declaration
- [ ] Configuration declaration
- [ ] Package declaration
