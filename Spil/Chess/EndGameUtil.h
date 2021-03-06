#pragma once

#include <CompactHashSet.h>
#include <Map.h>
#include <CountedByteStream.h>
#include <Timer.h>
#include "EndGameKeyDefinition.h"

// #define NEWCOMPRESSION

#ifdef NEWCOMPRESSION
#include <BigEndianStream.h>
#endif

typedef enum {
  EG_UNDEFINED
 ,EG_DRAW
 ,EG_WHITEWIN   // dont swap these. EG_WHITEWIN, EG_BLACKWIN must be the last. See IndexedMapEntryIteratorWinnerEntries
 ,EG_BLACKWIN
} EndGamePositionStatus;

const TCHAR *positionStatusToString(EndGamePositionStatus state);

#define STATUSTOWINNER(status) (((status) == EG_WHITEWIN) ? WHITEPLAYER : BLACKPLAYER)
#define PLIESTOMOVES(plies)    (((plies)+1)/2)
#define MOVESTOPLIES(moves)    ((moves)?((moves)*2-1):0)

#define BOOL2MASK(b1, b2)     (((b1)?1:0) | ((b2)?2:0))
#define BOOL3MASK(b1, b2, b3) (BOOL2MASK(b1, b2) | ((b3)?4:0))

#define FBOOL2MASK(f, x, y   ) BOOL2MASK(f(x), f(y))
#define FBOOL3MASK(f, x, y, z) BOOL3MASK(f(x), f(y), f(z))

class EndGameResult {     // bit 0-8:pliesToEnd, bit 9-10:positionStatus, bit 11:exist, bit 12:visited, bit 13:changed, bit 14:marked
private:                  // f e d c b a9     876543210
  USHORT m_data;          // - M C V E Status pliesToEnd

public:
  inline EndGameResult() {
    m_data = 0;
  }
  inline EndGameResult(EndGamePositionStatus status, UINT pliesToEnd) {
    m_data = (1<<11);
    setResult(status, pliesToEnd);
  }

  EndGameResult(GameResult r);

  EndGameResult &setResult(EndGamePositionStatus status, UINT pliesToEnd);
  EndGameResult &changePliesToEnd(UINT pliesToEnd);

  inline UINT getPliesToEnd() const {
    return (m_data & 0x1ff);
  }

  inline UINT getMovesToEnd() const {
    return PLIESTOMOVES(getPliesToEnd());
  }
#ifdef NEWCOMPRESSION
  inline void prunePliesToEnd() { // to be used with compression
    m_data &= ~0x1ff;
  }
#endif
  inline EndGamePositionStatus getStatus() const {
    return (EndGamePositionStatus)((m_data>>9) & 0x3);
  }

  inline bool exists() const {
    return (m_data & (1<<11)) != 0;
  }

  inline void setUndefined() {
    assert(exists());
    m_data &= ~0x07ff;
  }

  inline bool isDefined() const {
    return getStatus() != EG_UNDEFINED;
  }

  inline bool isWinner() const {
    return getStatus() >= EG_WHITEWIN;
  }

  inline void setExist() {
    m_data |= (1<<11);
  }

  inline void clearExist() {
    m_data = 0;
  }

  inline bool isVisited() const {
    return (m_data & (1<<12)) != 0;
  }

  inline void setVisited() {
    m_data |= (1<<12);
  }

  inline void clearVisited() {
    m_data &= ~(1<<12);
  }

  inline EndGameResult &setChanged() {
    m_data |= (1<<13);
    return *this;
  }

  inline void clearChanged() {
    m_data &= ~(1<<13);
  }

  inline bool isChanged() const {
    return (m_data & (1<<13)) != 0;
  }

  inline void setMark() {
    m_data |= (1<<14);
  }

  inline void clearMark() {
    m_data &= ~(1<<14);
  }

  inline bool isMarked() const {
    return (m_data & (1<<14)) != 0;
  }

  inline void clearHelpInfo() { // clear Visited, Changed, and Marked
    m_data &= ~(7<<12);
  }

  inline bool hasHelpInfo() const {
    return (m_data & (7 << 12)) ? true : false;
  }

  inline bool operator==(const EndGameResult r) const {
    return (m_data & 0x7ff) == (r.m_data & 0x7ff);
  }

  inline bool operator!=(const EndGameResult r) const {
    return (m_data & 0x7ff) != (r.m_data & 0x7ff);
  }

