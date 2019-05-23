#include <pe.hpp>

template <typename S>
struct mtype_policy<S, bi> {
  typedef S ints;
  typedef bi intb;
  static ints add(ints a, ints b, ints mod) {
    intb c = (intb)a + b;
    if (c >= mod) c -= mod;
    return c.toInt<ints>();
  }
  static ints sub(ints a, ints b, ints mod) {
    intb c = (intb)a - b;
    if (c < 0) c += mod;
    return c.toInt<ints>();
  }
  static ints mul(ints a, ints b, ints mod) {
    intb c = (intb)a * b % mod;
    return c.toInt<ints>();
  }
};

template <>
struct mtype_policy<bi, bi> {
  typedef bi ints;
  typedef bi intb;
  static ints add(ints a, ints b, ints mod) {
    intb c = (intb)a + b;
    if (c >= mod) c -= mod;
    return c.toInt<int64>();
  }
  static ints sub(ints a, ints b, ints mod) {
    intb c = (intb)a - b;
    if (c < 0) c += mod;
    return c.toInt<int64>();
  }
  static ints mul(ints a, ints b, ints mod) {
    intb c = (intb)a * b % mod;
    return c.toInt<int64>();
  }
};

void basic() {
  NModNumber3232<10005> orz;
  cerr << orz << endl;
  orz = orz * 12312321;
  cerr << NModNumber3232<10005>(12312321) << " " << 12312321 % 10005 << endl;
  cerr << orz << endl;
  cerr << 12312321 % 10005 << endl;
}

const int N = 10000000;
NModNumber3264<1000000007> u[N + 5];
// mintd3264 v[N+5];
// mint<int, bi, 1000000007> v[N+5];
NModNumber<int, fake_int128, 1000000007> v[N + 5];
void perf() {
  TimeRecorder tr;
  u[0] = 1;
  for (int i = 1; i <= N; ++i) u[i] = u[i - 1] * i;
  cerr << tr.elapsed().format() << endl;
  tr.record();
  // v[0].MOD = 1000000007;
  v[0] = 1;
  for (int i = 1; i <= N; ++i) v[i] = v[i - 1] * i;
  cerr << tr.elapsed().format() << endl;
  for (int i = 0; i <= N; ++i) assert(u[i].value() == v[i].value());
}
int main() {
  perf();
  return 0;
}