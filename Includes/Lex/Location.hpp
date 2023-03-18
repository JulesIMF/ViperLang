/*++

Copyright (c) 2023 JulesIMF, MIPT

Module Name:

    Location.hpp

Abstract:

    Location is structure that keeps where the token
    was obtained.

Author / Creation date:

    JulesIMF / 09.02.23

Revision History:

--*/

#pragma once

//
// Includes / usings
//

#include <fmt/core.h>

#include <cstddef>
#include <string>

//
// Definitions
//

namespace Lex
{

struct Location
{
    size_t ptr    = 0;
    size_t line   = 0;
    size_t column = 0;

    std::string
    Format() const
    {
        return fmt::format("line = {}, column = {}",  //
                           line + 1, column + 1);
    }

    std::string
    FormatShort() const
    {
        return fmt::format("{}:{}",  //
                           line + 1, column + 1);
    }
};

}  // namespace Lex
