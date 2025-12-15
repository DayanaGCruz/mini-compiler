CC = gcc
LEX = flex
YACC = bison
CFLAGS = -g -Wall

# Simple build pipeline: run Flex/Bison to refresh the scanner and parser, then
# compile each C translation unit before linking everything into `minicompiler`.

TARGET = minicompiler
OBJS = lex.yy.o parser.tab.o main.o ast.o symtab.o codegen.o tac.o errors.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

lex.yy.c: scanner.l parser.tab.h
	$(LEX) scanner.l

parser.tab.c parser.tab.h: parser.y
	$(YACC) -d parser.y

lex.yy.o: lex.yy.c
	$(CC) $(CFLAGS) -c lex.yy.c

parser.tab.o: parser.tab.c
	$(CC) $(CFLAGS) -c parser.tab.c

main.o: main.c ast.h codegen.h tac.h
	$(CC) $(CFLAGS) -c main.c

ast.o: ast.c ast.h
	$(CC) $(CFLAGS) -c ast.c

symtab.o: symtab.c symtab.h
	$(CC) $(CFLAGS) -c symtab.c

codegen.o: codegen.c codegen.h ast.h symtab.h
	$(CC) $(CFLAGS) -c codegen.c

tac.o: tac.c tac.h ast.h
	$(CC) $(CFLAGS) -c tac.c

errors.o: errors.c errors.h
	$(CC) $(CFLAGS) -c errors.c

clean:
	rm -f $(TARGET) $(OBJS) lex.yy.c parser.tab.c parser.tab.h *.s

.PHONY: all clean
