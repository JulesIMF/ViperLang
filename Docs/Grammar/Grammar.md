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
StmtBlock           -> <BEGIN> StmtList <END>

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
                        
StmtColon           -> { If       +
                         While    +
                         For } <COLON> StmtBlock

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

If                  -> <IF> Cond <COMMA> StmtBlock 
                       {<ELIF> Cond <COMMA> StmtBlock}*
                       <ELSE> <COMMA> StmtBlock

While               -> <WHILE> Cond <COMMA> StmtBlock

For                 -> <FOR> Expr <COMMA> StmtBlock

ArgDefList          -> <LPAREN> {VarDecl {<COMMA> VarDecl}*}? <RPAREN>
Type                -> Id

Cond                -> Expr
Expr                -> Comp {{<AND> + <OR>} Comp}*  
Comp                -> Form { <LSS> +
                              <GTR> +
                              <LEQ> +
                              <GEQ> +
                              <EQL> +
                              <NEQ>} Form

Form                -> Term {{<ADD> + <SUB>} Term}*
Term                -> Prim {{<MUL> + <DIV>} Prim}* 
Prim                -> {<NOT> + <SUB>}? Prim  | 
                       CallExpr               | 
                       <LPAREN> Expr <RPAREN> | 
                       Imm                    | 
                       Var

CallExpr            -> <ID> ArgPassList
Imm                 -> <INT> | <FLOAT> | <CHAR> | <STRING>
Var                 -> <ID>

```