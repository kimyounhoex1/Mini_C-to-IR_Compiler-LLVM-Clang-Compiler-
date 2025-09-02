#include "../include/semantic/semantic_analyzer.h"
#include "../include/ast/ast.h"

int main() {
    // { int x; x = 1 + 2; x = true; y = 10; b = 1 && true; }
    VarDecl* declX = new VarDecl("x", "int");

    // x = 1 + 2;  ✅ OK
    Assign* assign1 = new Assign("x",
        new BinaryOp("+", new Number(1), new Number(2)));

    // x = true;  ❌ 타입 에러
    Assign* assign2 = new Assign("x", new Boolean(true));

    // y = 10;    ❌ undeclared 변수
    Assign* assign3 = new Assign("y", new Number(10));

    // b = 1 && true;  ❌ undeclared 변수 b, 타입 불일치
    Assign* assign4 = new Assign("b",
        new BinaryOp("&&", new Number(1), new Boolean(true)));

    Block* block = new Block({declX, assign1, assign2, assign3, assign4});

    SemanticAnalyzer analyzer;
    block->accept(analyzer);

    // cleanup (학습용이라 생략해도 되지만 메모리 누수 방지용)
    delete block;

    return 0;
}