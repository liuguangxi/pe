#include <pe.hpp>
using namespace pe;

const int64 mod = 1000000007;

int main() {
  {
    NModCC64<mod> a(5);
    std::cout << a.Power(10) << std::endl;
    std::cout << Power(a, 10) << std::endl;
    std::cout << PowerMod(a, 10) << std::endl;
    std::cout << PowerMod(a, 10, mod) << std::endl;
    std::cout << PowerMod(a, 10) << std::endl;
    std::cout << PowerMod(a, 10, mod) << std::endl;
  }
  {
    TLMod<int64>::Set(mod);
    NModTL64<> a(5);
    std::cout << a.Power(10) << std::endl;
    std::cout << Power(a, 10) << std::endl;
    std::cout << PowerMod(a, 10) << std::endl;
    std::cout << PowerMod(a, 10, mod) << std::endl;
    std::cout << PowerMod(a, 10) << std::endl;
    std::cout << PowerMod(a, 10, mod) << std::endl;
  }
  {
    GlobalMod64::Set(mod);
    NModNumber<GlobalMod64> a(5);
    std::cout << a.Power(10) << std::endl;
    std::cout << Power(a, 10) << std::endl;
    std::cout << PowerMod(a, 10) << std::endl;
    std::cout << PowerMod(a, 10, mod) << std::endl;
    std::cout << PowerMod(a, 10) << std::endl;
    std::cout << PowerMod(a, 10, mod) << std::endl;
  }
  {
      // NModNumber<MemMod<int64>> a(5);
  }

  {
    NModMCC64<mod> a(5);
    std::cout << a.Power(10) << std::endl;
    std::cout << Power(a, 10) << std::endl;
    std::cout << PowerMod(a, 10) << std::endl;
    std::cout << PowerMod(a, 10, mod) << std::endl;
    std::cout << PowerMod(a, 10) << std::endl;
    std::cout << PowerMod(a, 10, mod) << std::endl;
  }
  {
    TLMod<int64>::Set(mod);
    NModMTL64<> a(5);
    std::cout << a.Power(10) << std::endl;
    std::cout << Power(a, 10) << std::endl;
    std::cout << PowerMod(a, 10) << std::endl;
    std::cout << PowerMod(a, 10, mod) << std::endl;
    std::cout << PowerMod(a, 10) << std::endl;
    std::cout << PowerMod(a, 10, mod) << std::endl;
  }
  {
    GlobalMod64::Set(mod);
    NModNumberM<GlobalMod64> a(5);
    std::cout << a.Power(10) << std::endl;
    std::cout << Power(a, 10) << std::endl;
    std::cout << PowerMod(a, 10) << std::endl;
    std::cout << PowerMod(a, 10, mod) << std::endl;
    std::cout << PowerMod(a, 10) << std::endl;
    std::cout << PowerMod(a, 10, mod) << std::endl;
  }
  {
    // Not recommended.
    NModNumberM<MemMod<int64>> a(5, MemMod<int64>(mod));
    std::cout << a.Power(10) << std::endl;
    std::cout << Power(a, 10) << std::endl;
    std::cout << PowerMod(a, 10) << std::endl;
    std::cout << PowerMod(a, 10, mod) << std::endl;
    std::cout << PowerMod(a, 10) << std::endl;
    std::cout << PowerMod(a, 10, mod) << std::endl;
  }
  return 0;
}