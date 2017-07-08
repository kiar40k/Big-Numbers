/* DO NOT EDIT THIS FILE - it is machine generated */
#line 29 "C:\\mytools2015\\CheckMnemonics\\Resource.lex"
#include "stdafx.h"
#include <HashMap.h>
#include <TreeMap.h>
#include "ResourceSymbol.h"
#include "ResourceLex.h"

static ResourceInputSymbol nameOrKeyWord(const TCHAR *lexeme);
static ResourceInputSymbol preprocssessorDirective(const TCHAR *lexeme);


#line 8 "C:\\mytools2015\\parsergen\\lib\\lexgencpp.par"


// The lexCharMap[] and lexStateMap arrays are used as follows:
//
// nextState = lexNext[lexStateMap[currentState]][lexCharMap[inputChar]];
//
// Character positions in the lexCharMap Array are:
//
//  \x00 \x01 \x02 \x03 \x04 \x05 \x06 \x07 \b   \t   \n   \x0b \f   \r   \x0e \x0f
//  \x10 \x11 \x12 \x13 \x14 \x15 \x16 \x17 \x18 \x19 \x1a \x1b \x1c \x1d \x1e \x1f
//  \s   !    "    #    $    %    &    \'   (    )    *    +    ,    -    .    /
//  0    1    2    3    4    5    6    7    8    9    :    ;    <    =    >    ?
//  @    A    B    C    D    E    F    G    H    I    J    K    L    M    N    O
//  P    Q    R    S    T    U    V    W    X    Y    Z    [    \\   ]    ^    _
//  `    a    b    c    d    e    f    g    h    i    j    k    l    m    n    o
//  p    q    r    s    t    u    v    w    x    y    z    {    |    }    ~    \x7f
//  \x80 \x81 \x82 \x83 \x84 \x85 \x86 \x87 \x88 \x89 \x8a \x8b \x8c \x8d \x8e \x8f
//  \x90 \x91 \x92 \x93 \x94 \x95 \x96 \x97 \x98 \x99 \x9a \x9b \x9c \x9d \x9e \x9f
//  \xa0 \xa1 \xa2 \xa3 \xa4 \xa5 \xa6 \xa7 \xa8 \xa9 \xaa \xab \xac \xad \xae \xaf
//  \xb0 \xb1 \xb2 \xb3 \xb4 \xb5 \xb6 \xb7 \xb8 \xb9 \xba \xbb \xbc \xbd \xbe \xbf
//  \xc0 \xc1 \xc2 \xc3 \xc4 \xc5 \xc6 \xc7 \xc8 \xc9 \xca \xcb \xcc \xcd \xce \xcf
//  \xd0 \xd1 \xd2 \xd3 \xd4 \xd5 \xd6 \xd7 \xd8 \xd9 \xda \xdb \xdc \xdd \xde \xdf
//  \xe0 \xe1 \xe2 \xe3 \xe4 \xe5 \xe6 \xe7 \xe8 \xe9 \xea \xeb \xec \xed \xee \xef
//  \xf0 \xf1 \xf2 \xf3 \xf4 \xf5 \xf6 \xf7 \xf8 \xf9 \xfa \xfb \xfc \xfd \xfe \xff

static unsigned char lexCharMap[256] = {
       0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   1,   0,   2,   3,   2,   2,
       2,   2,   2,   2,   2,   2,   2,   2,   2,   2,   2,   2,   2,   2,   2,   2,
       0,   2,   4,   5,   2,   2,   2,   2,   6,   7,   8,   2,   9,   2,  10,  11,
      12,  13,  13,  13,  13,  13,  13,  13,  13,  13,   2,   2,   2,   2,   2,   2,
       2,  14,  14,  14,  14,  14,  14,  15,  15,  15,  15,  15,  16,  15,  15,  15,
      15,  15,  15,  15,  15,  15,  15,  15,  17,  15,  15,   2,  18,   2,   2,  15,
       2,  19,  19,  19,  19,  19,  19,  20,  20,  20,  20,  20,  21,  20,  20,  20,
      20,  20,  20,  20,  20,  20,  20,  20,  22,  20,  20,   2,  23,   2,   2,   2,
       2,   2,   2,   2,   2,   2,   2,   2,   2,   2,   2,   2,   2,   2,   2,   2,
       2,   2,   2,   2,   2,   2,   2,   2,   2,   2,   2,   2,   2,   2,   2,   2,
       2,   2,   2,   2,   2,   2,   2,   2,   2,   2,   2,   2,   2,   2,   2,   2,
       2,   2,   2,   2,   2,   2,   2,   2,   2,   2,   2,   2,   2,   2,   2,   2,
       2,   2,   2,   2,   2,   2,   2,   2,   2,   2,   2,   2,   2,   2,   2,   2,
       2,   2,   2,   2,   2,   2,   2,   2,   2,   2,   2,   2,   2,   2,   2,   2,
       2,   2,   2,   2,   2,   2,   2,   2,   2,   2,   2,   2,   2,   2,   2,   2,
       2,   2,   2,   2,   2,   2,   2,   2,   2,   2,   2,   2,   2,   2,   2,   2
};

