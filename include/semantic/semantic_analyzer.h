#pragma once
#include "../ast/visitor.h"
#include "../symbol/symbol_table.h"

class SemanticAnalyzer : public Visitor {
    SymbolTable symbols;

public:
    void visit(VarDecl& node) override;      // 선언 → SymbolTable 등록
    void visit(Identifier& node) override;   // 사용 → lookup 검사
    void visit(Assign& node) override;       // 대입 → 좌변 선언 체크, RHS 순회
    void visit(Block& node) override;        // enterScope/exitScope
    void visit(Number& node) override;
    void visit(Boolean& node) override;
    void visit(BinaryOp& node) override;
    void visit(IfStmt& node) override;
    void visit(WhileStmt& node) override;
    void visit(FunctionDecl& node) override;
    
};