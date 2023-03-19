/*++

Copyright (c) 2023 JulesIMF, MIPT

Module Name:

    Prim.cpp

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
Parser::ParsePrim()
{
    if (auto node = ParseUnary())
        return node;
    
    if (auto node = ParseCallExpr())
        return node;
    
    if (auto node = ParseImm())
        return node;
    
    if (auto node = ParseVar())
        return node;
    
    if (!lexer_.Matches(TokenType::LPAREN))
        return nullptr;
    
    auto node = ParseExpr();

    if (node == nullptr)
    {
        // error: expected expression
    }

    if (!lexer_.Matches(TokenType::RPAREN))
    {
        // error: expected rparen
    }

    return node;
}

Unary*
Parser::ParseUnary()
{
    auto token = lexer_.Peek();
    switch (token.type)
    {
        case Lex::TokenType::SUB:
        {
            lexer_.Advance();
            auto node  = new Unary(token.location);
            node->kind = Unary::UnaryKind::Sub;
            node->prim = ParsePrim();
            return node;
        }

        case Lex::TokenType::NOT:
        {
            lexer_.Advance();
            auto node  = new Unary(token.location);
            node->kind = Unary::UnaryKind::Not;
            node->prim = ParsePrim();
            return node;
        }

        default:
            return nullptr;
    }
}

CallExpr*
Parser::ParseCallExpr()
{
    /*
        CallExpr -> <ID> ArgPassList
    */
    if (lexer_.Peek().type != TokenType::ID)
        return nullptr;

    auto idToken = lexer_.Peek();
    lexer_.Advance();

    if (lexer_.Peek().type != TokenType::LPAREN)
    {
        lexer_.Unget();
        return nullptr;
    }

    auto node         = new CallExpr(idToken.location);
    node->funcId      = idToken.GetIdAttributes();
    node->argPassList = ParseArgPassList();

    return node;
}

Imm*
Parser::ParseImm()
{
    /*
        Imm -> <INT> | <FLOAT> | <CHAR> | <STRING>
    */
    if (auto node = ParseInt())
        return node;

    if (auto node = ParseChar())
        return node;

    if (auto node = ParseString())
        return node;

    return nullptr;
}

Int*
Parser::ParseInt()
{
    /*
        Int -> <INT>
    */

    auto token = lexer_.Peek();
    if (token.type != TokenType::INT)
        return nullptr;

    auto node           = new Int(token.location);
    node->intAttributes = token.GetIntAttributes();
    return node;
}

Float*
Parser::ParseFloat()
{
    Unreachable();
    return nullptr;
}

Char*
Parser::ParseChar()
{
    /*
        Char -> <CHAR>
    */

    auto token = lexer_.Peek();
    if (token.type != TokenType::CHAR)
        return nullptr;

    auto node            = new Char(token.location);
    node->charAttributes = token.GetCharAttributes();
    return node;
}

String*
Parser::ParseString()
{
    /*
        String -> <STRING>
    */

    auto token = lexer_.Peek();
    if (token.type != TokenType::STRING)
        return nullptr;

    auto node              = new String(token.location);
    node->stringAttributes = token.GetStringAttributes();
    return node;
}

Var*
Parser::ParseVar()
{
    /*
        Var -> <ID>
    */

    auto token = lexer_.Peek();
    if (token.type != TokenType::ID)
        return nullptr;

    auto node   = new Var(token.location);
    node->varId = token.GetIdAttributes();
    return node;
}