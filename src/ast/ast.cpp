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
