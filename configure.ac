AC_INIT([fatso], [0.1.0], [sudharsh@gmail.com], [fatsox])
AC_CONFIG_SRCDIR([Makefile.am])
AC_CONFIG_HEADERS(config.h)
AM_INIT_AUTOMAKE([dist-bzip2])
AM_MAINTAINER_MODE

AC_PROG_CXX
AC_DISABLE_STATIC
AC_PROG_LIBTOOL

LLVM_CFLAGS=`llvm-config --cxxflags`
LLVM_LIBS=`llvm-config --libs`
LLVM_LDFLAGS=`llvm-config --ldflags`

echo "LLVM CFLAGS: ${LLVM_CFLAGS}"
echo "LLVM LIBS: ${LLVM_LIBS}"
echo "LLVM LDFLAGS: ${LLVM_LDFLAGS}"

AC_SUBST(LLVM_CFLAGS)
AC_SUBST(LLVM_LIBS)
AC_SUBST(LLVM_LDFLAGS)


AC_OUTPUT([
Makefile
src/Makefile
])