  TCHAR *toStr(TCHAR *dst, bool ply = false) const;
  TCHAR *toStr(TCHAR *dst, Player playerInTurn, bool ply = false) const;

  String toString(bool ply = false) const;
  String toString(Player playerInTurn, bool ply = false) const;
};

#define EGR_STALEMATE    EndGameResult(EG_DRAW     , 0)
#define EGR_TERMINALDRAW EndGameResult(EG_DRAW     , 1)
#define EGR_DRAW         EndGameResult(EG_DRAW     , 2)
#define EGR_WHITEISMATE  EndGameResult(EG_BLACKWIN , 0)
#define EGR_BLACKISMATE  EndGameResult(EG_WHITEWIN , 0)

typedef Entry<EndGameKey, EndGameResult> EndGameEntry;

class MoveWithResult : public MoveBase {
public:
  EndGameResult m_result;
  MoveWithResult() {
  }
  MoveWithResult(const MoveBase &move, const EndGameResult &result) : MoveBase(move), m_result(result) {
  }
  String toString() const {
    return format(_T("%8s - %s"), MoveBase::toString().cstr(), m_result.toString().cstr());
  }
};

class MoveResultArray : public CompactArray<MoveWithResult> {
private:
  Player m_playerInTurn;
public:
  MoveResultArray(Player playerInTurn) : m_playerInTurn(playerInTurn) {
  }
  MoveWithResult selectShortestWinnerMove() const {
    return (*this)[findShortestWinnerMoves().select()];
  }

  MoveWithResult selectLongestLoosingMove(int defendStrength) const { // defendStrength = [0..100]
    return (*this)[findLongestLoosingMoves(defendStrength).select()];
  }

  MoveWithResult selectDrawMove() const {
    return (*this)[findDrawMoves().select()];
  }

  CompactIntArray findShortestWinnerMoves()                   const;
  CompactIntArray findLongestLoosingMoves(int defendStrength) const; // defendStrength = [0..100]
  CompactIntArray findDrawMoves()                             const;
  MoveWithResult  selectBestMove(int defendStrength)          const; // defendStrength = [0..100]

  MoveResultArray &sort();
  String toString(const Game &game, MoveStringFormat mf, bool depthInPlies);
};

class WrongVersionException : public Exception {
public:
  WrongVersionException(const TCHAR *msg) : Exception(msg) {
  }
};

class MissingPositionException : public Exception {
public:
  MissingPositionException(const TCHAR *msg) : Exception(msg) {
  }
};

// Dont change layout of this class, as it is part of header-information
template<class T> class TwoCountersTemplate {
public:
  T m_count[2]; // one for each player

  TwoCountersTemplate(T wc, T bc) {
    m_count[0] = wc; m_count[1] = bc;
  }
  TwoCountersTemplate() {
    clear();
  }
  void clear() {
    m_count[0] = m_count[1] = 0;
  }
  bool isEmpty() const {
    return (m_count[0] | m_count[1]) == 0;
  }
  T getTotal() const {
    return m_count[0] + m_count[1];
  }
  T getMax() const {
    return max(m_count[0], m_count[1]);
  }
  TwoCountersTemplate<T> operator+(const TwoCountersTemplate<T> &tc) const {
    return TwoCountersTemplate(m_count[0] + tc.m_count[0], m_count[1] + tc.m_count[1]);
  }
  TwoCountersTemplate<T> &operator+=(const TwoCountersTemplate<T> &tc) {
    m_count[0] += tc.m_count[0]; m_count[1] += tc.m_count[1];
    return *this;
  }
  String toString(TCHAR separator = _T(' '), int width = 11) const {
    return format(_T("%*s%c%*s"), width, format1000(m_count[0]).cstr(), separator, width, format1000(m_count[1]).cstr());
  }
  inline void incr(Player player) {
    m_count[player]++;
  }
  inline void decr(Player player) {
    m_count[player]--;
  }
  bool operator==(const TwoCountersTemplate<T> &rhs) const {
    return m_count[0] == rhs.m_count[0] && m_count[1] == rhs.m_count[1];
  }
  bool operator!=(const TwoCountersTemplate<T> &rhs) const {
    return !(*this == rhs);
  }
};

template<class T> int compare(const TwoCountersTemplate<T> &tc1, const TwoCountersTemplate<T> &tc2) {
  return sign((long long)tc1.getTotal() - (long long)tc2.getTotal());
};

template<class T> int compare(const TwoCountersTemplate<T> &tc1, const TwoCountersTemplate<T> &tc2, Player player) {
  return sign((long long)tc1.m_count[player] - (long long)tc2.m_count[player]);
};

