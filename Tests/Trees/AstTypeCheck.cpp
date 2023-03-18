/*++

Copyright (c) 2023 JulesIMF, MIPT

Module Name:

    AstTypeCheck.cpp

Abstract:

    Checks for AST types inheritance correctness.

Author / Creation date:

    JulesIMF / 18.03.23

Revision History:

--*/

//
// Includes / usings
//

#include "AstTypeVisitor.hpp"
#include <Lex/Lexer.hpp>
#include <Lex/Location.hpp>
#include <Lex/Token.hpp>
#include <Trees/Parse/Ast.hpp>
#include <Trees/Parse/AstVisitor.hpp>
#include <Trees/BasicTree.hpp>
#include <catch2/catch.hpp>

#include <cstddef>
#include <iostream>

using namespace Parse;

//
// Definitions
//

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunused-variable"
// #pragma clang diagnostic ignored "-Wunused-but-set-variable"

TEST_CASE("Compile type checking", "[Trees/Ast/TypeCheck]")
{
    File*          pFile          = nullptr;
    SuperStmtList* pSuperStmtList = nullptr;
    SuperStmt*     pSuperStmt     = nullptr;
    StmtList*      pStmtList      = nullptr;
    StmtBlock*     pStmtBlock     = nullptr;
    FncDef*        pFncDef        = nullptr;
    Stmt*          pStmt          = nullptr;
    StmtSemiColon* pStmtSemiColon = nullptr;
    StmtColon*     pStmtColon     = nullptr;
    Ret*           pRet           = nullptr;
    Break*         pBreak         = nullptr;
    Continue*      pContinue      = nullptr;
    CallStmt*      pCallStmt      = nullptr;
    ArgPassList*   pArgPassList   = nullptr;
    VarDecl*       pVarDecl       = nullptr;
    Asgn*          pAsgn          = nullptr;
    If*            pIf            = nullptr;
    While*         pWhile         = nullptr;
    For*           pFor           = nullptr;
    ArgDefList*    pArgDefList    = nullptr;
    Type*          pType          = nullptr;
    Expr*          pExpr          = nullptr;
    Cond*          pCond          = nullptr;
    Logc*          pLogc          = nullptr;
    Comp*          pComp          = nullptr;
    Form*          pForm          = nullptr;
    Term*          pTerm          = nullptr;
    Prim*          pPrim          = nullptr;
    Unary*         pUnary         = nullptr;
    CallExpr*      pCallExpr      = nullptr;
    Imm*           pImm           = nullptr;
    Int*           pInt           = nullptr;
    Float*         pFloat         = nullptr;
    Char*          pChar          = nullptr;
    String*        pString        = nullptr;
    Var*           pVar           = nullptr;

    //
    // Commented ones should not compile!
    //
    {
    }

    pSuperStmt     = pFncDef;
    pSuperStmt     = pStmtList;
    // pSuperStmt  = pStmt;

    pStmt          = pStmtSemiColon;
    pStmt          = pStmtColon;

    pStmtSemiColon = pRet;
    pStmtSemiColon = pBreak;
    pStmtSemiColon = pContinue;
    pStmtSemiColon = pCallStmt;
    // pStmt       = pCallExpr;
    pStmtSemiColon = pVarDecl;
    pStmtSemiColon = pAsgn;

    pStmtColon     = pIf;
    pStmtColon     = pWhile;
    pStmtColon     = pFor;

    pCond          = pExpr;
    pExpr          = pLogc;
    pExpr          = pComp;
    pExpr          = pForm;
    pExpr          = pTerm;
    pExpr          = pPrim;
    pPrim          = pUnary;
    pPrim          = pCallExpr;
    pPrim          = pImm;
    pImm           = pInt;
    pImm           = pChar;
    pImm           = pString;
    pPrim          = pVar;

    {
        LValue lValue = pVar;
        lValue        = pVar;
    }
}

