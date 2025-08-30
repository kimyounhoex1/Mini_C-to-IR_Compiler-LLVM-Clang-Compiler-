#include "../../include/parser/parser.h"
#include <iostream>
using namespace std;

static std::runtime_error perr(const std::string& msg) {
  return std::runtime_error("ParserError: " + msg);
}

Parser::Parser(Lexer &l) : lex(l) {
  cur = lex.getNextToken();
}

void Parser::advance(){
  cur = lex.getNextToken();
}

bool Parser::match(TokenType t){
  if(cur.type == t){
    advance();
    return true;
  }
  return false;
}

void Parser::expect(TokenType t, const char* msg){
  if(!match(t))
    throw perr(msg);
}

std::unique_ptr<Ast> Parser::parse(){
  auto node = parseExpr();
  if(cur.type != TokenType::END) {
    throw perr("input not fully consumed. leftover token: '" + cur.value + "'");
  }

  return node;
}


std::unique_ptr<Ast> Parser::parseExpr() {
  auto node = parseTerm();
  while(cur.type == TokenType::MINUS || cur.type == TokenType::PLUS){
    std::string op = cur.value;
    advance();
    auto rhs = parseTerm();
    node = std::make_unique<BinaryAst>(op, std::move(node), std::move(rhs), cur.line, cur.col);
  }

  return node;
}

std::unique_ptr<Ast> Parser::parseTerm() {
  auto node = parseFactor();
  while(cur.type == TokenType::MUL || cur.type == TokenType::DIV) {
    std::string op = cur.value;
    advance();
    auto rhs = parseFactor();
    node = std::make_unique<BinaryAst>(op, std::move(node), std::move(rhs), cur.line, cur.col);
  }
  return node;
}

std::unique_ptr<Ast> Parser::parseFactor() {
  if(cur.type == TokenType::MINUS || cur.type == TokenType::PLUS) {
    std::string op = cur.value;
    advance();
    auto number = parseFactor();
    auto node = std::make_unique<UnaryAst>(op, std::move(number), cur.line, cur.col);
    return node;
  }

  if(cur.type == TokenType::NUMBER) {
    auto n = std::make_unique<NumberAst>(cur.value, cur.line, cur.col);
    advance();
    return n;
  }

  if (cur.type == TokenType::IDENT) {
    auto n = std::make_unique<VariableAst>(cur.value, cur.line, cur.col);
    advance();
    return n;
  }

  if(cur.type == TokenType::LPAREN) {
    advance();
    auto node = parseExpr();
    expect(TokenType::RPAREN, "expected ')");
    return node;
  }
  
  throw perr("expected NUMBER or '('");
}

Program Parser::parseProgram() {
  Program p;
  while(cur.type != TokenType::END){
    p.stmts.push_back(parseStmt());
  }
  return p;
}

std::unique_ptr<Stmt> Parser::parseStmt(){
  // 현재 토큰이 변수라면
  if(cur.type == TokenType::IDENT) {
    // 루트 토큰을 생성하고
    Token identTok = cur;
    // 다음으로 넘어가서, factor요소를 완성시키는데, 그전에 assign(=) 인지확인함
    advance();
    if(cur.type == TokenType::ASSIGN){
      advance();
      auto rhs = parseExpr();
      expect(TokenType::SEMI, "expected ';' after assignment");
      return std::make_unique<AssignStmt>(identTok.value, std::move(rhs), identTok.line, identTok.col);
    } else {
      // 변수를 선언만 했을 경우, 그냥 넘어감
      // cur = identTok;
      auto var = std::make_unique<VariableAst>(identTok.value, identTok.line, identTok.col);
      expect(TokenType::SEMI, "expected ';' after variable statement");
      return std::make_unique<ExprStmt>(std::move(var), identTok.line, identTok.col);
    }
  }

  int L = cur.line;
  int C = cur.col;
  auto e = parseExpr();
  expect(TokenType::SEMI, "expected ';' after expression");
  return std::make_unique<ExprStmt>(std::move(e), L, C);
}

void printAst(const Ast* node, int indent) {
  auto pad = [indent](){ for (int i=0;i<indent;i++) std::cout << ' '; };
  if (!node) { pad(); std::cout << "(null)\n"; return; }

  if (node->kind == AstKind::Number) {
    auto* n = static_cast<const NumberAst*>(node);
    pad();
    // std::cout << "Number(" << n->value << ") | line: " << n->line << ", col: " << n->col << "\n";
    std::cout << "Number(" << n->value << ")\n";
  } else if (node->kind == AstKind::Binary) {
    auto* b = static_cast<const BinaryAst*>(node);
    pad();
    // std::cout << "Binary(" << b->op << ") | line: " << b->line << ", col: " << b->col << "\n";
    std::cout << "Binary(" << b->op << ")\n";
    printAst(b->lhs.get(), indent+2);
    printAst(b->rhs.get(), indent+2);
  } else if (node->kind == AstKind::Unary) {
    auto* u = static_cast<const UnaryAst*>(node);
    pad();
    // std::cout << "Unary(" << u->op << ") | line:" << u->line << ", col: " << u->col << "\n";
    std::cout << "Unary(" << u->op << ")\n";
    printAst(u->expr.get(), indent + 2);
  } else if (node->kind == AstKind::Variable) {
    auto* u = static_cast<const VariableAst*>(node);
    pad();
    // std::cout << "Variable(" << u->name << ") | line: " << u->line << ", col: " << u->col << "\n";
    std::cout << "Variable(" << u->name << ")\n";
  }
}

long long eval(const Ast* node) {
  if (node->kind == AstKind::Number) {
    const auto* n = static_cast<const NumberAst*>(node);
    return std::stoll(n->value);
  }
  if (node->kind == AstKind::Unary) {
    const auto* u = static_cast<const UnaryAst*>(node);
    long long v = eval(u->expr.get());
    if (u->op == "+")
      return +v;
    if (u->op == "-")
      return -v;
    throw perr("unknown unary op: " + u->op);
  }
  const auto* b = static_cast<const BinaryAst*>(node);
  long long L = eval(b->lhs.get());
  long long R = eval(b->rhs.get());
  if (b->op == "+") return L + R;
  if (b->op == "-") return L - R;
  if (b->op == "*") return L * R;
  if (b->op == "/") return L / R;
  throw perr("unknown op in eval: " + b->op);
}

void printStmt(const Stmt* s, int indent=0) {
  auto pad=[&](){ for(int i=0;i<indent;i++) std::cout<<' '; };
  if (s->kind == StmtKind::ExprStmt) {
    pad();
    // std::cout << "ExprStmt() "<<s->line<<":"<<s->col<<"\n";
    std::cout << "ExprStmt()\n";
    printAst(static_cast<const ExprStmt*>(s)->expr.get(), indent+2);
  } else {
    auto* a = static_cast<const AssignStmt*>(s);
    pad();
    // std::cout << "Assign("<<a->name<<") | line: "<<s->line<<", col: "<<s->col<<"\n";
    std::cout << "Assign("<<a->name<<")\n";
    printAst(a->expr.get(), indent+2);
  }
}

void printProgram(const Program& p){
  std::cout << "== PROGRAM ==\n";
  for (auto& st : p.stmts) 
    printStmt(st.get(), 2);
}