/* DO NOT EDIT THIS FILE - it is machine generated */
#pragma once
#include <Scanner.h>

#line 2 "C:\\mytools2015\\CheckMnemonics\\Resource.lex"
#pragma once

 /* This part goes to the ResourceLex.h file */

#include <LRParser.h>

class ResourceLex : public Scanner {
private:
  LRparser *m_parser; // if set, redirect errors to parsers verror-routine
public:
  ResourceLex(LexStream *inputStream = NULL) : Scanner(inputStream) {
    m_parser = NULL;
  }
  void setParser(LRparser *parser) {
    m_parser = parser;
  }
  int  getNextLexeme();
  void verror(const SourcePosition &pos, const TCHAR *format, va_list argptr);
  static void findBestHashMapSize();
};


#line 5 "C:\\mytools2015\\parsergen\\lib\\lexgencpp.par"

