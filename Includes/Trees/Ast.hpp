/*++

Copyright (c) 2023 JulesIMF, MIPT

Module Name:

    ast.hpp

Abstract:



Author / Creation date:

    JulesIMF / 16.03.23

Revision History:

--*/

#pragma once

//
// Includes / usings
//

#include <Lex/Location.hpp>
#include <Lex/Token.hpp>
#include <Trees/BasicTree.hpp"
#include <cstddef>
#include <vector>

//
// Definitions
//

namespace Parse
{
class File;
class SuperStmtList;
class SuperStmt;
class StmtList;
class StmtBlock;
class FncDef;
class Stmt;
class StmtSemiColon;
class StmtColon;
class Ret;
class Break;
class Continue;
class CallStmt;
class ArgPassList;
class VarDecl;
class VarDeclInit;
class Asgn;
class If;
class While;
class For;
class ArgDefList;
class Type;
class Cond;
class Expr;
class Comp;
class Form;
class Term;
class Prim;
class CallExpr;
class Imm;
class Var;

class AstVisitor : public Visitor
{
public:
    virtual void
    File(File*) = 0;

    virtual void
    SuperStmtList(SuperStmtList*) = 0;

    virtual void
    SuperStmt(SuperStmt*) = 0;

    virtual void
    StmtList(StmtList*) = 0;

    virtual void
    StmtBlock(StmtBlock*) = 0;

    virtual void
    FncDef(FncDef*) = 0;

    virtual void
    Stmt(Stmt*) = 0;

    virtual void
    StmtSemiColon(StmtSemiColon*) = 0;

    virtual void
    StmtColon(StmtColon*) = 0;

    virtual void
    Ret(Ret*) = 0;

    virtual void
    Break(Break*) = 0;

    virtual void
    Continue(Continue*) = 0;

    virtual void
    CallStmt(CallStmt*) = 0;

    virtual void
    ArgPassList(ArgPassList*) = 0;

    virtual void
    VarDecl(VarDecl*) = 0;

    virtual void
    VarDeclInit(VarDeclInit*) = 0;

    virtual void
    Asgn(Asgn*) = 0;

    virtual void
    If(If*) = 0;

    virtual void
    While(While*) = 0;

    virtual void
    For(For*) = 0;

    virtual void
    ArgDefList(ArgDefList*) = 0;

    virtual void
    Type(Type*) = 0;

    virtual void
    Cond(Cond*) = 0;

    virtual void
    Expr(Expr*) = 0;

    virtual void
    Comp(Comp*) = 0;

    virtual void
    Form(Form*) = 0;

    virtual void
    Term(Term*) = 0;

    virtual void
    Prim(Prim*) = 0;

    virtual void
    CallExpr(CallExpr*) = 0;

    virtual void
    Imm(Imm*) = 0;

    virtual void
    Var(Var*) = 0;
};

class AstNode : public BasicTree
{
public:
    AstNode(Lex::Location location) :
        location_(location)
    {
    }

protected:
    Lex::Location location_;
};

template <typename T>
class AstList : public AstNode
{
public:
    AstList(Lex::Location location) :
        AstNode(location)
    {
    }

    inline bool
    Empty() const
    {
        return nodes_.empty();
    }

    inline size_t
    Size() const
    {
        return nodes_.size();
    }

    inline std::vector<T*>&
    Nodes()
    {
        return nodes_;
    }

protected:
    std::vector<T> nodes_;
};

class File : public AstNode
{
public:
    File(Lex::Location location) :
        AstNode(location)
    {
    }

    virtual void
    Accept(Visitor& visitor)
    {
        visitor.As<AstVisitor>().File(this);
    }

    SuperStmtList* superStmtList = nullptr;
};

class SuperStmtList : public AstList<SuperStmt*>
{
public:
    using SuperType = AstList<SuperStmt*>;

    SuperStmtList(Lex::Location location) :
        SuperType(location)
    {
    }

