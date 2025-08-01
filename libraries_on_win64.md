# Libraries on Win64

Outline of this doc
  * General intstructions for how to build C/C++ libraries on windows 64. It assumes those libraries provide script to build on linux environment.
  * Describe how to use C/C++ libraries on windows 64 in MinGW and MSVC.
  * For gmp, mpfr, mpir, flint2, libbf, ntl, this doc also gives a script to build them. Makefiles are also given if necessary.

In most cases, this doc is also applied to windows 32.

# Prepare
## Tools introduction
[MinGW-w64](https://www.mingw-w64.org)
  * MinGW-w64 homepage says
  >Mingw-w64 is an advancement of the original mingw.org project, created to support the GCC compiler on Windows systems. It has forked it in 2007 in order to provide support for 64 bits and new APIs. It has since then gained widespread use and distribution.

[MSYS2](https://www.msys2.org/)
 * MSYS homepage says
 >MSYS2 is a collection of tools and libraries providing you with an easy-to-use environment for building, installing and running native Windows software. 
 * Wikipedia says
 >MSYS2 ("minimal system 2") is a software distribution and a development platform for Microsoft Windows, based on Mingw-w64 and Cygwin, that helps to deploy code from the Unix world on Windows. It plays the same role the old MSYS did in MinGW.


## Install
For MSYS2, just download the [installer](https://www.msys2.org/#installation) and install it. For MinGW-w64, there are two ways
* Use [MinGW-w64 installer](https://sourceforge.net/projects/mingw-w64/)
  * The installer provides several install options, and a typical install option is MinGW-x86_64-8.1.0-win32-seh-rt_v6-rev0.
* Install the MinGW-w64 provided by MSYS2 (recommended, the binaries are updated more frequently)
  * Use the following commands to install it
    * pacman -Syuu
    * pacman -S --needed mingw-w64-x86_64-toolchain
  * If your are only interested in C/C++ development, some unnecessary packages can be removed by the following commands
    * pacman -R mingw-w64-x86_64-gcc-objc mingw-w64-x86_64-gcc-libgfortran mingw-w64-x86_64-gcc-fortran mingw-w64-x86_64-gcc-ada mingw-w64-x86_64-tools-git mingw-w64-x86_64-libgccjit mingw-w64-x86_64-gdb-multiarch

Note: it is possible to use the MinGW-w64 installed by "MinGW-w64 installer" on MSYS2, just copy the "mingw64" folder under the MinGW-w64 installation folder to \<MSYS2 path\>/mingw64. Meanwhile, you can also use MSYS2 to obtain MinGW-w64 and copy it to some other directories.


## Use MinGW-w64
As saied by the Wikipedia, there are several ways to run MinGW-w64:
>Mingw-w64 can be run either on the native Microsoft Windows platform, cross-hosted on Linux (or other Unix), or "cross-native" on MSYS2 or Cygwin. Mingw-w64 can generate 32 bit and 64-bit executables for x86 under the target names i686-w64-mingw32 and x86_64-w64-mingw32.

* Run MinGW-w64 on the native Microsoft Windows platform
  * Make sure the \<MinGW-w64 path\>\bin is a part of the einvironment variable named PATH.
  * Open the cmd.exe (or other command line shell).
  * Enter the parent directory of you source code.
  * Build your binary
    * The bassic command is "g++ source_code.cpp".
    * Usually, I often add the following options "--std=c++17 -O3 -march=native -mtune=native -Wl,--stack,268435456".
    * Please add "-fopenmp" if you want to use openmp.
    * See [x86 Options](https://gcc.gnu.org/onlinedocs/gcc/x86-Options.html) for more options.
* Run MinGW-w64 on MSYS2
  * Launch the MSYS2 with MinGW-w64 by double clicking "\<MSYS2 path\>/mingw64.exe".
  * The way of building binaries is the same that of "run it on the native Microsoft Windows platform".

When building libraries, makefile is frequently used. Please make a copy of \<MSYS2 path\>/mingw64/bin/mingw32-make.exe and rename the name of the copy to make.exe. Some libraries requires extra packages, please also install them. Here are the packges required by the following examples/scripts
  * pacman -S msys/m4
  * pacman -S mingw64/mingw-w64-x86_64-yasm


# Build libraries

Please read the README or INSTALL doc of the target library before building it, since **it may contain important configuration specifications**. If the library provides vc solution/project, you can use it to build. This doc only focuses on a library which can be built by makefile (other building system is not included).

## Build gmp
* Extract the package to build directory and cd the build directory (use msys2 terminal)
* Commands
  * ./configure --disable-shared --enable-static --prefix=/usr --enable-cxx --host=x86_64-w64-mingw32
  * make
  * make check
  * make install
* Notes
  * "--disable-shared --enable-static" we only build static library here.
    * sometimes, you can only enable one kind of build type. If you want to build both shared library and static library, please run the command twice.
    * it is a good practice only to build static library.
    * it is tricky if you have both static library and shared libarary and you want to let your building system decide which one to use.
  * "--prefix=/usr" is used to specify the install path.
    * You can find the header file (.h or other suffix) under /usr/include and find lib (.a) under /usr/lib.
    * TODO(baihacker): for shared library.
  * "--enable-cxx" gmp specified option to support c++ wrapper.
  * "--host=x86_64-w64-mingw32" required for building gmp on win64.
  * -D__USE_MINGW_ANSI_STDIO=0 in C or CXX flags to avoid mingw dependencies.
  * "make check" is optional but some libraries have this option in their makefile to check the build result.
  * "make install" copies the result to target path
  * "make clean" cleans intermediate outputs generated in the build process

# Use libraries
## MinGW
* CPLUS_INCLUDE_PATH contains the corresponding header files.
  * if "D:/X/Y/zzz.h" is your header file and CPLUS_INCLUDE_PATH contains "D:/X/Y" you can use #include <zzz.h> in your code. If "D:/X" is in it, you can use #include <Y/zzz.h> in your code.
* LIBRARY_PATH contains the corresponding lib files.
  * if "D:/X/Y/libzzz.a" is in LIBRARY_PATH, you can use "-lzzz" to add that in your compile command.
  * some libraries don't have a ".a" file, so just include the header files. e.g. eigen.
* Note for mutiple libraries:
  * The order of included header files is important. Please adjust them if necessaries.
  * The order of libraries (the order of additional library in compile command) is important (it usually happens). If the compiler says it cannot find a symbol, please try to adjust the library order. [Why does the order in which libraries are linked sometimes cause errors in GCC?](https://stackoverflow.com/questions/45135/why-does-the-order-in-which-libraries-are-linked-sometimes-cause-errors-in-gcc/409470#409470)

## MSVC
* You can edit the include path and lib path in the solution property dialog.
* In the solution property dialog, you can also add dependent libraries (in linker option section). Unlike that in MinGW, you need to specify libzzz.a instead of zzz.
  * You can also use #pragma comment(lib, "libzzz.lib") in your code to add dependent libraries.
* If the library is built by MinGW
  * Use /MT (release) or /MTd (debug) to specify c-runtime.
  * Add libgcc_s.a;libgcc.a; to dependent library list. (They can be found in the MinGW directory)
  * Sometimes legacy_stdio_definitions.lib; is also necessary to add to dependent library list.
* Enable other options if you want, e.g. openmp
* Sample options to compile a code using pe.
  * Release: /GS /GL /W3 /Gy /Zc:wchar_t /Zi /Gm- /O2 /Fd"x64\Release\vc141.pdb" /Zc:inline /fp:precise /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /errorReport:prompt /WX- /Zc:forScope /Gd /Oi /MT /openmp /FC /Fa"x64\Release\" /EHsc /nologo /Fo"x64\Release\" /Fp"x64\Release\pe.pch" /diagnostics:classic
  * Debug: /GS /W3 /Zc:wchar_t /ZI /Gm- /Od /Fd"x64\Debug\vc141.pdb" /Zc:inline /fp:precise /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /errorReport:prompt /WX- /Zc:forScope /RTC1 /Gd /MTd /openmp /FC /Fa"x64\Debug\" /EHsc /nologo /Fo"x64\Debug\" /Fp"x64\Debug\pe.pch" /diagnostics:classic
  * Build test on AppVeyor: "C:\Program Files (x86)\Microsoft Visual Studio\2017\Community\VC\Auxiliary\Build\vcvars64.bat"
cl test\pe_test.c /TP /GS /GL /W3 /Gy /Zc:wchar_t /Zi /Gm- /O2 /Zc:inline /fp:precise /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /errorReport:prompt /WX- /Zc:forScope /Gd /Oi /MT /openmp /FC /EHsc /nologo /diagnostics:classic /DTEST_ALL /DCONTINUOUS_INTEGRATION_TEST /DENABLE_ASSERT=0 /DTRY_TO_USE_INT128=1 /DENABLE_OPENMP=1 /DENABLE_EIGEN=0 /DENABLE_GMP=0 /DENABLE_FLINT=0 /DENABLE_MPFR=0 /DENABLE_LIBBF=0 /DENABLE_NTL=0 /I "C:\projects\pe"

# Build and use pe's dependent libraries
 * Current version
   * [gmp 6.3.0](https://gmplib.org/)
   * [mpfr 4.2.2](https://www.mpfr.org/mpfr-current/#download)
   * [mpir 3.0.0](http://mpir.org/downloads.html) (not used now)
   * [flint2 3.1.3](https://github.com/wbhart/flint2)
   * [libbf 2020-01-19](https://bellard.org/libbf/)
   * [ntl Windows: WinNTL-11_5_1.zip](https://www.shoup.net/ntl/download.html)
   * [prime count 7.15](https://github.com/kimwalisch/primecount)
   * [gperf tools 2.16](https://github.com/gperftools/gperftools)
 * Library order in compiling command: "-lbf -lflint -lmpfr -lntl -lgmp -lprimesieve -lprimecount -lzmq -lquadmath"
 * Use this script to build these libraries
   * Install msys2
   * Install building tools
     * pacman -Syuu
     * pacman -S --needed mingw-w64-x86_64-toolchain
     * pacman -S msys/m4
     * pacman -S mingw64/mingw-w64-x86_64-yasm
     * pacman -S unzip
     * pacman -S xz
     * pacman -S tar
     * pacman -S zip
     * pacman -S patch
     * pacman -S mingw-w64-x86_64-diffutils
     * pacman -S mingw-w64-x86_64-cmake
   * Download the library package and put them under "\<msys2 installation dir\>/home/\<your username\>". Please not the library version matters.
   * Put **build_pe_deps.sh**, **makefile_libbf** and **makefile_ntl** under "\<msys2 installation dir\>/home/\<your username\>".
   * Edit **build_pe_deps.sh** manually if you just want to build some of them.
   * Double click "\<msys2 instalation dir\>/mingw64.exe" to enter the msys2 environment and the current directory is "/home/\<your username\>".
   * Run "./build_pe_deps.sh".
  * build_pe_deps.sh
```cpp
#!/bin/bash

BUILD_ROOT=$(pwd)

GMP_DIR="gmp-6.3.0"
MPFR_DIR="mpfr-4.2.2"
MPIR_DIR="mpir-3.0.0"
LIBBF_DIR="libbf-2020-01-19"
WIN_NTL_DIR="WinNTL-11_5_1"
FLINT_DIR="flint-3.1.3"
GPERFTOOLS_DIR="gperftools-2.16"
PRIME_COUNT_DIR="primecount-7.15"

BUILD_DIR="build"
TARGET_DIR="$(pwd)/${BUILD_DIR}"
#sandybridge
#skylake
TARGET_ARCH=skylake
TUNE_ARCH=raptorlake
ENABLE_LTO=false

ARCH_FLAGS="-march=${TARGET_ARCH} -mtune=${TUNE_ARCH}"
OPT_FLAGS="-O3"
SHARED_FLAGS="${OPT_FLAGS} ${ARCH_FLAGS} -D__USE_MINGW_ANSI_STDIO=0"

if [ "${TARGET_ARCH}" == "sandybridge" ]; then
AVX2_CONFIG=""
else
AVX2_CONFIG="--enable-avx2"
fi

if [ "${ENABLE_LTO}" == "true" ]; then
LTO_SUFFIX="_lto"
SHARED_FLAGS="${SHARED_FLAGS} -flto"
else
LTO_SUFFIX=""
fi

ARCH_SUFFIX="_${TARGET_ARCH}"

echo "Build pe_dependencies_win64${ARCH_SUFFIX}${LTO_SUFFIX}_$(date '+%Y%m%d').zip"

function build_gperftools() {
  echo "build gperftools"
  cd "${GPERFTOOLS_DIR}"
  ./configure --prefix=${TARGET_DIR} --disable-shared --enable-static CXXFLAGS="-DPERFTOOLS_DLL_DECL="
  make -j8
  make install
  cd ..
}

function build_gmp() {
  echo "build gmp"
  cd "${GMP_DIR}"
  ./configure --disable-shared --enable-static --prefix=${TARGET_DIR} --disable-cxx --enable-fat --enable-alloca=yes --host=x86_64-w64-mingw32 CFLAGS="-std=c99 -m64 ${SHARED_FLAGS}" CXXFLAGS="--std=c++20 -m64 ${SHARED_FLAGS}"
  make -j8
  make install
  cd ..
}

function build_mpfr() {
  echo "build mpfr"
  cd "${MPFR_DIR}"
  ./configure --with-gmp=${TARGET_DIR} --enable-static --disable-shared --prefix=${TARGET_DIR} CFLAGS="-std=c99 -m64 ${SHARED_FLAGS}"
  make -j8
  make install
  cd ..
}

function build_mpir() {
  echo "build mpir"
  cd "${MPIR_DIR}"
  sed -i 's/ln -s "$ac_rel_source" "$ac_file" 2>\/dev\/null ||//g' configure
  sed -i 's/ln "$ac_source" "$ac_file" 2>\/dev\/null ||//g' configure
  ./configure --disable-shared --enable-static --prefix=${TARGET_DIR} CFLAGS="-m64 ${SHARED_FLAGS} -Wno-error=implicit-int -Wno-error=implicit-function-declaration" CXXFLAGS="--std=c++20 -m64 ${SHARED_FLAGS}"
  make -j8
  make install
  cd ..
}

function build_libbf() {
  echo "build libbf"
  cp makefile_libbf "${LIBBF_DIR}/makefile"
  cd "${LIBBF_DIR}"
  sed -i "s/__OPT_FLAGS__/${OPT_FLAGS}/g" makefile
  sed -i "s/__ARCH_FLAGS__/${ARCH_FLAGS}/g" makefile
  make -j8
  cp libbf.h "${TARGET_DIR}/include/libbf.h"
  cp libbf.a "${TARGET_DIR}/lib/libbf.a"
  #cp libbf.generic.a "${TARGET_DIR}/lib/libbf.generic.a"
  cd ..
}

function build_ntl() {
  echo "build win ntl"
  cp makefile_ntl "${WIN_NTL_DIR}/src/makefile"
  cd "${WIN_NTL_DIR}"
  cd "include/NTL"
  sed -i 's/\/\* sanity checks \*\//\/\* sanity checks \*\/\n#define NTL_STD_CXX14\n#undef NTL_DISABLE_MOVE_ASSIGN/g' config.h
  sed -i 's/#include <streambuf>/#include <streambuf>\n#include <sstream>/g' tools.h
  sed -i 's/plain_c_string_streambuf buf(y);//g' tools.h
  sed -i 's/std::istream istr(&buf)/std::istringstream istr(y)/g' tools.h
  cd "../../src"
  sed -i "s/__OPT_FLAGS__/${OPT_FLAGS}/g" makefile
  sed -i "s/__ARCH_FLAGS__/${ARCH_FLAGS}/g" makefile
  make -j8
  cp libntl.a "${TARGET_DIR}/lib/libntl.a"
  cd ..
  cp -r "./include/NTL" "${TARGET_DIR}/include/"
  cd ..
}

function build_flint() {
  echo "build flint"
  cd "${FLINT_DIR}"
  ./configure --disable-shared --enable-static --prefix=${TARGET_DIR} --with-gmp=${TARGET_DIR} --with-mpfr=${TARGET_DIR} --enable-pthread ${AVX2_CONFIG} CFLAGS="-std=c99 -Wno-long-long -Wno-declaration-after-statement -mpopcnt ${SHARED_FLAGS}" CXXFLAGS="--std=c++20 -Wno-long-long -Wno-declaration-after-statement -funroll-loops -mpopcnt ${SHARED_FLAGS}"
  sed -i 's/@$(LD) -r $($(1)_OBJS) -o $(BUILD_DIR)\/$(1)_merged.o/@$(LD) -r $($(1)_OBJS) -o $(BUILD_DIR)\/$(1)_merged.o\n\tmkdir -p $(FLINT_DIR)\/tmp\/$(1)\n\tcp $($(1)_OBJS) $(FLINT_DIR)\/tmp\/$(1) -f/g' makefile
  make -j12
  make install
  rm libflint.a

export src_dir="tmp"
export dst_dir="tmp"

mkdir -p "$dst_dir"

#find "$src_dir" -name "*.o" | while read file; do
#    dir_name=$(basename "$(dirname "$file")")
#    file_name=$(basename "$file")
#
#    new_name="${dir_name}_${file_name}"
#
#    mv "$file" "$dst_dir/$new_name"
#done

#find "${src_dir}" -name "*.o" -print0 | parallel -0 '
#  dir_name=$(basename "$(dirname {})")
#  file_name=$(basename {})
#  mv "{}" "'"${dst_dir}"'"/${dir_name}_${file_name}
#'

python3 ../move_files.py "${src_dir}" "${dst_dir}"

  find tmp -name "*.o" > obj_files.txt
  ar rcs libflint.a @obj_files.txt
  strip --strip-debug libflint.a
  cp -f ./libflint.a ${TARGET_DIR}/lib/libflint.a
  cd ..
}

function build_prime_count() {
  echo "build prime count"
  cd "${PRIME_COUNT_DIR}"
  cmake -G "Unix Makefiles" . -DCMAKE_INSTALL_PREFIX:PATH=${TARGET_DIR} -DBUILD_PRIMECOUNT=OFF
  make -j1
  make install
  rm -rf ${TARGET_DIR}/lib/cmake
  cd ..
}

function build_all() {
  build_gperftools
  build_gmp
  build_mpfr
  build_libbf
  build_ntl
  build_flint
  build_prime_count
}

function clean() {
  rm -r -f "${GPERFTOOLS_DIR}"
  rm -r -f "${GMP_DIR}"
  rm -r -f "${MPFR_DIR}"
  #rm -r -f "${MPIR_DIR}"
  rm -r -f "${LIBBF_DIR}"
  rm -r -f "${WIN_NTL_DIR}"
  rm -r -f "${FLINT_DIR}"
  rm -r -f "${PRIME_COUNT_DIR}"
  rm -r -f "./${BUILD_DIR}"
}

function extract_file() {
  #xz -d -k "${GMP_DIR}.tar.xz"
  #tar xf "${GMP_DIR}.tar"
  #rm "${GMP_DIR}.tar"
  unzip -o -q "${GPERFTOOLS_DIR}.zip"
  tar xf "${GMP_DIR}.tar.xz"
  unzip -o -q "${MPFR_DIR}.zip"
  #unzip -o -q "${MPIR_DIR}.zip"
  unzip -o -q "${WIN_NTL_DIR}.zip"
  tar xf "${LIBBF_DIR}.tar.gz"
  unzip -o -q "${FLINT_DIR}.zip"
  unzip -o -q "${PRIME_COUNT_DIR}.zip"
}

function build_main() {
  clean
  extract_file
  mkdir -p "${TARGET_DIR}/include"
  mkdir -p "${TARGET_DIR}/lib"
  build_all
  cp -f ./METADATA.txt "${TARGET_DIR}/METADATA.txt"
  cp -f ./makefile_ntl "${TARGET_DIR}/makefile_ntl"
  cp -f ./makefile_libbf "${TARGET_DIR}/makefile_libbf"
  cp -f ./build_pe_deps.sh "${TARGET_DIR}/build_pe_deps.sh"
  cp -f ./move_files.py "${TARGET_DIR}/move_files.py"
  rm -r -f "${TARGET_DIR}/share"
  rm -r -f "${TARGET_DIR}/lib/pkgconfig"
}

function package_file() {
  RELEASE_FILENAME="pe_dependencies_win64${ARCH_SUFFIX}${LTO_SUFFIX}_$(date '+%Y%m%d').zip"
  cd ${BUILD_DIR}
  zip -r -q "${RELEASE_FILENAME}" .
  cd ..
  mv -f "./${BUILD_DIR}/${RELEASE_FILENAME}" ./
}

function combine_objects() {
  libname=$1
  mkdir $libname
  cd $libname
  ar -x "../lib${libname}.a"
  mkdir -p "../combined"
  echo ld -x -X -r -o "../combined/lib${libname}_combined.o" "$2"
  ld -x -X -r -o "../combined/lib${libname}_combined.o" "$2"
  cd ..
  rm -rf $libname
}

function package_single_file() {
  RELEASE_FILENAME="pe_dependencies_win64${ARCH_SUFFIX}${LTO_SUFFIX}_single_$(date '+%Y%m%d').zip"
  rm -rf ${BUILD_DIR}_single
  cp -r ${BUILD_DIR} ${BUILD_DIR}_single
  cd ${BUILD_DIR}_single
  cd lib
  combine_objects bf.generic "*.o"
  combine_objects flint "*.o"
  combine_objects gmp "*.o"
  combine_objects mpfr "*.o"
  combine_objects ntl "*.o"
  combine_objects primecount "*.obj"
  combine_objects primesieve "*.obj"
  cd combined
  ld -r -o ../pedeps.o *.o
  cd ..
  rm -rf *.a
  rm -rf *.la
  ar rcs libpedeps.a pedeps.o
  rm -rf combined
  rm pedeps.o
  cd ..
  cd ..
  cd ${BUILD_DIR}_single
  zip -r -q "${RELEASE_FILENAME}" .
  cd ..
  mv -f "./${BUILD_DIR}_single/${RELEASE_FILENAME}" ./
}

build_main
package_file
#package_single_file

cd ${BUILD_ROOT}
```

  * makefile_libbf. This makefile will generate libbf.avx2.a and libbf.generic.a, please choose one and rename it to libbf.a
```cpp
CC=$(CROSS_PREFIX)gcc
CFLAGS=-Wall
CFLAGS+=__OPT_FLAGS__
CFLAGS+=-D__MSVCRT_VERSION__=0x1400
CFLAGS+=-std=c99
CFLAGS+=-Wno-format-extra-args
CFLAGS+=-Wno-format
CFLAGS+=__ARCH_FLAGS__
CLFAGS+=-D__USE_MINGW_ANSI_STDIO=0
LDFLAGS=

PROGS+=libbf.a

all: $(PROGS)

libbf.a : libbf.o  cutils.o
	gcc-ar crv libbf.a cutils.o libbf.o

#libbf.avx2.a : libbf.avx2.o  cutils.avx2.o
#	gcc-ar crv libbf.avx2.a cutils.avx2.o libbf.avx2.o

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

#%.avx2.o: %.c
#	$(CC) $(CFLAGS) -mavx -mavx2 -mfma -mbmi2 -c -o $@ $<

clean:
	rm -f $(PROGS) *.o *.d *.a *.exe *~

-include $(wildcard *.d)
```

  * makefile_ntl (windows). The script will edit config.h to enable c++14 and move-assignment.
```cpp
CC=$(CROSS_PREFIX)gcc
CFLAGS=-Wall
CFLAGS+=__OPT_FLAGS__
CFLAGS+=-D__MSVCRT_VERSION__=0x1400
CFLAGS+=-I../include
CFLAGS+=--std=c++20
CFLAGS+=-Wno-maybe-uninitialized
CFLAGS+=-Wno-unused-variable
CFLAGS+=-Wno-unused-function
CFLAGS+=-Wno-unused-but-set-variable
CFLAGS+=__ARCH_FLAGS__
CFLAGS+=-D__USE_MINGW_ANSI_STDIO=0
LDFLAGS=

SOURCE = $(wildcard *.cpp)
OBJS = $(patsubst %.cpp,%.o,$(SOURCE))

PROGS+=libntl.a

all: $(PROGS)

libntl.a : $(OBJS)
	gcc-ar crv libntl.a $(OBJS)

%.o: %.cpp
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(PROGS) *.o *.d *.a *.exe *~
```
