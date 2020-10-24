#include <iostream>
#include <cstdint>
#include <complex>

#include "complex_num.h"

// https://github.com/catchorg/Catch2/
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

using namespace std;
using namespace std::complex_literals;
using namespace Catch::literals;

TEST_CASE("rational number unit test") {
  SECTION("getter") {
    RationalNumber<int64_t> a = {20, 10};
    REQUIRE(a.GetNumer() == 2);
    REQUIRE(a.GetDenom() == 1);
    a = RationalNumber<int64_t>(50);
    REQUIRE(a.GetNumer() == 50);
    REQUIRE(a.GetDenom() == 1);
    a = RationalNumber<int64_t>(53, -3);
    REQUIRE(a.GetNumer() == -53);
    REQUIRE(a.GetDenom() == 3);
    a = {-43, -5};
    REQUIRE(a.GetNumer() == 43);
    REQUIRE(a.GetDenom() == 5);

  }SECTION("unary minus") {
    RationalNumber<int64_t> a = {20, 21}, b = -a;
    REQUIRE(b.GetNumer() == -20);
    REQUIRE(b.GetDenom() == 21);
    a = {-54}, b = -a;
    REQUIRE(b.GetNumer() == 54);
    REQUIRE(b.GetDenom() == 1);
    a = {}, b = -a;
    REQUIRE(b.GetNumer() == 0);
    REQUIRE(b.GetDenom() == 1);

  }SECTION("operator+ & operator-") {
    SECTION("First") {
      RationalNumber<int64_t> a = {3, 2}, b = {2, 3};
      auto c = a + b;
      REQUIRE(c.GetNumer() == 13);
      REQUIRE(c.GetDenom() == 6);
      c = a - b;
      REQUIRE(c.GetNumer() == 5);
      REQUIRE(c.GetDenom() == 6);
      a = {10, 4}, b = {15, 10};
      c = a + b;
      REQUIRE(c.GetNumer() == 4);
      REQUIRE(c.GetDenom() == 1);
      c = a - b;
      REQUIRE(c.GetNumer() == 1);
      REQUIRE(c.GetDenom() == 1);

    }SECTION("Second") {
      RationalNumber<int64_t> a = {3, 2}, b = {10}, c = {5, 2};
      auto d = a + b - c;
      REQUIRE(d.GetNumer() == 9);
      REQUIRE(d.GetDenom() == 1);
      d = a - b + c;
      REQUIRE(d.GetNumer() == -6);
      REQUIRE(d.GetDenom() == 1);
      a = {43, 2}, b = {3, 2}, c = 4;
      d = a + b + c;
      REQUIRE(d.GetNumer() == 27);
      REQUIRE(d.GetDenom() == 1);
      d = a - b - c;
      REQUIRE(d.GetNumer() == 16);
      REQUIRE(d.GetDenom() == 1);

    }
  }SECTION("operator* & operator/") {
    SECTION("First") {
      RationalNumber<int64_t> a = {5, 2}, b = {2, -7};
      auto c = a * b;
      REQUIRE(c.GetNumer() == -5);
      REQUIRE(c.GetDenom() == 7);
      c = a / b;
      REQUIRE(c.GetNumer() == -35);
      REQUIRE(c.GetDenom() == 4);
      a = {10, 4}, b = {15, 10};
      c = a * b;
      REQUIRE(c.GetNumer() == 15);
      REQUIRE(c.GetDenom() == 4);
      c = a / b;
      REQUIRE(c.GetNumer() == 5);
      REQUIRE(c.GetDenom() == 3);

    }SECTION("Second") {
      RationalNumber<int64_t> a = {4, -2}, b = 9, c = {7, 2};
      auto d = a * b / c;
      REQUIRE(d.GetNumer() == -36);
      REQUIRE(d.GetDenom() == 7);
      d = a / b * c;
      REQUIRE(d.GetNumer() == -7);
      REQUIRE(d.GetDenom() == 9);
      a = {23, 2}, b = 10, c = {4, 11};
      d = a / b / c;
      REQUIRE(d.GetNumer() == 253);
      REQUIRE(d.GetDenom() == 80);
      d = a * b * c;
      REQUIRE(d.GetNumer() == 460);
      REQUIRE(d.GetDenom() == 11);

    }
  }SECTION("operator+= & operator -=") {
    SECTION("First") {
      RationalNumber<int64_t> a = {5, 2}, b = {2, 3}, c = a;
      a += b;
      REQUIRE(a == c + b);
      a = c;
      a -= b;
      REQUIRE(a == c - b);
      a = {-19, 34}, b = 53, c = a;
      a += b;
      REQUIRE(a == c + b);
      a = c;
      a -= b;
      REQUIRE(a == c - b);

    }SECTION("Second") {
      RationalNumber<int64_t> a = {23, 54}, b = {754, 167}, c = {53}, d = a;
      a += b;
      a -= c;
      REQUIRE(a == d + b - c);
      a = d;
      a -= b;
      a += c;
      REQUIRE(a == d - b + c);
      a = {223, -474}, b = {4}, c = {54, 57}, d = a;
      a -= b;
      a -= c;
      REQUIRE(a == d - b - c);
      a = d;
      a += b;
      a += c;
      REQUIRE(a == d + b + c);
    }
  }SECTION("operator*= & operator/=") {
    SECTION("First") {
      RationalNumber<int64_t> a = {53, 65}, b = {122, 65463}, c = a;
      a *= b;
      REQUIRE(a == c * b);
      a = c;
      a /= b;
      REQUIRE(a == c / b);
      a = {-19, -34}, b = {5553}, c = a;
      a *= b;
      REQUIRE(a == c * b);
      a = c;
      a /= b;
      REQUIRE(a == c / b);
    }SECTION("Second") {
      RationalNumber<int64_t> a = {23, 54}, b = {754, 167}, c = {53}, d = a;
      a *= b;
      a /= c;
      REQUIRE(a == d * b / c);
      a = d;
      a /= b;
      a *= c;
      REQUIRE(a == d / b * c);
      a = {223, -474}, b = {4}, c = {54, 57}, d = a;
      a /= b;
      a /= c;
      REQUIRE(a == d / b / c);
      a = d;
      a *= b;
      a *= c;
      REQUIRE(a == d * b * c);
    }
  }SECTION("Complex expressions") {
    RationalNumber<int64_t> a, b = {3, 5}, c = {4}, d = {43, 5}, e = {7},
        f = {4, 2}, g = {20, 4};
    a = b + c - d * e - f / g;
    REQUIRE(a.GetNumer() == -56);
    REQUIRE(a.GetDenom() == 1);
    a += (g - c) * d * e / b + f;
    REQUIRE(a.GetNumer() == 139);
    REQUIRE(a.GetDenom() == 3);
    a *= (c + d) * e / (g - b + f);
    REQUIRE(a.GetNumer() == 20433);
    REQUIRE(a.GetDenom() == 32);

  }SECTION("Comparison") {
    SECTION("First") {
      RationalNumber<int64_t> a = {23, 22}, b = {23, 21};
      REQUIRE_FALSE(a == b);
      REQUIRE(a != b);
      REQUIRE(a < b);
      REQUIRE_FALSE(a > b);
      REQUIRE(a <= b);
      REQUIRE_FALSE(a >= b);
    }SECTION("Second") {
      RationalNumber<int64_t> a = {-44, -22}, b = {88, 44};
      REQUIRE(a == b);
      REQUIRE_FALSE(a != b);
      REQUIRE_FALSE(a > b);
      REQUIRE_FALSE(a < b);
      REQUIRE(a >= b);
      REQUIRE(a <= b);
    }
  }SECTION("ostream") {
    cout << endl << "SECTION ostream RationalNumber" << endl;
    RationalNumber<int64_t> a;
    cout << a << endl;
    a = {100, 20};
    cout << a << endl;
    a = {23};
    cout << a << endl;
    cout << endl;
  }
}

