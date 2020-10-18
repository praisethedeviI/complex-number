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

TEST_CASE("rational number unit test") {
  SECTION("getter & toDouble") {
    SECTION("double") {
      RationalNumber<double> a = 22.2;
      REQUIRE(a.toDouble() == Approx(22.2));
      REQUIRE(a.GetNumer() == Approx(22.2));
      REQUIRE(a.GetDenom() == Approx(1));
      a = RationalNumber<double>(10, 5);
      REQUIRE(a.toDouble() == Approx(2));
      REQUIRE(a.GetNumer() == Approx(2));
      REQUIRE(a.GetDenom() == Approx(1));
      a = RationalNumber<double>(24, -16);
      REQUIRE(a.toDouble() == Approx(-1.5));
      REQUIRE(a.GetNumer() == Approx(-3));
      REQUIRE(a.GetDenom() == Approx(2));
    }SECTION("integer") {
      RationalNumber<int> a = 30;
      REQUIRE(a.toDouble() == Approx(30));
      REQUIRE(a.GetNumer() == 30);
      REQUIRE(a.GetDenom() == 1);
      a = RationalNumber<int>(25, 15);
      REQUIRE(a.toDouble() == Approx((double) 25 / 15));
      REQUIRE(a.GetNumer() == 5);
      REQUIRE(a.GetDenom() == 3);
      a = RationalNumber<int>(10, 1);
      REQUIRE(a.toDouble() == Approx(10));
      REQUIRE(a.GetNumer() == 10);
      REQUIRE(a.GetDenom() == 1);
      a = RationalNumber<int>();
      REQUIRE(a.toDouble() == Approx(0));
      REQUIRE(a.GetNumer() == 0);
      REQUIRE(a.GetDenom() == 1);
    }
  }SECTION("unary minus, zero exception & sqrt") {
    SECTION("unary minus") {
      RationalNumber<int> a(100, 23);
      auto b = -a;
      REQUIRE(b == RationalNumber<int>(-100, 23));
      REQUIRE(b.toDouble() == Approx(-a.toDouble()));
      REQUIRE(b.GetNumer() == -100);
      REQUIRE(b.GetDenom() == 23);
      a = RationalNumber<int>(-25, -10);
      b = -a;
      REQUIRE(b == RationalNumber<int>(-25, 10));
      REQUIRE(b.toDouble() == Approx(-a.toDouble()));
      REQUIRE(b.GetNumer() == -5);
      REQUIRE(b.GetDenom() == 2);
    }SECTION("zero exception") {
      RationalNumber<int> a(100, 0);
      REQUIRE(a.toDouble() == Approx(100));
      REQUIRE(a.GetNumer() == 100);
      REQUIRE(a.GetDenom() == 1);
      RationalNumber<double> b(2.222, 0);
      REQUIRE(b.toDouble() == Approx(2.222));
      REQUIRE(b.GetNumer() == 2.222);
      REQUIRE(b.GetDenom() == 1);
    }SECTION("sqrt") {
      RationalNumber<double> a(23.2, 13.2);
      auto b = a.toDouble();
      auto c = a.Sqrt();
      REQUIRE(a.toDouble() == Approx(b));
      REQUIRE(c.toDouble() == Approx(std::sqrt(b)));
    }
  }SECTION("operator+ & operator-") {
    SECTION("First") {
      RationalNumber<int> a = 25;
      RationalNumber<int> b(25555, 55);
      auto c = a + b;
      REQUIRE(c.toDouble() == Approx(a.toDouble() + b.toDouble()));
      REQUIRE(c.GetNumer() == 5386);
      REQUIRE(c.GetDenom() == 11);
      c = a - b;
      REQUIRE(c.toDouble() == Approx(a.toDouble() - b.toDouble()));
      REQUIRE(c.GetNumer() == -4836);
      REQUIRE(c.GetDenom() == 11);
      b = -42;
      c = a + b;
      REQUIRE(c.toDouble() == Approx(a.toDouble() + b.toDouble()));
      REQUIRE(c.GetNumer() == -17);
      REQUIRE(c.GetDenom() == 1);
      c = a - b;
      REQUIRE(c.toDouble() == Approx(a.toDouble() - b.toDouble()));
      REQUIRE(c.GetNumer() == 67);
      REQUIRE(c.GetDenom() == 1);
      int d = 5;
      c = a + d;
      REQUIRE(c.toDouble() == Approx(a.toDouble() + d));
      c = a - d;
      REQUIRE(c.toDouble() == Approx(a.toDouble() - d));
    }SECTION("Second") {
      RationalNumber<double> a(20.2, 34.3), b = 23.3;
      auto c = a + b;
      REQUIRE(c.toDouble() == Approx(a.toDouble() + b.toDouble()));
      REQUIRE(c.GetNumer() / c.GetDenom() == Approx(819.39 / 34.3));
      c = a - b;
      REQUIRE(c.toDouble() == Approx(a.toDouble() - b.toDouble()));
      b = -15;
      c = a + b;
      REQUIRE(c.toDouble() == Approx(a.toDouble() + b.toDouble()));
      c = a - b;
      REQUIRE(c.toDouble() == Approx(a.toDouble() - b.toDouble()));
      double d = 5.34;
      c = a + d;
      REQUIRE(c.toDouble() == Approx(a.toDouble() + d));
      c = a - d;
      REQUIRE(c.toDouble() == Approx(a.toDouble() - d));
    }
  }SECTION("operator* & operator/") {
    SECTION("First") {
      RationalNumber<int> a(33, 22), b(22, 33);
      auto c = a * b;
      REQUIRE(c.toDouble() == Approx(a.toDouble() * b.toDouble()));
      REQUIRE(c.GetNumer() == 1);
      REQUIRE(c.GetDenom() == 1);
      c = a / b;
      REQUIRE(c.toDouble() == Approx(a.toDouble() / b.toDouble()));
      REQUIRE(c.GetNumer() == 9);
      REQUIRE(c.GetDenom() == 4);
      int d = 23;
      c = a * d;
      REQUIRE(c.toDouble() == Approx(a.toDouble() * d));
      c = a / d;
      REQUIRE(c.toDouble() == Approx(a.toDouble() / d));
    }SECTION("Second") {
      RationalNumber<double> a(33.2, 22.6), b(4, -3);
      auto c = a * b;
      REQUIRE(c.toDouble() == Approx(a.toDouble() * b.toDouble()));
      c = a / b;
      REQUIRE(c.toDouble() == Approx(a.toDouble() / b.toDouble()));
      double d = 23.23;
      c = a * d;
      REQUIRE(c.toDouble() == Approx(a.toDouble() * d));
      c = a / d;
      REQUIRE(c.toDouble() == Approx(a.toDouble() / d));
    }
  }SECTION("operator+= & operator -=") {
    SECTION("First") {
      RationalNumber<int> a(-2, 4), b = 3;
      auto c = a;
      a += b;
      REQUIRE(a.toDouble() == Approx(c.toDouble() + b.toDouble()));
      REQUIRE(a.GetNumer() == 5);
      a = c;
      a -= b;
      REQUIRE(a.toDouble() == Approx(c.toDouble() - b.toDouble()));
      int d = 5;
      a = c;
      a += d;
      REQUIRE(a.toDouble() == Approx(c.toDouble() + d));
      a = c;
      a -= d;
      REQUIRE(a.toDouble() == Approx(c.toDouble() - d));
    }SECTION("Second") {
      RationalNumber<double> a(3.3, 53.3), b = 23.3;
      auto c = a;
      a += b;
      REQUIRE(a.toDouble() == Approx(c.toDouble() + b.toDouble()));
      a = c;
      a -= b;
      REQUIRE(a.toDouble() == Approx(c.toDouble() - b.toDouble()));
      double d = 65.31;
      a = c;
      a += d;
      REQUIRE(a.toDouble() == Approx(c.toDouble() + d));
      a = c;
      a -= d;
      REQUIRE(a.toDouble() == Approx(c.toDouble() - d));
    }
  }SECTION("operator*= & operator/=") {
    SECTION("First") {
      RationalNumber<int> a(39, 75), b(42, 65);
      auto c = a;
      a *= b;
      REQUIRE(a.toDouble() == Approx(c.toDouble() * b.toDouble()));
      a = c;
      a /= b;
      REQUIRE(a.toDouble() == Approx(c.toDouble() / b.toDouble()));
      int d = 93;
      a = c;
      a *= d;
      REQUIRE(a.toDouble() == Approx(c.toDouble() * d));
      a = c;
      a /= d;
      REQUIRE(a.toDouble() == Approx(c.toDouble() / d));
    }SECTION("Second") {
      RationalNumber<double> a(75.34, 5), b(4.2, -65);
      auto c = a;
      a *= b;
      REQUIRE(a.toDouble() == Approx(c.toDouble() * b.toDouble()));
      a = c;
      a /= b;
      REQUIRE(a.toDouble() == Approx(c.toDouble() / b.toDouble()));
      double d = -463.3777;
      a = c;
      a *= d;
      REQUIRE(a.toDouble() == Approx(c.toDouble() * d));
      a = c;
      a /= d;
      REQUIRE(a.toDouble() == Approx(c.toDouble() / d));
    }
  }SECTION("Comparison") {
    SECTION("First") {
      RationalNumber<int> a(10, 5), b(10, 3);
      REQUIRE_FALSE(a == b);
      REQUIRE(a != b);
      REQUIRE_FALSE(a > b);
      REQUIRE(a < b);
      REQUIRE_FALSE(a >= b);
      REQUIRE(a <= b);
      a = b;
      REQUIRE(a == b);
      REQUIRE_FALSE(a != b);
      REQUIRE_FALSE(a > b);
      REQUIRE_FALSE(a < b);
      REQUIRE(a >= b);
      REQUIRE(a <= b);
      a = RationalNumber<int>(10, -3);
      REQUIRE_FALSE(a == b);
      REQUIRE(a != b);
      REQUIRE_FALSE(a > b);
      REQUIRE(a < b);
      REQUIRE_FALSE(a >= b);
      REQUIRE(a <= b);
    }SECTION("Second") {
      RationalNumber<double> a(23.333333, -23.33), b(23.3333, -23.33);
      REQUIRE_FALSE(a == b);
      REQUIRE(a != b);
      REQUIRE_FALSE(a > b);
      REQUIRE(a < b);
      REQUIRE_FALSE(a >= b);
      REQUIRE(a <= b);
      a = b;
      REQUIRE(a == b);
      REQUIRE_FALSE(a != b);
      REQUIRE_FALSE(a > b);
      REQUIRE_FALSE(a < b);
      REQUIRE(a >= b);
      REQUIRE(a <= b);
      a = RationalNumber<double>(53.2, 1);
      REQUIRE_FALSE(a == b);
      REQUIRE(a != b);
      REQUIRE(a > b);
      REQUIRE_FALSE(a < b);
      REQUIRE(a >= b);
      REQUIRE_FALSE(a <= b);
    }
  }

  SECTION("ostream") {
    RationalNumber<int> a(25, 5);
    cout << " RationalNumber " << a << endl;
    a = 10;
    cout << " RationalNumber " << a << endl;
    RationalNumber<double> b(233.33, 5);
    cout << " RationalNumber " << b << endl;
  }
}

