#include "lex/token.hpp"
#include <lex/lexer.hpp>

// Finally,
#include <catch2/catch.hpp>

#include <iostream>

TEST_CASE("Lexer: Just works", "[Lex]")
{
    std::stringstream source("1 + 2");
    Lex::Lexer l{source};

    CHECK(l.Matches(Lex::TokenType::INT));
    CHECK(l.Matches(Lex::TokenType::ADD));
    CHECK(l.Matches(Lex::TokenType::INT));
}

TEST_CASE("Bracets", "[Lex]")
{
    std::stringstream source("1 + ('\\n')");
    Lex::Lexer l{source};

    CHECK(l.Matches(Lex::TokenType::INT));
    CHECK(l.Matches(Lex::TokenType::ADD));
    CHECK(l.Matches(Lex::TokenType::LPAREN));
    auto tok = l.Peek();
    CHECK(l.Matches(Lex::TokenType::CHAR));
    CHECK(std::get<Lex::CharAttributes>(tok.attributes).value ==
          '\n');
    CHECK(l.Matches(Lex::TokenType::RPAREN));
}

// ///////////////////////////////////////////////////////////////////

TEST_CASE("Keywords", "[Lex]")
{
    std::stringstream source("for if else "
                             "return true false");
    Lex::Lexer l{source};
    CHECK(l.Matches(Lex::TokenType::FOR));
    CHECK(l.Matches(Lex::TokenType::IF));
    CHECK(l.Matches(Lex::TokenType::ELSE));
    CHECK(l.Matches(Lex::TokenType::RETURN));
    CHECK(l.Matches(Lex::TokenType::TRUE));
    CHECK(l.Matches(Lex::TokenType::FALSE));
}

TEST_CASE("Consequent", "[Lex]")
{
    std::stringstream source("!true");
    Lex::Lexer l{source};

    CHECK(l.Matches(Lex::TokenType::NOT));
    CHECK(l.Matches(Lex::TokenType::TRUE));
}

TEST_CASE("Comments", "[Lex]")
{
    std::stringstream source("# Comment if var a = 1; \n"
                             "# One more comment \n"
                             "1 # Token then comment \n"  // <---
                             "# Comment with no newline");
    Lex::Lexer l{source};

    // parses to just `1`
    CHECK(l.Matches(Lex::TokenType::INT));
}

TEST_CASE("Statement", "[Lex]")
{
    std::stringstream source("return abc = 0;");
    Lex::Lexer l{source};

    CHECK(l.Matches(Lex::TokenType::RETURN));
    CHECK(l.Matches(Lex::TokenType::ID));
    CHECK(l.Matches(Lex::TokenType::ASGN));
    CHECK(l.Matches(Lex::TokenType::INT));
    CHECK(l.Matches(Lex::TokenType::SEMICOLON));
}

TEST_CASE("String literal", "[Lex]")
{
    std::stringstream source(
        "\"\\\"Hello \"   \n  \"world\\\"\"  \"!\\n\"");
    Lex::Lexer l{source};
    auto tok = l.Peek();
    CHECK(l.Matches(Lex::TokenType::STRING));
    CHECK(std::get<Lex::StringAttributes>(tok.attributes).value ==
          "\"Hello world\"!\n");
}

TEST_CASE("Numeric literals", "[Lex]")
{
    std::stringstream source(
        "(0xF12de00Fa, 0b110011010011, -00018128637128)");
    Lex::Lexer l{source};

    CHECK(l.Matches(Lex::TokenType::LPAREN));
    auto token = l.Peek();
    CHECK(l.Matches(Lex::TokenType::INT));
    CHECK(std::get<Lex::IntAttributes>(token.attributes).base == 16);
    CHECK(std::get<Lex::IntAttributes>(token.attributes).value ==
          0xF12de00Fallu);

    CHECK(l.Matches(Lex::TokenType::COMMA));
    token = l.Peek();
    CHECK(l.Matches(Lex::TokenType::INT));
    CHECK(std::get<Lex::IntAttributes>(token.attributes).base == 2);
    CHECK(std::get<Lex::IntAttributes>(token.attributes).value ==
          0b110011010011llu);

    CHECK(l.Matches(Lex::TokenType::COMMA));
    CHECK(l.Matches(Lex::TokenType::SUB));
    token = l.Peek();
    CHECK(l.Matches(Lex::TokenType::INT));
    CHECK(std::get<Lex::IntAttributes>(token.attributes).base == 10);
    CHECK(std::get<Lex::IntAttributes>(token.attributes).value ==
          18128637128);
    CHECK(l.Matches(Lex::TokenType::RPAREN));
}

