/*++

Copyright (c) 2023 JulesIMF, MIPT

Module Name:

    Main.cpp

Abstract:

    Main playground file.

Author / Creation date:

    JulesIMF / 19.03.23

Revision History:

--*/

//
// Includes / usings
//

#include "Lex/Location.hpp"
#include "Trees/Parse/Ast.hpp"
#include <Trees/Parse/AstDumpVisitor.hpp>

//
// Definitions
//

using namespace Parse;

int
main()
{
    Lex::Location location = {.line = 12, .column = 34};
    auto          file     = new File(location);
    file->superStmtList =
        new SuperStmtList({.line = 10, .column = 20});

    auto funcDecl          = new FncDef(location);
    funcDecl->funcId.value = "foo";
    funcDecl->argDefList   = new ArgDefList(location);
    {
        auto vd                = new VarDecl(location);
        vd->varId.value        = "farg";
        vd->type               = new Type(location);
        vd->type->typeId.value = "ui32";
        vd->initExpr           = new Int(location);
        vd->initExpr->As<Int>()->intAttributes = {.base  = 16,
                                                  .value = 100};
        funcDecl->argDefList->Nodes().push_back(vd);
    }

    funcDecl->type               = new Type(location);
    funcDecl->type->typeId.value = "uint32";

    funcDecl->stmtBlock          = new StmtBlock(location);

    {
        auto wh                          = new While(location);
        wh->cond                         = new Var(location);
        wh->cond->As<Var>()->varId.value = "farg";
        wh->stmtBlock                    = new StmtBlock(location);
        {
            wh->cond = new Var(location);
            wh->cond->As<Var>()->varId.value = "farg";
            wh->stmtBlock = new StmtBlock(location);
            {
                auto iff = new If(location);
                iff->ifBlock.cond = new Var(location);
                iff->ifBlock.cond->As<Var>()->varId.value = "farg";
                iff->ifBlock.stmtBlock = new StmtBlock(location);

                auto brk = new Break(location);
                iff->ifBlock.stmtBlock->Nodes().push_back(brk);

                wh->stmtBlock->Nodes().push_back(iff);
            }

            {
                auto asgn = new Asgn(location);
                asgn->kind = Asgn::Kind::Sub;
                auto var = new Var(location);
                var->varId.value = "farg";
                asgn->lValue = var;

                asgn->expr = new Int(location);
                asgn->expr->As<Int>()->intAttributes.base = 10;
                asgn->expr->As<Int>()->intAttributes.value = 1;

                wh->stmtBlock->Nodes().push_back(asgn);
            }
        }

        funcDecl->stmtBlock->Nodes().push_back(wh);
    }

    {
        auto ret = new Ret(location);
        ret->expr = new Var(location);
        ret->expr->As<Var>()->varId.value = "farg";
        funcDecl->stmtBlock->Nodes().push_back(ret);
    }

    file->superStmtList->Nodes().push_back(funcDecl);

    auto stmtList          = new StmtList(location);
    auto vd                = new VarDecl(location);
    vd->varId.value        = "init";
    vd->type               = new Type(location);
    vd->type->typeId.value = "uint32";

    {
        auto form = new Form(location);
        {
            auto term = new Term(location);

            {
                auto termleft = new Int(location);
                termleft->As<Int>()->intAttributes.value = 100;
                termleft->As<Int>()->intAttributes.base  = 10;
                term->operands.push_back(termleft);
            }

            term->operations.push_back(Term::OpKind::Mul);

            {
                auto termright         = new Var(location);
                termright->varId.value = "init";
                term->operands.push_back(termright);
            }

            form->operands.push_back(term);
        }

        form->operations.push_back(Form::OpKind::Add);

        {
            auto imm                            = new Int(location);
            imm->As<Int>()->intAttributes.value = 100;
            imm->As<Int>()->intAttributes.base  = 10;
            form->operands.push_back(imm);
        }

        form->operations.push_back(Form::OpKind::Sub);

        {
            auto imm                            = new Int(location);
            imm->As<Int>()->intAttributes.value = 100;
            imm->As<Int>()->intAttributes.base  = 10;
            form->operands.push_back(imm);
        }

        vd->initExpr = form;
    }

    stmtList->Nodes().push_back(vd);

    auto call = new CallStmt(location);
    call->funcId.value = "foo";
    auto var         = new Var(location);
    var->varId.value = "init";
    call->argPassList = new ArgPassList(location);
    call->argPassList->Nodes().push_back(var);

    file->superStmtList->Nodes().push_back(stmtList);

    AstDumpVisitor("ast.png").Visit(file);
}