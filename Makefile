NAME := gouge

all: ${NAME}.exe

${NAME}.exe: y.tab.c y.tab.h lex.yy.c declaration.c declaration.h
	gcc -o ${NAME}.exe declaration.c y.tab.c lex.yy.c -ll -ly -mmacosx-version-min=14.0

lex.yy.c: ${NAME}_lexer.l
	lex ${NAME}_lexer.l

y.tab.c y.tab.h: ${NAME}_parser.y
	yacc -d ${NAME}_parser.y

clean:
	rm lex.yy.c ${NAME}.exe y.tab.c y.tab.h
