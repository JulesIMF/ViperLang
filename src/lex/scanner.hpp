#pragma once

#include <lex/token_type.hpp>
#include <lex/location.hpp>

#include <istream>

namespace lex {

//////////////////////////////////////////////////////////////////////

class Scanner {
 public:
  Scanner(std::istream& source) : source_{source} {
    FetchNextSymbol();
  }

  void MoveRight() {
    switch (CurrentSymbol()) {
      case '\n':
        location_.columnno = 0;
        location_.lineno += 1;
        break;

      case EOF:
        break;

      default:
        location_.columnno += 1;
    }

    FetchNextSymbol();
  }

  void MoveNextLine() {
    while (CurrentSymbol() != '\n') {
      MoveRight();
    }

    // Finally, move to the next line
    MoveRight();
  }

  char CurrentSymbol() {
    return symbol_;
  }

  char PeekNextSymbol() {
    return source_.peek();
  }

  Location GetLocation() const {
    return location_;
  }

 private:
  void FetchNextSymbol() {
    symbol_ = source_.get();
  }

 private:
  // TODO: save the source in a buffer for error reporting

  std::istream& source_;

  Location location_;

  char symbol_;
};

//////////////////////////////////////////////////////////////////////

}  // namespace lex
