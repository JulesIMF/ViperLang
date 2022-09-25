#include <lex/token_type.hpp>

#include <fmt/core.h>

namespace lex {

// https://journal.stuffwithstuff.com/2012/01/24/higher-order-macros-in-c/

////////////////////////////////////////////////////////////////

// clang-format off
#define AST_NODE_LIST(code) \
  code(NUMBER)              \
  code(STRING)              \
  code(IDENTIFIER)          \
  code(UNIT)                \
  code(TRUE)                \
  code(FALSE)               \
  code(PLUS)                \
  code(MINUS)               \
  code(ASSIGN)              \
  code(EQUALS)              \
  code(LT)                  \
  code(LEFT_BRACE)          \
  code(RIGHT_BRACE)         \
  code(LEFT_CBRACE)         \
  code(RIGHT_CBRACE)        \
  code(NOT)                 \
  code(ADDR)                \
  code(STAR)                \
  code(FUN)                 \
  code(DOT)                 \
  code(COMMA)               \
  code(VAR)                 \
  code(TYPE)                \
  code(STRUCT)              \
  code(TY_INT)              \
  code(TY_BOOL)             \
  code(TY_UNIT)             \
  code(TY_STRING)           \
  code(IF)                  \
  code(ELSE)                \
  code(FOR)                 \
  code(COLUMN)              \
  code(SEMICOLUMN)          \
  code(RETURN)              \
  code(YIELD)               \
  code(TOKEN_EOF)
// clang-format on

////////////////////////////////////////////////////////////////

#define DEFINE_TYPE_STRING(type) \
  case TokenType::type:          \
    return #type;

////////////////////////////////////////////////////////////////

const char* FormatTokenType(TokenType type) {
  switch (type) {
    AST_NODE_LIST(DEFINE_TYPE_STRING)
    default:
      break;
  }
  FMT_ASSERT(false, "Trying to print an unknown token type");
}

#undef DEFINE_TYPE_STRING

////////////////////////////////////////////////////////////////

}  // namespace lex
