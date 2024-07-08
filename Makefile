NAME := gouge

files := exceptions types object function

add_suffix = $(foreach element,$(1),$(element).$2)

cpp_files := $(call add_suffix,$(files),cpp)
o_files := $(call add_suffix,$(files),o)

CXX = g++
CXXFLAGS = -std=c++11

all: ${NAME}.exe

${NAME}.exe: ${NAME}.o ${o_files} lex.yy.o
	$(CXX) $(CXXFLAGS) ${NAME}.o lex.yy.o ${o_files} -o $@ -mmacosx-version-min=14.0

lex.yy.o: lex.yy.c
	gcc -c lex.yy.c -o lex.yy.o -mmacosx-version-min=14.0

${NAME}.o: y.tab.c y.tab.h
	gcc -c -o $@ y.tab.c -mmacosx-version-min=14.0


lex.yy.c: ${NAME}_lexer.l
	lex ${NAME}_lexer.l

y.tab.c y.tab.h: ${NAME}_parser.y
	yacc -d ${NAME}_parser.y

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm lex.yy.c ${NAME}.exe y.tab.c y.tab.h *.o *~

test_files := object

test_headers := $(call add_suffix,$(test_files),hpp)
test_cpp := $(call add_suffix,$(test_files),cpp)

test:
	g++ -std=c++11 -c -o test.o $(test_cpp)
