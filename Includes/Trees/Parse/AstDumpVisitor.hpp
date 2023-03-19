/*++

Copyright (c) 2023 JulesIMF, MIPT

Module Name:

    AstDumpVisitor.hpp

Abstract:



Author / Creation date:

    JulesIMF / 19.03.23

Revision History:

--*/

#pragma once

//
// Includes / usings
//

#include <Trees/Parse/Ast.hpp>
#include <Trees/Parse/AstVisitor.hpp>
#include <fstream>
#include <string>

//
// Definitions
//

namespace Parse
{
class AstDumpVisitor : public AstVisitor
{
public:
    AstDumpVisitor(std::string);

    void
    SpecifyOutputFile(std::string filename);

    virtual void
    File(class File* pFile) override;

    virtual void
    SuperStmtList(class SuperStmtList* pSuperStmtList) override;

    virtual void
    StmtList(class StmtList* pStmtList) override;

    virtual void
    StmtBlock(class StmtBlock* pStmtBlock) override;

    virtual void
    FncDef(class FncDef* pFncDef) override;

    virtual void
    Ret(class Ret* pRet) override;

    virtual void
    Break(class Break* pBreak) override;

    virtual void
    Continue(class Continue* pContinue) override;

    virtual void
    CallStmt(class CallStmt* pCallStmt) override;

    virtual void
    ArgPassList(class ArgPassList* pArgPassList) override;

    virtual void
    VarDecl(class VarDecl* pVarDecl) override;

    virtual void
    Asgn(class Asgn* pAsgn) override;

    virtual void
    If(class If* pIf) override;

    virtual void
    While(class While* pWhile) override;

    virtual void
    For(class For* pFor) override;

    virtual void
    ArgDefList(class ArgDefList* pArgDefList) override;

    virtual void
    Type(class Type* pType) override;

    virtual void
    Logc(class Logc* pLogc) override;

    virtual void
    Comp(class Comp* pComp) override;

    virtual void
    Form(class Form* pForm) override;

    virtual void
    Term(class Term* pTerm) override;

    virtual void
    Unary(class Unary* pUnary) override;

    virtual void
    CallExpr(class CallExpr* pCallExpr) override;

    virtual void
    Int(class Int* pInt) override;

    virtual void
    Float(class Float* pFloat) override;

    virtual void
    Char(class Char* pChar) override;

    virtual void
    String(class String* pString) override;

    virtual void
    Var(class Var* pVar) override;

protected:
    class Guard
    {
    public:
        Guard(AstDumpVisitor* visitor) :
            visitor_(visitor)
        {
            level_ = visitor_->Enter_();
        }

        ~Guard()
        {
            visitor_->Exit_(level_);
        }

    protected:
        int             level_;
        AstDumpVisitor* visitor_;
    };

    Guard
    MakeGuard_();
    int
    Enter_();
    void
    Exit_(int oldLevel);
    void
    Link_(AstNode* from, AstNode* to);
    
    template <typename T>
    void
    CommonBinaryVisitor_(T* ptr, char const* name);

    std::string   filename_;
    int           level_ = 0;
    std::ofstream file_;
};
}  // namespace Parse