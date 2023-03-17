#pragma once

#include <string>

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
