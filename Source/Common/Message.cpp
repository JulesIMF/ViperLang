#include <Common/Colors.hpp>
#include <Common/Message.hpp>

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