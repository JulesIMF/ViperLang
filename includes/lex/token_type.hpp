#pragma once

#include <cstdlib>

namespace Lex
{

//////////////////////////////////////////////////////////////////////

enum class TokenType
{
    //
    // Pseudo tokens
    //

    NONE,     // default constructed
    ERROR,    // returned when error
    WS,       // '\n', '\t', ' '
    COMMENT,  // #
    EOFILE,   // non-existant

    //
    // General tokens
    //

    ID,      // "n", "wdog1", "id"
    INT,     // 12, 500000000ll, 100'000
    FLOAT,   // 10e5, -3.14
    CHAR,    // 'x', '\t'
    STRING,  // "hello", "hello"  "world"

    //
    // Delimiters
    //

    LPAREN,  // (
    RPAREN,  // )
    LBRACK,  // [
    RBRACK,  // ]
    LBRACE,  // {
    RBRACE,  // }
    IDENT,   // identation that may be converted to the next two
    BEGIN,   // new identation
    END,     // old identation

    COMMA,      // ,
    DOT,        // .
    SEMICOLON,  // ;
    COLON,      // :
    RARROW,     // ->

    //
    // Operators
    //

    ADD,   // +
    SUB,   // -
    MUL,   // *
    DIV,   // /
    REM,   // %
    AND,   // &
    OR,    // |
    NOT,   // !
    LAND,  // &&
    LOR,   // ||
    LSS,   // <
    GTR,   // >
    LEQ,   // <=
    GEQ,   // >=
    EQL,   // ==
    NEQ,   // !=

    //
    // Assignation
    //

    ASGN,       // =
    ADD_ASGN,   // +=
    SUB_ASGN,   // -=
    MUL_ASGN,   // *=
    DIV_ASGN,   // /=
    REM_ASGN,   // %=
    AND_ASGN,   // &=
    OR_ASGN,    // |=
    LAND_ASGN,  // &&=
    LOR_ASGN,   // ||=

    //
    // Keywords
    //

    FUNCTION,  // function
    WHILE,     // while
    FOR,       // for
    BREAK,     // break
    CONTINUE,  // continue
    IF,        // if
    ELSE,      // else
    SWITCH,    // switch
    CASE,      // case
    DEFAULT,   // default
    STRUCT,    // struct
    RETURN,    // return
    TRUE,      // true
    FALSE,     // false
};

////////////////////////////////////////////////////////////////

char const*
FormatTokenType(TokenType type);

////////////////////////////////////////////////////////////////

}  // namespace Lex
