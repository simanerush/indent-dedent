#ifndef _FOO_HH
#define _FOO_HH

#include <iostream>
#include <vector>

#if !defined(yyFlexLexerOnce)
#include <FlexLexer.h>
#endif

namespace foo {
class Lexer : public yyFlexLexer {
public:
  Lexer(std::istream *in)
      : yyFlexLexer{in}, line{1}, column{1}, start_line{1},
        start_column{1}, indents{}, spaces{0}, at_sol(true) {}
  virtual ~Lexer() {}

  // get rid of override virtual function warning
  using FlexLexer::yylex;

  // Critical method for supporting Bison parsing.
  virtual int yylex(void);
  // YY_DECL defined in .ll
  // Method body created by flex in .cc

private:
  //
  // Token location information. Advanced by advance_location.
  // Used by do_foo.
  int line, column;
  int start_line, start_column;

  bool at_sol;

  int spaces;

  std::vector<int> indents;
  //
  // Bump the line/column
  void advance_location(std::string txt);
  //
  void do_foo(void);
  //
  void do_indent(void);
  //
  void do_dedent(void);
  //
  void do_eoln(void);

  int current_spaces();

  // if nonzero, return that
  void handle_indentation();
};

} // namespace foo

#endif
