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

#include <Common/Assert.hpp>
#include <Lex/Lexer.hpp>
#include <Lex/Location.hpp>
#include <Lex/Token.hpp>
#include <Lex/TokenType.hpp>
#include <Parse/Parser.hpp>
#include <Trees/Parse/Ast.hpp>
#include <cstddef>
#include <set>

using namespace Parse;
using Lex::TokenType;
using OpKind = BinaryOperation::OpKind;

//
// Definitions
//

Expr*
Parser::ParseExpr()
{
    /*
        Expr -> Logc
    */

    return ParseLogc();
}

Cond*
Parser::ParseCond()
{
    /*
        Cond -> Expr
    */

    return ParseExpr();
}

template <typename Head,
          typename Body,
          bool SingleKindAllowed = false>
Expr*
ParseBinaryOperation(Parser&                           parser,
                     Lex::Lexer&                       lexer,
                     std::set<BinaryOperation::OpKind> kinds,
                     Expr* (Parser::*ParseBody)())
{
    auto first = (parser.*ParseBody)();
    if (first == nullptr)
        return nullptr;

    Head*  head         = nullptr;
    OpKind firstKindMet = OpKind::None;

    while (true)
    {
        auto   token = lexer.Peek();
        OpKind kind  = OpKind::None;

        for (auto allowedKind : kinds)
        {
            if (BinaryOperation::KindToTokenType(allowedKind) ==
                token.type)
            {
                kind = allowedKind;
                break;
            }
        }

        if (kind == OpKind::None)
            return head ? head : first;

        lexer.Advance();

        if (firstKindMet == OpKind::None)
            firstKindMet = kind;

        else if (SingleKindAllowed && firstKindMet != kind)
        {
            // error: allowed only one kind

            // but we proceed to process, because it is
            // the best error recovery in this case
        }

        if (head == nullptr)
        {
            // executed once
            head = new Head(first->Location());
            Assert(head);

            auto binary = static_cast<BinaryOperation*>(head);
            binary->operands.push_back(first);

            // for safety & possible sanity checks
            first = nullptr;
        }

        auto binary = static_cast<BinaryOperation*>(head);

        binary->operations.push_back(kind);

        auto second = (parser.*ParseBody)();
        if (second == nullptr)
        {
            // error: expected Body

            // binary.Correct() == false
            return head;
        }

        binary->operands.push_back(second);
    }
}

Expr*
Parser::ParseLogc()
{
    /*
        Logc -> Comp {{<LAND> + <LOR>} Comp}*
    */

    return ParseBinaryOperation<Logc, Comp, true>(
        *this, lexer_, {OpKind::Land, OpKind::Lor},
        &Parser::ParseComp);
}

Expr*
Parser::ParseComp()
{
    /*
        Comp -> Form {{ <LSS> +
                        <GTR> +
                        <LEQ> +
                        <GEQ> +
                        <EQL> +
                        <NEQ>} Form}*
    */

    return ParseBinaryOperation<Comp, Form>(
        *this, lexer_,
        {OpKind::Lss, OpKind::Gtr, OpKind::Leq, OpKind::Geq,
         OpKind::Eql, OpKind::Neq},
        &Parser::ParseForm);
}

Expr*
Parser::ParseForm()
{
    /*
        Form -> Term {{<ADD> + <SUB> + <OR>} Term}*
    */

    return ParseBinaryOperation<Form, Term>(
        *this, lexer_, {OpKind::Add, OpKind::Sub, OpKind::Or},
        &Parser::ParseTerm);
}

Expr*
Parser::ParseTerm()
{
    /*
        Term -> Prim {{<MUL> + <DIV> + <AND>} Prim}*
    */

    return ParseBinaryOperation<Term, Prim>(
        *this, lexer_, {OpKind::Mul, OpKind::Div, OpKind::And},
        &Parser::ParsePrim);
}
