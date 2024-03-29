/*++

Copyright (c) 2023 JulesIMF, MIPT

Module Name:

    Lexer.hpp

Abstract:

    Lexicographical analyzer (tokenizer) declaration.

Author / Creation date:

    JulesIMF / 09.02.23

Revision History:

--*/

#pragma once

//
// Includes / usings
//

#include <Lex/IdentTable.hpp>
#include <Lex/Token.hpp>
#include <cstddef>

#include <fmt/format.h>

#include <optional>
#include <stack>
#include <string>
#include <vector>

//
// Definitions
//

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

    void
    Unget(unsigned long count = 1);

    Token
    Peek();

    // Check current token type and maybe consume it.
    bool
    Matches(Lex::TokenType type);

    std::vector<Token> const&
    TokenVector() const
    {
        return tokens_;
    }

protected:
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