static const unsigned char lexStateMap[23] = {
    /*   0 */   0,   1,   2,   3,   4,   4,   4,   4,   5,   6,
    /*  10 */   4,   7,   8,   4,   4,   9,  10,  11,  12,  13,
    /*  20 */   4,  14,  15
};

static const char lexNext[16][24] = {
    /*   0 */ { 1, 2,-1, 3,15,17, 4, 5,-1, 6, 7,19, 8,16, 9, 9, 9, 9,-1, 9, 9, 9, 9,10},
    /*   1 */ { 1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
    /*   2 */ {-1, 2,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
    /*   3 */ {-1,-1,-1, 3,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
    /*   4 */ {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
    /*   5 */ {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,16,16,-1,-1,-1,22,-1,-1,-1,-1,22,-1},
    /*   6 */ {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1, 9, 9, 9, 9, 9, 9,-1, 9, 9, 9, 9,-1},
    /*   7 */ {-1,-1,-1,-1,15,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
    /*   8 */ {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,12,12,12,12,-1},
    /*   9 */ {15,-1,15,-1,11,15,15,15,15,15,15,15,15,15,15,15,15,15,21,15,15,15,15,15},
    /*  10 */ {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,16,16,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
    /*  11 */ {17,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,12,12,12,12,-1},
    /*  12 */ {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,18,18,18,-1,20,-1,-1,18,-1,20,-1,-1},
    /*  13 */ {-1,-1,-1,-1,-1,-1,-1,-1,13,-1,-1,14,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
    /*  14 */ {15,-1,15,-1,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15},
    /*  15 */ {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,18,18,18,-1,-1,-1,-1,18,-1,-1,-1,-1}
};

static const char lexAccept[] = {
    /*   0 */  0,  4,  4,  4,  4,  4,  4,  4,  4,  4,
    /*  10 */  4,  4,  4,  4,  4,  0,  4,  0,  4,  0,
    /*  20 */  4,  0,  0
};

#line 11 "C:\\mytools2015\\parsergen\\lib\\lexgencpp.par"

// nextState(state,c) is given the current state number and input
// character and evaluates to the next state.
#define nextState(state,c) (lexNext[lexStateMap[state]][lexCharMap[c]])

int ResourceLex::getNextLexeme() {
  int  state           = 0;     // Current state
  int  lastAcceptState = 0;     // Most recently seen accept state
  int  prevState;               // State before lastAcceptState
  int  nextState;               // Next state
  unsigned int  lookahead;      // Lookahead character
  int  anchor;                  // Anchor mode for most recently seen accepting state

  unTerminateLexeme();
  initMore();
  markStart();

  for(;;) {
    // Check end of file. If there's an unprocessed accepting state,
    // lastAcceptState will be nonzero. In this case, ignore EOF for now so
    // that you can do the accepting action; otherwise, try to open another
    // file and return if you can't.

    for(;;) {
      if(((int)(lookahead = look(1))) != EOF) {
        assert(lookahead < 256);
        nextState = nextState(state, lookahead);
        break;
      } else if(lastAcceptState != 0) {   // still something to do
        nextState = -1;
        break;
      } else if(isWrap()) {               // another file?
        terminateLexeme();
        return 0;                         // EOI
      }
    }
    if(m_debug) {
      debugState(_T("--------"), state, lookahead);
    }

    if(nextState != -1) {
      if(advance() < 0) {                 // Buffer full
        const TCHAR *tooLongMessage = _T("Lexeme too long. Discarding extra characters.");
        error(getPos(), tooLongMessage);

        flush(true);

        if(m_debug) {
          debug(tooLongMessage);
          debugState(_T("--------"), state, look(1));
        }
      }

      if(anchor = lexAccept[nextState]) { // Is this an accept state
        prevState       = state;
        lastAcceptState = nextState;
        markEnd();                        // Mark input at current character
      }                                   // A subsequent gotoMark() returns us to this position.
      state = nextState;
    } else if(lastAcceptState == 0) {     // illegal input
      error(getPos(), _istprint(lookahead)?_T("Ignore bad input:'%c'"):_T("Ignore bad input:%#x"),lookahead);

      if(m_debug) {
        debug(_T("Ignore bad input:'%c'"), lookahead);
      }

      advance();
    } else {
      if(m_debug) {
        debugState(_T("accept--"), lastAcceptState, lookahead);
      }

      gotoMark();                         // Back up to previous accept state
      if(anchor & ANCHOR_END) {           // If end anchor is active
        pushback(1);                      // Push back the CR or LF
      }
      if(anchor & ANCHOR_START) {         // If start anchor is active
        moveStart();                      // Skip the leading newline
      }
      terminateLexeme();                  // Null-terminate the string

      switch(lastAcceptState) {
      case 1:
#line 102 "C:\\mytools2015\\CheckMnemonics\\Resource.lex"
        ;

#line 93 "C:\\mytools2015\\parsergen\\lib\\lexgencpp.par"
        break;
      case 2:
#line 103 "C:\\mytools2015\\CheckMnemonics\\Resource.lex"
        ;

#line 93 "C:\\mytools2015\\parsergen\\lib\\lexgencpp.par"
        break;
      case 3:
#line 104 "C:\\mytools2015\\CheckMnemonics\\Resource.lex"
        ;

#line 93 "C:\\mytools2015\\parsergen\\lib\\lexgencpp.par"
        break;
      case 4:
#line 54 "C:\\mytools2015\\CheckMnemonics\\Resource.lex"
        return LPAR;

#line 93 "C:\\mytools2015\\parsergen\\lib\\lexgencpp.par"
        break;
      case 5:
#line 55 "C:\\mytools2015\\CheckMnemonics\\Resource.lex"
        return RPAR;

#line 93 "C:\\mytools2015\\parsergen\\lib\\lexgencpp.par"
        break;
      case 6:
#line 58 "C:\\mytools2015\\CheckMnemonics\\Resource.lex"
        return COMMA;

#line 93 "C:\\mytools2015\\parsergen\\lib\\lexgencpp.par"
        break;
      case 7:
#line 59 "C:\\mytools2015\\CheckMnemonics\\Resource.lex"
        return DOT;

#line 93 "C:\\mytools2015\\parsergen\\lib\\lexgencpp.par"
        break;
      case 8:
      case 16:
      case 18:
      case 20:
#line 50 "C:\\mytools2015\\CheckMnemonics\\Resource.lex"
        return NUMBER;

#line 93 "C:\\mytools2015\\parsergen\\lib\\lexgencpp.par"
        break;
      case 9:
#line 101 "C:\\mytools2015\\CheckMnemonics\\Resource.lex"
        return nameOrKeyWord(getText());

#line 93 "C:\\mytools2015\\parsergen\\lib\\lexgencpp.par"
        break;
      case 10:
#line 56 "C:\\mytools2015\\CheckMnemonics\\Resource.lex"
        return OR;

#line 93 "C:\\mytools2015\\parsergen\\lib\\lexgencpp.par"
        break;
      case 11:
#line 52 "C:\\mytools2015\\CheckMnemonics\\Resource.lex"
        return STRING;

#line 93 "C:\\mytools2015\\parsergen\\lib\\lexgencpp.par"
        break;
      case 12:
#line 86 "C:\\mytools2015\\CheckMnemonics\\Resource.lex"
        { int i;
                                  while(i = input()) { // skip until end of line ie handle as a comment
                                    if(i < 0) {
                                      flushBuf();  /* Discard lexeme. */
                                    } else if(i == '\\' && (look(1) == '\n' || look(1) == '\r')) {
                                      flushBuf();
                                      if(input() == '\r') { // eat '\r' and '\n' and skip next line too
                                        input();
                                      }
                                    } else if(i == '\n') {
                                      break;
                                    }
                                  }
                                }

#line 93 "C:\\mytools2015\\parsergen\\lib\\lexgencpp.par"
        break;
      case 13:
#line 71 "C:\\mytools2015\\CheckMnemonics\\Resource.lex"
        { int i;
                                  SourcePosition startpos = getPos();
                                  while(i = input()) {
                                    if(i < 0) {
                                      flushBuf();  /* Discard lexeme. */
                                    } else if(i == '*' && look(1) == '/') {
                                      input();
                                      break;       /* Recognized comment.*/
                                    }
                                  }
                                  if(i == 0) {
                                    error( startpos,_T("End of file in comment\n") );
                                  }
                                }

#line 93 "C:\\mytools2015\\parsergen\\lib\\lexgencpp.par"
        break;
      case 14:
#line 61 "C:\\mytools2015\\CheckMnemonics\\Resource.lex"
        { int i;
                                  while(i = input()) {
                                    if(i < 0) {
                                      flushBuf();  /* Discard lexeme. */
                                    } else if(i == '\n') {
                                      break;
                                    }
                                  }
                                }

#line 93 "C:\\mytools2015\\parsergen\\lib\\lexgencpp.par"
        break;

      default:
        throwException(_T("%s:Unknown accept state:%d, text=<%s>"), __TFUNCTION__, lastAcceptState,getText());
        break;
      }

      unTerminateLexeme();
      lastAcceptState = 0;

      if(isMore()) {
        state = prevState;                // Back up
        initMore();
      } else {
        state = 0;
        markStart();
      }
    }
  }
}

#line 107 "C:\\mytools2015\\CheckMnemonics\\Resource.lex"

  /* This part goes to the last part of ResourceLex.cpp */

typedef struct {
  TCHAR              *m_name;
  ResourceInputSymbol m_token;
} KeyWord;

#define KW(w)  _T(#w), w
#define UKW(w) _T(#w), _##w

static const KeyWord keywordTable[] = {
  KW(DIALOG)
 ,KW(DIALOGEX)
 ,UKW(BITMAP)
 ,KW(STRINGTABLE)
 ,KW(GUIDELINES)
 ,KW(DESIGNINFO)
 ,KW(LEFTMARGIN)
 ,KW(RIGHTMARGIN)
 ,KW(TOPMARGIN)
 ,KW(BOTTOMMARGIN)
 ,KW(HORZGUIDE)
 ,KW(VERTGUIDE)
 ,KW(TOOLBAR)
 ,KW(BUTTON)
 ,KW(ACCELERATORS)
 ,KW(VIRTKEY)
 ,KW(ALT)
 ,KW(SHIFT)
 ,KW(NOINVERT)
 ,KW(ASCII)
 ,KW(RCDATA)
 ,KW(DLGINIT)
 ,UKW(MENU)
 ,KW(MENUEX)
 ,KW(POPUP)
 ,UKW(MENUITEM)
 ,KW(GRAYED)
 ,KW(CHECKED)
 ,KW(INACTIVE)
 ,KW(SEPARATOR)
 ,KW(TEXTINCLUDE)
 ,KW(LANGUAGE)
 ,KW(VERSIONINFO)
 ,KW(FILEVERSION)
 ,KW(PRODUCTVERSION)
 ,KW(FILEFLAGSMASK)
 ,KW(FILEFLAGS)
 ,KW(FILEOS)
 ,KW(FILETYPE)
 ,KW(FILESUBTYPE)
 ,KW(BLOCK)
 ,KW(VALUE)
 ,KW(TYPELIB)
 ,KW(PUSHBUTTON)
 ,KW(DEFPUSHBUTTON)
 ,KW(EDITTEXT)
 ,KW(SCROLLBAR)
 ,KW(COMBOBOX)
 ,KW(LISTBOX)
 ,KW(GROUPBOX)
 ,UKW(ICON)
 ,KW(LTEXT)
 ,KW(RTEXT)
 ,KW(CTEXT)
 ,KW(CONTROL)
 ,UKW(FONT)
 ,KW(STYLE)
 ,KW(EXSTYLE)
 ,KW(CAPTION)
 ,KW(DISCARDABLE)
 ,KW(MOVEABLE)
 ,KW(PURE)
 ,KW(IMPURE)
 ,KW(PRELOAD)
 ,KW(LOADONCALL)
 ,KW(AFX_DIALOG_LAYOUT)
 ,UKW(WS_OVERLAPPED)
 ,UKW(WS_POPUP)
 ,UKW(WS_CHILD)
 ,UKW(WS_MINIMIZE)
 ,UKW(WS_VISIBLE)
 ,UKW(WS_DISABLED)
 ,UKW(WS_CLIPSIBLINGS)
 ,UKW(WS_CLIPCHILDREN)
 ,UKW(WS_MAXIMIZE)
 ,UKW(WS_CAPTION)
 ,UKW(WS_BORDER)
 ,UKW(WS_DLGFRAME)
 ,UKW(WS_VSCROLL)
 ,UKW(WS_HSCROLL)
 ,UKW(WS_SYSMENU)
 ,UKW(WS_THICKFRAME)
 ,UKW(WS_GROUP)
 ,UKW(WS_TABSTOP)
 ,UKW(WS_MINIMIZEBOX)
 ,UKW(WS_MAXIMIZEBOX)
 ,UKW(WS_EX_DLGMODALFRAME)
 ,UKW(WS_EX_NOPARENTNOTIFY)
 ,UKW(WS_EX_TOPMOST)
 ,UKW(WS_EX_ACCEPTFILES)
 ,UKW(WS_EX_TRANSPARENT)
 ,UKW(WS_EX_MDICHILD)
 ,UKW(WS_EX_TOOLWINDOW)
 ,UKW(WS_EX_WINDOWEDGE)
 ,UKW(WS_EX_CLIENTEDGE)
 ,UKW(WS_EX_CONTEXTHELP)
 ,UKW(WS_EX_RIGHT)
 ,UKW(WS_EX_LEFT)
 ,UKW(WS_EX_RTLREADING)
 ,UKW(WS_EX_LTRREADING)
 ,UKW(WS_EX_LEFTSCROLLBAR)
 ,UKW(WS_EX_RIGHTSCROLLBAR)
 ,UKW(WS_EX_CONTROLPARENT)
 ,UKW(WS_EX_STATICEDGE)
 ,UKW(WS_EX_APPWINDOW)
 ,UKW(SS_LEFT)
 ,UKW(SS_CENTER)
 ,UKW(SS_RIGHT)
 ,UKW(SS_ICON)
 ,UKW(SS_BLACKRECT)
 ,UKW(SS_GRAYRECT)
 ,UKW(SS_WHITERECT)
 ,UKW(SS_BLACKFRAME)
 ,UKW(SS_GRAYFRAME)
 ,UKW(SS_WHITEFRAME)
 ,UKW(SS_USERITEM)
 ,UKW(SS_SIMPLE)
 ,UKW(SS_LEFTNOWORDWRAP)
 ,UKW(SS_OWNERDRAW)
 ,UKW(SS_BITMAP)
 ,UKW(SS_ENHMETAFILE)
 ,UKW(SS_ETCHEDHORZ)
 ,UKW(SS_ETCHEDVERT)
 ,UKW(SS_ETCHEDFRAME)
 ,UKW(SS_TYPEMASK)
 ,UKW(SS_NOPREFIX)
 ,UKW(SS_NOTIFY)
 ,UKW(SS_CENTERIMAGE)
 ,UKW(SS_RIGHTJUST)
 ,UKW(SS_REALSIZEIMAGE)
 ,UKW(SS_SUNKEN)
 ,UKW(SS_ENDELLIPSIS)
 ,UKW(SS_PATHELLIPSIS)
 ,UKW(SS_WORDELLIPSIS)
 ,UKW(SS_ELLIPSISMASK)
 ,UKW(ES_LEFT)
 ,UKW(ES_CENTER)
 ,UKW(ES_RIGHT)
 ,UKW(ES_MULTILINE)
 ,UKW(ES_UPPERCASE)
 ,UKW(ES_LOWERCASE)
 ,UKW(ES_PASSWORD)
 ,UKW(ES_AUTOVSCROLL)
 ,UKW(ES_AUTOHSCROLL)
 ,UKW(ES_NOHIDESEL)
 ,UKW(ES_OEMCONVERT)
 ,UKW(ES_READONLY)
 ,UKW(ES_WANTRETURN)
 ,UKW(ES_NUMBER)
 ,UKW(BS_PUSHBUTTON)
 ,UKW(BS_DEFPUSHBUTTON)
 ,UKW(BS_CHECKBOX)
 ,UKW(BS_AUTOCHECKBOX)
 ,UKW(BS_RADIOBUTTON)
 ,UKW(BS_3STATE)
 ,UKW(BS_AUTO3STATE)
 ,UKW(BS_GROUPBOX)
 ,UKW(BS_USERBUTTON)
 ,UKW(BS_AUTORADIOBUTTON)
 ,UKW(BS_OWNERDRAW)
 ,UKW(BS_LEFTTEXT)
 ,UKW(BS_TEXT)
 ,UKW(BS_ICON)
 ,UKW(BS_BITMAP)
 ,UKW(BS_LEFT)
 ,UKW(BS_RIGHT)
 ,UKW(BS_CENTER)
 ,UKW(BS_TOP)
 ,UKW(BS_BOTTOM)
 ,UKW(BS_VCENTER)
 ,UKW(BS_PUSHLIKE)
 ,UKW(BS_MULTILINE)
 ,UKW(BS_NOTIFY)
 ,UKW(BS_FLAT)
 ,UKW(BS_RIGHTBUTTON)
 ,UKW(SBS_HORZ)
 ,UKW(SBS_VERT)
 ,UKW(SBS_TOPALIGN)
 ,UKW(SBS_LEFTALIGN)
 ,UKW(SBS_BOTTOMALIGN)
 ,UKW(SBS_RIGHTALIGN)
 ,UKW(SBS_SIZEBOXTOPLEFTALIGN)
 ,UKW(SBS_SIZEBOXBOTTOMRIGHTALIGN)
 ,UKW(SBS_SIZEBOX)
 ,UKW(SBS_SIZEGRIP)
 ,UKW(CBS_SIMPLE)
 ,UKW(CBS_DROPDOWN)
 ,UKW(CBS_DROPDOWNLIST)
 ,UKW(CBS_OWNERDRAWFIXED)
 ,UKW(CBS_OWNERDRAWVARIABLE)
 ,UKW(CBS_AUTOHSCROLL)
 ,UKW(CBS_OEMCONVERT)
 ,UKW(CBS_SORT)
 ,UKW(CBS_HASSTRINGS)
 ,UKW(CBS_NOINTEGRALHEIGHT)
 ,UKW(CBS_DISABLENOSCROLL)
 ,UKW(CBS_UPPERCASE)
 ,UKW(CBS_LOWERCASE)
 ,UKW(LBS_NOTIFY)
 ,UKW(LBS_SORT)
 ,UKW(LBS_NOREDRAW)
 ,UKW(LBS_MULTIPLESEL)
 ,UKW(LBS_OWNERDRAWFIXED)
 ,UKW(LBS_OWNERDRAWVARIABLE)
 ,UKW(LBS_HASSTRINGS)
 ,UKW(LBS_USETABSTOPS)
 ,UKW(LBS_NOINTEGRALHEIGHT)
 ,UKW(LBS_MULTICOLUMN)
 ,UKW(LBS_WANTKEYBOARDINPUT)
 ,UKW(LBS_EXTENDEDSEL)
 ,UKW(LBS_DISABLENOSCROLL)
 ,UKW(LBS_NODATA)
 ,UKW(LBS_NOSEL)
 ,UKW(TBS_AUTOTICKS)
 ,UKW(TBS_VERT)
 ,UKW(TBS_HORZ)
 ,UKW(TBS_TOP)
 ,UKW(TBS_BOTTOM)
 ,UKW(TBS_LEFT)
 ,UKW(TBS_RIGHT)
 ,UKW(TBS_BOTH)
 ,UKW(TBS_NOTICKS)
 ,UKW(TBS_ENABLESELRANGE)
 ,UKW(TBS_FIXEDLENGTH)
 ,UKW(TBS_NOTHUMB)
 ,UKW(TBS_TOOLTIPS)
 ,UKW(TVS_HASBUTTONS)
 ,UKW(TVS_HASLINES)
 ,UKW(TVS_LINESATROOT)
 ,UKW(TVS_EDITLABELS)
 ,UKW(TVS_DISABLEDRAGDROP)
 ,UKW(TVS_SHOWSELALWAYS)
 ,UKW(TVS_RTLREADING)
 ,UKW(TVS_NOTOOLTIPS)
 ,UKW(TVS_CHECKBOXES)
 ,UKW(TVS_TRACKSELECT)
 ,UKW(TVS_SINGLEEXPAND)
 ,UKW(TVS_INFOTIP)
 ,UKW(TVS_FULLROWSELECT)
 ,UKW(TVS_NOSCROLL)
 ,UKW(TVS_NONEVENHEIGHT)
 ,UKW(LVS_ICON)
 ,UKW(LVS_REPORT)
 ,UKW(LVS_SMALLICON)
 ,UKW(LVS_LIST)
 ,UKW(LVS_TYPEMASK)
 ,UKW(LVS_SINGLESEL)
 ,UKW(LVS_SHOWSELALWAYS)
 ,UKW(LVS_SORTASCENDING)
 ,UKW(LVS_SORTDESCENDING)
 ,UKW(LVS_SHAREIMAGELISTS)
 ,UKW(LVS_NOLABELWRAP)
 ,UKW(LVS_AUTOARRANGE)
 ,UKW(LVS_EDITLABELS)
 ,UKW(LVS_OWNERDATA)
 ,UKW(LVS_NOSCROLL)
 ,UKW(LVS_TYPESTYLEMASK)
 ,UKW(LVS_ALIGNTOP)
 ,UKW(LVS_ALIGNLEFT)
 ,UKW(LVS_ALIGNMASK)
 ,UKW(LVS_OWNERDRAWFIXED)
 ,UKW(LVS_NOCOLUMNHEADER)
 ,UKW(LVS_NOSORTHEADER)
 ,UKW(UDS_WRAP)
 ,UKW(UDS_SETBUDDYINT)
 ,UKW(UDS_ALIGNRIGHT)
 ,UKW(UDS_ALIGNLEFT)
 ,UKW(UDS_AUTOBUDDY)
 ,UKW(UDS_ARROWKEYS)
 ,UKW(UDS_HORZ)
 ,UKW(UDS_NOTHOUSANDS)
 ,UKW(UDS_HOTTRACK)
 ,UKW(PBS_SMOOTH)
 ,UKW(PBS_VERTICAL)
 ,UKW(MCS_DAYSTATE)
 ,UKW(MCS_MULTISELECT)
 ,UKW(MCS_WEEKNUMBERS)
 ,UKW(MCS_NOTODAYCIRCLE)
 ,UKW(MCS_NOTODAY)
 ,UKW(DS_ABSALIGN)
 ,UKW(DS_SYSMODAL)
 ,UKW(DS_LOCALEDIT)
 ,UKW(DS_SETFONT)
 ,UKW(DS_MODALFRAME)
 ,UKW(DS_NOIDLEMSG)
 ,UKW(DS_SETFOREGROUND)
 ,UKW(DS_3DLOOK)
 ,UKW(DS_FIXEDSYS)
 ,UKW(DS_NOFAILCREATE)
 ,UKW(DS_CONTROL)
 ,UKW(DS_CENTER)
 ,UKW(DS_CENTERMOUSE)
 ,UKW(DS_CONTEXTHELP)
 ,UKW(MFT_STRING)
 ,UKW(MFT_BITMAP)
 ,UKW(MFT_MENUBARBREAK)
 ,UKW(MFT_MENUBREAK)
 ,UKW(MFT_OWNERDRAW)
 ,UKW(MFT_RADIOCHECK)
 ,UKW(MFT_SEPARATOR)
 ,UKW(MFT_RIGHTORDER)
 ,UKW(MFT_RIGHTJUSTIFY)
 ,UKW(MFS_GRAYED)
 ,UKW(MFS_DISABLED)
 ,UKW(MFS_CHECKED)
 ,UKW(MFS_HILITE)
 ,UKW(MFS_ENABLED)
 ,UKW(MFS_UNCHECKED)
 ,UKW(MFS_UNHILITE)
 ,UKW(MFS_DEFAULT)
 ,UKW(MFS_MASK)
 ,UKW(MFS_HOTTRACKDRAWN)
 ,UKW(MFS_CACHEDBMP)
 ,UKW(MFS_BOTTOMGAPDROP)
 ,UKW(MFS_TOPGAPDROP)
 ,UKW(MFS_GAPDROP)
 ,KW(BEGIN)
 ,KW(END)
 ,KW(OR)
 ,KW(NOT)
};

typedef StrHashMap<ResourceInputSymbol> HashMapType;

class MapInfo {
public:
  int             m_capacity;
  int             m_size;
  int             m_maxChainLength;
  CompactIntArray m_chainCount;

  MapInfo(size_t capacity, size_t size, size_t maxChainLength, const CompactIntArray &chainCount)
  : m_capacity((int)capacity)
  , m_size((int)size)
  , m_maxChainLength((int)maxChainLength)
  , m_chainCount(chainCount) {
  }
  String toString() const;
};

String MapInfo::toString() const {
  String result = format(_T("Capacity:%4d, Size:%4d, MaxChainLength:%2d, chaincount:"), m_capacity, m_size, m_maxChainLength);
  for(size_t i = 0; i < m_chainCount.size(); i++) {
    result += format(_T(" (%d,%3d)"), i, m_chainCount[i]);
  }
  return result;
}

class ResourceKeyWordMap : public HashMapType {
public:
  ResourceKeyWordMap(size_t capacity, const KeyWord *initTable, size_t size) : HashMapType(capacity) {
    for(size_t i = 0; i < size; i++) {
      put(initTable[i].m_name, initTable[i].m_token);
    }
  }
  MapInfo getMapInfo() const {
    return MapInfo(getCapacity(), size(), getMaxChainLength(), getLength());
  }

};

#define DEFINE_KEYWORDTABLE(name, capacity, initTable) \
  static ResourceKeyWordMap name(capacity, initTable, ARRAYSIZE(initTable));

DEFINE_KEYWORDTABLE(keywords    , 2156, keywordTable    )

static ResourceInputSymbol nameOrKeyWord(const TCHAR *lexeme) {
  ResourceInputSymbol *p = keywords.get(lexeme);
  return p ? *p : IDENTIFIER;
}

void ResourceLex::findBestHashMapSize() {
  IntTreeMap<MapInfo> cl;
  int bestCapacity;
  int currentMax = -1;
  for(int capacity = 500; capacity < 3000; capacity++) {
    ResourceKeyWordMap ht(capacity, keywordTable, ARRAYSIZE(keywordTable));
    MapInfo v = ht.getMapInfo();
    cl.put((int)ht.getCapacity(), v);
    if((currentMax < 0) || v.m_maxChainLength < currentMax) {
      bestCapacity = capacity;
      currentMax = v.m_maxChainLength;
    }
    if(currentMax == 1) {
      break;
    }
  }

  if(currentMax > 1) {
    for(Iterator<Entry<int, MapInfo> > it = cl.entrySet().getIterator(); it.hasNext();) {
      Entry<int, MapInfo > &e = it.next();
      const int capacity = e.getKey();
      const MapInfo &v = e.getValue();
      if(v.m_maxChainLength == currentMax && v.m_chainCount[2] <= 12) {
        _tprintf(_T("%s\n"), v.toString().cstr());
      }
    }
  }
  const MapInfo *bestInfo = cl.get(bestCapacity);
  _tprintf(_T("bestInfo:%s\n"), bestInfo->toString().cstr());
  MapInfo info = keywords.getMapInfo();
  _tprintf(_T("current map:%s\n"), info.toString().cstr());
}

void ResourceLex::verror(const SourcePosition &pos, const TCHAR *format, va_list argptr) {
  if(m_parser) {
    m_parser->verror(pos,format,argptr);
  } else {
    Scanner::verror(pos,format,argptr);
  }
}


#line 114 "C:\\mytools2015\\parsergen\\lib\\lexgencpp.par"
