NAME := gouge

cpp_files := exceptions types object function

all: ${NAME}.exe

${NAME}.exe: y.tab.c y.tab.h lex.yy.c declaration.c declaration.h
	gcc -o ${NAME}.exe declaration.c y.tab.c lex.yy.c -ll -ly -mmacosx-version-min=14.0

lex.yy.c: ${NAME}_lexer.l
	lex ${NAME}_lexer.l

y.tab.c y.tab.h: ${NAME}_parser.y
	yacc -d ${NAME}_parser.y

clean:
	rm lex.yy.c ${NAME}.exe y.tab.c y.tab.h

test_files := exceptions

add_suffix = $(foreach element,$(1),$(element).$2)

test_headers := $(call add_suffix,$(test_files),hpp)
test_cpp := $(call add_suffix,$(test_files),cpp)

test:
	g++ -std=c++11 -c -o test.o $(test_cpp)
