#pragma once

#include <cstddef>
#include <Lex/IdentTable.hpp>
#include <Lex/Token.hpp>

#include <fmt/format.h>

#include <optional>
#include <stack>
#include <string>
#include <vector>

namespace Lex
{

class Lexer
{
public:
    Lexer(std::istream& source);

    void
    GetNextToken();

    void
    PushToken(Token token);

    void
    Advance();

    Token
    Peek();

    // Check current token type and maybe consume it.
    bool
    Matches(Lex::TokenType type);

private:
    bool
    SkipWhiteSpace();

    bool
    SkipEmptyLines();

    bool
    SkipToNewLine();

    bool
    SkipComments();

    bool
    SkipUseless();

    std::optional<Token>
    MatchIdentation();

    bool
    MatchBeginEnd();

    bool
    MatchDelimiters();

    bool
    MatchOperatorsAsgn();

    bool
    MatchLiterals();

    bool
    MatchNumericLiteral();

    bool
    MatchStringLiteral();

    bool
    MatchCharLiteral();

    bool
    MatchWords();

    void
    SendWarning();

private:
    std::vector<Token> tokens_;
    size_t curr_ = 0;
    
    Scanner scanner_;
    IdentTable table_;

    unsigned int tabSize_ = 4;
    std::stack<unsigned int> identationLevel_;
    std::optional<Token> identToken = std::nullopt;
};

}  // namespace Lex