TEST_CASE("Complex number unit test") {
  SECTION("getter & setter") {
    RationalNumber<int64_t> z = {42, 23}, x = {5, 4};
    ComplexNumber<int64_t> a = {z, x};
    REQUIRE(a.getReal() == z);
    REQUIRE(a.getImag() == x);
    REQUIRE(a.getReal().toDouble() == Approx(z.toDouble()));
    a.setReal({23, 3});
    a.setImag(34);
    REQUIRE(a.getReal() == RationalNumber<int64_t>(23, 3));
    REQUIRE(a.getImag() == RationalNumber<int64_t>(34));
    REQUIRE(a.getReal().toDouble() == Approx((double) 23 / 3));
    a.setReal({50, 5});
    a.setImag(RationalNumber<int64_t>());
    REQUIRE(a.getReal() == RationalNumber<int64_t>(50, 5));
    REQUIRE(a.getImag() == RationalNumber<int64_t>());

  }SECTION("unary minus") {
    RationalNumber<int64_t> n1 = {43, 3}, n2 = {23, -3};
    ComplexNumber<int64_t> a = {n1, n2};
    auto b = -a;
    complex<double> z(n1.toDouble(), n2.toDouble());
    auto x = -z;
    REQUIRE(a.getReal().toDouble() == Approx(z.real()));
    REQUIRE(a.getImag().toDouble() == Approx(z.imag()));
    REQUIRE(b.getReal().toDouble() == Approx(x.real()));
    REQUIRE(b.getImag().toDouble() == Approx(x.imag()));

  }SECTION("operator+ & operator-") {
    SECTION("First") {
      RationalNumber<int64_t> n1 = {43, 3}, n2 = {23, -3};
      RationalNumber<int64_t> n3 = {53, 2}, n4 = {4, 34};
      ComplexNumber<int64_t> a = {n1, n2}, b = {n3, n4};
      complex<double> z(n1.toDouble(), n2.toDouble()),
          x(n3.toDouble(), n4.toDouble());
      auto c = a + b;
      auto y = z + x;
      REQUIRE(c.getReal().toDouble() == Approx(y.real()));
      REQUIRE(c.getImag().toDouble() == Approx(y.imag()));
      c = a - b;
      y = z - x;
      REQUIRE(c.getReal().toDouble() == Approx(y.real()));
      REQUIRE(c.getImag().toDouble() == Approx(y.imag()));

    }SECTION("Second") {
      RationalNumber<int64_t> n1 = {5477, -3777}, n2 = {-2, 33};
      RationalNumber<int64_t> n3 = {53333, 24}, n4 = {-46, -354};
      ComplexNumber<int64_t> a = {n1, n2}, b = {n3, n4};
      complex<double> z(n1.toDouble(), n2.toDouble()),
          x(n3.toDouble(), n4.toDouble());
      auto c = a + b + a + a;
      auto y = z + x + z + z;
      REQUIRE(c.getReal().toDouble() == Approx(y.real()));
      REQUIRE(c.getImag().toDouble() == Approx(y.imag()));
      c = a - b - b - b;
      y = z - x - x - x;
      REQUIRE(c.getReal().toDouble() == Approx(y.real()));
      REQUIRE(c.getImag().toDouble() == Approx(y.imag()));

    }
  }SECTION("operator* & operator/") {
    SECTION("First") {
      RationalNumber<int64_t> n1 = {-432, -35}, n2 = {3, 2};
      RationalNumber<int64_t> n3 = {553, -8}, n4 = {8, 7};
      ComplexNumber<int64_t> a = {n1, n2}, b = {n3, n4};
      complex<double> z(n1.toDouble(), n2.toDouble()),
          x(n3.toDouble(), n4.toDouble());
      auto c = a * b;
      auto y = z * x;
      REQUIRE(c.getReal().toDouble() == Approx(y.real()));
      REQUIRE(c.getImag().toDouble() == Approx(y.imag()));
      c = a / b;
      y = z / x;
      REQUIRE(c.getReal().toDouble() == Approx(y.real()));
      REQUIRE(c.getImag().toDouble() == Approx(y.imag()));

    }SECTION("Second") {
      RationalNumber<int64_t> n1 = {-44, 3}, n2 = {23, 4};
      RationalNumber<int64_t> n3 = {3, 27}, n4 = {-74, -86};
      RationalNumber<int64_t> n5 = {5, 7}, n6 = {34, 876};
      ComplexNumber<int64_t> a = {n1, n2}, b = {n3, n4}, c = {n5, n6};
      complex<double> z(n1.toDouble(), n2.toDouble()),
          x(n3.toDouble(), n4.toDouble()), y(n5.toDouble(), n6.toDouble());
      auto d = a * b / c;
      auto w = z * x / y;
      REQUIRE(d.getReal().toDouble() == Approx(w.real()));
      REQUIRE(d.getImag().toDouble() == Approx(w.imag()));
      d = a / b * c;
      w = z / x * y;
      REQUIRE(d.getReal().toDouble() == Approx(w.real()));
      REQUIRE(d.getImag().toDouble() == Approx(w.imag()));

    }
  }SECTION ("operator+= & operator-=") {
    SECTION("First") {
      RationalNumber<int64_t> n1 = {4, -3}, n2 = {-3, -2};
      RationalNumber<int64_t> n3 = {65, -1}, n4 = {45, 5};
      ComplexNumber<int64_t> a = {n1, n2}, b = {n3, n4}, c = a;
      complex<double> z(n1.toDouble(), n2.toDouble()),
          x(n3.toDouble(), n4.toDouble()), y = z;
      a += b;
      z += x;
      REQUIRE(a.getReal().toDouble() == Approx(z.real()));
      REQUIRE(a.getImag().toDouble() == Approx(z.imag()));
      a = c;
      z = y;
      a -= b;
      z -= x;
      REQUIRE(a.getReal().toDouble() == Approx(z.real()));
      REQUIRE(a.getImag().toDouble() == Approx(z.imag()));

    }SECTION("Second") {
      RationalNumber<int64_t> n1 = {-4, 43}, n2 = {26, 9};
      RationalNumber<int64_t> n3 = {3, 27}, n4 = {-74, -856};
      RationalNumber<int64_t> n5 = {56, 73}, n6 = {-98, 876};
      ComplexNumber<int64_t> a = {n1, n2}, b = {n3, n4}, c = {n5, n6}, d = a;
      complex<double> z(n1.toDouble(), n2.toDouble()),
          x(n3.toDouble(), n4.toDouble()), y(n5.toDouble(), n6.toDouble()),
          w = z;
      a += b;
      a -= c;
      z += x;
      z -= y;
      REQUIRE(a.getReal().toDouble() == Approx(z.real()));
      REQUIRE(a.getImag().toDouble() == Approx(z.imag()));
      a = d;
      z = w;
      a -= b;
      a += c;
      z -= x;
      z += y;
      REQUIRE(a.getReal().toDouble() == Approx(z.real()));
      REQUIRE(a.getImag().toDouble() == Approx(z.imag()));

    }
  }SECTION("operator*= & operator/=") {
    SECTION("First") {
      RationalNumber<int64_t> n1 = {-2, 35}, n2 = {83, 42};
      RationalNumber<int64_t> n3 = {-53, -8}, n4 = {89, 47};
      ComplexNumber<int64_t> a = {n1, n2}, b = {n3, n4}, c = a;
      complex<double> z(n1.toDouble(), n2.toDouble()),
          x(n3.toDouble(), n4.toDouble()), y = z;
      a *= b;
      z *= x;
      REQUIRE(a.getReal().toDouble() == Approx(z.real()));
      REQUIRE(a.getImag().toDouble() == Approx(z.imag()));
      a = c;
      z = y;
      a /= b;
      z /= x;
      REQUIRE(a.getReal().toDouble() == Approx(z.real()));
      REQUIRE(a.getImag().toDouble() == Approx(z.imag()));

    }SECTION("Second") {
      RationalNumber<int64_t> n1 = {-4, 43}, n2 = {2, 9};
      RationalNumber<int64_t> n3 = {3, 27}, n4 = {-74, -8};
      RationalNumber<int64_t> n5 = {56, 73}, n6 = {-98, 8};
      ComplexNumber<int64_t> a = {n1, n2}, b = {n3, n4}, c = {n5, n6}, d = a;
      complex<double> z(n1.toDouble(), n2.toDouble()),
          x(n3.toDouble(), n4.toDouble()), y(n5.toDouble(), n6.toDouble()),
          w = z;
      a *= b;
      a /= c;
      z *= x;
      z /= y;
      REQUIRE(a.getReal().toDouble() == Approx(z.real()));
      REQUIRE(a.getImag().toDouble() == Approx(z.imag()));
      a = d;
      z = w;
      a /= b;
      a *= c;
      z /= x;
      z *= y;
      REQUIRE(a.getReal().toDouble() == Approx(z.real()));
      REQUIRE(a.getImag().toDouble() == Approx(z.imag()));

    }
  }SECTION("Complex expressions") {
    ComplexNumber<int64_t> a(23, 3), b({5, 2}, {-4, 3}), c(5, {-4, -5}),
        d({5, 3}, -4), e(5, 1), f({3, -4}, {3, -4});
    complex<double> a1(23, 3), b1((double) 5 / 2, (double) -4 / 3),
        c1(5, (double) -4 / -5), d1((double) 5 / 3, -4), e1(5, 1),
        f1((double) 3 / -4, (double) 3 / -4);
    a += b + c + d * e / f;
    a1 += b1 + c1 + d1 * e1 / f1;
    REQUIRE(a.getReal().toDouble() == Approx(a1.real()));
    REQUIRE(a.getImag().toDouble() == Approx(a1.imag()));
    a -= (b + c) * d + e / f;
    a1 -= (b1 + c1) * d1 + e1 / f1;
    REQUIRE(a.getReal().toDouble() == Approx(a1.real()));
    REQUIRE(a.getImag().toDouble() == Approx(a1.imag()));
    a *= b - c * d - e / f;
    a1 *= b1 - c1 * d1 - e1 / f1;
    REQUIRE(a.getReal().toDouble() == Approx(a1.real()));
    REQUIRE(a.getImag().toDouble() == Approx(a1.imag()));
    a /= b * c - (d - e) - f;
    a1 /= b1 * c1 - (d1 - e1) - f1;
    REQUIRE(a.getReal().toDouble() == Approx(a1.real()));
    REQUIRE(a.getImag().toDouble() == Approx(a1.imag()));
  }SECTION("Comparison") {
    ComplexNumber<int64_t> a = {{30, 15}, 4}, b = {2, {-20, -5}};
    REQUIRE(a == b);
    REQUIRE_FALSE(a != b);
    a = {{50, -20}, {5}};
    b = {{-50, -20}, {}};
    REQUIRE(a != b);
    REQUIRE_FALSE(a == b);

  }SECTION("arg, abs, pow, ostream") {
    SECTION("arg") {
      ComplexNumber<int64_t> a({23, 20}, {50, 20});
      complex<double> z(RationalNumber<int64_t>(23, 20).toDouble(),
                        RationalNumber<int64_t>(50, 20).toDouble());
      REQUIRE(a.Arg() == Approx(arg(z)));
      a = {45, -12};
      z = 45. - 12i;
      REQUIRE(a.Arg() == Approx(arg(z)));
      a = {{22, -33}, -12};
      z = complex<double>(RationalNumber<int64_t>(22, -33).toDouble(),
                          RationalNumber<int64_t>(-12).toDouble());
      REQUIRE(a.Arg() == Approx(arg(z)));

    }SECTION("abs") {
      ComplexNumber<int64_t> a({7, 32}, {65, 21});
      complex<double> z(RationalNumber<int64_t>(7, 32).toDouble(),
                        RationalNumber<int64_t>(65, 21).toDouble());
      REQUIRE(a.Abs() == Approx(abs(z)));
      a = {4, 3};
      z = 4. + 3i;
      REQUIRE(a.Abs() == Approx(abs(z)));
      a = {{-22, 434}, 5};
      z = complex<double>(RationalNumber<int64_t>(-22, 434).toDouble(),
                          RationalNumber<int64_t>(5).toDouble());
      REQUIRE(a.Abs() == Approx(abs(z)));

    }SECTION("pow") {
      ComplexNumber<int64_t> a({9, 3}, {5, 4});
      complex<double> z(RationalNumber<int64_t>(9, 3).toDouble(),
                        RationalNumber<int64_t>(5, 4).toDouble());
      auto b = a.Pow(3);
      auto x = pow(z, 3);
      REQUIRE(b.getReal().toDouble() == Approx(x.real()));
      REQUIRE(b.getImag().toDouble() == Approx(x.imag()));
      a = {4, 3};
      z = 4. + 3i;
      b = a.Pow();
      x = pow(z, 2);
      REQUIRE(b.getReal().toDouble() == Approx(x.real()));
      REQUIRE(b.getImag().toDouble() == Approx(x.imag()));
      a = {{-2, -4}, 5};
      z = complex<double>(RationalNumber<int64_t>(-2, -4).toDouble(),
                          RationalNumber<int64_t>(5).toDouble());
      b = a.Pow(5);
      x = pow(z, 5);
      REQUIRE(b.getReal().toDouble() == Approx(x.real()));
      REQUIRE(b.getImag().toDouble() == Approx(x.imag()));

    }SECTION("ostream") {
      cout << endl << "SECTION ostream ComplexNumber" << endl;
      ComplexNumber<int64_t> a;
      cout << a << endl;
      a = 45;
      cout << a << endl;
      a = {23, 3};
      cout << a << endl;
      a = {{-34, -5}, {34, 6}};
      cout << a << endl;
      a = {45, {34, -6}};
      cout << a << endl;
      cout << endl;
    }
  }
}