template<class T> int compareMax(const TwoCountersTemplate<T> &tc1, const TwoCountersTemplate<T> &tc2) {
  return sign((long long)tc1.getMax() - (long long)tc2.getMax());
};

typedef TwoCountersTemplate<UINT>           PositionCount32;
typedef TwoCountersTemplate<unsigned short> MaxVariantCount;

class PositionCount64 : public TwoCountersTemplate<UINT64> {
public:
  PositionCount64() : TwoCountersTemplate<UINT64>() {
  }
  PositionCount64(UINT64 wc, UINT64 bc) : TwoCountersTemplate(wc, bc) {
  }
  PositionCount64(const PositionCount32 &src) : TwoCountersTemplate(src.m_count[0], src.m_count[1]) {
  }
  PositionCount64(const TwoCountersTemplate<UINT64> &src) : TwoCountersTemplate(src) {
  }
};

// Bits for TablebaseInfo.m_stateFlags
#define TBISTATE_CONSISTENT          0x01
#define TBISTATE_NONWINNERFIXED      0x02
#define TBISTATE_WINNERFORWARD1FIXED 0x04
#define TBISTATE_WINNERRETROFIXED    0x08
#define TBISTATE_WINNERFORWARD2FIXED 0x10

#define TBISTATE_MASK                0x1f

#define WHITECANWIN 0x01
#define BLACKCANWIN 0x02
#define BOTHCANWIN  (WHITECANWIN|BLACKCANWIN)

#ifdef NEWCOMPRESSION
typedef BYTE NotPrunedFlags;
#define NPFLAGS(player,parity) ((NotPrunedFlags)(((player)<<1) | (parity)))
#define NPGETPLAYER(npf)       ((Player)(((npf)>>1)&1))
#define NPGETPARITY(npf)       ((npf)&1)
#endif // NEWCOMPRESSION

#ifdef TABLEBASE_BUILDER
typedef enum {
  TBIFORMAT_PRINT_TERMINALS
 ,TBIFORMAT_PRINT_NONTERMINALS
 ,TBIFORMAT_PRINT_UNDEFANDWINS
 ,TBIFORMAT_PRINT_COLUMNS1
 ,TBIFORMAT_PRINT_COLUMNS2
} TablebaseInfoStringFormat;

#define WBWIDTH(n) (2*(n)+1)

#define POSITIONWIDTH    14
#define INDEXSIZEWIDTH   14
#define UNDEFINEDWIDTH   11
#define STALEMATEWIDTH   10
#define MATEPOSWIDTH      9
#define WINNERPOSWIDTH   14
#define TERMPOSWIDTH     11
#define NTPOSWIDTH       13
#define MAXVARFLDWIDTH    3
#define MAXVARWIDTH       WBWIDTH(MAXVARFLDWIDTH)
#define VERSIONWIDTH      5

#endif // TABLEBASE_BUILDER

class TablebaseInfo {
private:
  void checkVersion() const; // throws exception if wrong version
public:
  mutable char       m_version[20];
  UINT64             m_totalPositions;
  UINT64             m_indexCapacity;
  UINT64             m_undefinedPositions;
  UINT64             m_stalematePositions;
  UINT64             m_drawPositions;                // excl. stalemates and terminalDrawPositions;
  PositionCount64    m_checkMatePositions;           // m_checkMatePositions[WHITEPLAYER] = #positions where black is checkmate (white win) likewise black
  PositionCount64    m_terminalWinPositions;         // excl. checkmates
  PositionCount64    m_nonTerminalWinPositions;      // excl. checkmates and terminalWinPositions
  MaxVariantCount    m_maxPlies;                     // max length in plies of forced winning variant for each player. 0 if no winnerpositions
  bool               m_canWin[2];                    // Indicates if a player has any winner-positions,
                                                     // ie. checkmates or conversions to a winning position in another endgame exist
  BYTE               m_stateFlags;
  __time64_t         m_buildTime;
  __time64_t         m_consistencyCheckedTime;

  inline TablebaseInfo() {
    clear();
  }
  void clear();
  void save(ByteOutputStream      &s) const;
  void load(ByteInputStream       &s);
#ifdef NEWCOMPRESSION
  void save(BigEndianOutputStream &s) const;
  void load(BigEndianInputStream  &s);
#endif

