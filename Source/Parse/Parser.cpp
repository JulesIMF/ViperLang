/*++

Copyright (c) 2023 JulesIMF, MIPT

Module Name:

    Parser.cpp

Abstract:



Author / Creation date:

    JulesIMF / 19.03.23

Revision History:

--*/

//
// Includes / usings
//

#include "Lex/Lexer.hpp"
#include "Lex/Location.hpp"
#include "Trees/Parse/Ast.hpp"
#include <Common/Assert.hpp>
#include <Lex/Token.hpp>
#include <Lex/TokenType.hpp>
#include <Parse/Parser.hpp>
#include <cstddef>

using namespace Parse;
using Lex::CharAttributes;
using Lex::IdAttributes;
using Lex::IdentationAttributes;
using Lex::IntAttributes;
using Lex::Location;
using Lex::StringAttributes;
using Lex::TokenType;

//
// Definitions
//

Parser::Parser(Lex::Lexer& lexer) :
    lexer_(lexer)
{
}

File*
Parser::ParseFile()
{
    return nullptr;
}

SuperStmtList*
Parser::ParseSuperStmtList()
{
    return nullptr;
}

SuperStmt*
Parser::ParseSuperStmt()
{
    return nullptr;
}

Type*
Parser::ParseType()
{
    return nullptr;
}
void
Parser::SendError_(ParsingError error)
{
}
