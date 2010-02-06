NULL = 
bin_PROGRAMS = fatso

AM_CPPFLAGS = \
	${LLVM_CFLAGS} \
	-fexceptions  # Overriding llvm-config's -fno-exceptions

fatso_LDADD = \
	${LLVM_LIBS}


fatso_SOURCES = \
	lexer.h \
	lexer.cpp \
	parser.h \
	parser.cpp \
	$(NULL)

