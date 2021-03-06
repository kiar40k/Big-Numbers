#pragma once

#include <NumberInterval.h>
#include "Matrix.h"

#define MAXDEGREE 30
#define MAXM (MAXDEGREE+2)

class DataPoint {
public:
  Real x,y,w;
  DataPoint();
  DataPoint(const Real &x, const Real &y, const Real &w = 1);
  DataPoint(const Point2D &p);
  String toString() const;
};

class AbstractDataFit : public Function {
protected:
  bool m_ok;
public:
  virtual Real operator()(const Real &x) = 0;
  virtual Real operator()(int d, const Real &x) = 0; // evaluate f',f'',f'''
  virtual AbstractDataFit *clone() const = 0;
  virtual ~AbstractDataFit() {};

  virtual int getMaxDegree() const {
    return 0;
  }

  virtual void setDegree(int degree) {
  }

  virtual int  getDegree() const {
    return 0;
  }

  virtual int  getActualDegree() const {
    return 0;
  }

  Real ssd(const CompactArray<DataPoint> &data);
  virtual String generateCFunction() const = 0;

  bool ok() const {
    return m_ok;
  }
};

typedef enum {
  LSSD
 ,NATURAL_SPLINE
 ,DYDXMATCH_SPLINE
 ,IGNOREENDPOINT_SPLINE
 ,AKIMA_SPLINE
 ,FRITSCH_CARLSON
} FittingType;

class Polynomial;

class LssdPolynomial : public AbstractDataFit {
private:
  Real alfa[MAXM],beta[MAXM],b[MAXM];
  int m;
  int m_degree;
  int countDistinct(const CompactArray<DataPoint> &data);
public:
  LssdPolynomial(const CompactArray<DataPoint> &data);
  AbstractDataFit *clone() const;

  int  getMaxDegree() const {
    return m;
  }

  void setDegree(int degree) {
    m_degree = degree;
  }

  int getDegree() const {
    return m_degree;
  }

  int getActualDegree() const {
    return (m_degree < m) ? m_degree : m;
  }

  Real operator()(const  Real &x);
  Real operator()(int d, const Real &x);
  String generateCFunction() const;
  operator Polynomial() const;
};

class CubicSpline : public AbstractDataFit {
private:
  Vector M;
  Vector a;
  Vector y;
  Vector h;
  mutable int m_lastInterval;
  int findInterval(const Real &x) const;
public:
  CubicSpline(FittingType type, const CompactArray<DataPoint> &data, const Real &dydx1, const Real &dydx2);
  AbstractDataFit *clone() const;
  Real operator()(const Real &x);
  Real operator()(int d, const Real &x);
  NumberInterval<Real> getDomain() const;
  String generateCFunction() const;
};

class CommonSpline : public AbstractDataFit {
protected:
  Matrix yd;
  Vector a;
  mutable int m_lastInterval;
  int findInterval(const Real &X) const;
  int preprocessdata(const CompactArray<DataPoint> &data, Vector &x, Vector &y);
public:
  Real operator()(const Real &x);
  Real operator()(int d, const Real &x);
  String generateCFunction() const;
};

class AkimaSpline : public CommonSpline {
public:
  AkimaSpline(const CompactArray<DataPoint> &data);
  AbstractDataFit *clone() const;
};

class FritschCarlsonSpline : public CommonSpline {
public:
  FritschCarlsonSpline(const CompactArray<DataPoint> &data);
  AbstractDataFit *clone() const;
};

class DataFit : public AbstractDataFit {
private:
  AbstractDataFit *m_dataFit;
  FittingType      m_type;
public:
  bool solve(FittingType type, const CompactArray<DataPoint> &data, const Real &dydx1 = 0, const Real &dydx2 = 0);
  DataFit();
  ~DataFit();
  DataFit(const DataFit &src);
  AbstractDataFit *clone() const;
  DataFit &operator=(const DataFit &src);

  Real operator()(const Real &x) {
    return (*m_dataFit)(x);
  }

  Real operator()(int d, const Real &x) {
    return (*m_dataFit)(d,x);
  }

  int getMaxDegree() const {
    return m_dataFit->getMaxDegree();
  }

  void setDegree(int degree) {
    m_dataFit->setDegree(degree);
  }

  int getDegree() const {
    return m_dataFit->getDegree();
  }

  int getActualDegree() const {
    return m_dataFit->getActualDegree();
  }

  FittingType getType() const {
    return m_type;
  }

  String generateCFunction() const {
    return m_dataFit->generateCFunction();
  }

  operator Polynomial() const;
};

class Polynomial : public ComplexFunction {
private:
  ComplexVector m_coef;
  Polynomial &trimLeadingZeroes(); // return *this
  Polynomial(int degree);
public:
  Polynomial(const Vector &coef);
  Polynomial(const ComplexVector &coef);

  Polynomial &setCoef(int n, const Complex &a) {
    m_coef[n] = a;
    return *this;
  }

  const Complex &getCoef(int n) const {
    return m_coef[n];
  }

  int getDegree() const {
    return (int)m_coef.getDimension() - 1;
  }

  Complex     operator()( const Complex &x);
  Polynomial  operator+(  const Polynomial &rhs) const;
  Polynomial  operator-(  const Polynomial &rhs) const;
  Polynomial  operator*(  const Polynomial &rhs) const;
  Polynomial  operator/(  const Polynomial &rhs) const;
  friend Polynomial div(  const Polynomial &p, const Polynomial &d, Polynomial &rem);
  Polynomial  operator*(  const Complex &rhs   ) const;
  Polynomial  operator/(  const Complex &rhs   ) const;
  Polynomial &operator/=( const Complex &root  );
  Polynomial dfdx() const;
  Complex findRoot(const Complex &start, bool verbose, const Real &rootCriterium = 1e-15) const;
  ComplexVector findRoots(bool verbose, const Real &rootCriterium = 1e-15) const;
  friend tostream& operator<<(tostream &out,const Polynomial &poly);
  String toString() const;
};
