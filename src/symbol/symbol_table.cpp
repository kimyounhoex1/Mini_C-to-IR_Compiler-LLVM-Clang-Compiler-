#include "symbol_table.h"
#include <string>
#include <unordered_map>
#include <vector>
#include <optional>
#include <iostream>

// 새로운 스코프가 생긴다면, {가 생긴다면, push로 엔트리를 새로 생성해준다.
SymbolTable::SymbolTable(){
  enterScope();
}

void SymbolTable::enterScope() {
  scopes.push_back({});
}

// 스코프가 닺혀서 더이상 사용하지 않는다면, pop으로 스코프 엔트리를 빼준다.
void SymbolTable::exitScope() {
  if(!scopes.empty()){
    scopes.pop_back();
  }
}

// 새로우 변수가 선언되었다면, 현재 스코프에 있는지 검사하고, 검사할때는 find()를 통해서 하는데, find()는 iterator를 반환하니까, 주소를 기준으로 값을 비교
// curScope.end()는 최종 요소, 즉 마지막 요소의 다음값인 빈 주소를 가리키기에 선언이 find()해서 값이 안나온다면, 그건 end()를 return 하는 것이다.

bool SymbolTable::declare(const std::string& name, const SymbolInfo& info) {
  auto& curScope = scopes.back();
  if (curScope.find(name) != curScope.end()) {
    return false; // 이미 존재
  }
  curScope[name] = info; // 새로운 심볼 등록
  return true;
}

// scopes의 vector안에 push된 최상위 엔트리부터 차례대로 확인하는데, 스코프별 맵을 하나하나씩 확인하는 절차
std::optional<SymbolInfo> SymbolTable::lookup(const std::string& name) const {
  for (auto it = scopes.rbegin(); it != scopes.rend(); ++it) {
    auto found = it->find(name);
    if (found != it->end())
      return found->second;
  }
  return std::nullopt; // 못 찾음  
}


