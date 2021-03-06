#include "pe_test.h"

namespace comb_moder_test {
SL void comb_moder_test() {
  const int mod = 10007;
  CombModer m1(mod);
  CombModerEx m2(mod);
  for (int i = 0; i < 10000; ++i) {
    const int n = rand() % mod;
    const int m = rand() % mod;
    assert(m1.comb(n, m) == m2.comb(n, m));
  }
#if PE_HAS_INT128
  {
    const int64 mod = 99999999907;
    CombModerEx moder(mod);
    const int64 n = 66666666604;
    const int64 m = 33333333302;
    auto result = moder.comb(n, m);

    assert(result == 99999410307);
  }
#endif
}
PE_REGISTER_TEST(&comb_moder_test, "comb_moder_test", MEDIUM);
}  // namespace comb_moder_test