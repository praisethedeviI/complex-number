#include <algorithm>
#include <cmath>
#include <iostream>
#include <cmath>
#include <cstdint>
#define _USE_MATH_DEFINES
#define EPSILON_VALUE 0.000000001


// https://en.wikipedia.org/wiki/Complex_number
class ComplexNumber {
  double real;
  double imag;

  static bool comparator(double A, double B) {
    return (std::fabs(A - B) < EPSILON_VALUE);
  }

 public:
  ComplexNumber(double num = 0) {
    this->real = num;
    this->imag = 0;
  }

  explicit ComplexNumber(double real, double imag) {
    this->real = real;
    this->imag = imag;
  }

  ComplexNumber operator+(const ComplexNumber &other) const {
    // (a + bi) + (c + di) = (a + c) + (b + d)i
    auto r_real = this->real + other.real;
    auto r_imag = this->imag + other.imag;
    return ComplexNumber(r_real, r_imag);
  }

  ComplexNumber operator+(int num) const {
    return operator+(ComplexNumber(num));
  }

  ComplexNumber operator+(double num) const {
    return operator+(ComplexNumber(num));
  }

  ComplexNumber operator-(const ComplexNumber &other) const {
    // (a + bi) - (c + di) = (a - c) + (b - d)i
    auto r_real = this->real - other.real;
    auto r_imag = this->imag - other.imag;
    return ComplexNumber(r_real, r_imag);
  }

  ComplexNumber operator-(int num) const {
    return operator-(ComplexNumber(num));
  }

  ComplexNumber operator-(double num) const {
    return operator-(ComplexNumber(num));
  }

  ComplexNumber operator*(const ComplexNumber &other) const {
    // (a + bi) * (c + di) = ac + bci + adi + bdi^2 =
    // = (ac + bdi^2) + (bc + ad) = (ac - bd) + (bc + ad)i
    auto r_real = this->real * other.real - this->imag * other.imag;
    auto r_imag = this->imag * other.real + this->real * other.imag;
    return ComplexNumber(r_real, r_imag);
  }

  ComplexNumber operator*(int num) const {
    return operator*(ComplexNumber(num));
  }

  ComplexNumber operator*(double num) const {
    return operator*(ComplexNumber(num));
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

  ComplexNumber operator/(int num) const {
    return operator/(ComplexNumber(num, 0));
  }

  ComplexNumber operator/(double num) const {
    return operator/(ComplexNumber(num, 0));
  }

  ComplexNumber &operator+=(const ComplexNumber &other) {
    // (a + bi) + (c + di) = (a + c) + (b + d)i
    this->real += other.real;
    this->imag += other.imag;
    return *this;
  }

  ComplexNumber &operator+=(int num) {
    return operator+=(ComplexNumber(num, 0));
  }

  ComplexNumber &operator+=(double num) {
    return operator+=(ComplexNumber(num, 0));
  }

  ComplexNumber &operator-=(const ComplexNumber &other) {
    // (a + bi) - (c + di) = (a - c) + (b - d)i
    this->real -= other.real;
    this->imag -= other.imag;
    return *this;
  }

  ComplexNumber &operator-=(int num) {
    return operator-=(ComplexNumber(num, 0));
  }

  ComplexNumber &operator-=(double num) {
    return operator-=(ComplexNumber(num, 0));
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

  ComplexNumber &operator*=(int num) {
    return operator*=(ComplexNumber(num, 0));
  }

  ComplexNumber &operator*=(double num) {
    return operator*=(ComplexNumber(num, 0));
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

  ComplexNumber &operator/=(int num) {
    return operator/=(ComplexNumber(num, 0));
  }

  ComplexNumber &operator/=(double num) {
    return operator/=(ComplexNumber(num, 0));
  }

  ComplexNumber operator-() const {
    auto r_real = -this->real;
    auto r_imag = -this->imag;
    return ComplexNumber(r_real, r_imag);
  }

  bool operator==(const ComplexNumber &other) const {
    return comparator(this->real, other.real)
        && comparator(this->imag, other.imag);
  }

  bool operator!=(const ComplexNumber &other) const {
    return !comparator(this->real, other.real) || !comparator(this->imag,
                                                              other.imag);
  }

  friend std::ostream &operator<<(std::ostream &os, const ComplexNumber &num) {
    return os << "(" << num.real << "," << num.imag << ")";
  }

  double Arg() const {
    // tan(angle) = b / a
    // need to return angle in radians
    auto result = this->real == 0 && this->imag == 0 ? 0 : atan(
        this->imag / this->real);

    return this->real < 0 ? (
        this->imag < 0 ? result - M_PI : result + M_PI) : result;
  }

  double Abs() const {
    // z = a + bi, i^2 = -1
    // |z| = sqrt(sqr(real) + sqr(imag)) or |z| = sqrt(sqr(a) + sqr(b))
    // need to return |z|
    return sqrt(this->real * this->real + this->imag * this->imag);
  }

  ComplexNumber Pow(unsigned int exp = 2) {
    auto real = this->real;
    auto imag = this->imag;
    for (unsigned int i = 1; i < exp; i++) {
      this->operator*=(ComplexNumber(real, imag));
    }
    return *this;
  }

  double getReal() const {
    return this->real;
  }

  void setReal(double s_real) {
    this->real = s_real;
  }

  double getImag() const {
    return this->imag;
  }

  void setImag(double s_imag) {
    this->imag = s_imag;
  }
};
