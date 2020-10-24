#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstdint>

#include "rational_num.h"

// https://en.wikipedia.org/wiki/Complex_number

template<class T>
class ComplexNumber {
  RationalNumber<T> real;
  RationalNumber<T> imag;

 public:
  ComplexNumber(const T &num) : real(num), imag(0) {}

  ComplexNumber(const RationalNumber<T> &real = 0,
                const RationalNumber<T> &imag = 0) : real(real), imag(imag) {}

  ComplexNumber &operator=(const ComplexNumber &other) = default;

  ComplexNumber operator+(const ComplexNumber &other) const {
    // (a + bi) + (c + di) = (a + c) + (b + d)i
    auto r_real = this->real + other.real;
    auto r_imag = this->imag + other.imag;
    return ComplexNumber(r_real, r_imag);
  }

  ComplexNumber operator-(const ComplexNumber &other) const {
    // (a + bi) - (c + di) = (a - c) + (b - d)i
    auto r_real = this->real - other.real;
    auto r_imag = this->imag - other.imag;
    return ComplexNumber(r_real, r_imag);
  }

  ComplexNumber operator*(const ComplexNumber &other) const {
    // (a + bi) * (c + di) = ac + bci + adi + bdi^2 =
    // = (ac + bdi^2) + (bc + ad) = (ac - bd) + (bc + ad)i
    auto r_real = this->real * other.real - this->imag * other.imag;
    auto r_imag = this->imag * other.real + this->real * other.imag;
    return ComplexNumber(r_real, r_imag);
  }

  ComplexNumber operator/(const ComplexNumber &other) const {
    // (a + bi) / (c + di) =
    // = (ac + bd) / (c^2 + d^2) + ((bc - ad) / (c^2 + d^2))i
    auto r_real = (this->real * other.real + this->imag * other.imag)
        / (other.real * other.real + other.imag * other.imag);
    auto r_imag = (this->imag * other.real - this->real * other.imag)
        / (other.real * other.real + other.imag * other.imag);
    return ComplexNumber(r_real, r_imag);
  }

  ComplexNumber &operator+=(const ComplexNumber &other) {
    // (a + bi) + (c + di) = (a + c) + (b + d)i
    this->real += other.real;
    this->imag += other.imag;
    return *this;
  }

  ComplexNumber &operator-=(const ComplexNumber &other) {
    // (a + bi) - (c + di) = (a - c) + (b - d)i
    this->real -= other.real;
    this->imag -= other.imag;
    return *this;
  }

  ComplexNumber &operator*=(const ComplexNumber &other) {
    // (a + bi) * (c + di) = ac + bci + adi + bdi^2 =
    // = (ac + bdi^2) + (bc + ad) = (ac - bd) + (bc + ad)i
    auto this_real = this->real;
    auto other_real = other.real;
    this->real = this->real * other.real - this->imag * other.imag;
    this->imag = this->imag * other_real + this_real * other.imag;
    return *this;
  }

  ComplexNumber &operator/=(const ComplexNumber &other) {
    // (a + bi) / (c + di) =
    // = (ac + bd) / (c^2 + d^2) + ((bc - ad) / (c^2 + d^2))i
    auto this_real = this->real;
    auto other_real = other.real;
    this->real = (this->real * other.real + this->imag * other.imag)
        / (other.real * other.real + other.imag * other.imag);
    this->imag = (this->imag * other_real - this_real * other.imag)
        / (other_real * other_real + other.imag * other.imag);
    return *this;
  }

  ComplexNumber operator-() const {
    auto r_real = -this->real;
    auto r_imag = -this->imag;
    return ComplexNumber(r_real, r_imag);
  }

  bool operator==(const ComplexNumber &other) const {
    return (this->real == other.real) && (this->imag == other.imag);
  }

  bool operator!=(const ComplexNumber &other) const {
    return (this->real != other.real) || (this->imag != other.imag);
  }

  friend std::ostream &operator<<(std::ostream &os, const ComplexNumber &num) {
    return os << "(" << num.real << ", " << num.imag << ")";
  }

  double Arg() const {
    // tan(angle) = b / a
    // need to return angle in radians
    auto result = this->real == 0 && this->imag == 0 ? 0 : atan(
        this->imag.toDouble() / this->real.toDouble());

    return this->real < 0 ? (
        this->imag < 0 ? result - M_PI : result + M_PI) : result;
  }

  double Abs() const {
    // z = a + bi, i^2 = -1
    // |z| = sqrt(sqr(real) + sqr(imag)) or |z| = sqrt(sqr(a) + sqr(b))
    // need to return |z|
    return std::sqrt((this->real * this->real
        + this->imag * this->imag).toDouble());
  }

  ComplexNumber Pow(const int exp = 2) const {
    ComplexNumber a(this->real, this->imag), b = a;
    for (int i = 1; i < exp; i++) {
      a *= b;
    }
    return a;
  }

  RationalNumber<T> getReal() const {
    return this->real;
  }

  void setReal(RationalNumber<T> s_real) {
    this->real = s_real;
  }

  RationalNumber<T> getImag() const {
    return this->imag;
  }

  void setImag(RationalNumber<T> s_imag) {
    this->imag = s_imag;
  }
};
