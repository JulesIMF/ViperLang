/*++

Copyright (c) 2023 JulesIMF, MIPT

Module Name:

    BasicTree.hpp

Abstract:



Author / Creation date:

    JulesIMF / 15.03.23

Revision History:

--*/

#pragma once

//
// Includes / usings
//

#include <vector>

//
// Definitions
//

class Visitor
{
public:
    template <typename T>
    T&
    As()
    {
        return *static_cast<T*>(this);
    }
};

class BasicTree
{
public:
    virtual void
    Accept(Visitor&) = 0;

    template <typename T>
    T*
    As()
    {
        return dynamic_cast<T*>(this);
    }
};