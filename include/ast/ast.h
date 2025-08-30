#include <string>
#include <vector>

struct AstNode {
    virtual ~AstNode() = default;
    virtual void accept(class Visitor& v) = 0; // 방문자 받아들이기
};

struct VarDecl : AstNode {
    std::string name, type;
    void accept(Visitor& v) override; 
};

struct Identifier : AstNode {
    std::string name;
    void accept(Visitor& v) override;
};

struct Assign : AstNode {
    std::string name;
    AstNode* expr;
    void accept(Visitor& v) override;
};

struct Block : AstNode {
    std::vector<AstNode*> stmts;
    void accept(Visitor& v) override;
};