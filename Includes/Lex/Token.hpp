/*++

Copyright (c) 2023 JulesIMF, MIPT

Module Name:

    Token.hpp

Abstract:

    Token is structure produced by the lexer.
    It is the terminal symbol used in the parser.

Author / Creation date:

    JulesIMF / 09.02.23

Revision History:

--*/

#pragma once

//
// Includes / usings
//

#include <Lex/Location.hpp>
#include <Lex/Scanner.hpp>
#include <Lex/TokenType.hpp>

#include <cstddef>
#include <variant>

namespace Lex
{

struct IntAttributes
{
    unsigned int base  = 0;
    uint64_t     value = 0;
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

struct IdentationAttributes
{
    uint64_t ident = 0;
};

struct Token
{
    using Attributes = std::variant<std::monostate,
                                    IntAttributes,
                                    IdAttributes,
                                    CharAttributes,
                                    StringAttributes,
                                    IdentationAttributes>;

    IntAttributes
    GetIntAttributes()
    {
        return std::get<IntAttributes>(attributes);
    }

    IdAttributes
    GetIdAttributes()
    {
        return std::get<IdAttributes>(attributes);
    }

    CharAttributes
    GetCharAttributes()
    {
        return std::get<CharAttributes>(attributes);
    }

    StringAttributes
    GetStringAttributes()
    {
        return std::get<StringAttributes>(attributes);
    }

    IdentationAttributes
    GetIdentationAttributes()
    {
        return std::get<IdentationAttributes>(attributes);
    }

    TokenType  type;
    Location   location;
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
