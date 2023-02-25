#pragma once

#include <algorithm>
#include <cctype>
#include <cstdio>
#include <functional>
#include <lex/location.hpp>
#include <lex/token_type.hpp>

#include <fmt/core.h>

#include <filesystem>
#include <iostream>
#include <istream>
#include <string>
#include <vector>

namespace Lex
{

class Scanner
{
public:
    using StreamType               = std::istream;
    using CharType                 = StreamType::char_type;
    static char constexpr EofConst = '\0';

    Scanner(StreamType& source) :
        source_(source)
    {
    }

    /*
        Проверяет, закончились ли символы в буфере и потоке
    */
    bool
    Eof()
    {
        TryEnsureBufferNotEmpty_();
        return int(buffer_.size()) <= buffer_ptr_;
    }

    /*
        Удаляет из буфера не более shift символов и забывает про них
    */
    void
    Advance(int shift)
    {
        shift = std::min(shift, int(buffer_.size() - advanced_ptr_));
        for (int i = 0; i != shift; i++)
            if (buffer_[i] == '\n')
            {
                line_++;
                column_ = 0;
            }

            else
            {
                column_++;
            }

        advanced_ptr_ += shift;
    }

    /*
        Удаляет из буфера все просмотренные символы
    */
    void
    AdvanceAll()
    {
        Advance(buffer_ptr_ - advanced_ptr_);
    }

    /*
        Подсматривает следующий символ
    */
    CharType
    Peek()
    {
        if (Eof())
            return EofConst;
        else
            return buffer_.at(buffer_ptr_);
    }

    /*
        Сдвигает указатель в буфере
    */
    void
    MovePtr()
    {
        buffer_ptr_++;
    }

    /*
        Подсматривает следующий символ и сдвигает указатель в буфере
    */
    CharType
    PeekMove()
    {
        auto value = Peek();
        MovePtr();
        return value;
    }

    CharType
    Get()
    {
        auto value = PeekMove();
        AdvanceAll();
        return value;
    }

    unsigned int
    SkipWhile(std::function<bool(CharType)> predicat)
    {
        unsigned int totalSkipped = 0;
        while (!Eof() && predicat(Peek()))
        {
            Get();
            totalSkipped++;
        }

        return totalSkipped;
    }

    unsigned int
    SkipToNewLine()
    {
        return SkipWhile([](CharType c) { return c != '\n'; });
    }

    unsigned int
    SkipWhiteSpace()
    {
        return SkipWhile([](CharType c)
                         { return !!isspace(c) && c != '\n'; });
    }

    void
    Unget(size_t n = 1)
    {
        buffer_ptr_ = std::min(buffer_ptr_, buffer_ptr_ - int(n));
    }

    void
    UngetAll()
    {
        buffer_ptr_ = advanced_ptr_;
    }

    Location
    GetLocation()
    {
        return Location{size_t(advanced_ptr_), line_, column_};
    }

protected:
    StreamType&           source_;
    std::vector<CharType> buffer_;
    int                   buffer_ptr_   = 0;
    int                   advanced_ptr_ = 0;

    size_t                line_         = 0;
    size_t                column_       = 0;

    void
    TryEnsureBufferNotEmpty_()
    {
        if (int(buffer_.size()) <= buffer_ptr_ && !source_.eof())
            buffer_.push_back(source_.get());
    }
};

}  // namespace Lex
