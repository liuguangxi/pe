# pe

[![Build Status](https://travis-ci.com/baihacker/pe.svg?branch=master)](https://travis-ci.com/baihacker/pe)
[![Build status](https://ci.appveyor.com/api/projects/status/scaji00tde2gb7uy?svg=true)](https://ci.appveyor.com/project/baihacker/pe)
[![Github Releases](https://img.shields.io/github/release/baihacker/pe.svg)](https://github.com/baihacker/pe/releases)
<a href="https://projecteuler.net/recent" target="_blank">![project euler](https://projecteuler.net/profile/baihacker.png)</a>

It is my basic code for solving problem on <a href="https://projecteuler.net/recent" target="_blank">project euler</a>.

## Prerequirements:
C++ dev environment that supports C++17 or above.

## Installation:
* Make sure "#include <pe.hpp>" work.
  * Put all the files in an installation folder (directory).
  * Add the installation folder to the environment variable CPLUS_INCLUDE_PATH. Other approaches are also OK.
 
* Configure this library by generating and editing **[pe_config](https://github.com/baihacker/pe/blob/master/pe_config)**.
  * Execute **[gen_config.py](https://github.com/baihacker/pe/blob/master/gen_config.py)** in the installation folder to generate the config file.
    * Static configuration. The values are always 1 in the generated config file. You can edit the values after generating the config file.
      * ENABLE_ASSERT whether to assert some inputs or conditions.
      * TRY_TO_USE_INT128 whether to check whether the compiler support int128 and use it. If it is 0, it int128 is disabled even if the compiler supports it.
    * Auto-deduced configuration for third party libraries. The script searches for the corresponding header file and set the value to 1 if found. See [Build and use third party libraries in pe](https://github.com/baihacker/pe/blob/master/libraries_on_win64.md#build-and-use-third-party-libraries-in-pe) for the pre-built third party binaries.
      * ENABLE_EIGEN whether to use [Eigen](http://eigen.tuxfamily.org/index.php?title=Main_Page) library.
      * ENABLE_GMP whether to use [gmp](https://gmplib.org).
      * ENABLE_FLINT whether to use [FLINT](http://www.flintlib.org).
      * ENABLE_MPFR whether to use [mpfr](https://www.mpfr.org).
      * ENABLE_LIBBF wheter to use [libbf](https://bellard.org/libbf).
      * ENABLE_NTL whether to use [ntl](https://www.shoup.net/ntl/download.html).
  * Edit the config file by adding more configuration items manually.
    * ENABLE_OPENMP whether to use [openmp](http://www.openmp.org). It is NOT generated by the script automatically becaused it's inferred at the compiling time. You can still define it in pe_config to prevernt the library from inferring the value from the compiling environment. If it is enabled but the environment doesn't support it, a warning message will show.

* [optional, recommended] Generate precompile header "pe.hpp.gch".
  * Run "g++ -xc++-header pe.hpp" in the installation folder.
  * Add more compiling options if necessary. Usually, they are the same as the options used to build your binary. e.g. "g++ -xc++-header pe.hpp --std=c++17 -O3 -march=native -fopenmp".

## Use:
See [example.c](https://github.com/baihacker/pe/blob/master/example/example.c) for quick start.

## File list:
* pe: Including all the files except pe_config and pe.hpp.
* pe.hpp: The file for generating precompile header.
* pe_algo: Algorithms.
* pe_array: An array implementation with compiling time dimension length. The element count can be more than the limit of int32 and you can specify customized allocator.
* pe_base: Some pre-including headers. Some macros and typedef. Some basic inline functions.
* pe_bi32: Big integer whose base is 1 << 32.
* pe_bit: Bit operation tricks.
* pe_config: a centralized place the configure pe.
* pe_db: load and save pre-calculated result such as prime pi and prime sum.
* pe_fft: Fast fourier transform and polynomial multiplication.
* pe_float128: Unified float number functions of __float128.
* pe_fraction: Fraction arithmetic.
* pe_gbi: general big integer. The content corresponds to pe_nt.
* pe_geometry: Support Point2D and Point3D.
* pe_int128: Support to output int128 and the corresponding type traits.
* pe_io: methods and macros that simplify or fasten reading from and writing std io.
* pe_mat: Matrix operations.
* pe_memory: Memory manipulation such as allocating large memory. (windows only)
* pe_misc: misc codes.
* pe_mma: support mma: helper method or class to generate mma codes.
* pe_mod: Modular arithmetic.
* pe_nt: Basic code of number theory.
* pe_nt_base: Generate prime list, factorize integer, prime test, compute phi and mu.
* pe_parallel: A simple framework to solve problem with multi-threads. (windows only)
* pe_parallel_algo: Parallel algorithms.
* pe_persistance: KVPersistance. (it may support linux but we need change the generated cmdline and check the other codes)
* pe_poly: Polynomial c++ wrapper.
* pe_poly_algo: Polynomial algorithms.
* pe_poly_base: Polynomial basic algorithms.
* pe_poly_base_flint: Flint based polynomial basic algorithms.
* pe_poly_base_libbf: Libbf based polynomial basic algorithms.
* pe_poly_base_min_25: [Min_25](https://github.com/min-25)'s polynomial basic algorithms. The polynomial multiplication implementation is the fastest one among mod polynomials integrated into pe.
* pe_poly_base_ntl: Ntl based polynomial basic algorithms.
* pe_rand: Random number.
* pe_range: generate an range of numbers, iterate a container with index.
* pe_sym_poly: Symbolic polynomial.
* pe_time: Support TimeDelta, TimeRecorder.
* pe_tree: Some tree based data structures.
* pe_type_traits: Type traits.
