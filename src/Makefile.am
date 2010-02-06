NULL = 
bin_PROGRAMS = fatso

AM_CPPFLAGS = \
	${LLVM_CFLAGS}  \
	-fexceptions


fatso_LDADD = \
	${LLVM_LIBS} \
	${LLVM_LDFLAGS} 



fatso_SOURCES = \
	lexer.h \
	lexer.cpp \
	parser.h \
	parser.cpp \
	ast.h \
	ast.cpp \
	$(NULL)

