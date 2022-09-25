#pragma once

#include <lex/token_type.hpp>

#include <string>
#include <map>

namespace lex {

class IdentTable {
 public:
  IdentTable() {
    Populate();
  }

  TokenType Lookup(const std::string&) {
    // Your code goes here
    std::abort();
  }

 private:
  void Populate() {
    map_.insert({"String", TokenType::TY_STRING});
    map_.insert({"Bool", TokenType::TY_BOOL});
    map_.insert({"Unit", TokenType::TY_UNIT});
    map_.insert({"Int", TokenType::TY_INT});

    map_.insert({"return", TokenType::RETURN});
    map_.insert({"struct", TokenType::STRUCT});
    map_.insert({"yield", TokenType::YIELD});
    map_.insert({"false", TokenType::FALSE});
    map_.insert({"else", TokenType::ELSE});
    map_.insert({"true", TokenType::TRUE});
    map_.insert({"unit", TokenType::UNIT});
    map_.insert({"type", TokenType::TYPE});
    map_.insert({"var", TokenType::VAR});
    map_.insert({"fun", TokenType::FUN});
    map_.insert({"for", TokenType::FOR});
    map_.insert({"if", TokenType::IF});
  }

 private:
  std::map<std::string, TokenType> map_;
};

}  // namespace lex