TEST_CASE("Construct / destruct", "[Trees/Ast/TypeCheck]")
{
    Lex::Location     location;
    Lex::IdAttributes id;

    File*             pFile          = new File(location);
    SuperStmtList*    pSuperStmtList = new SuperStmtList(location);
    SuperStmt*        pSuperStmt     = nullptr;
    StmtList*         pStmtList      = new StmtList(location);
    StmtBlock*        pStmtBlock     = new StmtBlock(location);
    FncDef*           pFncDef        = new FncDef(location);
    Stmt*             pStmt          = nullptr;
    StmtSemiColon*    pStmtSemiColon = nullptr;
    StmtColon*        pStmtColon     = nullptr;
    Ret*              pRet           = new Ret(location);
    Break*            pBreak         = new Break(location);
    Continue*         pContinue      = new Continue(location);
    CallStmt*         pCallStmt      = new CallStmt(location);
    ArgPassList*      pArgPassList   = new ArgPassList(location);
    VarDecl*          pVarDecl       = new VarDecl(location);
    Asgn*             pAsgn          = new Asgn(location);
    If*               pIf            = new If(location);
    While*            pWhile         = new While(location);
    For*              pFor           = new For(location);
    ArgDefList*       pArgDefList    = new ArgDefList(location);
    Type*             pType          = new Type(location);
    Expr*             pExpr          = nullptr;
    Cond*             pCond          = nullptr;
    Logc*             pLogc          = new Logc(location);
    Comp*             pComp          = new Comp(location);
    Form*             pForm          = new Form(location);
    Term*             pTerm          = new Term(location);
    Prim*             pPrim          = nullptr;
    Unary*            pUnary         = new Unary(location);
    CallExpr*         pCallExpr      = new CallExpr(location);
    Imm*              pImm           = nullptr;
    Int*              pInt           = new Int(location);
    Char*             pChar          = new Char(location);
    String*           pString        = new String(location);
    Var*              pVar           = new Var(location);

    delete pFile;
    delete pSuperStmtList;
    delete pStmtList;
    delete pStmtBlock;
    delete pFncDef;
    delete pRet;
    delete pBreak;
    delete pContinue;
    delete pCallStmt;
    delete pArgPassList;
    delete pVarDecl;
    delete pAsgn;
    delete pIf;
    delete pWhile;
    delete pFor;
    delete pArgDefList;
    delete pType;
    delete pLogc;
    delete pComp;
    delete pForm;
    delete pTerm;
    delete pUnary;
    delete pCallExpr;
    delete pInt;
    delete pChar;
    delete pString;
    delete pVar;
}

