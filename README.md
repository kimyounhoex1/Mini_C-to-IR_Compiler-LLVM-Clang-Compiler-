# Mini C-to-IR Compiler // LLVM-Clang-Compiler 

Toy compiler project designed to understand how real compilers (Clang/LLVM) work.  
C-subset source → Custom IR → (optionally) LLVM IR emission.

---

## ✨ Features

- **Frontend**
  - Lexer: tokenize C-like source
  - Parser: recursive descent parser (Expr, If, While, Function)
  - AST Builder: JSON export

- **Semantic Analysis**
  - Scope + Symbol table
  - Simple type checker (int, float, bool)

- **IR**
  - Custom 3-address code IR
  - Constant folding optimization
  - Dead code elimination

- **Backend**
  - Export to LLVM IR
  - (Optional) Translate to pseudo-NPU instructions (GEMM, CONV, ADD)

---

## 📚 Learning Goals
- Understand compiler pipeline (Lex → Parse → AST → IR → CodeGen)
- Implement basic optimizations (constant folding, DCE)
- Learn LLVM IR structure (SSA form, passes)
- Map high-level IR ops to NPU-like instructions
