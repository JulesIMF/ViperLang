#include <lex/lexer.hpp>

#include <lex/errors.hpp>

namespace lex {

Lexer::Lexer(std::istream& source) : scanner_{source} {
}

////////////////////////////////////////////////////////////////////

Token Lexer::GetNextToken() {
  SkipWhitespace();

  SkipComments();

  if (auto op = MatchOperators()) {
    return *op;
  }

  if (auto lit = MatchLiterls()) {
    return *lit;
  }

  if (auto word = MatchWords()) {
    return *word;
  }

  throw LexError{"Could not match any token", scanner_.GetLocation()};
}

////////////////////////////////////////////////////////////////////

Token Lexer::GetPreviousToken() {
  return prev_;
}

////////////////////////////////////////////////////////////////////

// Lazy loading of the next Token
void Lexer::Advance() {
  prev_ = peek_;

  if (!need_advance_) {
    need_advance_ = true;
  } else {
    peek_ = GetNextToken();
    need_advance_ = false;
  }
}

////////////////////////////////////////////////////////////////////

bool Lexer::Matches(lex::TokenType type) {
  if (Peek().type != type) {
    return false;
  }

  Advance();
  return true;
}

////////////////////////////////////////////////////////////////////

Token Lexer::Peek() {
  if (need_advance_) {
    Advance();
  }
  return peek_;
}

////////////////////////////////////////////////////////////////////

bool IsWhitespace(char ch) {
  return ch == ' ' || ch == '\n' || ch == '\t';
}

void Lexer::SkipWhitespace() {
  while (IsWhitespace(scanner_.CurrentSymbol())) {
    scanner_.MoveRight();
  }
}

////////////////////////////////////////////////////////////////////

void Lexer::SkipComments() {
  while (scanner_.CurrentSymbol() == '#') {
    scanner_.MoveNextLine();
    SkipWhitespace();
  }
}

////////////////////////////////////////////////////////////////////

std::optional<Token> Lexer::MatchOperators() {
  if (auto type = MatchOperator()) {
    scanner_.MoveRight();
    return Token{*type, scanner_.GetLocation()};
  }

  return std::nullopt;
}

////////////////////////////////////////////////////////////////////

std::optional<TokenType> Lexer::MatchOperator() {
  switch (scanner_.CurrentSymbol()) {
      // TODO: make less special
    case '=': {
      if (scanner_.PeekNextSymbol() == '=') {
        scanner_.MoveRight();
        return TokenType::EQUALS;
      } else {
        return TokenType::ASSIGN;
      }
    }

    case '+':
      return TokenType::PLUS;
    case '-':
      return TokenType::MINUS;
    case '*':
      return TokenType::STAR;
    case '&':
      return TokenType::ADDR;
    case '!':
      return TokenType::NOT;
    case '<':
      return TokenType::LT;
    case '(':
      return TokenType::LEFT_BRACE;
    case ')':
      return TokenType::RIGHT_BRACE;
    case '{':
      return TokenType::LEFT_CBRACE;
    case '}':
      return TokenType::RIGHT_CBRACE;
    case ';':
      return TokenType::SEMICOLUMN;
    case ':':
      return TokenType::COLUMN;
    case ',':
      return TokenType::COMMA;
    case '.':
      return TokenType::DOT;
    case EOF:
      return TokenType::TOKEN_EOF;
    default:
      return std::nullopt;
  }
}

////////////////////////////////////////////////////////////////////

std::optional<Token> Lexer::MatchLiterls() {
  if (auto num_token = MatchNumericLiteral()) {
    return num_token;
  }

  if (auto string_token = MatchStringLiteral()) {
    return string_token;
  }

  return std::nullopt;
}

////////////////////////////////////////////////////////////////////

std::optional<Token> Lexer::MatchNumericLiteral() {
  int result = 0, match_span = 0;

  while (isdigit(scanner_.CurrentSymbol())) {
    result *= 10;
    result += scanner_.CurrentSymbol() - '0';

    scanner_.MoveRight();
    match_span += 1;
  }

  if (match_span == 0) {
    return std::nullopt;
  }

  return Token{TokenType::NUMBER, scanner_.GetLocation(), {result}};
}

////////////////////////////////////////////////////////////////////

std::optional<Token> Lexer::MatchStringLiteral() {
  auto first_quote = [](char first) -> bool {
    return first == '\"';
  };

  if (!first_quote(scanner_.CurrentSymbol())) {
    return std::nullopt;
  }

  // It matched! Now do match the whole string

  // Consume commencing "
  scanner_.MoveRight();

  std::string lit;
  while (scanner_.CurrentSymbol() != '\"') {
    lit.push_back(scanner_.CurrentSymbol());
    scanner_.MoveRight();
  }

  // Consume enclosing "
  scanner_.MoveRight();

  return Token{TokenType::STRING, scanner_.GetLocation(), {lit}};
}

////////////////////////////////////////////////////////////////////

std::optional<Token> Lexer::MatchWords() {
  auto word = BufferWord();
  auto type = table_.Lookup(word);

  if (type == TokenType::IDENTIFIER) {
    return Token{type, scanner_.GetLocation(), {word}};
  }

  // So it must be a keyword with the
  // exact type encoded direcly in `type`
  return Token{type, scanner_.GetLocation()};
}

////////////////////////////////////////////////////////////////////

std::string Lexer::BufferWord() {
  std::string result;

  while (isalnum(scanner_.CurrentSymbol())) {
    result.push_back(scanner_.CurrentSymbol());
    scanner_.MoveRight();
  }

  return result;
}

}  // namespace lex
