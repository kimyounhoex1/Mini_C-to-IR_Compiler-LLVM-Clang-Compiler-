#include "../../include/ast/visitor.h"

void VarDecl::accept(Visitor& v) { 
  v.visit(*this); 
}
void Identifier::accept(Visitor& v) { 
  v.visit(*this); 
}
void Assign::accept(Visitor& v) {
   v.visit(*this); 
}
void Block::accept(Visitor& v) {
  v.visit(*this);
}
void Number::accept(Visitor& v) {
  v.visit(*this);
}
void Boolean::accept(Visitor& v) {
  v.visit(*this);
}
void BinaryOp::accept(Visitor& v) {
  v.visit(*this);
}
void IfStmt::accept(Visitor& v) {
  v.visit(*this);
}
void WhileStmt::accept(Visitor& v) {
  v.visit(*this);
}
void FunctionDecl::accept(Visitor& v) {
  v.visit(*this);
}