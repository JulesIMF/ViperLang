#pragma once

#include "lex/location.hpp"
#include "lex/token_type.hpp"
#include <lex/scanner.hpp>

#include <cstddef>
#include <variant>

namespace Lex
{

struct IntAttributes
{
    unsigned int base = 0;
    uint64_t value = 0;
};

struct IdAttributes
{
    std::string value;
};

struct CharAttributes
{
    char value = '\0';
    bool empty = false;
};

struct StringAttributes
{
    std::string value;
};

struct Token
{
    using Attributes = std::variant<std::monostate,
                                    IntAttributes,
                                    IdAttributes,
                                    CharAttributes,
                                    StringAttributes>;

    TokenType type;
    Location location;
    Attributes attributes;

    Token(TokenType type, Location location = Location()) :
        type(type),
        location(location)
    {
        switch (type)
        {
            case TokenType::INT:
                attributes = IntAttributes();
                break;

            case TokenType::ID:
                attributes = IdAttributes();
                break;

            case TokenType::CHAR:
                attributes = CharAttributes();
                break;

            case TokenType::STRING:
                attributes = StringAttributes();
                break;

            default:
                break;
        }
    }

    Token() :
        Token(TokenType::NONE)
    {
    }

    static Token
    None()
    {
        return Token();
    }

    bool
    IsNone()
    {
        return type == TokenType::NONE;
    }
};

}  // namespace Lex
