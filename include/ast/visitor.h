#include "ast.h"

class Visitor {
public:
    virtual void visit(VarDecl& node) = 0;
    virtual void visit(Identifier& node) = 0;
    virtual void visit(Assign& node) = 0;
    virtual void visit(Block& node) = 0;
};