/*++

Copyright (c) 2023 JulesIMF, MIPT

Module Name:

    AstDumpVisitor.cpp

Abstract:



Author / Creation date:

    JulesIMF / 19.03.23

Revision History:

--*/

//
// Includes / usings
//

#include "Lex/IdentTable.hpp"
#include "Lex/Location.hpp"
#include "Trees/Parse/Ast.hpp"
#include <Common/Assert.hpp>
#include <Trees/Parse/AstDumpVisitor.hpp>
#include <fmt/core.h>
#include <pthread.h>
#include <string>
#include <utility>

using namespace Parse;

//
// Definitions
//

static char const* dotFileName = "/tmp/viper_dbg_dot_file.dot";

// Non-visitor functions

AstDumpVisitor::AstDumpVisitor(std::string filename) :
    filename_(filename)
{
}

void
AstDumpVisitor::SpecifyOutputFile(std::string filename)
{
    filename_ = filename;
}

int
AstDumpVisitor::Enter_()
{
    if (level_ == 0)
    {
        Assert(!file_.is_open());

        file_.open(dotFileName);
        AssertMsg(file_.is_open(),
                  fmt::format(
                      "Could not open file \"{}!\n"
                      "M.b. you are running under Windows or have no "
                      "access to the folder?\'",
                      dotFileName));

        file_ << "digraph\n{\ndpi = 300;\n";
    }

    return ++level_;
}

void
AstDumpVisitor::Exit_(int level)
{
    AssertMsg(
        level == level_,
        fmt::format(
            "Somebody forgot to exit and level ({}) != level_ ({})!",
            level, level_));

    if (--level_ == 0)
    {
        Assert(file_.is_open());
        file_ << "}\n";

        file_.close();

        system(fmt::format("dot -Tpng {0} -o "
                           "{1} > /dev/null",
                           dotFileName, filename_)
                   .c_str());
    }
}

AstDumpVisitor::Guard
AstDumpVisitor::MakeGuard_()
{
    return Guard(this);
}

std::string
PtrToName(void* ptr, bool nptr = false)
{
    static int nullCount = 0;
    if (nptr)
        return fmt::format("np_{}_{}", nullCount++, ptr);

    return fmt::format("p{}", ptr);
}

// Visitor functions

std::string
FormatDescription(AstNode*    node,
                  std::string label,
                  std::string shape     = "parallelogram",
                  std::string fillcolor = "orange",
                  std::string style     = "filled, bold")
{
    return fmt::format("{0}"                       // ptrToName
                       "[label = \"{1}\\n{2}\", "  // location, label
                       "shape = \"{3}\", "         // shape
                       "fillcolor = \"{4}\", "     // fillcolor
                       "style = \"{5}\", "         // style
                       "fontsize = 15"
                       "];\n",
                       PtrToName(node),
                       node->Location().FormatShort(), label, shape,
                       fillcolor, style);
}

void
AstDumpVisitor::Link_(AstNode* from, AstNode* to)
{
    AssertMsg(from, "Nullptr passed to Link function");

    if (to)
    {
        file_ << PtrToName(from) << "->" << PtrToName(to) << ";\n";
        to->Accept(*this);
    }

    else
    {
        auto name = PtrToName(from, true);
        file_ << PtrToName(from) << "->" << name << ";\n";
        file_ << name
              << "[label = \"nullptr\", shape = \"record\", "
                 "color = \"red\"];\n";
    }
}

void
AstDumpVisitor::File(class File* pFile)
{
    auto guard = MakeGuard_();

    file_ << FormatDescription(pFile, "File", "parallelogram",
                               "forestgreen");
    Link_(pFile, pFile->superStmtList);
}

void
AstDumpVisitor::SuperStmtList(class SuperStmtList* pSuperStmtList)
{
    auto guard = MakeGuard_();

    file_ << FormatDescription(pSuperStmtList,
                               fmt::format("SuperStmtList"));

    for (auto superStmt : pSuperStmtList->Nodes())
        Link_(pSuperStmtList, superStmt);
}

void
AstDumpVisitor::StmtList(class StmtList* pStmtList)
{
    auto guard = MakeGuard_();

    file_ << FormatDescription(pStmtList, fmt::format("StmtList"));

    for (auto stmt : pStmtList->Nodes())
        Link_(pStmtList, stmt);
}

void
AstDumpVisitor::StmtBlock(class StmtBlock* pStmtBlock)
{
    auto guard = MakeGuard_();

    file_ << FormatDescription(pStmtBlock, fmt::format("StmtBlock"));

    for (auto stmt : pStmtBlock->Nodes())
        Link_(pStmtBlock, stmt);
}

