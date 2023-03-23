/*++

Copyright (c) 2023 JulesIMF, MIPT

Module Name:

    Visitors.cpp

Abstract:

    Tests for visitors.

Author / Creation date:

    JulesIMF / 23.03.23

Revision History:

--*/

//
// Includes / usings
//

#include <Lex/Lexer.hpp>
#include <Lex/Location.hpp>
#include <Lex/Token.hpp>
#include <Trees/BasicTree.hpp>
#include <Trees/Parse/Ast.hpp>
#include <Trees/Parse/AstTypeVisitor.hpp>
#include <Trees/Parse/AstVisitor.hpp>
#include <catch2/catch.hpp>

#include <cstddef>
#include <iostream>

using namespace Parse;

//
// Definitions
//

TEST_CASE("Visitors", "[Trees/Ast/Visitors]")
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

    CHECK(visitor.TypeOf(pFile) == "File");
    CHECK(visitor.TypeOf(pSuperStmtList) == "SuperStmtList");
    CHECK(visitor.TypeOf(pStmtList) == "StmtList");
    CHECK(visitor.TypeOf(pStmtBlock) == "StmtBlock");
    CHECK(visitor.TypeOf(pFncDef) == "FncDef");
    CHECK(visitor.TypeOf(pRet) == "Ret");
    CHECK(visitor.TypeOf(pBreak) == "Break");
    CHECK(visitor.TypeOf(pContinue) == "Continue");
    CHECK(visitor.TypeOf(pCallStmt) == "CallStmt");
    CHECK(visitor.TypeOf(pArgPassList) == "ArgPassList");
    CHECK(visitor.TypeOf(pVarDecl) == "VarDecl");
    CHECK(visitor.TypeOf(pAsgn) == "Asgn");
    CHECK(visitor.TypeOf(pIf) == "If");
    CHECK(visitor.TypeOf(pWhile) == "While");
    CHECK(visitor.TypeOf(pFor) == "For");
    CHECK(visitor.TypeOf(pArgDefList) == "ArgDefList");
    CHECK(visitor.TypeOf(pType) == "Type");
    CHECK(visitor.TypeOf(pLogc) == "Logc");
    CHECK(visitor.TypeOf(pComp) == "Comp");
    CHECK(visitor.TypeOf(pForm) == "Form");
    CHECK(visitor.TypeOf(pTerm) == "Term");
    CHECK(visitor.TypeOf(pUnary) == "Unary");
    CHECK(visitor.TypeOf(pCallExpr) == "CallExpr");
    CHECK(visitor.TypeOf(pInt) == "Int");
    CHECK(visitor.TypeOf(pChar) == "Char");
    CHECK(visitor.TypeOf(pString) == "String");
    CHECK(visitor.TypeOf(pVar) == "Var");

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
