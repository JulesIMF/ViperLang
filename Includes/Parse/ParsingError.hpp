/*++

Copyright (c) 2023 JulesIMF, MIPT

Module Name:

    ParsingError.hpp

Abstract:



Author / Creation date:

    JulesIMF / 19.03.23

Revision History:

--*/

#pragma once

//
// Includes / usings
//

//
// Definitions
//

#include <Trees/Parse/Ast.hpp>

namespace Parse
{
class ParsingError
{
public:
    enum class Code
    {
        OK,
        MISSING_SEMICOLON,
        MISSING_COMMA,
    };

    Code code;
    AstNode* where;
};
}  // namespace Parse