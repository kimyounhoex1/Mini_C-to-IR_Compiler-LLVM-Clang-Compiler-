#pragma once
#include "ast.h"

class Visitor {
public:
    // statement 계열
    virtual void visit(VarDecl& node) = 0;
    virtual void visit(Assign& node) = 0;
    virtual void visit(Block& node) = 0;
    
    // expression 계열
    virtual void visit(Identifier& node) = 0;
    virtual void visit(Number& node) = 0;
    virtual void visit(Boolean& node) = 0;
    virtual void visit(BinaryOp& node) = 0;
};