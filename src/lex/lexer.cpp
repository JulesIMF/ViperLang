#include <lex/ident_table.hpp>
#include <lex/scanner.hpp>
#include <lex/token.hpp>
#include <lex/token_type.hpp>
#include <cctype>
#include <cstddef>
#include <cassert>
#include <cstdint>
#include <lex/lexer.hpp>
#include <optional>
#include <string>

namespace Lex
{

Lexer::Lexer(std::istream& source) :
    scanner_{source},
    identationLevel_({0})
{
}

Token
Lexer::GetNextToken()
{
    if (scanner_.Eof())
        return Token(TokenType::EOFILE, scanner_.GetLocation());

    // first we have to check if there is an identation
    SkipUseless();

    if (auto ident = MatchBeginEnd())
    {
        return *ident;
    }

    if (auto del = MatchDelimiters())
    {
        return *del;
    }

    if (auto op = MatchOperatorsAsgn())
    {
        return *op;
    }

    if (auto lit = MatchLiterals())
    {
        return *lit;
    }

    if (auto word = MatchWords())
    {
        return *word;
    }

    // FMT_ASSERT(false, "Could not match any token\n");
    return Token(TokenType::ERROR);  // calm analyzers
}

Token
Lexer::GetPreviousToken()
{
    return prev_;
}

void
Lexer::Advance()
{
    if (curr_.IsNone())
        return;

    prev_ = curr_;
    curr_ = GetNextToken();
}

bool
Lexer::Matches(Lex::TokenType type)
{
    if (Peek().type == type)
    {
        Advance();
        return true;
    }

    else
    {
        return false;
    }
}

Token
Lexer::Peek()
{
    if (curr_.IsNone())
        curr_ = GetNextToken();

    return curr_;
}

bool
Lexer::SkipWhiteSpace()
{
    return scanner_.SkipWhiteSpace();
}

bool
Lexer::SkipEmptyLines()
{
    bool skippedAny = false;

    // We assume that we start from '\n', then we skip
    // it and skip white spaces until we get another symbol.
    // If next symbol is unexistant or a new line,
    // than we actually had an empty line and need to advance

    while (scanner_.PeekMove() == '\n')
    {
        while (scanner_.Peek() == ' ' ||
               scanner_.Peek() == '\t')
        {
            scanner_.MovePtr();
        }

        if (scanner_.Eof() || scanner_.Peek() == '\n')
        {
            scanner_.AdvanceAll();
            skippedAny = true;
        }
    }

    scanner_.UngetAll();

    return skippedAny;
}

bool
Lexer::SkipToNewLine()
{
    return scanner_.SkipToNewLine();
}

bool
Lexer::SkipComments()
{
    bool skippedAny = false;

    while (table_.LookupWord(std::string() + scanner_.Peek()) ==
           TokenType::COMMENT)
    {
        skippedAny = true;
        scanner_.Get();  // skip comment symbol
        SkipToNewLine();
        
        // skipping possible empty lines with comments
        if (scanner_.Peek() == '\n')
        {
            scanner_.MovePtr();
            while (scanner_.Peek() == ' ' ||
               scanner_.Peek() == '\t')
            {
                scanner_.MovePtr();
            }

            if (table_.LookupWord(std::string() + scanner_.Peek()) ==
                TokenType::COMMENT)
            {
                scanner_.AdvanceAll();
            }

            else
                scanner_.UngetAll();
        }
    }

    return skippedAny;
}

bool
Lexer::SkipUseless()
{
    bool skippedAny = false;
    bool skippedThisIteration = false;

    do
    {
        skippedAny = skippedThisIteration;
        skippedThisIteration = false;

        skippedThisIteration |= SkipWhiteSpace();
        skippedThisIteration |= SkipComments();
        skippedThisIteration |= SkipEmptyLines();
    }
    while (skippedThisIteration);

    return skippedAny;
}

std::optional<Token>
Lexer::MatchIdentation()
{
    if (scanner_.Peek() != '\n')
        return std::nullopt;

    scanner_.Get();  // skipped new line
    auto location = scanner_.GetLocation();

    char symbol = '\0';
    unsigned int ident = 0;
    while ((symbol = scanner_.Peek()) == ' ' || symbol == '\t')
    {
        ident += (symbol == ' ') ? 1 : tabSize_;
        scanner_.MovePtr();
    }

    scanner_.AdvanceAll();

    Token token(TokenType::IDENT, location);
    token.attributes = IdentationAttributes{.ident = ident};

    return token;
}

std::optional<Token>
Lexer::MatchBeginEnd()
{
    // we need to keep it beacause in situations like
    // def fnc(n: int32):
    //   if n == 0:
    //      return 0
    // n = 1 <----
    // we need to give two END tokens, not one


    assert(!identationLevel_.empty());

    // if nothing left from previous, we have either begin or nothing
    if (identToken == std::nullopt)
    {
        identToken = MatchIdentation();
        if (identToken == std::nullopt)
            return std::nullopt;
    }

    auto ident =
        std::get<IdentationAttributes>(identToken->attributes).ident;

    if (ident == identationLevel_.top())
    {
        identToken = std::nullopt;
        return std::nullopt;
    }

    if (ident > identationLevel_.top())
    {
        identationLevel_.push(ident);
        identToken = std::nullopt;
        return Token(TokenType::BEGIN, identToken->location);
    }

    // ident keeps new identation size which is less than previous ones
    // so we will use it until we can

    assert(identationLevel_.size() >= 2);
    identationLevel_.pop();

    auto location = identToken->location;

    if (ident >= identationLevel_.top())
        identToken = std::nullopt;
    
    return Token(TokenType::END, location);
}

std::optional<Token>
Lexer::MatchDelimiters()
{
    auto location = scanner_.GetLocation();
    switch (scanner_.PeekMove())
    {
        case '(':
            scanner_.AdvanceAll();
            return Token(TokenType::LPAREN, location);

        case ')':
            scanner_.AdvanceAll();
            return Token(TokenType::RPAREN, location);

        case '[':
            scanner_.AdvanceAll();
            return Token(TokenType::LBRACK, location);

        case ']':
            scanner_.AdvanceAll();
            return Token(TokenType::RBRACK, location);

        case '{':
            scanner_.AdvanceAll();
            return Token(TokenType::LBRACE, location);

        case '}':
            scanner_.AdvanceAll();
            return Token(TokenType::RBRACE, location);

        case ',':
            scanner_.AdvanceAll();
            return Token(TokenType::COMMA, location);

        case '.':
            scanner_.AdvanceAll();
            return Token(TokenType::DOT, location);

        case ';':
            scanner_.AdvanceAll();
            return Token(TokenType::SEMICOLON, location);

        case ':':
            scanner_.AdvanceAll();
            return Token(TokenType::COLON, location);
        
        case '-':
            if (scanner_.PeekMove() == '>')
            {
                scanner_.AdvanceAll();
                return Token(TokenType::RARROW, location);
            }
            // fallthrough

        default:
            scanner_.UngetAll();
            return std::nullopt;
    }
}

std::optional<Token>
Lexer::MatchOperatorsAsgn()
{
    // If we haven`t returned after this switch,
    // then we have next symbol == '='

    auto location = scanner_.GetLocation();

#define ASGN_OPERS(c, type)                                          \
    case c:                                                          \
        if (scanner_.Peek() != '=')                                  \
        {                                                            \
            scanner_.AdvanceAll();                                   \
            return Token(TokenType::type, location);                 \
        }                                                            \
        scanner_.MovePtr();                                          \
        scanner_.AdvanceAll();                                       \
        return Token(TokenType::type##_ASGN, location);

    switch (scanner_.PeekMove())
    {
        ASGN_OPERS('+', ADD)
        ASGN_OPERS('-', SUB) 
        ASGN_OPERS('*', MUL)
        ASGN_OPERS('/', DIV)
        ASGN_OPERS('%', REM)

#undef ASGN_OPERS

        case '&':
            if (scanner_.Peek() == '=')
            {
                scanner_.MovePtr();
                scanner_.AdvanceAll();
                return Token(TokenType::AND_ASGN, location);
            }

            if (scanner_.Peek() != '&')
            {
                scanner_.AdvanceAll();
                return Token(TokenType::AND, location);
            }

            scanner_.MovePtr();

            if (scanner_.Peek() == '=')
            {
                scanner_.MovePtr();
                scanner_.AdvanceAll();
                return Token(TokenType::LAND_ASGN, location);
            }

            scanner_.AdvanceAll();
            return Token(TokenType::LAND, location);

        case '|':
            if (scanner_.Peek() == '=')
            {
                scanner_.MovePtr();
                scanner_.AdvanceAll();
                return Token(TokenType::OR_ASGN, location);
            }

            if (scanner_.Peek() != '|')
            {
                scanner_.AdvanceAll();
                return Token(TokenType::OR, location);
            }

            scanner_.MovePtr();

            if (scanner_.Peek() == '=')
            {
                scanner_.MovePtr();
                scanner_.AdvanceAll();
                return Token(TokenType::LOR_ASGN, location);
            }

            scanner_.AdvanceAll();
            return Token(TokenType::LOR, location);

#define REL(c, neq, eq)                                              \
    case c:                                                          \
        if (scanner_.Peek() != '=')                                  \
        {                                                            \
            scanner_.AdvanceAll();                                   \
            return Token(TokenType::neq, location);                  \
        }                                                            \
        scanner_.MovePtr();                                          \
        scanner_.AdvanceAll();                                       \
        return Token(TokenType::eq, location);

            REL('!', NOT, NEQ)
            REL('<', LSS, LEQ)
            REL('>', GTR, GEQ)
            REL('=', ASGN, EQL)
#undef REL

        default:
            scanner_.UngetAll();
            return std::nullopt;
    }
}

std::optional<Token>
Lexer::MatchLiterals()
{
    if (auto numLiteral = MatchNumericLiteral())
    {
        return numLiteral;
    }

    if (auto charLiteral = MatchCharLiteral())
    {
        return charLiteral;
    }

    if (auto stringLiteral = MatchStringLiteral())
    {
        return stringLiteral;
    }

    return std::nullopt;
}

static uint64_t
DigitToNumber(unsigned int base, char digit)
{
    if (base > 10 + 26)
        return base;  // fail

    if ('0' <= digit && digit <= '9')
    {
        uint64_t number = digit - '0';
        return number < base ? number : base;
    }

    if ('a' <= digit && digit <= 'z')
    {
        uint64_t number = 10 + (digit - 'a');
        return number < base ? number : base;
    }

    if ('A' <= digit && digit <= 'Z')
    {
        uint64_t number = 10 + (digit - 'A');
        return number < base ? number : base;
    }

    return base;
}

std::optional<Token>
Lexer::MatchNumericLiteral()
{
    enum Base
    {
        NON = 0,
        BIN = 2,
        DEC = 10,
        HEX = 16
    };

    Base base = Base::DEC;
    uint64_t value = 0;

    switch (scanner_.Peek())
    {
        case '0':
            scanner_.MovePtr();
            switch (scanner_.Peek())
            {
                case 'x':  // hex number, skipped 0, skip x
                case 'X':
                    base = Base::HEX;
                    scanner_.MovePtr();
                    break;

                case 'b':  // bin number, skipped 0, skip b
                case 'B':
                    base = Base::BIN;
                    scanner_.MovePtr();
                    break;

                case '0':  // just dec number, started with 0
                case '1':  // so we got number like 0... == ...
                case '2':
                case '3':
                case '4':
                case '5':
                case '6':
                case '7':
                case '8':
                case '9':
                    break;

                default:  // we can`t get more digits
                {
                    scanner_.AdvanceAll();
                    Token token(TokenType::INT,
                                scanner_.GetLocation());
                    token.attributes =
                        IntAttributes{.base = base, .value = value};

                    return token;
                }
            }
            break;

        case '1':
            value = 1ull;
            scanner_.MovePtr();
            break;

        case '2':
            value = 2ull;
            scanner_.MovePtr();
            break;

        case '3':
            value = 3ull;
            scanner_.MovePtr();
            break;

        case '4':
            value = 4ull;
            scanner_.MovePtr();
            break;

        case '5':
            value = 5ull;
            scanner_.MovePtr();
            break;

        case '6':
            value = 6ull;
            scanner_.MovePtr();
            break;

        case '7':
            value = 7ull;
            scanner_.MovePtr();
            break;

        case '8':
            value = 8ull;
            scanner_.MovePtr();
            break;

        case '9':
            value = 9ull;
            scanner_.MovePtr();
            break;

        default:
            return std::nullopt;
    }

    if (base != Base::DEC &&
        DigitToNumber(base, scanner_.Peek()) == base)
    {
        // we got situation like 0x???, but 0x is not a valid hex
        // number!
        scanner_.UngetAll();
        return std::nullopt;
    }

    while (true)
    {
        auto number = DigitToNumber(base, scanner_.Peek());
        if (number == base)
            break;

        value = value * uint64_t(base) + number;
        scanner_.MovePtr();
    }

    Token token(TokenType::INT, scanner_.GetLocation());
    scanner_.AdvanceAll();
    token.attributes = IntAttributes{.base = base, .value = value};

    return token;
}

char
CharFromEscaped(char value)
{
    switch (value)
    {
        case 'a':
            return '\a';
            break;

        case 'b':
            return '\b';
            break;

        case 'e':
            return '\x18';
            break;

        case 'f':
            return '\f';
            break;

        case 'n':
            return '\n';
            break;

        case 'r':
            return '\r';
            break;

        case 't':
            return '\t';
            break;

        case 'v':
            return '\v';
            break;

        default:
            return value;
            break;
    }
}

std::optional<Token>
Lexer::MatchStringLiteral()
{
    if (scanner_.Peek() != '"')
        return std::nullopt;

    auto location = scanner_.GetLocation();
    std::string literal;
    std::string value;
    bool scaning = false;

    // we want to glue several literals into one
    while (scanner_.Peek() == '"')
    {
        scaning = true;
        scanner_.MovePtr();  // skipped "
        while (!scanner_.Eof() && scaning)
        {
            switch (scanner_.Peek())
            {
                case '"':
                    // it is not an escaped symbol,
                    // so we finished single literal
                    scaning = false;
                    scanner_.MovePtr();
                    scanner_.AdvanceAll();
                    SkipUseless();
                    MatchIdentation();  // just skipped
                    value += literal;
                    break;

                case '\\':
                    // we have an escaped symbol
                    scanner_.PeekMove();
                    if (!scanner_.Eof())
                        literal +=
                            CharFromEscaped(scanner_.PeekMove());
                    break;

                default:
                    literal += scanner_.PeekMove();
            }
        }
    }

    if (scaning)
        scanner_.UngetAll();  // we encountered a problem while
                              // parsing last literal

    auto token = Token(TokenType::STRING, location);
    token.attributes = StringAttributes{literal};

    return token;
}

std::optional<Token>
Lexer::MatchCharLiteral()
{
    if (scanner_.Peek() != '\'')
        return std::nullopt;

    auto location = scanner_.GetLocation();
    scanner_.MovePtr();

    char value = '\0';

    switch (scanner_.Peek())
    {
        case '\'':
        {
            // empty literal is '\0'
            scanner_.MovePtr();
            scanner_.AdvanceAll();
            auto token = Token(TokenType::CHAR, location);
            token.attributes = CharAttributes{.empty = true};
            return token;
        }

        case '\\':
            // we have an escaped symbol
            scanner_.PeekMove();
            if (scanner_.Eof())
            {
                scanner_.UngetAll();
                return std::nullopt;
            }

            value = CharFromEscaped(scanner_.PeekMove());
            break;

        default:
            value = scanner_.PeekMove();
    }

    if (scanner_.PeekMove() != '\'')
    {
        scanner_.UngetAll();
        return std::nullopt;
    }

    auto token = Token(TokenType::CHAR, location);
    scanner_.AdvanceAll();
    token.attributes = CharAttributes{.value = value, .empty = false};
    return token;
}

std::optional<Token>
Lexer::MatchWords()
{
    auto location = scanner_.GetLocation();
    if (scanner_.Peek() != '_' && !isalpha(scanner_.Peek()))
        return std::nullopt;

    std::string id;
    id += scanner_.PeekMove();

    while (isalnum(scanner_.Peek()) || scanner_.Peek() == '_')
        id += scanner_.PeekMove();

    scanner_.AdvanceAll();
    auto type = table_.LookupWord(id);
    if (type == TokenType::NONE)
    {
        auto token = Token(TokenType::ID, location);
        token.attributes = IdAttributes{id};
        return token;
    }

    else
        return Token(type);
}

}  // namespace Lex