void
AstDumpVisitor::FncDef(class FncDef* pFncDef)
{
    auto guard = MakeGuard_();

    file_ << FormatDescription(
        pFncDef,
        fmt::format("FncDef\\nid: {}", pFncDef->funcId.value),
        "parallelogram", "forestgreen");

    Link_(pFncDef, pFncDef->argDefList);

    if (pFncDef->type)
        Link_(pFncDef, pFncDef->type);

    Link_(pFncDef, pFncDef->stmtBlock);
}

void
AstDumpVisitor::Ret(class Ret* pRet)
{
    auto guard = MakeGuard_();

    file_ << FormatDescription(pRet, fmt::format("Ret"), "diamond",
                               "darkorchid1");
    Link_(pRet, pRet->expr);
}

void
AstDumpVisitor::Break(class Break* pBreak)
{
    auto guard = MakeGuard_();

    file_ << FormatDescription(pBreak, fmt::format("Break"),
                               "diamond", "darkorchid1");
}

void
AstDumpVisitor::Continue(class Continue* pContinue)
{
    auto guard = MakeGuard_();

    file_ << FormatDescription(pContinue, fmt::format("Continue"),
                               "diamond", "darkorchid1");
}

void
AstDumpVisitor::CallStmt(class CallStmt* pCallStmt)
{
    auto guard = MakeGuard_();

    file_ << FormatDescription(
        pCallStmt,
        fmt::format("CallStmt\\nid: {}", pCallStmt->funcId.value),
        "octagon", "darkorchid1");

    Link_(pCallStmt, pCallStmt->argPassList);
}

void
AstDumpVisitor::ArgPassList(class ArgPassList* pArgPassList)
{
    auto guard = MakeGuard_();

    file_ << FormatDescription(pArgPassList,
                               fmt::format("ArgPassList"));

    for (auto arg : pArgPassList->Nodes())
        Link_(pArgPassList, arg);
}

void
AstDumpVisitor::VarDecl(class VarDecl* pVarDecl)
{
    auto guard = MakeGuard_();

    file_ << FormatDescription(
        pVarDecl,
        fmt::format("VarDecl\\nid: {}", pVarDecl->varId.value),
        "diamond", "lightblue");

    Link_(pVarDecl, pVarDecl->type);

    if (pVarDecl->initExpr)
        Link_(pVarDecl, pVarDecl->initExpr);
}

void
AstDumpVisitor::Asgn(class Asgn* pAsgn)
{
    auto guard = MakeGuard_();

    file_ << FormatDescription(
        pAsgn,
        fmt::format("Asgn\\ntype: {}", Asgn::KindToStr(pAsgn->kind)),
        "diamond", "darkorchid1");

    switch (pAsgn->lValue.CurrentKind())
    {
        case LValue::Kind::Var:
            Link_(pAsgn, pAsgn->lValue.AsVar());

        default:;  // pass
    }

    Link_(pAsgn, pAsgn->expr);
}

void
AstDumpVisitor::If(class If* pIf)
{
    auto guard = MakeGuard_();

    file_ << FormatDescription(pIf, fmt::format("If"),
                               "parallelogram", "darkorchid1");

    Link_(pIf, pIf->ifBlock.cond);
    Link_(pIf, pIf->ifBlock.stmtBlock);

    for (auto block : pIf->elifBlocks)
    {
        Link_(pIf, block.cond);
        Link_(pIf, block.stmtBlock);
    }

    if (pIf->elseBlock)
        Link_(pIf, pIf->elseBlock);
}

void
AstDumpVisitor::While(class While* pWhile)
{
    auto guard = MakeGuard_();

    file_ << FormatDescription(pWhile, fmt::format("While"),
                               "parallelogram", "darkorchid1");

    Link_(pWhile, pWhile->cond);
    Link_(pWhile, pWhile->stmtBlock);
}

void
AstDumpVisitor::For(class For* pFor)
{
    auto guard = MakeGuard_();

    file_ << FormatDescription(pFor, fmt::format("For"),
                               "parallelogram", "darkorchid1");

    Link_(pFor, pFor->expr);
    Link_(pFor, pFor->stmtBlock);
}

void
AstDumpVisitor::ArgDefList(class ArgDefList* pArgDefList)
{
    auto guard = MakeGuard_();

    file_ << FormatDescription(pArgDefList,
                               fmt::format("ArgDefList"));

    for (auto def : pArgDefList->Nodes())
        Link_(pArgDefList, def);
}