    virtual void
    Accept(Visitor& visitor)
    {
        visitor.As<AstVisitor>().SuperStmtList(this);
    }
};

class SuperStmt : public AstNode
{
public:
    SuperStmt(Lex::Location location) :
        AstNode(location)
    {
    }

    virtual void
    Accept(Visitor& visitor)
    {
        visitor.As<AstVisitor>().SuperStmt(this);
    }
};

class StmtList : public AstList<Stmt*>
{
public:
    using SuperType = AstList<Stmt*>;

    StmtList(Lex::Location location) :
        SuperType(location)
    {
    }

    virtual void
    Accept(Visitor& visitor)
    {
        visitor.As<AstVisitor>().StmtList(this);
    }
};

class StmtBlock : public StmtList
{
public:
    StmtBlock(Lex::Location location) :
        StmtList(location)
    {
    }

    virtual void
    Accept(Visitor& visitor)
    {
        visitor.As<AstVisitor>().StmtBlock(this);
    }
};

class FncDef : public SuperStmt
{
public:
    FncDef(Lex::Location location) :
        SuperStmt(location)
    {
    }

    virtual void
    Accept(Visitor& visitor)
    {
        visitor.As<AstVisitor>().FncDef(this);
    }

    Lex::Token* Id = nullptr;
    ArgDefList* argDefList = nullptr;
    Type* type = nullptr;
    StmtBlock* stmtBlock = nullptr;
};

class Stmt : public SuperStmt
{
public:
    Stmt(Lex::Location location) :
        SuperStmt(location)
    {
    }

    virtual void
    Accept(Visitor& visitor)
    {
        visitor.As<AstVisitor>().Stmt(this);
    }
};

class StmtSemiColon : public Stmt
{
public:
    StmtSemiColon(Lex::Location location) :
        Stmt(location)
    {
    }

    virtual void
    Accept(Visitor& visitor)
    {
        visitor.As<AstVisitor>().StmtSemiColon(this);
    }
};

class StmtColon : public Stmt
{
public:
    StmtColon(Lex::Location location) :
        Stmt(location)
    {
    }

    virtual void
    Accept(Visitor& visitor)
    {
        visitor.As<AstVisitor>().StmtColon(this);
    }
};

class Ret : public StmtSemiColon
{
public:
    Ret(Lex::Location location) :
        StmtSemiColon(location)
    {
    }

    virtual void
    Accept(Visitor& visitor)
    {
        visitor.As<AstVisitor>().Ret(this);
    }
};

class Break : public StmtSemiColon
{
public:
    Break(Lex::Location location) :
        StmtSemiColon(location)
    {
    }

    virtual void
    Accept(Visitor& visitor)
    {
        visitor.As<AstVisitor>().Break(this);
    }
};

class Continue : public StmtSemiColon
{
public:
    Continue(Lex::Location location) :
        StmtSemiColon(location)
    {
    }

    virtual void
    Accept(Visitor& visitor)
    {
        visitor.As<AstVisitor>().Continue(this);
    }
};

class CallStmt : public StmtSemiColon
{
public:
    CallStmt(Lex::Location location) :
        StmtSemiColon(location)
    {
    }

    virtual void
    Accept(Visitor& visitor)
    {
        visitor.As<AstVisitor>().CallStmt(this);
    }
};

class ArgPassList : public AstNode
{
public:
    ArgPassList(Lex::Location location) :
        AstNode(location)
    {
    }

    virtual void
    Accept(Visitor& visitor)
    {
        visitor.As<AstVisitor>().ArgPassList(this);
    }
};

class VarDecl : public StmtSemiColon
{
public:
    VarDecl(Lex::Location location) :
        StmtSemiColon(location)
    {
    }

    virtual void
    Accept(Visitor& visitor)
    {
        visitor.As<AstVisitor>().VarDecl(this);
    }
};

class VarDeclInit : public VarDecl
{
public:
    VarDeclInit(Lex::Location location) :
        VarDecl(location)
    {
    }

