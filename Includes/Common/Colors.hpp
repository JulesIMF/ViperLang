/*++

Copyright (c) 2023 JulesIMF, MIPT

Module Name:

    Colors.hpp

Abstract:

    Terminal escape colors.

Author / Creation date:

    JulesIMF / 26.02.23

Revision History:

--*/

#pragma once

//
// Includes / usings
//

//
// Definitions
//

namespace TerminalColor
{
//
// Restoration escape seq
//
extern char const* Default;

//
// Regular text
//

extern char const* Black;
extern char const* Red;
extern char const* Green;
extern char const* Yellow;
extern char const* Blue;
extern char const* Purple;
extern char const* Cyan;
extern char const* White;

//
// Bold text
//

extern char const* BlackB;
extern char const* RedB;
extern char const* GreenB;
extern char const* YellowB;
extern char const* BlueB;
extern char const* PurpleB;
extern char const* CyanB;
extern char const* WhiteB;

//
// Underlined text
//

extern char const* BlackU;
extern char const* RedU;
extern char const* GreenU;
extern char const* YellowU;
extern char const* BlueU;
extern char const* PurpleU;
extern char const* CyanU;
extern char const* WhiteU;
}  // namespace TerminalColor