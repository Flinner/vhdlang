# VHDLang - VHDL Parser

VHDL Parser that transforms source code into an AST.

## Current TODO List

List to be updated and improved once there is a proper skeleton

- [ ] Basic Lexer (tokenizer)
- [ ] Basic Parser
- [ ] Basic test environment
- [ ] Some sort of "compiler" to check variable scopes, etc.

After these steps are implemented, the next goal would be to add more features
and have the option to choose a standard


## Build Commands

```bash
 cmake -GNinja -DENABLE_DOCS=ON -B build
 ninja -C build
```