void
AstDumpVisitor::Type(class Type* pType)
{
    auto guard = MakeGuard_();

    file_ << FormatDescription(
        pType, fmt::format("Type\\nid: {}", pType->typeId.value));
}

template <typename T>
void
AstDumpVisitor::CommonBinaryVisitor_(T* ptr, char const* name)
{
    if (!ptr->Correct() || !ptr->TwoOperands())
    {
        std::string ops = "";
        for (auto op : ptr->operations)
            ops += T::KindToStr(op) + ", ";

        if (ops.empty())
            ops = "[]";

        else
        {
            ops.pop_back();
            ops.pop_back();
            ops = "[" + ops + "]";
        }

        if (!ptr->Correct())
            file_ << FormatDescription(
                ptr, fmt::format("{}\\nBROKEN\\nOps: {}", name, ops),
                "octagon", "yellow");

        else
            file_ << FormatDescription(
                ptr, fmt::format("{}\\nOps: {}", name, ops),
                "octagon", "yellow");

        for (auto opnd : ptr->operands)
            Link_(ptr, opnd);
    }

    else
    {
        file_ << FormatDescription(
            ptr,
            fmt::format("{}\\n{}", name,
                        T::KindToStr(ptr->Operation())),
            "octagon", "yellow");

        Link_(ptr, ptr->Left());
        Link_(ptr, ptr->Right());
    }
}

void
AstDumpVisitor::Logc(class Logc* pLogc)
{
    auto guard = MakeGuard_();

    CommonBinaryVisitor_(pLogc, "Logic");
}

void
AstDumpVisitor::Comp(class Comp* pComp)
{
    auto guard = MakeGuard_();

    CommonBinaryVisitor_(pComp, "Comparasion");
}

void
AstDumpVisitor::Form(class Form* pForm)
{
    auto guard = MakeGuard_();

    CommonBinaryVisitor_(pForm, "Formula");
}

void
AstDumpVisitor::Term(class Term* pTerm)
{
    auto guard = MakeGuard_();

    CommonBinaryVisitor_(pTerm, "Term");
}

void
AstDumpVisitor::Unary(class Unary* pUnary)
{
    auto guard = MakeGuard_();

    file_ << FormatDescription(
        pUnary, fmt::format("Unary\\nKind: {}",
                            Unary::KindToStr(pUnary->kind)));
    Link_(pUnary, pUnary->prim);
}

void
AstDumpVisitor::CallExpr(class CallExpr* pCallExpr)
{
    auto guard = MakeGuard_();

    file_ << FormatDescription(pCallExpr, fmt::format("CallExpr"));
    file_ << FormatDescription(
        pCallExpr,
        fmt::format("CallExpr\\nid: {}", pCallExpr->funcId.value),
        "octagon", "yellow");

    Link_(pCallExpr, pCallExpr->argPassList);
}

void
AstDumpVisitor::Int(class Int* pInt)
{
    auto guard = MakeGuard_();

    file_ << FormatDescription(
        pInt,
        fmt::format("Int\\nbase: {}, value: {}",
                    pInt->intAttributes.base,
                    pInt->intAttributes.value),
        "record", "lightgrey");
}

void
AstDumpVisitor::Float(class Float*)
{
    Unreachable();
    auto guard = MakeGuard_();
}

void
AstDumpVisitor::Char(class Char* pChar)
{
    auto guard = MakeGuard_();

    file_ << FormatDescription(
        pChar,
        fmt::format("Char\\nvalue: \'{}\'",
                    pChar->charAttributes.value),
        "record", "lightgrey");
}

void
AstDumpVisitor::String(class String* pString)
{
    auto guard = MakeGuard_();

    file_ << FormatDescription(
        pString,
        fmt::format("String\\nvalue: \'{}\'",
                    pString->stringAttributes.value),
        "record", "lightgrey");
}

void
AstDumpVisitor::Var(class Var* pVar)
{
    auto guard = MakeGuard_();

    file_ << FormatDescription(
        pVar, fmt::format("Var\\nid: \'{}\'", pVar->varId.value),
        "record", "lightgrey");
}

void
AstDumpVisitor::Bool(class Bool* pBool)
{
    auto guard = MakeGuard_();

    file_ << FormatDescription(
        pBool,
        fmt::format("Bool\\nvalue: \'{}\'",
                    pBool->value ? "true" : "false"),
        "record", "lightgrey");
}
