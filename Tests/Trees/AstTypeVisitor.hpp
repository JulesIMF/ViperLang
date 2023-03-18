/*++

Copyright (c) 2023 JulesIMF, MIPT

Module Name:

    AstTypeVisitor.hpp

Abstract:

    Visits an AST node and writes down its type.

Author / Creation date:

    JulesIMF / 18.03.23

Revision History:

--*/

#pragma once

//
// Includes / usings
//

#include <string>
#include <Trees/Parse/Ast.hpp>

//
// Definitions
//

namespace Parse
{

class AstTypeVisitor : protected Visitor
{
public:
    std::string
    Visit(AstNode* node)
    {
        node->Accept(*this);
        return type_;
    }

protected:
    virtual void
    File(File*)
    {
        type_ = "File";
    }

    virtual void
    SuperStmtList(SuperStmtList*)
    {
        type_ = "SuperStmtList";
    }

    virtual void
    StmtList(StmtList*)
    {
        type_ = "StmtList";
    }

    virtual void
    StmtBlock(StmtBlock*)
    {
        type_ = "StmtBlock";
    }

    virtual void
    FncDef(FncDef*)
    {
        type_ = "FncDef";
    }

    virtual void
    Ret(Ret*)
    {
        type_ = "Ret";
    }

    virtual void
    Break(Break*)
    {
        type_ = "Break";
    }

    virtual void
    Continue(Continue*)
    {
        type_ = "Continue";
    }

    virtual void
    CallStmt(CallStmt*)
    {
        type_ = "CallStmt";
    }

    virtual void
    ArgPassList(ArgPassList*)
    {
        type_ = "ArgPassList";
    }

    virtual void
    VarDecl(VarDecl*)
    {
        type_ = "VarDecl";
    }

    virtual void
    Asgn(Asgn*)
    {
        type_ = "Asgn";
    }

    virtual void
    If(If*)
    {
        type_ = "If";
    }

    virtual void
    While(While*)
    {
        type_ = "While";
    }

    virtual void
    For(For*)
    {
        type_ = "For";
    }

    virtual void
    ArgDefList(ArgDefList*)
    {
        type_ = "ArgDefList";
    }

    virtual void
    Type(Type*)
    {
        type_ = "Type";
    }

    virtual void
    Logc(Logc*)
    {
        type_ = "Logc";
    }

    virtual void
    Comp(Comp*)
    {
        type_ = "Comp";
    }

    virtual void
    Form(Form*)
    {
        type_ = "Form";
    }

    virtual void
    Term(Term*)
    {
        type_ = "Term";
    }

    virtual void
    Unary(Unary*)
    {
        type_ = "Unary";
    }

    virtual void
    CallExpr(CallExpr*)
    {
        type_ = "CallExpr";
    }

    virtual void
    Int(Int*)
    {
        type_ = "Int";
    }

    virtual void
    Float(Float*)
    {
        type_ = "Float";
    }

    virtual void
    Char(Char*)
    {
        type_ = "Char";
    }

    virtual void
    String(String*)
    {
        type_ = "String";
    }

    virtual void
    Var(Var*)
    {
        type_ = "Var";
    }

protected:
    std::string type_;
};
}  // namespace Parse