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

  
Token Lexer::getNextToken() { // 이거 처음에 Token getNextToken() 이렇게 구현해서 안된거임, 글 쓰자.
  while(pos < text.size()){
    char c = text.at(pos);
    
    if(is_space(c)){
      pos++;
      continue;
    } 
    if('0'<=c && c<='9'){
      string num = "";
      while( pos < text.size() && (is_digit(text.at(pos)))){
        num = num + text.at(pos++);
      }
      return {TokenType::NUMBER, num};
    }

    if(c == '+'){
      pos++;
      return {TokenType::PLUS, "+"};
    }
    if(c == '-'){
      pos++;
      return {TokenType::MINUS, "-"};
    }
    if(c == '*'){
      pos++;
      return {TokenType::MUL, "*"};
    }
    if(c == '/'){
      pos++;
      return {TokenType::DIV, "/"};
    }
    if(c == '('){
      pos++;
      return {TokenType::LPAREN, "("};
    }
    if(c == ')'){
      pos++;
        return {TokenType::RPAREN, ")"};  
    }

    throw runtime_error("Invalid character");
  }

  return {TokenType::END, ""};
}
