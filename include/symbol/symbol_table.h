#pragma once
#include <string>
#include <vector>
#include <unordered_map>

struct SymbolInfo {
  std::string type;
  int line;
  int col;
};

class SymbolTable {
private:
  // 스코프, Vector에 map으로 선언되고, 스택처럼 사용된다.( 프로시져 호출시 생성되는 메모리 구조와 유사 )
  std::vector<std::unordered_map<std::string, SymbolInfo>> scopes;  

public:
  SymbolTable();

  void enterScope(); //진입점, {  <=
  void exitScope();  //탈출    }  <=
  //선언 되어져 있는지
  // bool SymbolTable::isDeclared(const std::string& name, const SymbolInfo& info);
  // 선언
  bool declare(const std::string& name, const SymbolInfo& info);
  // 성공시 true, 중복선언 및 규칙 허용x -> false;

  // 조회 관련
  std::optional<SymbolInfo> lookup(const std::string& name) const;
};
