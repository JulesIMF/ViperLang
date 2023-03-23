/*++

Copyright (c) 2023 JulesIMF, MIPT

Module Name:

    Parser.hpp

Abstract:



Author / Creation date:

    JulesIMF / 19.03.23

Revision History:

--*/

#pragma once

//
// Includes / usings
//

#include <Lex/Lexer.hpp>
#include <Parse/ParsingError.hpp>
#include <Trees/Parse/Ast.hpp>

//
// Definitions
//

namespace Parse
{
class Parser
{
public:
    Parser(Lex::Lexer& lexer_);

    File*
    ParseFile();
    SuperStmtList*
    ParseSuperStmtList();
    SuperStmt*
    ParseSuperStmt();
    StmtList*
    ParseStmtList();
    StmtBlock*
    ParseStmtBlock();
    FncDef*
    ParseFncDef();
    Stmt*
    ParseStmt();
    StmtSemiColon*
    ParseStmtSemiColon();
    StmtColon*
    ParseStmtColon();
    Ret*
    ParseRet();
    Break*
    ParseBreak();
    Continue*
    ParseContinue();
    CallStmt*
    ParseCallStmt();
    ArgPassList*
    ParseArgPassList();
    VarDecl*
    ParseVarDecl();
    Asgn*
    ParseAsgn();
    If*
    ParseIf();
    While*
    ParseWhile();
    For*
    ParseFor();
    ArgDefList*
    ParseArgDefList();
    Type*
    ParseType();
    Expr*
    ParseExpr();
    Cond*
    ParseCond();
    Expr*
    ParseLogc();
    Expr*
    ParseComp();
    Expr*
    ParseForm();
    Expr*
    ParseTerm();
    Expr*
    ParsePrim();
    Unary*
    ParseUnary();
    CallExpr*
    ParseCallExpr();
    Imm*
    ParseImm();
    Int*
    ParseInt();
    Float*
    ParseFloat();
    Char*
    ParseChar();
    String*
    ParseString();
    Var*
    ParseVar();
    Bool*
    ParseBool();

protected:
    void
    SendError_(ParsingError error);

protected:
    Lex::Lexer& lexer_;
};
}  // namespace Parse