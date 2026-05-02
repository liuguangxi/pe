#include "pe_test.h"

namespace fraction_test {

SL void FractionArithmeticTest() {
  using F = Fraction<int64>;

  // Constructor auto-reduces: 4/6 -> 2/3
  {
    F a(4, 6);
    assert(a.a == 2 && a.b == 3);
  }

  // Negative denominator normalised: 1/-3 -> -1/3
  {
    F b(1, -3);
    assert(b.a == -1 && b.b == 3);
  }

  // Both negative: -4/-6 -> 2/3
  {
    F c(-4, -6);
    assert(c.a == 2 && c.b == 3);
  }

  // Zero numerator: 0/5 -> 0/1
  {
    F d(0, 5);
    assert(d.a == 0 && d.b == 1);
  }

  // Addition: 1/2 + 1/3 = 5/6
  {
    F r = F(1, 2) + F(1, 3);
    assert(r.a == 5 && r.b == 6);
  }

  // Subtraction: 3/4 - 1/4 = 1/2
  {
    F r = F(3, 4) - F(1, 4);
    assert(r.a == 1 && r.b == 2);
  }

  // Multiplication with reduction: 2/3 * 3/4 = 1/2
  {
    F r = F(2, 3) * F(3, 4);
    assert(r.a == 1 && r.b == 2);
  }

  // Division: (1/2) / (3/4) = 2/3
  {
    F r = F(1, 2) / F(3, 4);
    assert(r.a == 2 && r.b == 3);
  }

  // Mixed scalar: 1/2 + 1 = 3/2
  {
    assert((F(1, 2) + 1).a == 3);
    assert((1 + F(1, 2)).a == 3);
    assert((F(3, 2) - 1).a == 1);
    assert((2 - F(1, 2)).a == 3);
    assert((F(1, 2) * 2).a == 1);
    assert((2 * F(1, 2)).a == 1);
    assert((F(3, 2) / 3).a == 1);
  }

  // Comparisons
  assert(F(1, 2) < F(2, 3));
  assert(F(2, 3) > F(1, 2));
  assert(F(1, 2) == F(2, 4));
  assert(F(1, 3) != F(1, 2));
  assert(F(1, 2) <= F(1, 2));
  assert(F(1, 2) >= F(1, 2));
  assert(F(1, 3) <= F(2, 3));
  assert(F(2, 3) >= F(1, 3));

  // Unary negation: -(1/3) = -1/3
  {
    F r = -F(1, 3);
    assert(r.a == -1 && r.b == 3);
  }

  // Unary plus is identity
  {
    F r = +F(1, 3);
    assert(r.a == 1 && r.b == 3);
  }

  // Compound assignment
  {
    F x(1, 6);
    x += F(1, 6);
    assert(x.a == 1 && x.b == 3);
    x -= F(1, 6);
    assert(x.a == 1 && x.b == 6);
    x *= F(2, 1);
    assert(x.a == 1 && x.b == 3);
    x /= F(2, 1);
    assert(x.a == 1 && x.b == 6);
  }

  // Accumulate harmonic series: sum 1/i for i=1..10 = 7381/2520
  {
    F sum;
    for (int i = 1; i <= 10; ++i) sum += F(1, i);
    assert(sum.a == 7381 && sum.b == 2520);
  }
}

PE_REGISTER_TEST(&FractionArithmeticTest, "FractionArithmeticTest", SMALL);

SL void FractionIncrDecrTest() {
  using F = Fraction<int64>;
  F x(3, 4);

  F& ref = ++x;
  assert(x.a == 7 && x.b == 4);
  assert(&ref == &x);

  F old = x++;
  assert(old.a == 7 && old.b == 4);
  assert(x.a == 11 && x.b == 4);

  --x;
  assert(x.a == 7 && x.b == 4);

  old = x--;
  assert(old.a == 7 && old.b == 4);
  assert(x.a == 3 && x.b == 4);
}

PE_REGISTER_TEST(&FractionIncrDecrTest, "FractionIncrDecrTest", SMALL);

SL void FractionToDoubleTest() {
  using F = Fraction<int64>;

  assert(std::abs(F(1, 4).ToDouble() - 0.25) < 1e-15);
  assert(std::abs(F(1, 3).ToDouble() - 1.0 / 3.0) < 1e-14);
  assert(std::abs(F(22, 7).ToDouble() - 22.0 / 7.0) < 1e-14);
  assert(std::abs(F(-1, 2).ToDouble() - (-0.5)) < 1e-15);
  assert(std::abs(F(1, 4).ToLongDouble() - 0.25L) < 1e-18L);
}

PE_REGISTER_TEST(&FractionToDoubleTest, "FractionToDoubleTest", SMALL);

}  // namespace fraction_test
