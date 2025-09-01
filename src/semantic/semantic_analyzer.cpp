#include "../../include/semantic/semantic_analyzer.h"
#include <iostream>

void SemanticAnalyzer::visit(VarDecl& node){
  SymbolInfo info{node.type, 0, 0};
  if (!symbols.declare(node.name, info)) {
    std::cerr << "Error: 중복 선언된 변수 '" << node.name << "'\n";
  }
}

void SemanticAnalyzer::visit(Identifier& node) {
  auto result = symbols.lookup(node.name);
  if(!result) {
    std::cerr << "Error: 선언되지 않은 변수 '" << node.name << "' 사용\n";
  }
}

void SemanticAnalyzer::visit(Assign& node) {
  auto lhs = symbols.lookup(node.name);
  if(!lhs) {
    std::cerr << "Error: 선언되지 않은 변수 '" << node.name << "'에 대입\n";
  }
  if(node.expr) {
   node.expr->accept(*this); 
  }
}

void SemanticAnalyzer::visit(Block& node) {
  symbols.enterScope();
  for (auto* stmt : node.stmts) {
    stmt->accept(*this);
  }
  symbols.exitScope();
}
