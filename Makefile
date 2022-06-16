DIR := ${CURDIR}

exec = lexer.out
sources = $(wildcard src/*.c)
objects = $(sources:.c=.o)
flags = -g -Wall -fPIC -std=c11

$(exec): $(objects)
	gcc $(objects) $(flags) -o $(exec)

%.o: %.c include/%.h
	gcc -c $(flags) $< -o $@

clean:
	-rm *.out
	-rm *.o
	-rm *.a
	-rm src/*.o

run: $(exec)
	./lexer.out input.txt