TEST_CASE("complex number unit test") {
  SECTION("getter & setter") {
    ComplexNumber a(2, 4);
    SECTION("Get 2 and 4") {
      REQUIRE(a.getReal().toDouble() == 2_a);
      REQUIRE(a.getImag().toDouble() == 4_a);
    }SECTION("int") {
      int z = 100;
      a.setReal(z);
      a.setImag(2000);
      REQUIRE(a.getReal().toDouble() == Approx(z));
      REQUIRE(a.getImag().toDouble() == 2000_a);
      z = 200;
      REQUIRE_FALSE(a.getReal().toDouble() == Approx(z));
      REQUIRE(a.getReal().toDouble() != Approx(z));
      ComplexNumber b = z;
      REQUIRE(b.getReal().toDouble() == Approx(z));
      REQUIRE(b.getImag().toDouble() == 0_a);
    }SECTION("double") {
      double z = 100.01;
      a.setReal(z);
      a.setImag(101.00000001);
      REQUIRE(a.getReal().toDouble() == Approx(z));
      REQUIRE(a.getImag().toDouble() == 101.00000001_a);
      ComplexNumber b = z;
      REQUIRE(b.getReal().toDouble() == Approx(z));
      REQUIRE(b.getImag().toDouble() == 0_a);
    }SECTION("float & double_t") {
      double_t z = 100.000002;
      float x = -203.00005;
      a.setReal(z);
      a.setImag(x);
      REQUIRE(a.getReal().toDouble() == Approx(z));
      REQUIRE(a.getImag().toDouble() == Approx(x));
      ComplexNumber b = z;
      ComplexNumber c = x;
      REQUIRE(b.getReal().toDouble() == Approx(z));
      REQUIRE(b.getImag().toDouble() == 0_a);
      REQUIRE(c.getReal().toDouble() == Approx(x));
      REQUIRE(c.getImag().toDouble() == 0_a);
    }
  }SECTION("unary minus") {
    ComplexNumber a(11, 23);
    complex<double> z = 11. + 23i;
    REQUIRE(a.getReal().toDouble() == Approx(z.real()));
    REQUIRE(a.getImag().toDouble() == Approx(z.imag()));

    ComplexNumber b = -a;
    auto x = -z;
    REQUIRE(b.getReal().toDouble() == Approx(x.real()));
    REQUIRE(b.getImag().toDouble() == Approx(x.imag()));
  }SECTION("operator+ & operator-") {
    SECTION("First") {
      ComplexNumber a(5, 2), b(7, 1);
      ComplexNumber c = a + b;
      ComplexNumber d = a - b;
      REQUIRE(c.getReal().toDouble() == 12_a);
      REQUIRE(c.getImag().toDouble() == 3_a);
      REQUIRE(d.getReal().toDouble() == -2_a);
      REQUIRE(d.getImag().toDouble() == 1_a);
      REQUIRE(a.getReal().toDouble() == 5_a);
      REQUIRE(a.getImag().toDouble() == 2_a);
      REQUIRE(b.getReal().toDouble() == 7_a);
      REQUIRE(b.getImag().toDouble() == 1_a);
    }SECTION("Second") {
      ComplexNumber a = 3;
      ComplexNumber b(0, 5), c(2.3, -6);
      ComplexNumber d = a + b;
      REQUIRE(d.getReal().toDouble() == 3_a);
      REQUIRE(d.getImag().toDouble() == 5_a);
      d = a - b;
      REQUIRE(d.getReal().toDouble() == 3_a);
      REQUIRE(d.getImag().toDouble() == -5_a);
      d = a + c;
      REQUIRE(d.getReal().toDouble() == 5.3_a);
      REQUIRE(d.getImag().toDouble() == -6_a);
      d = a - c;
      REQUIRE(d.getReal().toDouble() == 0.7_a);
      REQUIRE(d.getImag().toDouble() == 6_a);
      d = b + c;
      REQUIRE(d.getReal().toDouble() == 2.3_a);
      REQUIRE(d.getImag().toDouble() == -1_a);
      d = b - c;
      REQUIRE(d.getReal().toDouble() == -2.3_a);
      REQUIRE(d.getImag().toDouble() == 11_a);
    }SECTION("With int & double") {
      ComplexNumber a(5, 2);
      int b = 2;
      double c = 3.3;
      ComplexNumber d = a + b;
      REQUIRE(d.getReal().toDouble() == 7_a);
      REQUIRE(d.getImag().toDouble() == 2_a);
      d = a - b;
      REQUIRE(d.getReal().toDouble() == 3_a);
      REQUIRE(d.getImag().toDouble() == 2_a);
      d = a + c;
      REQUIRE(d.getReal().toDouble() == 8.3_a);
      REQUIRE(d.getImag().toDouble() == 2_a);
      d = a - c;
      REQUIRE(d.getReal().toDouble() == 1.7_a);
      REQUIRE(d.getImag().toDouble() == 2_a);
    }
  }SECTION("operator* & operator/") {
    SECTION("operator*") {
      ComplexNumber a(2, -3), b(12.5, 2);
      ComplexNumber c = a * b;
      ComplexNumber d = b * a;
      REQUIRE(c.getReal().toDouble() == Approx(d.getReal().toDouble()));
      REQUIRE(c.getImag().toDouble() == Approx(d.getImag().toDouble()));
      REQUIRE(c == d);
      REQUIRE_FALSE(c != d);
      complex<double> z = (2. - 3i) * (12.5 + 2i);
      REQUIRE(c.getReal().toDouble() == Approx(z.real()));
      REQUIRE(c.getImag().toDouble() == Approx(z.imag()));
    }SECTION("operator/") {
      ComplexNumber a(3.3, 6), b(-5, 1);
      ComplexNumber c = a / b;
      complex<double> z = (3.3 + 6i) / (-5. + 1i);
      REQUIRE(c.getReal().toDouble() == Approx(z.real()));
      REQUIRE(c.getImag().toDouble() == Approx(z.imag()));
    }SECTION("With int & double") {
      ComplexNumber a(23.32432, 12.2332);
      int b = 6;
      double c = 12.23;
      ComplexNumber d = a * b;
      complex<double> z = (23.32432 + 12.2332i) * (double) b;
      REQUIRE(d.getReal().toDouble() == Approx(z.real()));
      REQUIRE(d.getImag().toDouble() == Approx(z.imag()));
      d = a / b;
      z = (23.32432 + 12.2332i) / (double) b;
      REQUIRE(d.getReal().toDouble() == Approx(z.real()));
      REQUIRE(d.getImag().toDouble() == Approx(z.imag()));
      d = a * c;
      z = (23.32432 + 12.2332i) * c;
      REQUIRE(d.getReal().toDouble() == Approx(z.real()));
      REQUIRE(d.getImag().toDouble() == Approx(z.imag()));
      d = a / c;
      z = (23.32432 + 12.2332i) / c;
      REQUIRE(d.getReal().toDouble() == Approx(z.real()));
      REQUIRE(d.getImag().toDouble() == Approx(z.imag()));
    }
  }SECTION ("operator+= & operator-=") {
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
    }SECTION("Second") {
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
    }SECTION("With int & double") {
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
  }SECTION("operator*= & operator/=") {
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
    }SECTION("Second") {
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
    }SECTION("With int & double") {
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
  }SECTION("arg, abs, pow, ostream") {
    SECTION("arg") {
      ComplexNumber a(233.222, -232.2223);
      complex<double> z = 233.222 - 232.2223i;
      REQUIRE(a.Arg().toDouble() == Approx(arg(z)));
      a = ComplexNumber(0, 21.2);
      z = 21.2i;
      REQUIRE(a.Arg().toDouble() == Approx(arg(z)));
      a = ComplexNumber(-2, 2);
      z = -2. + 2i;
      REQUIRE(a.Arg().toDouble() == Approx(arg(z)));
      a = ComplexNumber(-2, -2);
      z = -2. - 2i;
      REQUIRE(a.Arg().toDouble() == Approx(arg(z)));
      a = 0;
      z = 0i;
      REQUIRE(a.Arg().toDouble() == Approx(arg(z)));
    }SECTION("abs") {
      ComplexNumber a(3.3333333, -3.33333333);
      complex<double> z = 3.3333333 - 3.33333333i;
      REQUIRE(a.Abs().toDouble() == Approx(abs(z)));
      a = ComplexNumber(-2, 4);
      z = -2. + 4i;
      REQUIRE(a.Abs().toDouble() == Approx(abs(z)));
      a = ComplexNumber(-4, -6.666666);
      z = -4. - 6.666666i;
      REQUIRE(a.Abs().toDouble() == Approx(abs(z)));
      a = 0;
      z = 0i;
      REQUIRE(a.Abs().toDouble() == Approx(abs(z)));
    }SECTION("pow") {
      ComplexNumber a(3.333333, 3.333333);
      complex<double> z = 3.333333 + 3.333333i;
      int power = 3;
      a = a.Pow(power);
      z = pow(z, power);
      REQUIRE(a.getReal().toDouble() == Approx(z.real()));
      REQUIRE(a.getImag().toDouble() == Approx(z.imag()));
      a = ComplexNumber(-3, -5);
      z = -3. - 5i;
      power = 2;
      a = a.Pow(power);
      z = pow(z, power);
      REQUIRE(a.getReal().toDouble() == Approx(z.real()));
      REQUIRE(a.getImag().toDouble() == Approx(z.imag()));
      a = ComplexNumber(-10, 5.344);
      z = -10. + 5.344i;
      power = 9;
      a = a.Pow(power);
      z = pow(z, power);
      REQUIRE(a.getReal().toDouble() == Approx(z.real()));
      REQUIRE(a.getImag().toDouble() == Approx(z.imag()));
      a = ComplexNumber(3, 5);
      auto b = a.Pow();
      REQUIRE(a.getReal().toDouble() == Approx(3));
      REQUIRE(a.getImag().toDouble() == Approx(5));
    }SECTION("ostream") {
      ComplexNumber a(233, 333.333);
      complex<double> z = 233. + 333.333i;
      cout << " ComplexNumber " << a << "   std::complex " << z << endl;
      ComplexNumber b;
      z = 0i;
      cout << " ComplexNumber " << b << "   std::complex " << z << endl;
      ComplexNumber c = 3;
      z = 3.;
      cout << " ComplexNumber " << c << "   std::complex " << z << endl;
      ComplexNumber d = 4.3333;
      z = 4.3333;
      cout << " ComplexNumber " << d << "   std::complex " << z << endl;
      ComplexNumber e = a;
      e.setReal(-222222222222);
      z = -222222222222. + 333.333i;
      cout << " ComplexNumber " << e << "   std::complex " << z << endl;
    }
  }
}
