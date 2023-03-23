/*++

Copyright (c) 2023 JulesIMF, MIPT

Module Name:

    Prim.cpp

Abstract:

    Tests for parsing functions in Source/Parse/Prim.cpp

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

TEST_CASE("", "[Parse/Prim]")
{
    std::stringstream source("");
    Lex::Lexer        l{source};
    Parser            p(l);
}
*/

TEST_CASE("Primary in parens", "[Parse/Prim]")
{
    std::stringstream source("( ( ( fupm ) ) )");
    Lex::Lexer        l{source};
    Parser            p(l);

    CHECK(p.ParsePrim()->As<Var>()->varId.value == "fupm");
}

TEST_CASE("Int", "[Parse/Prim]")
{
    std::stringstream source("1 0xaa");
    Lex::Lexer        l{source};
    Parser            p(l);

    CHECK(p.ParseInt()->intAttributes.value == 1);
    CHECK(p.ParseInt()->intAttributes.value == 0xaa);
}

TEST_CASE("Char", "[Parse/Prim]")
{
    std::stringstream source("'''\n'");
    Lex::Lexer        l{source};
    Parser            p(l);

    CHECK(p.ParseChar()->charAttributes.empty);
    CHECK(p.ParseChar()->charAttributes.value == '\n');
}

TEST_CASE("String", "[Parse/Prim]")
{
    std::stringstream source("\"Hehe\"   \n   \"Haha\"");
    Lex::Lexer        l{source};
    Parser            p(l);

    CHECK(!p.ParseVar());
    CHECK(p.ParseString());
}

TEST_CASE("Var", "[Parse/Prim]")
{
    std::stringstream source("lol");
    Lex::Lexer        l{source};
    Parser            p(l);

    CHECK(p.ParseVar());
}