#pragma once
#include <string>
#include "../lexer/lexer.h"

enum class AstKind { Number, Binary };

struct Ast {
  AstKind kind;
  int line = 0;
  int col = 0;
  virtual ~Ast() noexcept = default; // 뭔지 모르겠음
};

struct NumberAst : Ast {
  std::string value; // 숫자, 12, 34, 56 등등
  NumberAst(std::string v, int L, int C){
    value = std::move(v);
    kind = AstKind::Number;
    line = L;
    col = C;
  }
};

struct BinaryAst : Ast {
  std::string op; // 연산자, +, -, * 등등
  std::unique_ptr<Ast> lhs, rhs;
  BinaryAst(std::string o, std::unique_ptr<Ast> l, std::unique_ptr<Ast> r, int L, int C){
    op = std::move(o);
    lhs = std::move(l);
    rhs = std::move(r);
    kind = AstKind::Binary;
    line = L;
    col = C;
  }

  ~BinaryAst() noexcept override = default;
};
  /* 위 코드의 개선된 코드
    BinaryAst(std::string o, std::unique_ptr<Ast> L, std::unique_ptr<Ast> R)
    : op(std::move(o)), lhs(std::move(L)), rhs(std::move(R)) { kind = AstKind::Binary; }
  */


class Parser {
  Lexer &lex;
  Token cur;

  void advance();                             // 다음 토큰으로
  bool match(TokenType t);                    // 현재 토큰 타입이 t변 소비하고 true
  void expect(TokenType t, const char* msg);  // t가 아닐 경우, 에러 발생

  std::unique_ptr<Ast> parseExpr();
  std::unique_ptr<Ast> parseTerm();
  std::unique_ptr<Ast> parseFactor();

public:
  explicit Parser(Lexer& L);

  std::unique_ptr<Ast> parse();
};

void printAst(const Ast* node, int indent = 0);
long long eval(const Ast* node);
