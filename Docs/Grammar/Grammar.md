<!--
* ++
*
* Copyright (c) 2023 JulesIMF, MIPT
*
* Module Name:
*
*     Grammar.md
*
* Abstract:
*
*     Grammar description.
*
* Author / Creation date:
*
*     JulesIMF / 17.03.23
*
* Revision History:
*	18.03.23  04:14  JulesIMF		Fixed some contraversals / mistakes
*	17.03.23  23:53  JulesIMF		Split Call into CallExpr and CallStmt
* 
* --
*
-->

# Viper grammar description

## Example of code
```python
# This is C with about Python synthax
# These are comments
# This module calculates Fibbonaci numbers

module Entry; # Entry is a reserved name for,
              # obviously, entry module

import Viper.IO as IO;

n: uint64 = input();

def Fibonacci(n: uint64) -> uint64:
    if n <= 1:
        return n;
    
    return Fibonacci(n - 1) + Fibonacci(n - 2);

def LinearFibbonacci(n: uint64) -> uint64:
    a: uint64 = 0;
    b: uint64 = 1;

    for i: uint64 = 0 while i < n with i += 1:
        t = a + b; # Auto-type declaration
        a = b;
        b = t;

    # Different for variants:
    # 1) for n: ...
    # 2) for i in generator(...): ...
    
    return a;

print(Rec);

```

## Grammar
Start symbol: __File__

```
File                -> SuperStmtList <EOFILE>
SuperStmtList       -> {SuperStmt}*
SuperStmt           -> FncDef | StmtList
StmtList            -> Stmt {Stmt}*
StmtBlock           -> <BEGIN> {Stmt}* <END>

FncDef              -> <DEF> <ID> ArgDefList {<RARROW> Type}? <COLON>
                       StmtBlock

Stmt                -> StmtSemiColon |
                       StmtColon

StmtSemiColon       -> { Ret      +
                         Break    +
                         Continue +
                         Call + 
                         VarDecl  + 
                         Asgn } <SEMICOLON>
                        
StmtColon           ->  If | While | For 

Ret                 -> <RETURN> Expr
Break               -> <BREAK>
Continue            -> <CONTINUE>

CallStmt            -> <ID> ArgPassList
ArgPassList         -> <LPAREN> {Expr {<COMMA>Expr}*}? <RPAREN>

VarDecl             -> VarDeclInit | <ID> <COMMA> Type
VarDeclInit         -> <ID> <COMMA> Type <ASGN> Expr

Asgn                -> LValue { <ASGN>      +
                                <ADD_ASGN>  +
                                <SUB_ASGN>  +
                                <MUL_ASGN>  +
                                <DIV_ASGN>  +
                                <REM_ASGN>  +
                                <AND_ASGN>  +
                                <OR_ASGN>   +
                                <LAND_ASGN> +
                                <LOR_ASGN> } Expr

LValue              -> Var

If                  -> <IF> Cond <COMMA> StmtBlock 
                       {<ELIF> Cond <COMMA> StmtBlock}*
                       <ELSE> <COMMA> StmtBlock

While               -> <WHILE> Cond <COMMA> StmtBlock

For                 -> <FOR> Expr <COMMA> StmtBlock

ArgDefList          -> <LPAREN> {VarDecl {<COMMA> VarDecl}*}? <RPAREN>
Type                -> Id

Cond                -> Expr
Expr                -> Logc
Logc                -> Comp {{<LAND> + <LOR>} Comp}*  
Comp                -> Form {{ <LSS> +
                               <GTR> +
                               <LEQ> +
                               <GEQ> +
                               <EQL> +
                               <NEQ>} Form}*

Form                -> Term {{<ADD> + <SUB> + <OR>} Term}*
Term                -> Prim {{<MUL> + <DIV> + <AND>} Prim}*
Prim                -> Unary                  | 
                       CallExpr               | 
                       <LPAREN> Expr <RPAREN> | 
                       Imm                    | 
                       Var

Unary               -> {<NOT> + <SUB>} Prim

CallExpr            -> <ID> ArgPassList
Imm                 -> <INT> | <FLOAT> | <CHAR> | <STRING> | Bool
Var                 -> <ID>
Bool                -> <TRUE> | <FALSE>

```