TEST_CASE("Usage", "[Trees/Ast/TypeCheck]")
{
    Lex::Location     location;
    Lex::IdAttributes id;

    File*             pFile          = new File(location);
    SuperStmtList*    pSuperStmtList = new SuperStmtList(location);
    SuperStmt*        pSuperStmt     = nullptr;
    StmtList*         pStmtList      = new StmtList(location);
    StmtBlock*        pStmtBlock     = new StmtBlock(location);
    FncDef*           pFncDef        = new FncDef(location);
    Stmt*             pStmt          = nullptr;
    StmtSemiColon*    pStmtSemiColon = nullptr;
    StmtColon*        pStmtColon     = nullptr;
    Ret*              pRet           = new Ret(location);
    Break*            pBreak         = new Break(location);
    Continue*         pContinue      = new Continue(location);
    CallStmt*         pCallStmt      = new CallStmt(location);
    ArgPassList*      pArgPassList   = new ArgPassList(location);
    VarDecl*          pVarDecl       = new VarDecl(location);
    Asgn*             pAsgn          = new Asgn(location);
    If*               pIf            = new If(location);
    While*            pWhile         = new While(location);
    For*              pFor           = new For(location);
    ArgDefList*       pArgDefList    = new ArgDefList(location);
    Type*             pType          = new Type(location);
    Expr*             pExpr          = nullptr;
    Cond*             pCond          = nullptr;
    Logc*             pLogc          = new Logc(location);
    Comp*             pComp          = new Comp(location);
    Form*             pForm          = new Form(location);
    Term*             pTerm          = new Term(location);
    Prim*             pPrim          = nullptr;
    Unary*            pUnary         = new Unary(location);
    CallExpr*         pCallExpr      = new CallExpr(location);
    Imm*              pImm           = nullptr;
    Int*              pInt           = new Int(location);
    Char*             pChar          = new Char(location);
    String*           pString        = new String(location);
    Var*              pVar           = new Var(location);

    pFile->superStmtList             = pSuperStmtList;

    pSuperStmtList->Nodes().push_back(pSuperStmt);

    pSuperStmt = pStmtList;
    pStmtList  = pSuperStmt->As<StmtList>();

    pStmtList->Nodes().push_back(pStmt);

    pStmtBlock->Nodes().push_back(pStmt);

    pFncDef->argDefList    = pArgDefList;
    pFncDef->stmtBlock     = pStmtBlock;
    pFncDef->type          = pType;
    pFncDef->stmtBlock     = pStmtBlock;

    pStmt                  = pRet;
    pRet                   = pStmt->As<Ret>();

    pStmtSemiColon         = pContinue;
    pContinue              = pStmtSemiColon->As<Continue>();

    pStmtColon             = pFor;
    pFor                   = pStmtColon->As<For>();

    pRet->expr             = pVar;

    pCallStmt->argPassList = pArgPassList;
    pCallStmt->funcId      = id;

    pArgPassList->Nodes().push_back(pExpr);

    pVarDecl->type     = pType;
    pVarDecl->initExpr = pChar;
    pVarDecl->varId    = id;

    pAsgn->expr        = pExpr;
    pAsgn->lValue      = pVar;
    CHECK(pAsgn->lValue.CurrentKind() == LValue::Kind::Var);

    pIf->ifBlock = {.cond = pCond, .stmtBlock = pStmtBlock};
    pIf->elifBlocks.push_back(pIf->ifBlock);
    pIf->elseBlock    = pStmtBlock;

    pFor->expr        = pTerm;
    pFor->stmtBlock   = pStmtBlock;

    pWhile->cond      = pCond;
    pWhile->stmtBlock = pStmtBlock;

    pArgDefList->Nodes().push_back(pVarDecl);

    pType->typeId = id;

    pExpr         = pLogc;
    pLogc         = pExpr->As<Logc>();

    pLogc->operands.push_back(pComp);
    pComp->operands.push_back(pForm);
    pForm->operands.push_back(pTerm);
    pTerm->operands.push_back(pPrim);

    pPrim                     = pUnary;
    pUnary                    = pPrim->As<Unary>();

    pUnary->prim              = pPrim;

    pCallExpr->funcId         = id;
    pCallExpr->argPassList    = pArgPassList;

    pImm                      = pInt;
    pInt                      = pImm->As<Int>();

    pInt->intAttributes       = Lex::IntAttributes();
    pChar->charAttributes     = Lex::CharAttributes();
    pString->stringAttributes = Lex::StringAttributes();

    pVar->varId               = id;

    CHECK(pRet->StmtKind() == Stmt::Kind::Ret);
    CHECK(pBreak->StmtKind() == Stmt::Kind::Break);
    CHECK(pContinue->StmtKind() == Stmt::Kind::Continue);
    CHECK(pCallStmt->StmtKind() == Stmt::Kind::Call);
    CHECK(pVarDecl->StmtKind() == Stmt::Kind::VarDecl);
    CHECK(pAsgn->StmtKind() == Stmt::Kind::Asgn);
    CHECK(pIf->StmtKind() == Stmt::Kind::If);
    CHECK(pWhile->StmtKind() == Stmt::Kind::While);
    CHECK(pFor->StmtKind() == Stmt::Kind::For);

    CHECK(pLogc->ExprKind() == Expr::Kind::Logc);
    CHECK(pComp->ExprKind() == Expr::Kind::Comp);
    CHECK(pForm->ExprKind() == Expr::Kind::Form);
    CHECK(pTerm->ExprKind() == Expr::Kind::Term);
    CHECK(pUnary->ExprKind() == Expr::Kind::Unary);
    CHECK(pCallExpr->ExprKind() == Expr::Kind::CallExpr);
    CHECK(pInt->ExprKind() == Expr::Kind::Int);
    CHECK(pChar->ExprKind() == Expr::Kind::Char);
    CHECK(pString->ExprKind() == Expr::Kind::String);
    CHECK(pVar->ExprKind() == Expr::Kind::Var);

    delete pFile;
    delete pSuperStmtList;
    delete pStmtList;
    delete pStmtBlock;
    delete pFncDef;
    delete pRet;
    delete pBreak;
    delete pContinue;
    delete pCallStmt;
    delete pArgPassList;
    delete pVarDecl;
    delete pAsgn;
    delete pIf;
    delete pWhile;
    delete pFor;
    delete pArgDefList;
    delete pType;
    delete pLogc;
    delete pComp;
    delete pForm;
    delete pTerm;
    delete pUnary;
    delete pCallExpr;
    delete pInt;
    delete pChar;
    delete pString;
    delete pVar;
}

