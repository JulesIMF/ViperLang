#pragma once

#include <lex/ident_table.hpp>
#include <lex/token.hpp>

#include <fmt/format.h>

#include <optional>
#include <stack>
#include <string>

namespace Lex
{

class Lexer
{
public:
    Lexer(std::istream& source);

    Token
    GetNextToken();

    void
    Advance();

    Token
    Peek();

    Token
    GetPreviousToken();

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

    std::optional<Token>
    MatchBeginEnd();

    std::optional<Token>
    MatchDelimiters();

    std::optional<Token>
    MatchOperatorsAsgn();

    std::optional<Token>
    MatchLiterals();

    std::optional<Token>
    MatchNumericLiteral();

    std::optional<Token>
    MatchStringLiteral();

    std::optional<Token>
    MatchCharLiteral();

    std::optional<Token>
    MatchWords();

    void
    SendWarning();

private:
    // For easy access to locations
    Token prev_{};

    // Current token
    Token curr_{};

    Scanner scanner_;
    IdentTable table_;

    unsigned int tabSize_ = 4;
    std::stack<unsigned int> identationLevel_;
    std::optional<Token> identToken = std::nullopt;
};

}  // namespace Lex