    virtual void
    Accept(Visitor& visitor)
    {
        visitor.As<AstVisitor>().VarDeclInit(this);
    }
};

class Asgn : public StmtSemiColon
{
public:
    Asgn(Lex::Location location) :
        StmtSemiColon(location)
    {
    }

    virtual void
    Accept(Visitor& visitor)
    {
        visitor.As<AstVisitor>().Asgn(this);
    }
};

class If : public StmtColon
{
public:
    If(Lex::Location location) :
        StmtColon(location)
    {
    }

    virtual void
    Accept(Visitor& visitor)
    {
        visitor.As<AstVisitor>().If(this);
    }

    StmtBlock* stmtBlock = nullptr;
};

class While : public StmtColon
{
public:
    While(Lex::Location location) :
        StmtColon(location)
    {
    }

    virtual void
    Accept(Visitor& visitor)
    {
        visitor.As<AstVisitor>().While(this);
    }

    StmtBlock* stmtBlock = nullptr;
};

class For : public StmtColon
{
public:
    For(Lex::Location location) :
        StmtColon(location)
    {
    }

    virtual void
    Accept(Visitor& visitor)
    {
        visitor.As<AstVisitor>().For(this);
    }

    StmtBlock* stmtBlock = nullptr;
};

class ArgDefList : public AstNode
{
public:
    ArgDefList(Lex::Location location) :
        AstNode(location)
    {
    }

    virtual void
    Accept(Visitor& visitor)
    {
        visitor.As<AstVisitor>().ArgDefList(this);
    }
};

class Type : public AstNode
{
public:
    Type(Lex::Location location) :
        AstNode(location)
    {
    }

    virtual void
    Accept(Visitor& visitor)
    {
        visitor.As<AstVisitor>().Type(this);
    }
};

class Cond : public AstNode
{
public:
    Cond(Lex::Location location) :
        AstNode(location)
    {
    }

    virtual void
    Accept(Visitor& visitor)
    {
        visitor.As<AstVisitor>().Cond(this);
    }
};

class Expr : public AstNode
{
public:
    Expr(Lex::Location location) :
        AstNode(location)
    {
    }

    virtual void
    Accept(Visitor& visitor)
    {
        visitor.As<AstVisitor>().Expr(this);
    }
};

class Comp : public AstNode
{
public:
    Comp(Lex::Location location) :
        AstNode(location)
    {
    }

    virtual void
    Accept(Visitor& visitor)
    {
        visitor.As<AstVisitor>().Comp(this);
    }
};

class Form : public AstNode
{
public:
    Form(Lex::Location location) :
        AstNode(location)
    {
    }

    virtual void
    Accept(Visitor& visitor)
    {
        visitor.As<AstVisitor>().Form(this);
    }
};

class Term : public AstNode
{
public:
    Term(Lex::Location location) :
        AstNode(location)
    {
    }

    virtual void
    Accept(Visitor& visitor)
    {
        visitor.As<AstVisitor>().Term(this);
    }
};

class Prim : public AstNode
{
public:
    Prim(Lex::Location location) :
        AstNode(location)
    {
    }

    virtual void
    Accept(Visitor& visitor)
    {
        visitor.As<AstVisitor>().Prim(this);
    }
};

class CallExpr : public AstNode
{
public:
    CallExpr(Lex::Location location) :
        AstNode(location)
    {
    }

    virtual void
    Accept(Visitor& visitor)
    {
        visitor.As<AstVisitor>().CallExpr(this);
    }
};

class Imm : public AstNode
{
public:
    Imm(Lex::Location location) :
        AstNode(location)
    {
    }

    virtual void
    Accept(Visitor& visitor)
    {
        visitor.As<AstVisitor>().Imm(this);
    }
};

class Var : public AstNode
{
public:
    Var(Lex::Location location) :
        AstNode(location)
    {
    }

    virtual void
    Accept(Visitor& visitor)
    {
        visitor.As<AstVisitor>().Var(this);
    }
};

};  // namespace Parse