/*++

Copyright (c) 2023 JulesIMF, MIPT

Module Name:

    Expr.cpp

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

Expr*
Parser::ParseExpr()
{
    return nullptr;
}

Cond*
Parser::ParseCond()
{
    return nullptr;
}

Expr*
Parser::ParseLogc()
{
    return nullptr;
}

Expr*
Parser::ParseComp()
{
    return nullptr;
}

Expr*
Parser::ParseForm()
{
    return nullptr;
}

Expr*
Parser::ParseTerm()
{
    return nullptr;
}
