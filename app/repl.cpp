#include <lex/lexer.hpp>
#include <fmt/color.h>
#include <iostream>

#define CHECK(x) std::cout << #x << ": " << x;

int
main()
{
    std::stringstream source(":;<<");
    Lex::Lexer l{source};

    CHECK(l.Matches(Lex::TokenType::COLON));
    CHECK(l.Matches(Lex::TokenType::SEMICOLON));
}
