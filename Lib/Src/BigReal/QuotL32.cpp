#include "pch.h"

#define MAXDIGITS_INT32     9
#define MAXDIGITS_DIVISOR32 ((MAXDIGITS_INT32+1)/2)

class QuotL32Constants {
public:
  const ConstBigReal c1;
  const ConstBigReal c2;
  const ConstBigReal c3;
  const ConstBigReal c4;

  QuotL32Constants()
    :c1(e(ConstBigReal(24),-2))
    ,c2(e(ConstBigReal( 4),-2))
    ,c3(e(ConstBigReal( 8),-2))
    ,c4(e(ConstBigReal(11),-1))
  {
  }
};

static const QuotL32Constants Q32C;

// Linear quot. Assume x != 0 and y != 0 and f != 0
BigReal BigReal::quotLinear32(const BigReal &x, const BigReal &y, const BigReal &f, DigitPool *pool) { // static
  const bool yNegative = y.isNegative();
  ((BigReal&)y).setPositive(); // cheating. We set it back agin

  const BigReal v = PAPCprod(<, PAPCprod(<, f, Q32C.c1, pool), y, pool); // v >= 0

  BigReal z(pool);
  copy(z, x, v*Q32C.c2);

  z.setPositive();

  BigReal u(pool);
  u.approxQuot32(z, v);
  u.approxQuot32(v, getExpo10N(u)*Q32C.c3 + Q32C.c4);

  BRExpoType scale;
  const unsigned long yFirst = y.getFirst32(MAXDIGITS_DIVISOR32,&scale);

  BigReal result(pool), t(pool), tmp(pool);
  bool loopDone = false;
  for(; compareAbs(z,v) > 0; loopDone = true) {
    t.approxQuot32Abs(z, yFirst, scale).m_negative = z.m_negative;
    result += t;
    z -= product(tmp, t, y, u, 0);
  }

  ((BigReal&)y).m_negative = yNegative;

  if(loopDone) {
    return result.setSignByProductRule(x,y);
  } else {
    return result.approxQuot32Abs(x, yFirst, scale).setSignByProductRule(x,y);
  }
}

// Assume x != 0 and y != 0
BigReal &BigReal::approxQuot32(const BigReal &x, const BigReal &y) {
  BRExpoType scale;
  const unsigned long yFirst = y.getFirst32(MAXDIGITS_DIVISOR32,&scale);
  return approxQuot32Abs(x, yFirst, scale).setSignByProductRule(x, y);
}

// Assume x != 0 and y != 0
BigReal &BigReal::approxQuot32Abs(const BigReal &x, unsigned long y, BRExpoType scale) {
  const unsigned long q = x.getFirst32(MAXDIGITS_INT32)/y;
  *this = q;
  return multPow10(getExpo10(x) - scale - MAXDIGITS_INT32);
}

BigReal BigReal::reciprocal(const BigReal &x, DigitPool *digitPool) { // static
  static const int k = MAXDIGITS_DIVISOR32;
  BigReal result(pow10(MAXDIGITS_INT32)/x.getFirst32(k), digitPool);
  result.multPow10(k - 1 - MAXDIGITS_INT32 - getExpo10(x));
  result.m_negative = x.m_negative;
  return result;
}

// Assume k <= MAXDIGITS_INT32 (=9). scale can be NULL.
// Return the first k decimal digits of this.
// if scale != NULL, result = n/10^scale, where scale = max(s|(n/10^s) % 10 != 0) and n = first k decimal digits of this
// if scale == NULL, result = first k decimal digits of this, which can contain trailing zeroes
unsigned long BigReal::getFirst32(const UINT k, BRExpoType *scale) const {
#ifdef _DEBUG
  DEFINEMETHODNAME;
  if(k > MAXDIGITS_INT32) {
    throwBigRealInvalidArgumentException(method, _T("k=%d. Legal interval is [0..%d]"), k, MAXDIGITS_INT32);
  }
#endif

  const Digit *p = m_first;
  if(p == NULL) {
    if(scale) *scale = 0;
    return 0;
  }

  BRExpoType    tmpScale = 0;
  BRDigitType   result   = p->n;

  int           digits   = getDecimalDigitCount(result), firstDigits = digits;;
  if((UINT)digits >= k) {
    result /= pow10(digits-k); // digits-k <= LOG10_BIGREALBASE, so pow10 will not fail
    if(scale) {
      while(result % 10 == 0) {
        result /= 10;
        tmpScale++;
      }
    }
  } else { // digits < k
    if(scale) {
      for(p = p->next; (UINT)digits < k; digits += LOG10_BIGREALBASE) {
        if(p) {
          const BRDigitType p10 = pow10(min(LOG10_BIGREALBASE,k-digits));
          result = result * p10 + p->n / (BIGREALBASE/p10);
          p = p->next;
        } else {
          tmpScale = k - digits;
          break;
        }
      }
      while(result % 10 == 0) {
        result /= 10;
        tmpScale++;
      }
    } else { // scale == NULL
      for(p = p->next; (UINT)digits < k; digits += LOG10_BIGREALBASE) {
        const BRDigitType p10 = pow10(min(LOG10_BIGREALBASE,k-digits));
        result *= p10;
        if(p) {
          result += p->n / (BIGREALBASE/p10);
          p = p->next;
        }
      }
    }
  }

  if(scale) {
    *scale = m_expo * LOG10_BIGREALBASE + firstDigits - 1 + tmpScale - k;
  }
  return (unsigned long)result;
}

