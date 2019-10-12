# Benchmark

## Ntt benchmark

### Test Environment:

* Date： 2019.09.18
* OS:  Win10 Pro 1903 (18362.356)
* CPU: i9-9900K (MMX, SSE, SSE2, SSE3, SSE4.1, SSE4.2, EM64T, VT-x, AES, AVX, AVX2, FMA3, TSX)
* Compiler: MinGW-x86_64-8.1.0-win32-seh-rt_v6-rev0
* Msys2: msys2-x86_64-20190524
* Test code: [Ntt test](https://github.com/baihacker/pe/blob/master/test/ntt_test.c)
* Build libbf:
  > gcc -Wall -O3 -mavx -mavx2 -mfma -mbmi2 -c -o libbf.avx2.o libbf.c
 
  > gcc -Wall -O3 -mavx -mavx2 -mfma -mbmi2 -c -o cutils.avx2.o cutils.c
 
  > gcc-ar crv libbf.avx2.a cutils.avx2.o libbf.avx2.o
* Build test target:
  > -o a.exe --std=c++14 -fno-diagnostics-color -O3 -march=native -mtune=native -fopenmp -Wl,--stack,268435456 -static -s -lbf -lgmpxx -lflint -lgmp -lmpfr -lmpir

### Test result

#### Openmp enabled
```cpp
ntt test : data = random, size = 0, n = 1000000, mod = 100019
flint n  : 0.306
flint p  : 1.029
ntt32 s  : 0.816
ntt32 l  : 0.870
ntt64 s  : 1.376
ntt64 l  : 1.422
Min_25 s : 0.114
Min_25 l : 0.125
libbf    : 0.635
ntt test : data = random, size = 1, n = 1479725, mod = 100000000003
flint n  : 0.919
flint p  : 2.633
ntt32 l  : 1.743
ntt64 l  : 2.857
Min_25 l : 0.255
libbf    : 1.084
ntt test : data = random, size = 2, n = 1000000, mod = 316227766016779
flint n  : 0.623
flint p  : 1.869
ntt64 l  : 1.429
Min_25 l : 0.133
libbf    : 0.682
ntt test : data = max mod, size = 0, n = 999996, mod = 1000003
flint n  : 0.313
flint p  : 1.087
ntt32 s  : 0.813
ntt32 l  : 0.878
ntt64 s  : 1.354
ntt64 l  : 1.419
Min_25 s : 0.111
Min_25 l : 0.125
libbf    : 0.645
ntt test : data = max mod, size = 1, n = 1479725, mod = 100000000003
flint n  : 0.922
flint p  : 2.502
ntt32 l  : 1.743
ntt64 l  : 2.839
Min_25 l : 0.253
libbf    : 1.088
ntt test : data = max mod, size = 2, n = 1000000, mod = 316227766016779
flint n  : 0.624
flint p  : 1.873
ntt64 l  : 1.406
Min_25 l : 0.133
libbf    : 0.682

mod = 100019
log2(n)  10     11     12     13     14     15     16     17     18     19     20
flint n  0.000  0.000  0.001  0.001  0.003  0.006  0.012  0.028  0.059  0.160  0.318
flint p  0.001  0.001  0.003  0.006  0.014  0.028  0.058  0.123  0.253  0.532  1.097
ntt32 s  0.001  0.003  0.003  0.007  0.015  0.032  0.048  0.101  0.201  0.403  0.819
ntt32 l  0.001  0.002  0.004  0.008  0.016  0.032  0.051  0.110  0.223  0.427  0.877
ntt64 s  0.001  0.002  0.006  0.012  0.025  0.055  0.081  0.165  0.338  0.677  1.376
ntt64 l  0.001  0.003  0.006  0.012  0.026  0.055  0.081  0.173  0.353  0.704  1.413
Min_25 s 0.000  0.000  0.001  0.001  0.002  0.002  0.006  0.014  0.027  0.054  0.112
Min_25 l 0.001  0.001  0.000  0.001  0.003  0.006  0.010  0.016  0.030  0.059  0.128
libbf    0.000  0.001  0.002  0.005  0.009  0.022  0.048  0.072  0.149  0.310  0.645
mod = 100000000003
log2(n)  10     11     12     13     14     15     16     17     18     19     20
flint n  0.001  0.000  0.001  0.002  0.005  0.010  0.021  0.045  0.099  0.301  0.645
flint p  0.001  0.002  0.005  0.010  0.021  0.043  0.092  0.190  0.397  0.828  1.727
ntt32 l  0.001  0.002  0.004  0.008  0.017  0.035  0.053  0.111  0.217  0.439  0.869
ntt64 l  0.001  0.003  0.005  0.012  0.027  0.057  0.085  0.174  0.352  0.705  1.431
Min_25 l 0.001  0.001  0.001  0.002  0.004  0.008  0.013  0.020  0.034  0.062  0.133
libbf    0.001  0.001  0.002  0.004  0.010  0.024  0.045  0.077  0.159  0.330  0.682
mod = 316227766016779
log2(n)  10     11     12     13     14     15     16     17     18     19     20
flint n  0.000  0.000  0.001  0.002  0.005  0.012  0.029  0.072  0.152  0.298  0.625
flint p  0.001  0.002  0.006  0.011  0.022  0.049  0.104  0.208  0.430  0.910  1.910
ntt64 l  0.001  0.003  0.006  0.013  0.027  0.056  0.085  0.173  0.350  0.707  1.434
Min_25 l 0.000  0.001  0.001  0.002  0.003  0.008  0.013  0.020  0.034  0.066  0.157
libbf    0.000  0.001  0.002  0.004  0.010  0.024  0.051  0.077  0.159  0.333  0.692
```

#### Openmp disabled (option "-fopenmp" removed)
```cpp
ntt test : data = random, size = 0, n = 1000000, mod = 100019
flint n  : 0.303
flint p  : 1.063
ntt32 s  : 2.720
ntt32 l  : 4.035
ntt64 s  : 2.284
ntt64 l  : 4.605
Min_25 s : 0.121
Min_25 l : 0.264
libbf    : 0.638
ntt test : data = random, size = 1, n = 1479725, mod = 100000000003
flint n  : 0.932
flint p  : 2.630
ntt32 l  : 8.624
ntt64 l  : 9.764
Min_25 l : 0.617
libbf    : 1.083
ntt test : data = random, size = 2, n = 1000000, mod = 316227766016779
flint n  : 0.628
flint p  : 1.884
ntt64 l  : 4.664
Min_25 l : 0.341
libbf    : 0.682
ntt test : data = max mod, size = 0, n = 999996, mod = 1000003
flint n  : 0.312
flint p  : 1.092
ntt32 s  : 2.703
ntt32 l  : 4.038
ntt64 s  : 2.254
ntt64 l  : 4.560
Min_25 s : 0.121
Min_25 l : 0.262
libbf    : 0.650
ntt test : data = max mod, size = 1, n = 1479725, mod = 100000000003
flint n  : 0.929
flint p  : 2.527
ntt32 l  : 8.570
ntt64 l  : 9.727
Min_25 l : 0.648
libbf    : 1.095
ntt test : data = max mod, size = 2, n = 1000000, mod = 316227766016779
flint n  : 0.630
flint p  : 1.885
ntt64 l  : 4.601
Min_25 l : 0.332
libbf    : 0.687

mod = 100019
log2(n)  10     11     12     13     14     15     16     17     18     19     20
flint n  0.000  0.001  0.000  0.001  0.002  0.005  0.011  0.028  0.060  0.159  0.317
flint p  0.001  0.001  0.003  0.006  0.014  0.029  0.060  0.123  0.251  0.534  1.094
ntt32 s  0.001  0.003  0.006  0.014  0.030  0.064  0.137  0.288  0.607  1.287  2.722
ntt32 l  0.002  0.004  0.009  0.022  0.045  0.096  0.204  0.430  0.901  1.910  4.044
ntt64 s  0.001  0.002  0.006  0.011  0.025  0.053  0.113  0.244  0.516  1.082  2.438
ntt64 l  0.003  0.005  0.012  0.024  0.054  0.115  0.247  0.525  1.096  2.230  4.652
Min_25 s 0.000  0.000  0.001  0.001  0.001  0.003  0.007  0.014  0.029  0.058  0.132
Min_25 l 0.000  0.001  0.000  0.001  0.003  0.006  0.014  0.029  0.061  0.131  0.267
libbf    0.001  0.000  0.002  0.004  0.009  0.019  0.044  0.073  0.150  0.311  0.649
mod = 100000000003
log2(n)  10     11     12     13     14     15     16     17     18     19     20
flint n  0.001  0.000  0.001  0.001  0.005  0.009  0.021  0.046  0.098  0.302  0.651
flint p  0.001  0.002  0.005  0.010  0.022  0.045  0.092  0.190  0.400  -0.662 1.775
ntt32 l  0.002  0.005  0.010  0.021  0.046  0.097  0.206  0.438  0.915  2.034  4.193
ntt64 l  0.002  0.005  0.011  0.025  0.052  0.118  0.247  0.500  1.050  2.217  4.675
Min_25 l 0.000  0.000  0.001  0.001  0.003  0.009  0.018  0.039  0.076  0.158  0.328
libbf    0.001  0.001  0.002  0.005  0.009  0.021  0.047  0.077  0.159  0.328  0.688
mod = 316227766016779
log2(n)  10     11     12     13     14     15     16     17     18     19     20
flint n  0.000  0.001  0.001  0.002  0.005  0.012  0.029  0.072  0.153  0.299  0.630
flint p  0.002  0.003  0.005  0.011  0.023  0.048  0.105  0.213  0.437  0.933  1.912
ntt64 l  0.002  0.005  0.012  0.024  0.052  0.110  0.237  0.499  1.054  2.224  4.694
Min_25 l 0.001  0.001  0.001  0.002  0.004  0.009  0.018  0.038  0.079  0.166  0.344
libbf    0.001  0.001  0.002  0.004  0.010  0.023  0.047  0.076  0.159  0.335  0.699
```