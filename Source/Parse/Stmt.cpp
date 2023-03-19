/*++

Copyright (c) 2023 JulesIMF, MIPT

Module Name:

    Stmt.cpp

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

StmtList*
Parser::ParseStmtList()
{
    return nullptr;
}

StmtBlock*
Parser::ParseStmtBlock()
{
    return nullptr;
}

Stmt*
Parser::ParseStmt()
{
    return nullptr;
}

StmtSemiColon*
Parser::ParseStmtSemiColon()
{
    return nullptr;
}

StmtColon*
Parser::ParseStmtColon()
{
    return nullptr;
}

Ret*
Parser::ParseRet()
{
    return nullptr;
}

Break*
Parser::ParseBreak()
{
    return nullptr;
}

Continue*
Parser::ParseContinue()
{
    return nullptr;
}

VarDecl*
Parser::ParseVarDecl()
{
    return nullptr;
}

Asgn*
Parser::ParseAsgn()
{
    return nullptr;
}

If*
Parser::ParseIf()
{
    return nullptr;
}

While*
Parser::ParseWhile()
{
    return nullptr;
}

For*
Parser::ParseFor()
{
    return nullptr;
}