TEST_CASE("Braces", "[Lex]")
{
    std::stringstream source("{ }");
    Lex::Lexer l{source};

    CHECK(l.Matches(Lex::TokenType::LBRACE));
    CHECK(l.Matches(Lex::TokenType::RBRACE));
}

TEST_CASE("Assign vs Equals", "[Lex]")
{
    std::stringstream source("== = ==");
    Lex::Lexer l{source};

    CHECK(l.Matches(Lex::TokenType::EQL));
    CHECK(l.Matches(Lex::TokenType::ASGN));
    CHECK(l.Matches(Lex::TokenType::EQL));
}

TEST_CASE("Delims / opers", "[Lex]")
{
    std::stringstream source(":;<<==");
    Lex::Lexer l{source};

    CHECK(l.Matches(Lex::TokenType::COLON));
    CHECK(l.Matches(Lex::TokenType::SEMICOLON));
    CHECK(l.Matches(Lex::TokenType::LSS));
    CHECK(l.Matches(Lex::TokenType::LEQ));
    CHECK(l.Matches(Lex::TokenType::ASGN));
}

TEST_CASE("Delims / opers with spaces", "[Lex]")
{
    std::stringstream source(": ;\n\n   << ==");
    Lex::Lexer l{source};

    CHECK(l.Matches(Lex::TokenType::COLON));
    CHECK(l.Matches(Lex::TokenType::SEMICOLON));
    CHECK(l.Matches(Lex::TokenType::BEGIN));
    CHECK(l.Matches(Lex::TokenType::LSS));
    CHECK(l.Matches(Lex::TokenType::LSS));
    CHECK(l.Matches(Lex::TokenType::EQL));
}

TEST_CASE("Delims / opers with comments", "[Lex]")
{
    std::stringstream source("# haha comment\n"
                             "### haha another\n"
                             ":;\n"
                             "<<#comm\n"
                             "#another\n"
                             "== #lol");
    Lex::Lexer l{source};

    CHECK(l.Matches(Lex::TokenType::COLON));
    CHECK(l.Matches(Lex::TokenType::SEMICOLON));
    CHECK(l.Matches(Lex::TokenType::LSS));
    CHECK(l.Matches(Lex::TokenType::LSS));
    CHECK(l.Matches(Lex::TokenType::EQL));
}

TEST_CASE("BeginEnd 1", "[Lex]")
{
    std::stringstream source("function\n"
                                  "  if\n"
                                  "    return\n"
                                  "  else\n"
                                  "    if\n"
                                  "      return\n");
    Lex::Lexer        l{source};

    CHECK(l.Matches(Lex::TokenType::FUNCTION));
    CHECK(l.Matches(Lex::TokenType::BEGIN));
    CHECK(l.Matches(Lex::TokenType::IF));
    CHECK(l.Matches(Lex::TokenType::BEGIN));
    CHECK(l.Matches(Lex::TokenType::RETURN));
    CHECK(l.Matches(Lex::TokenType::END));
    CHECK(l.Matches(Lex::TokenType::ELSE));
    CHECK(l.Matches(Lex::TokenType::BEGIN));
    CHECK(l.Matches(Lex::TokenType::IF));
    CHECK(l.Matches(Lex::TokenType::BEGIN));
    CHECK(l.Matches(Lex::TokenType::RETURN));
    CHECK(l.Matches(Lex::TokenType::END));
    CHECK(l.Matches(Lex::TokenType::END));
    CHECK(l.Matches(Lex::TokenType::END));
}

TEST_CASE("BeginEnd 2", "[Lex]")
{
    std::stringstream source("function   \n"
                             "  if \n"
                             "  \n"
                             "\n"
                             "            \n"
                             "\n"
                             "    return\n"
                             "\n"
                             "  else\n"
                             "    if\n"
                             "\n"
                             "      return\n");
    Lex::Lexer        l{source};

    CHECK(l.Matches(Lex::TokenType::FUNCTION));
    CHECK(l.Matches(Lex::TokenType::BEGIN));
    CHECK(l.Matches(Lex::TokenType::IF));
    CHECK(l.Matches(Lex::TokenType::BEGIN));
    CHECK(l.Matches(Lex::TokenType::RETURN));
    CHECK(l.Matches(Lex::TokenType::END));
    CHECK(l.Matches(Lex::TokenType::ELSE));
    CHECK(l.Matches(Lex::TokenType::BEGIN));
    CHECK(l.Matches(Lex::TokenType::IF));
    CHECK(l.Matches(Lex::TokenType::BEGIN));
    CHECK(l.Matches(Lex::TokenType::RETURN));
    CHECK(l.Matches(Lex::TokenType::END));
    CHECK(l.Matches(Lex::TokenType::END));
    CHECK(l.Matches(Lex::TokenType::END));
}