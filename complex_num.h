#include <algorithm>
#include <cmath>
#include <iostream>
#include <cmath>
#include <cstdint>
#define _USE_MATH_DEFINES

#include "rational_num.h"

// https://en.wikipedia.org/wiki/Complex_number
class ComplexNumber {
  RationalNumber<double> real;
  RationalNumber<double> imag;

 public:
  ComplexNumber(double num = 0) {
    this->real = RationalNumber<double>(num);
    this->imag = 0;
  }

  explicit ComplexNumber(RationalNumber<double> real,
                         RationalNumber<double> imag) {
    this->real = real;
    this->imag = imag;
  }

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
    return os << "(" << num.real << "," << num.imag << ")";
  }

  RationalNumber<double> Arg() const {
    // tan(angle) = b / a
    // need to return angle in radians
    auto result = this->real == 0 && this->imag == 0 ? 0 : atan(
        this->imag.toDouble() / this->real.toDouble());

    return this->real < 0 ? (
        this->imag < 0 ? result - M_PI : result + M_PI) : result;
  }

  RationalNumber<double> Abs() const {
    // z = a + bi, i^2 = -1
    // |z| = sqrt(sqr(real) + sqr(imag)) or |z| = sqrt(sqr(a) + sqr(b))
    // need to return |z|
    return (this->real * this->real + this->imag * this->imag).Sqrt();
  }

  ComplexNumber Pow(int exp = 2) {
    auto real = this->real;
    auto imag = this->imag;
    ComplexNumber a(real, imag);
    for (int i = 1; i < exp; i++) {
      a *= ComplexNumber(real, imag);
    }
    return a;
  }

  RationalNumber<double> getReal() const {
    return this->real;
  }

  void setReal(double s_real) {
    this->real = s_real;
  }

  RationalNumber<double> getImag() const {
    return this->imag;
  }

  void setImag(double s_imag) {
    this->imag = s_imag;
  }
};
