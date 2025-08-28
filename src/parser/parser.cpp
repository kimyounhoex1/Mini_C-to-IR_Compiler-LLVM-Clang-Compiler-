#include "parser.h"
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
  cout << "여기 오닝? ";
  if(cur.type == TokenType::MINUS || cur.type == TokenType::PLUS) {
    cout << "저는 얘입니다." << cur.value << "\n";
    std::string op = cur.value;
    advance();
    auto number = parseFactor();
    auto node = std::make_unique<UnaryAst>(op, std::move(number), cur.line, cur.col);
    return node;
  }

  if(cur.type == TokenType::NUMBER) {
    cout << "저는 얘입니다." << cur.value << "\n";
    auto n = std::make_unique<NumberAst>(cur.value, cur.line, cur.col);
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

void printAst(const Ast* node, int indent) {
  auto pad = [indent](){ for (int i=0;i<indent;i++) std::cout << ' '; };
  if (!node) { pad(); std::cout << "(null)\n"; return; }

  if (node->kind == AstKind::Number) {
    auto* n = static_cast<const NumberAst*>(node);
    pad(); std::cout << "Number(" << n->value << "), line: " << n->line << ", col: " << n->col << "\n";
  } else if (node->kind == AstKind::Binary) {
    auto* b = static_cast<const BinaryAst*>(node);
    pad(); std::cout << "Binary(" << b->op << "), line: " << b->line << ", col: " << b->col << "\n";
    printAst(b->lhs.get(), indent+2);
    printAst(b->rhs.get(), indent+2);
  } else if (node->kind == AstKind::Unary) {
    auto* u = static_cast<const UnaryAst*>(node);
    pad(); std::cout << "Unary(" << u->op << ") @" << u->line << ":" << u->col << "\n";
    printAst(u->expr.get(), indent + 2);
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
    if (u->op == "+") return +v;
    if (u->op == "-") return -v;
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