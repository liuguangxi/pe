pe
==

It is my basic code for solving problem on project euler.

Latest release: [Pe2.0](https://github.com/baihacker/pe/releases)

Installation:
-------------
* Put all the files in a folder (directory). For example, we put them in the directory D:\usr\include.
* Make sure the environment variable CPLUS_INCLUDE_PATH contain D:\usr\include.
* In [pe](https://github.com/baihacker/pe/blob/master/pe), configure this library. 
  > ENABLE_EIGEN whether to use [Eigen](http://eigen.tuxfamily.org/index.php?title=Main_Page) library.

  > ENABLE_OPENMP swhether to use [openmp](http://www.openmp.org).
  
  > ENABLE_GMP whether to use [gmp](https://gmplib.org).
  
  > ENABLE_FLINT whether to use [FLINT](http://www.flintlib.org).
  
  > ENABLE_MPFR whether to use [mpfr](https://www.mpfr.org).
  
  > ENABLE_MPIR whether to use [mpir](http://mpir.org).

  * Note: The compiled flint, gmp, mpfr, mpir (all for win64) can be found [here](https://pan.baidu.com/s/1OI-vk3JJevYphIsFoNg_vA)(pwd:x7cg). All are in package flint.

* [optional, recommended] Generate precompile header "pe.hpp.gch".
  * Command: "g++ xc++-header pe.hpp". Run in D:\usr\include
  * You can add more options, usually, they are the same as the options to compile your target. e.g. "g++ -xc++-header pe.hpp --std=c++11 -O3 -march=native -fopenmp".

Use:
----
#include <pe.hpp> in your source code.

Prerequirements:
----------------
C++11 or above

File list:
-----------
* pe: Including all the files.
* pe.hpp: The file for generating precompile header.
* pe_base: Some pre-including headers. Some macros and typedef.
* pe_bi: Big integer whose base is 1 << 30.
* pe_bi32: Big integer whose base is 1 << 32.
* pe_bit: Bit operation tricks.
* pe_bn: Old big integer implementation.
* pe_fft: Fast fourier transform and polynomial multiplication.
* pe_geometry: Support Point2D and Point3D.
* pe_integer_util: integer utils.
* pe_mat: Matrix operations.
* pe_misc：misc codes.
* pe_memory: Memory manipulation such as allocating large memory. (windows only)
* pe_mod: Modular arithmetic.
* pe_nt: Basic code of number theory.
* pe_ntt: Number theoretic transform and polynomial multiplication.
* pe_ntt_libbf: An adapter which makes use of libbf to implement ntt.
* pe_ntt_min_25: Min_25's ntt implementation. The fastest one for mod polynomials integrated into pe.
* pe_parallel: A simple framework to solve problem with multi-threads. (windows only)
* pe_parallel_algo: Parallel algorithms.
* pe_poly: Polynomial.
* pe_poly_algo: Polynomial algorithms.
* pe_tree: Some tree based data structures.
* pe_util: Utilities such as TimeDelta, KVPersistance. (it may support linux but we need change the generated cmdline and check the other codes)

Design principle:
--------------------
Fast and easy to use.

eg:

The factorizing interface is c++ style. It will be a little slower but it's easy to use.

[Use global variable plist (array of integers), pcnt to store the prime list and prime count, because they are frequently used. phi and miu are a c-style pointers, because they are not frequently used while vector<int> is a little heavier.] But now, the type of plist can be both array of integers and c-stype pointer, because the performance is nearly the same and sometimes we need dynamic allocation to obtain much more primes where a static allocation will make the binary not work.

Example:
--------
```cpp
#include <pe.hpp>

int main()
{
  init_primes();

  int64 result = PARALLEL_RESULT(
  BEGIN_PARALLEL
    FROM 1 TO 100000000 EACH_BLOCK_IS 10000000 CACHE ""
    THREADS 10
    MAP
      {
        return is_prime_ex(key);
      }
    REDUCE
      {
        result += value;
        return result;
      }
  END_PARALLEL);
  dbg(result);

  return 0;
}
```

Ntt benchmark:
-----------

### Test Environment:

* OS:  Win10 Pro 1803
* CPU: i7-4790K (MMX, SSE, SSE2, SSE3, SSE4.1, SSE4.2, EM64T, VT-x, AES, AVX, AVX2, FMA3)
* Compiler: MinGW-x86_64-8.1.0-win32-seh-rt_v6-rev0
* Msys2: msys2-x86_64-20180531
* Build libbf:
 > gcc -Wall -O3 -mavx -mavx2 -mfma -mbmi2 -c -o libbf.avx2.o libbf.c
 > gcc -Wall -O3 -mavx -mavx2 -mfma -mbmi2 -c -o cutils.avx2.o cutils.c
 > gcc-ar crv libbf.avx2.a cutils.avx2.o libbf.avx2.o
* Run tests:
 > -o a.exe --std=c++11 -O3 -march=native -mtune=native -fopenmp -Wl,--stack,268435456 -lbf -lgmpxx -lflint -lgmp -lmpfr -lmpir
* Test code: [Ntt test](https://github.com/baihacker/pe/blob/master/test/ntt_test.c)

### Test result
```cpp
ntt test: isRandom = 1, largeOnly = 0, n = 1000000, mod = 100019
flint    : 1.141
ntt32 s  : 1.016
ntt32 l  : 1.167
ntt64 s  : 1.532
ntt64 l  : 1.666
Min_25 s : 0.156
Min_25 l : 0.156
libbf    : 0.812
ntt test: isRandom = 1, largeOnly = 1, n = 1479725, mod = 100000000003
flint    : 2.891
ntt32 l  : 2.375
ntt64 l  : 3.375
Min_25 l : 0.328
libbf    : 1.344
ntt test: isRandom = 0, largeOnly = 0, n = 999996, mod = 1000003
flint    : 1.219
ntt32 s  : 1.000
ntt32 l  : 1.140
ntt64 s  : 1.519
ntt64 l  : 1.642
Min_25 s : 0.141
Min_25 l : 0.156
libbf    : 0.813
ntt test: isRandom = 0, largeOnly = 1, n = 1479725, mod = 100000000003
flint    : 2.750
ntt32 l  : 2.390
ntt64 l  : 3.383
Min_25 l : 0.328
libbf    : 1.376
End ntt_test
```