  UINT64 getCheckMatePositions() const {
    return m_checkMatePositions.getTotal();
  }
  UINT64 getTerminalPositions() const {
    return m_terminalWinPositions.getTotal();
  }
  UINT64 getNonterminalPositions() const {
    return m_nonTerminalWinPositions.getTotal();
  }
  PositionCount64 getWinnerPositionCount() const;
  UINT64 getWinnerPositionCount(Player winner) const;
  String formatMaxVariants(bool plies=false) const;

  bool isConsistent() const {
    return (m_stateFlags & TBISTATE_CONSISTENT) != 0;
  }
#ifdef NEWCOMPRESSION
  void setNPFlags(NotPrunedFlags flags); // comes from PositionTypeCounters.getMinCounterIndex()
  NotPrunedFlags getNPFlags() const;
#endif
  inline BYTE getCanWinFlags() const {
    return (m_canWin[WHITEPLAYER]?WHITECANWIN:0)|(m_canWin[BLACKPLAYER]?BLACKCANWIN:0);
  }
  String getVersion() const {
    return m_version;
  }
  static const char *s_programVersion;
  static String getProgramVersion() {
    return s_programVersion;
  }

#ifdef TABLEBASE_BUILDER
  // only defined for TBIFORMAT_PRINT_COLUMNS1/2
  static int getDataStringLength(TablebaseInfoStringFormat format);
  static String getColumnHeaders(TablebaseInfoStringFormat f, const String &headerLeft, const String &headerRight, bool plies);
  String toString(TablebaseInfoStringFormat f, bool plies = true) const;
#endif // TABLEBASE_BUILDER
};

class StreamProgress : public ByteCounter, public TimeoutHandler {
private:
  UINT64 m_total;
  Timer  m_timer;
public:
  StreamProgress(const EndGameTablebase *tb);
  StreamProgress(const String &fileName);
  ~StreamProgress();
  void handleTimeout(Timer &timer);
};

#ifdef TABLEBASE_BUILDER

typedef Iterator<EndGameKey>   EndGameKeyIterator;

class EndGameManualPositions {
private:
  const EndGameKeyDefinition &m_keydef;
  CompactHashSet<EndGameKey>  m_keySet;
public:
  EndGameManualPositions(const EndGameKeyDefinition &keydef);
  bool addKey(const EndGameKey &key);
  EndGameKey createKey(const String &str) const;
  void save(FILE *f);
  void load(FILE *f, int &lineCount);
  void load();
  String getName() const {
    return m_keydef.toString();
  }
  const EndGameKeyDefinition &getKeyDefinition() const {
    return m_keydef;
  }
  EndGameKeyIterator getKeyIterator();
  CompactArray<EndGameKey> readUndefinedKeysLog(const String &fileName) const;
};

class AllManualPositions {
private:
  Array<EndGameManualPositions> m_endGamePositions;
  static String getFileName();
  friend class EndGameManualPositions;
public:
  void load();
  void save();
  void clear();
  EndGameManualPositions &get(const String &name);
};

class IntervalChecker {
private:
  const TCHAR  *m_name;
  EndGamePosIndex m_minValue;
  EndGamePosIndex m_maxValue;
public:
  IntervalChecker(const TCHAR *name);
  ~IntervalChecker();
  void update(EndGamePosIndex v);
};

#ifdef NEWCOMPRESSION

class PositionTypeCounters {
public:
  UINT64 m_count[2][2]; // indexed by playerInTurn, moveToEnd&1
  inline PositionTypeCounters() {
    m_count[0][0] = m_count[0][1] = m_count[1][0] = m_count[1][1] = 0;
  }
  inline void updateCount(const EndGameEntry &e) {
    m_count[e.getKey().getPlayerInTurn()][e.getValue().getMovesToEnd()&1]++;
  }
  String toString() const {
    return format(_T("  %14s  %14s\nW:%14s  %14s\nB:%14s  %14s\n")
                 ,_T("Even par"), _T("Odd par")
                 ,format1000(m_count[WHITEPLAYER][0]).cstr(),format1000(m_count[WHITEPLAYER][1]).cstr()
                 ,format1000(m_count[BLACKPLAYER][0]).cstr(),format1000(m_count[BLACKPLAYER][1]).cstr()
                 );
  }
  NotPrunedFlags getBestNPFlags() const; // bit 0:(0=even Parity,1=odd), bit 1:(0=WhiteToMove,1=BlacktoMove)
};

#endif // NEWCOMPRESSION

#endif // TABLEBASE_BUILDER
