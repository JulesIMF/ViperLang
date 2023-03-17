/*++

Copyright (c) 2023 JulesIMF, MIPT

Module Name:

    Message.hpp

Abstract:

    Compilation message module.

Author / Creation date:

    JulesIMF / 26.02.23

Revision History:

--*/

//
// Includes / usings
//

#include <Common/Colors.hpp>
#include <Common/Message.hpp>

//
// Definitions
//

std::string
Warning::ToColoredString()
{
    return std::string(TerminalColor::YellowB) +
           "Warning: " + TerminalColor::Default + ToString();
}

std::string
Error::ToColoredString()
{
    return std::string(TerminalColor::RedB) +
           "Error: " + TerminalColor::Default + ToString();
}