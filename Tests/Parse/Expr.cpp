/*++

Copyright (c) 2023 JulesIMF, MIPT

Module Name:

    Expr.cpp

Abstract:

    Tests for parsing functions in Source/Parse/Expr.cpp

Author / Creation date:

    JulesIMF / 23.03.23

Revision History:

--*/

//
// Includes / usings
//

#include <Parse/Parser.hpp>
#include <catch2/catch.hpp>

using namespace Parse;

//
// Definitions
//

/*
    Template:

TEST_CASE("", "[Parse/Expr]")
{
    std::stringstream source("");
    Lex::Lexer        l{source};
    Parser            p(l);
}
*/

TEST_CASE("Term", "[Parse/Expr]")
{
    std::stringstream source("a*5/b");
    Lex::Lexer        l{source};
    Parser            p(l);

    CHECK(p.ParseTerm()->As<Term>()->operands.size() == 3);
}

TEST_CASE("Form", "[Parse/Expr]")
{
    std::stringstream source("a*5/b + lol*99/0 - -9");
    Lex::Lexer        l{source};
    Parser            p(l);

    CHECK(p.ParseForm()->As<Form>()->operands.size() == 3);
}

TEST_CASE("Comp", "[Parse/Expr]")
{
    std::stringstream source("a*5/b + lol*99/0 <= 0 == !true");
    Lex::Lexer        l{source};
    Parser            p(l);

    CHECK(p.ParseComp()->As<Comp>()->operands.size() == 3);
}

TEST_CASE("Logc", "[Parse/Expr]")
{
    std::stringstream source(
        "a*5/b + lol*99/0 <= 0 == !true || false || !!!true || 0");
    Lex::Lexer l{source};
    Parser     p(l);

    CHECK(p.ParseLogc()->As<Logc>()->operands.size() == 4);
}
