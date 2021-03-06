/* DO NOT EDIT THIS FILE - it is machine generated */
#pragma once

#include <LRparser.h>

const extern ParserTables *CppTables;

#line 5 "C:\\mytools2015\\ParserGen\\cpp\\Cpp.y"
#include "ParserTree.h"
#include "CppSymbol.h"
#include "CppLex.h"

typedef SyntaxNode *stype;

class CppParser : public LRparser, public ParserTree {
public:
  CppParser(CppLex *lex = NULL) : LRparser(*CppTables,lex) {}
  SyntaxNode *newNode( int token, ... );
  void  appendError(const TCHAR *format, ...);
  void	verror(const SourcePosition &pos, const TCHAR *format, va_list argptr);
private:
  stype m_dollardollar,*m_stacktop,m_userstack[256];
  int	reduceAction(unsigned int prod);
//void	traceStack(unsigned int prod);
  stype getStackTop(int fromtop)          { return m_stacktop[-fromtop];	  }
  void	initUserStack()                   { m_stacktop = m_userstack;         }
  void	shiftSymbol(unsigned int symbol)  { m_stacktop++;				      } // push 1 element (garbage) on userstack
  void	popSymbols(unsigned int count)    { m_stacktop -= count;	          } // pop count symbols from userstack
  void	shiftDollarDollar()               { *(++m_stacktop) = m_dollardollar; } // push($$) on userstack
  void	defaultReduce(unsigned int prod)  { m_dollardollar  = *m_stacktop;    } // $$ = $1
};


#line 18 "C:\\mytools2015\\ParserGen\\lib\\parsergencpp.par"

