#pragma once

#include <fmt/core.h>

#include <cstddef>
#include <string>

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
};

}  // namespace Lex
