#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include <stdexcept>
#include "lexer.h"
using namespace std;

static bool is_space(char c){
    return c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\f' || c == '\v';
}

static bool is_digit(char c){
    return '0' <= c && c <= '9';
}

Lexer::Lexer(const string& input) {
  text = input;
}

char Lexer::advance() {
  char c = text[pos++];
  if (c=='\n') {
    ++line;
    col = 1;
  } else {
    ++col;
  }
  return c;
}
  
Token Lexer::getNextToken() { // 이거 처음에 Token getNextToken() 이렇게 구현해서 안된거임, 글 쓰자.
  
  while(pos < text.size()){
    char c = text.at(pos);
    if(is_space(c)){
      advance();
      continue;
    }

    int startLine = line;
    int startCol = col;

    if('0'<=c && c<='9'){ 
      string num;
      while( pos < text.size() && (is_digit(text.at(pos)))){
        // num = num + text.at(pos++);
        num.push_back(advance());
      }
      return {TokenType::NUMBER, num, startLine, startCol};
    }

    if(c == '+'){
      pos++;
      return {TokenType::PLUS, "+", startLine, startCol};
    }
    if(c == '-'){
      pos++;
      return {TokenType::MINUS, "-", startLine, startCol};
    }
    if(c == '*'){
      pos++;
      return {TokenType::MUL, "*", startLine, startCol};
    }
    if(c == '/'){
      pos++;
      return {TokenType::DIV, "/", startLine, startCol};
    }
    if(c == '('){
      pos++;
      return {TokenType::LPAREN, "(", startLine, startCol};
    }
    if(c == ')'){
      pos++;
        return {TokenType::RPAREN, ")", startLine, startCol};
    }

    throw runtime_error("Invalid character");
  }
  return {TokenType::END, "", line, col};
}
