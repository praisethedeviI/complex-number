#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <cstdint>
#include <complex>
#include <cassert>
#include <random>

#include "complex_num.h"

#define CATCH_CONFIG_MAIN
#include "catch.hpp"
// https://github.com/catchorg/Catch2/

using namespace std;
using namespace std::complex_literals;
using namespace Catch::literals;

TEST_CASE("complex number unit test") {
  SECTION("getter & setter") {
    ComplexNumber a(2, 4);
    SECTION("Get 2 and 4") {
      REQUIRE(a.getReal() == 2_a);
      REQUIRE(a.getImag() == 4_a);
    }
    SECTION("int") {
      int z = 100;
      a.setReal(z);
      a.setImag(2000);
      REQUIRE(a.getReal() == Approx(z));
      REQUIRE(a.getImag() == 2000_a);
      z = 200;
      REQUIRE_FALSE(a.getReal() == Approx(z));
      REQUIRE(a.getReal() != Approx(z));
      ComplexNumber b = z;
      REQUIRE(b.getReal() == Approx(z));
      REQUIRE(b.getImag() == 0_a);
    }
    SECTION("double") {
      double z = 100.01;
      a.setReal(z);
      a.setImag(101.00000001);
      REQUIRE(a.getReal() == Approx(z));
      REQUIRE(a.getImag() == 101.00000001_a);
      ComplexNumber b = z;
      REQUIRE(b.getReal() == Approx(z));
      REQUIRE(b.getImag() == 0_a);
    }
    SECTION("float & double_t") {
      double_t z = 100.000002;
      float x = -203.00005;
      a.setReal(z);
      a.setImag(x);
      REQUIRE(a.getReal() == Approx(z));
      REQUIRE(a.getImag() == Approx(x));
      ComplexNumber b = z;
      ComplexNumber c = x;
      REQUIRE(b.getReal() == Approx(z));
      REQUIRE(b.getImag() == 0_a);
      REQUIRE(c.getReal() == Approx(x));
      REQUIRE(c.getImag() == 0_a);
    }
  }
  SECTION("unary minus") {
    ComplexNumber a(11, 23);
    complex<double> z = 11. + 23i;
    REQUIRE(a.getReal() == Approx(z.real()));
    REQUIRE(a.getImag() == Approx(z.imag()));

    ComplexNumber b = -a;
    auto x = -z;
    REQUIRE(b.getReal() == Approx(x.real()));
    REQUIRE(b.getImag() == Approx(x.imag()));
  }
  SECTION("operator+ & operator-") {
    SECTION("First") {
      ComplexNumber a(5, 2), b(7, 1);
      ComplexNumber c = a + b;
      ComplexNumber d = a - b;
      REQUIRE(c.getReal() == 12_a);
      REQUIRE(c.getImag() == 3_a);
      REQUIRE(d.getReal() == -2_a);
      REQUIRE(d.getImag() == 1_a);
      REQUIRE(a.getReal() == 5_a);
      REQUIRE(a.getImag() == 2_a);
      REQUIRE(b.getReal() == 7_a);
      REQUIRE(b.getImag() == 1_a);
    }
    SECTION("Second") {
      ComplexNumber a = 3;
      ComplexNumber b(0, 5), c(2.3, -6);
      ComplexNumber d = a + b;
      REQUIRE(d.getReal() == 3_a);
      REQUIRE(d.getImag() == 5_a);
      d = a - b;
      REQUIRE(d.getReal() == 3_a);
      REQUIRE(d.getImag() == -5_a);
      d = a + c;
      REQUIRE(d.getReal() == 5.3_a);
      REQUIRE(d.getImag() == -6_a);
      d = a - c;
      REQUIRE(d.getReal() == 0.7_a);
      REQUIRE(d.getImag() == 6_a);
      d = b + c;
      REQUIRE(d.getReal() == 2.3_a);
      REQUIRE(d.getImag() == -1_a);
      d = b - c;
      REQUIRE(d.getReal() == -2.3_a);
      REQUIRE(d.getImag() == 11_a);
    }
    SECTION("With int & double") {
      ComplexNumber a(5, 2);
      int b = 2;
      double c = 3.3;
      ComplexNumber d = a + b;
      REQUIRE(d.getReal() == 7_a);
      REQUIRE(d.getImag() == 2_a);
      d = a - b;
      REQUIRE(d.getReal() == 3_a);
      REQUIRE(d.getImag() == 2_a);
      d = a + c;
      REQUIRE(d.getReal() == 8.3_a);
      REQUIRE(d.getImag() == 2_a);
      d = a - c;
      REQUIRE(d.getReal() == 1.7_a);
      REQUIRE(d.getImag() == 2_a);
    }
  }
  SECTION("operator* & operator/") {
    SECTION("operator*") {
      ComplexNumber a(2, -3), b(12.5, 2);
      ComplexNumber c = a * b;
      ComplexNumber d = b * a;
      REQUIRE(c.getReal() == Approx(d.getReal()));
      REQUIRE(c.getImag() == Approx(d.getImag()));
      REQUIRE(c == d);
      REQUIRE_FALSE(c != d);
      complex<double> z = (2. - 3i) * (12.5 + 2i);
      REQUIRE(c.getReal() == Approx(z.real()));
      REQUIRE(c.getImag() == Approx(z.imag()));
    }
    SECTION("operator/") {
      ComplexNumber a(3.3, 6), b(-5, 1);
      ComplexNumber c = a / b;
      complex<double> z = (3.3 + 6i) / (-5. + 1i);
      REQUIRE(c.getReal() == Approx(z.real()));
      REQUIRE(c.getImag() == Approx(z.imag()));
    }
    SECTION("With int & double") {
      ComplexNumber a(23.32432, 12.2332);
      int b = 6;
      double c = 12.23;
      ComplexNumber d = a * b;
      complex<double> z = (23.32432 + 12.2332i) * (double)b;
      REQUIRE(d.getReal() == Approx(z.real()));
      REQUIRE(d.getImag() == Approx(z.imag()));
      d = a / b;
      z = (23.32432 + 12.2332i) / (double)b;
      REQUIRE(d.getReal() == Approx(z.real()));
      REQUIRE(d.getImag() == Approx(z.imag()));
      d = a * c;
      z = (23.32432 + 12.2332i) * c;
      REQUIRE(d.getReal() == Approx(z.real()));
      REQUIRE(d.getImag() == Approx(z.imag()));
      d = a / c;
      z = (23.32432 + 12.2332i) / c;
      REQUIRE(d.getReal() == Approx(z.real()));
      REQUIRE(d.getImag() == Approx(z.imag()));
    }
  }
  SECTION ("operator+= & operator-=") {
    SECTION("First") {
      ComplexNumber a(1, 1), b(2, 2);
      ComplexNumber c = a + b;
      a += b;
      REQUIRE(a == c);
      REQUIRE_FALSE(a != c);
      a.setReal(1);
      a.setImag(1);
      c = a - b;
      a -= b;
      REQUIRE(a == c);
      REQUIRE_FALSE(a != c);
    }
    SECTION("Second") {
      ComplexNumber a(23.2, 12.2), b(-12, 2.23);
      ComplexNumber c = a + b;
      a += b;
      REQUIRE(a == c);
      REQUIRE_FALSE(a != c);
      a.setReal(23.2);
      a.setImag(12.2);
      c = a - b;
      a -= b;
      REQUIRE(a == c);
      REQUIRE_FALSE(a != c);
    }
    SECTION("With int & double") {
      ComplexNumber a(42, -4.2);
      int b = 2;
      double c = -4.4;
      ComplexNumber d = a + b;
      a += b;
      REQUIRE(a == d);
      d = a - c;
      a -= c;
      REQUIRE(a == d);
      d = a - b;
      a -= b;
      REQUIRE(a == d);
      d = a + c;
      a += c;
      REQUIRE(a == d);
    }
  }
  SECTION("operator*= & operator/=") {
    SECTION("First") {
      ComplexNumber a(2, 2), b(3.2, -4);
      ComplexNumber c = a * b;
      a *= b;
      REQUIRE(a == c);
      a.setReal(2);
      a.setImag(2);
      c = a / b;
      a /= b;
      REQUIRE(a == c);
      c = b / a;
      b /= a;
      REQUIRE(c == b);
    }
    SECTION("Second") {
      ComplexNumber a(-232.3433333, 2.2222333);
      ComplexNumber b(0.33, -23.3333);
      ComplexNumber c = a * b;
      a *= b;
      REQUIRE(a == c);
      a.setReal(-232.3433333);
      a.setImag(2.2222333);
      c = a / b;
      a /= b;
      REQUIRE(a == c);
      c = b / a;
      b /= a;
      REQUIRE(c == b);
    }
    SECTION("With int & double") {
      ComplexNumber a(-0.25, 0.25);
      int b = 5;
      double c = 25.25252525;
      ComplexNumber d = a * b;
      a *= b;
      REQUIRE(a == d);
      a = ComplexNumber(-0.25, 0.25);
      d = a / b;
      a /= b;
      REQUIRE(a == d);
      a = ComplexNumber(-0.25, 0.25);
      d = a * c;
      a *= c;
      REQUIRE(a == d);
      a = ComplexNumber(-0.25, 0.25);
      d = a / c;
      a /= c;
      REQUIRE(a == d);
    }
  }
  SECTION("arg, abs, pow, ostream") {
    SECTION("arg") {
        ComplexNumber a(233.222, -232.2223);
        complex<double> z = 233.222 - 232.2223i;
        REQUIRE(a.Arg() == Approx(arg(z)));
        a = ComplexNumber(0, 21.2);
        z = 21.2i;
        REQUIRE(a.Arg() == Approx(arg(z)));
        a = ComplexNumber(-2, 2);
        z = -2. + 2i;
        REQUIRE(a.Arg() == Approx(arg(z)));
        a = ComplexNumber(-2, -2);
        z = -2. - 2i;
        REQUIRE(a.Arg() == Approx(arg(z)));
        a = 0;
        z = 0i;
        REQUIRE(a.Arg() == Approx(arg(z)));
    }
    SECTION("abs") {
      ComplexNumber a(3.3333333, -3.33333333);
      complex<double> z = 3.3333333 -3.33333333i;
      REQUIRE(a.Abs() == Approx(abs(z)));
      a = ComplexNumber(-2, 4);
      z = -2. + 4i;
      REQUIRE(a.Abs() == Approx(abs(z)));
      a = ComplexNumber(-4, -6.666666);
      z = -4. - 6.666666i;
      REQUIRE(a.Abs() == Approx(abs(z)));
      a = 0;
      z = 0i;
      REQUIRE(a.Abs() == Approx(abs(z)));
    }
    SECTION("pow") {
      ComplexNumber a(3.333333, 3.333333);
      complex<double> z = 3.333333 + 3.333333i;
      int power = 3;
      a = a.Pow(power);
      z = pow(z, power);
      REQUIRE(a.getReal() == Approx(z.real()));
      REQUIRE(a.getImag() == Approx(z.imag()));
      a = ComplexNumber(-3, -5);
      z = -3. - 5i;
      power = 2;
      a = a.Pow(power);
      z = pow(z, power);
      REQUIRE(a.getReal() == Approx(z.real()));
      REQUIRE(a.getImag() == Approx(z.imag()));
      a = ComplexNumber(-10, 5.344);
      z = -10. + 5.344i;
      power = 9;
      a = a.Pow(power);
      z = pow(z, power);
      REQUIRE(a.getReal() == Approx(z.real()));
      REQUIRE(a.getImag() == Approx(z.imag()));
    }
    SECTION("ostream") {
      ComplexNumber a(233, 333.333);
      complex<double> z = 233. + 333.333i;
      cout << " ComplexNumber " << a << "   std::complex " << z << endl;
      ComplexNumber b;
      z = 0i;
      cout << " ComplexNumber " << b << "   std::complex " << z  << endl;
      ComplexNumber c = 3;
      z = 3.;
      cout << " ComplexNumber " << c << "   std::complex " << z  << endl;
      ComplexNumber d = 4.3333;
      z = 4.3333;
      cout << " ComplexNumber " << d << "   std::complex " << z  << endl;
      ComplexNumber e = a;
      e.setReal(-222222222222);
      z = -222222222222. + 333.333i;
      cout << " ComplexNumber " << e << "   std::complex " << z  << endl;
    }
  }
}



