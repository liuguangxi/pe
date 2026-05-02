#include "pe_test.h"

namespace int_algo_test {

SL void ContinuedFractionTest() {
  // 3/2 = [1; 2]
  {
    auto cf = ToContinuedFraction<int64>(int64(3), int64(2));
    assert(std::size(cf) == 2 && cf[0] == 1 && cf[1] == 2);
    auto f = FromContinuedFraction<int64>(cf);
    assert(f.a == 3 && f.b == 2);
  }

  // 22/7 = [3; 7]
  {
    auto cf = ToContinuedFraction<int64>(int64(22), int64(7));
    assert(std::size(cf) == 2 && cf[0] == 3 && cf[1] == 7);
    auto f = FromContinuedFraction<int64>(cf);
    assert(f.a == 22 && f.b == 7);
  }

  // Integer: 5/1 = [5]
  {
    auto cf = ToContinuedFraction<int64>(int64(5), int64(1));
    assert(std::size(cf) == 1 && cf[0] == 5);
    auto f = FromContinuedFraction<int64>(cf);
    assert(f.a == 5 && f.b == 1);
  }

  // Convergents of [1; 1, 1, 1, ...] are consecutive Fibonacci ratios
  // h_k / k_k: 1/1, 2/1, 3/2, 5/3, 8/5, 13/8, 21/13, 34/21, 55/34, 89/55
  {
    std::vector<int64> cf(10, int64(1));
    auto convs = FromContinuedFractionN<int64>(cf);
    const int64 fib_num[] = {1, 2, 3, 5, 8, 13, 21, 34, 55, 89};
    const int64 fib_den[] = {1, 1, 2, 3, 5, 8, 13, 21, 34, 55};
    for (int i = 0; i < 10; ++i) {
      assert(convs[i].a == fib_num[i]);
      assert(convs[i].b == fib_den[i]);
    }
    // FromContinuedFractionN with pos parameter
    auto convs5 = FromContinuedFractionN<int64>(cf, 4);
    assert(std::size(convs5) == 5);
    assert(convs5.back().a == fib_num[4] && convs5.back().b == fib_den[4]);
  }

  // Round-trip: p/q -> ToCf -> FromCf -> p/q for random fractions
  srand(42);
  for (int iter = 0; iter < 200; ++iter) {
    int64 p = rand() % 999 + 1;
    int64 q = rand() % 999 + 1;
    int64 g = Gcd(p, q);
    p /= g;
    q /= g;
    auto cf = ToContinuedFraction<int64>(p, q);
    auto frac = FromContinuedFraction<int64>(cf);
    assert(frac.a == p && frac.b == q);
  }

  // ToCf with truncation limit n
  {
    // 355/113 truncated to first 3 terms
    auto cf3 = ToContinuedFraction<int64>(int64(355), int64(113), 3);
    assert(std::size(cf3) == 3);
    assert(cf3[0] == 3);
  }
}

PE_REGISTER_TEST(&ContinuedFractionTest, "ContinuedFractionTest", SMALL);

SL void ExGcdExtTest() {
  using Int128 = pe::ExtendedSignedInt<uint64>;

  // Full Bezout identity for non-trivial inputs
  for (int a = 1; a <= 15; ++a) {
    for (int b = 1; b <= 15; ++b) {
      Int128 ia(a), ib(b);
      Int128 x, y;
      Int128 d = ExGcd(ia, ib, x, y);
      assert(d.ToInt<int>() == Gcd(a, b));
      assert(ia * x + ib * y == d);
    }
  }

  // Tuple form
  {
    auto [d, x, y] = ExGcd(Int128(24), Int128(36));
    assert(d.ToInt<int>() == 12);
    assert(Int128(24) * x + Int128(36) * y == d);
  }

  // Single-x form: d = ExGcd(a, b, x) satisfies a*x ≡ d (mod b)
  {
    Int128 x;
    Int128 d = ExGcd(Int128(7), Int128(13), x);
    assert(d.ToInt<int>() == 1);
  }

  // Large-ish values where gcd > 1
  {
    Int128 a(1000000000LL), b(999999993LL); // gcd = 3
    Int128 x, y;
    Int128 d = ExGcd(a, b, x, y);
    assert(d.ToInt<int64>() == Gcd(int64(1000000000), int64(999999993)));
    assert(a * x + b * y == d);
  }
}

PE_REGISTER_TEST(&ExGcdExtTest, "ExGcdExtTest", SMALL);

SL void CrtNExtTest() {
  using Int128 = pe::ExtendedSignedInt<uint64>;

  // x = 1 (mod 3), x = 2 (mod 5) -> x = 7 (mod 15)
  {
    Int128 val[] = {Int128(1), Int128(2)};
    Int128 mod[] = {Int128(3), Int128(5)};
    auto ans = CrtN<Int128>(val, mod, 2);
    assert(ans.ok());
    assert(ans.value.ToInt<int>() == 7);
    assert(ans.mod.ToInt<int>() == 15);
  }

  // x = 1 (mod 2), x = 2 (mod 3), x = 3 (mod 5) -> x = 23 (mod 30)
  {
    std::vector<Int128> val = {Int128(1), Int128(2), Int128(3)};
    std::vector<Int128> mod = {Int128(2), Int128(3), Int128(5)};
    auto ans = CrtN(val, mod);
    assert(ans.ok());
    assert(ans.value.ToInt<int>() == 23);
    assert(ans.mod.ToInt<int>() == 30);
  }

  // No solution: x = 0 (mod 4), x = 1 (mod 2)
  {
    std::vector<Int128> val = {Int128(0), Int128(1)};
    std::vector<Int128> mod = {Int128(4), Int128(2)};
    auto ans = CrtN(val, mod);
    assert(!ans.ok());
  }

  // Brute-force verify small CRT system
  for (int a = 0; a < 6; ++a) {
    for (int b = 0; b < 10; ++b) {
      std::vector<Int128> val = {Int128(a), Int128(b)};
      std::vector<Int128> mod = {Int128(6), Int128(10)};
      auto ans = CrtN(val, mod);
      int found = -1;
      for (int x = 0; x < 60; ++x) {
        if (x % 6 == a && x % 10 == b) { found = x; break; }
      }
      if (found < 0) {
        assert(!ans.ok());
      } else {
        assert(ans.ok());
        assert(ans.value.ToInt<int>() == found);
      }
    }
  }
}

PE_REGISTER_TEST(&CrtNExtTest, "CrtNExtTest", SMALL);

}  // namespace int_algo_test
