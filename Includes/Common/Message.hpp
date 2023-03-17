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

#pragma once

//
// Includes / usings
//

#include <string>

//
// Definitions
//

class Message
{
public:
    virtual std::string
    ToString() = 0;

    virtual std::string
    ToColoredString() = 0;
};

class Error : public Message
{
public:
    virtual std::string
    ToColoredString();
};

class Warning : public Message
{
public:
    virtual std::string
    ToColoredString();
};
