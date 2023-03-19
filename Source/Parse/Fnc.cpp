/*++

Copyright (c) 2023 JulesIMF, MIPT

Module Name:

    Fnc.cpp

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
using Lex::TokenType;

//
// Definitions
//

FncDef*
Parser::ParseFncDef()
{
    return nullptr;
}

ArgDefList*
Parser::ParseArgDefList()
{
    return nullptr;
}

CallStmt*
Parser::ParseCallStmt()
{
    return nullptr;
}

ArgPassList*
Parser::ParseArgPassList()
{
    return nullptr;
}