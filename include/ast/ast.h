#pragma once
#include <string>
#include <vector>

class Visitor;

struct AstNode {
    virtual ~AstNode() = default;
    virtual void accept(class Visitor& v) = 0; // 방문자 받아들이기
};

struct VarDecl : AstNode {
    std::string name, type;
    VarDecl(std::string n, std::string t) {
        name = n;
        type = t;
    }
    void accept(Visitor& v) override; 
};

struct Identifier : AstNode {
    std::string name;
    Identifier(std::string n){
        name = n;
    }
    void accept(Visitor& v) override;
};

struct Assign : AstNode {
    std::string name;
    AstNode* expr;
    Assign(std::string n, AstNode* e) {
        name = n;
        expr = e;
    }
    void accept(Visitor& v) override;
};

struct Block : AstNode {
    std::vector<AstNode*> stmts;
    Block(std::vector<AstNode*> s) {
        stmts = s;
    }
    void accept(Visitor& v) override;
};