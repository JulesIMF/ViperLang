/*++

Copyright (c) 2023 JulesIMF, MIPT

Module Name:

    Cases.cpp

Abstract:

    Tests cases for Assert module.

Author / Creation date:

    JulesIMF / 19.03.23

Revision History:

--*/

//
// Includes / usings
//

#include <Common/Assert.hpp>
#include <catch2/catch.hpp>

#include <iostream>

//
// Definitions
//

// TEST_CASE("Assert", "[Common/Assert]")
// {
//     Assert(false);
// }

// TEST_CASE("AssertMsg", "[Common/AssertMsg]")
// {
//     AssertMsg(false, "Custom message");
// }

// TEST_CASE("Unreachable", "[Common/Unreachable]")
// {
//     Unreachable();
// }

// TEST_CASE("UnreachableMsg", "[Common/UnreachableMsg]")
// {
//     UnreachableMsg("Custom message");
// }

TEST_CASE("Assert / Unreachable", "[Common/Assert]")
{
    if (true)
    {
        Assert(true);
    }

    else
    {
        Unreachable();
    }
}

TEST_CASE("Assert / Unreachable Msg", "[Common/Assert]")
{
    if (true)
    {
        AssertMsg(true, "assert msg");
    }

    else
    {
        UnreachableMsg("unreachable msg");
    }
}