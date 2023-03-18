/*++

Copyright (c) 2023 JulesIMF, MIPT

Module Name:

    Assert.cpp

Abstract:



Author / Creation date:

    JulesIMF / 19.03.23

Revision History:

--*/

//
// Includes / usings
//

#include <assert.h>
#include <cstdlib>
#include <fmt/color.h>
#include <string>

//
// Definitions
//

namespace Common::Internal
{
int
AssertMsgFailure(char const* file,
                 int         line,
                 char const* func,
                 std::string message)
{
    fmt::print(fg(fmt::color::red) | fmt::emphasis::bold,
               "Assertion failed:\n\n");
    
    fmt::print(fmt::emphasis::underline, "\t{}\n\n", message);
    
    if (file)
    {
        fmt::print(fmt::emphasis::bold, "File: ");
        fmt::print("{}\n", file);
    }

    fmt::print(fmt::emphasis::bold, "Line: ");
    fmt::print("{}\n", line);

    if (func)
    {
        fmt::print(fmt::emphasis::bold, "Func: ");
        fmt::print("{}\n", file);
    }

    fmt::print("\nAbort\n");
    std::abort();
}

int
UnreachableFailure(char const* file,
                   int         line,
                   char const* func,
                   std::string message)
{
    if (message != "")
    {
        fmt::print(fg(fmt::color::red) | fmt::emphasis::bold,
                   "Reached unreachable:\n\n");

        fmt::print(fmt::emphasis::underline, "\t{}\n\n", message);
    }

    else
        fmt::print(fg(fmt::color::red) | fmt::emphasis::bold,
                   "Reached unreachable!\n\n");

    if (file)
    {
        fmt::print(fmt::emphasis::bold, "File: ");
        fmt::print("{}\n", file);
    }

    fmt::print(fmt::emphasis::bold, "Line: ");
    fmt::print("{}\n", line);

    if (func)
    {
        fmt::print(fmt::emphasis::bold, "Func: ");
        fmt::print("{}\n", file);
    }

    fmt::print("\nAbort\n");
    std::abort();
}
}  // namespace Common::Internal