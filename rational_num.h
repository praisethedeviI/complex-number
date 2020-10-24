#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstdint>
#include <numeric>

// only for int, int64_t and same types
template<class T>
class RationalNumber {
  T numer;
  T denom;

  void Reduce() {
    auto got_gcd =
        std::gcd(this->numer < 0 ? -this->numer : this->numer, this->denom);
    this->numer /= got_gcd;
    this->denom /= got_gcd;
  }

 public:
  RationalNumber(const T &numer = 0, const T &denom = 1) {
    this->numer = numer;
    this->denom = denom;

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
    this->numer = this->numer * other.denom + other.numer * this->denom;
    this->denom = this->denom * other.denom;
    Reduce();
    return *this;
  }

  RationalNumber<T> &operator-=(const RationalNumber<T> &other) {
    this->numer = this->numer * other.denom - other.numer * this->denom;
    this->denom = this->denom * other.denom;
    Reduce();
    return *this;
  }

  RationalNumber<T> &operator*=(const RationalNumber<T> &other) {
    this->numer = this->numer * other.numer;
    this->denom = this->denom * other.denom;
    Reduce();
    return *this;
  }

  RationalNumber<T> &operator/=(const RationalNumber<T> &other) {
    this->numer = this->numer * other.denom;
    this->denom = this->denom * other.numer;
    Reduce();
    return *this;
  }

  RationalNumber<T> operator-() const {
    return RationalNumber<T>(-numer, denom);
  }

  bool operator==(const RationalNumber<T> &other) const {
    return this->numer == other.numer && this->denom == other.denom;
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
    return os << num.GetNumer() << "/" << num.GetDenom();
  }

  T GetNumer() const {
    return numer;
  }

  T GetDenom() const {
    return denom;
  }
};