TEST_CASE("Visitors", "[Trees/Ast/TypeCheck]")
{
    Lex::Location location = {.ptr = 123, .line = 22, .column = 31};
    Lex::IdAttributes id;

    File*             pFile          = new File(location);
    SuperStmtList*    pSuperStmtList = new SuperStmtList(location);
    StmtList*         pStmtList      = new StmtList(location);
    StmtBlock*        pStmtBlock     = new StmtBlock(location);
    FncDef*           pFncDef        = new FncDef(location);
    Ret*              pRet           = new Ret(location);
    Break*            pBreak         = new Break(location);
    Continue*         pContinue      = new Continue(location);
    CallStmt*         pCallStmt      = new CallStmt(location);
    ArgPassList*      pArgPassList   = new ArgPassList(location);
    VarDecl*          pVarDecl       = new VarDecl(location);
    Asgn*             pAsgn          = new Asgn(location);
    If*               pIf            = new If(location);
    While*            pWhile         = new While(location);
    For*              pFor           = new For(location);
    ArgDefList*       pArgDefList    = new ArgDefList(location);
    Type*             pType          = new Type(location);
    Logc*             pLogc          = new Logc(location);
    Comp*             pComp          = new Comp(location);
    Form*             pForm          = new Form(location);
    Term*             pTerm          = new Term(location);
    Unary*            pUnary         = new Unary(location);
    CallExpr*         pCallExpr      = new CallExpr(location);
    Int*              pInt           = new Int(location);
    Char*             pChar          = new Char(location);
    String*           pString        = new String(location);
    Var*              pVar           = new Var(location);

    AstTypeVisitor    visitor;

    CHECK(visitor.Visit(pFile) == "File");
    CHECK(visitor.Visit(pSuperStmtList) == "SuperStmtList");
    CHECK(visitor.Visit(pStmtList) == "StmtList");
    CHECK(visitor.Visit(pStmtBlock) == "StmtBlock");
    CHECK(visitor.Visit(pFncDef) == "FncDef");
    CHECK(visitor.Visit(pRet) == "Ret");
    CHECK(visitor.Visit(pBreak) == "Break");
    CHECK(visitor.Visit(pContinue) == "Continue");
    CHECK(visitor.Visit(pCallStmt) == "CallStmt");
    CHECK(visitor.Visit(pArgPassList) == "ArgPassList");
    CHECK(visitor.Visit(pVarDecl) == "VarDecl");
    CHECK(visitor.Visit(pAsgn) == "Asgn");
    CHECK(visitor.Visit(pIf) == "If");
    CHECK(visitor.Visit(pWhile) == "While");
    CHECK(visitor.Visit(pFor) == "For");
    CHECK(visitor.Visit(pArgDefList) == "ArgDefList");
    CHECK(visitor.Visit(pType) == "Type");
    CHECK(visitor.Visit(pLogc) == "Logc");
    CHECK(visitor.Visit(pComp) == "Comp");
    CHECK(visitor.Visit(pForm) == "Form");
    CHECK(visitor.Visit(pTerm) == "Term");
    CHECK(visitor.Visit(pUnary) == "Unary");
    CHECK(visitor.Visit(pCallExpr) == "CallExpr");
    CHECK(visitor.Visit(pInt) == "Int");
    CHECK(visitor.Visit(pChar) == "Char");
    CHECK(visitor.Visit(pString) == "String");
    CHECK(visitor.Visit(pVar) == "Var");

    delete pFile;
    delete pSuperStmtList;
    delete pStmtList;
    delete pStmtBlock;
    delete pFncDef;
    delete pRet;
    delete pBreak;
    delete pContinue;
    delete pCallStmt;
    delete pArgPassList;
    delete pVarDecl;
    delete pAsgn;
    delete pIf;
    delete pWhile;
    delete pFor;
    delete pArgDefList;
    delete pType;
    delete pLogc;
    delete pComp;
    delete pForm;
    delete pTerm;
    delete pUnary;
    delete pCallExpr;
    delete pInt;
    delete pChar;
    delete pString;
    delete pVar;
}

TEST_CASE("Location", "[Trees/Ast/TypeCheck]")
{
    Lex::Location location = {.ptr = 123, .line = 22, .column = 31};
    File*         pFile    = new File(location);

    CHECK(pFile->Location().ptr == 123);
    CHECK(pFile->Location().line == 22);
    CHECK(pFile->Location().column == 31);

    delete pFile;
}

#pragma clang diagnostic pop