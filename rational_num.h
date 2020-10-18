#include <algorithm>
#include <cmath>
#include <iostream>
#include <cmath>
#include <cstdint>
#include <exception>
#define _USE_MATH_DEFINES
#define EPSILON_VALUE 0.00000001

template<class T>
class RationalNumber {
  T numer;
  T denom;

  static bool comparator(double A, double B) {
    return (std::fabs(A - B) < EPSILON_VALUE);
  }

  void Reduce() {
    auto got_gcd =
        gcd(this->numer < 0 ? -this->numer : this->numer, this->denom);
    this->numer /= got_gcd;
    this->denom /= got_gcd;
  }

  static int64_t gcd(int64_t a, int64_t b) {
    while (a) {
      auto t = b % a;
      b = a;
      a = t;
    }
    return b;
  }

 public:
  RationalNumber() : numer(0), denom(1) {};

  RationalNumber(const T num) {
    this->numer = num;
    this->denom = 1;
  }

  explicit RationalNumber(const T numer, const T denom) {
    this->numer = numer;
    this->denom = denom;

    if (this->denom == 0) {
      std::cout << "Warning: denominator cannot be zero, it will be set 1"
                << std::endl;
      this->denom = 1;
    }

    if (this->denom < 0) {
      this->numer = -this->numer;
      this->denom = -this->denom;
    }
    Reduce();
  }

  RationalNumber<T> &operator=(const RationalNumber<T> &other) = default;

  RationalNumber<T> operator+(const RationalNumber<T> &other) const {
    return RationalNumber<T>(
        this->numer * other.denom + other.numer * this->denom,
        this->denom * other.denom);
  }

  RationalNumber<T> operator-(const RationalNumber<T> &other) const {
    return -other + *this;
  }

  RationalNumber<T> operator*(const RationalNumber<T> &other) const {
    return RationalNumber<T>(this->numer * other.numer,
                             this->denom * other.denom);
  }

  RationalNumber<T> operator/(const RationalNumber<T> &other) const {
    return RationalNumber<T>(this->numer * other.denom,
                             this->denom * other.numer);
  }

  RationalNumber<T> &operator+=(const RationalNumber<T> &other) {
    *this = *this + other;
    return *this;
  }

  RationalNumber<T> &operator-=(const RationalNumber<T> &other) {
    *this = *this - other;
    return *this;
  }

  RationalNumber<T> &operator*=(const RationalNumber<T> &other) {
    *this = *this * other;
    return *this;
  }

  RationalNumber<T> &operator/=(const RationalNumber<T> &other) {
    *this = *this / other;
    return *this;
  }

  RationalNumber<T> operator-() const {
    return RationalNumber<T>(-numer, denom);
  }

  bool operator==(const RationalNumber<T> &other) const {
    return comparator(this->numer, other.numer)
        && comparator(this->denom, other.denom);
  }

  bool operator!=(const RationalNumber<T> &other) const {
    return !this->operator==(other);
  }

  bool operator>(const RationalNumber<T> &other) const {
    return this->numer * other.denom > other.numer * this->denom;
  }

  bool operator<(const RationalNumber<T> &other) const {
    return other > *this;
  }

  bool operator>=(const RationalNumber<T> &other) const {
    return *this > other || *this == other;
  }

  bool operator<=(const RationalNumber<T> &other) const {
    return *this < other || *this == other;
  }

  double toDouble() const {
    return (double) numer / denom;
  }

  friend std::ostream &operator<<(std::ostream &os,
                                  const RationalNumber<T> &num) {
    return os << num.toDouble();
  }

  RationalNumber<double> Sqrt() const {
    return RationalNumber<T>(std::sqrt(numer), std::sqrt(denom));
  }

  T GetNumer() const {
    return numer;
  }

  T GetDenom() const {
    return denom;
  }
};
