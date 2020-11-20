CC = gcc
CFILES = *.c
HFILES = *.h
OBJETOS = abb.o
FILES = Enunciado README.md makefile
EXEC = abb
CFLAGS =  -g -std=c99 -Wall -Wconversion -Wtype-limits -pedantic -Werror -O0
GFLAGS = --tui
VFLAGS = --leak-check=full --track-origins=yes --show-reachable=yes 

$(EXEC): abb_minipruebas.c $(OBJETOS)
	$(CC) $^ $(CFLAGS) -o $(EXEC)

debug: $(EXEC)
	gdb $(GFLAGS) $(EXEC)

test: $(EXEC)
	valgrind $(VFLAGS) ./$(EXEC) $(arg_1) $(arg_2) $(arg_3)

run: $(EXEC)
	./$(EXEC) $(arg_1) $(arg_2) $(arg_3)

%.o: %.c %.h
	$(CC) $(CFLAGS) -c $< -o $@

zip: 
	zip -r $(EXEC).zip $(CFILES) $(HFILES) $(FILES)

.PHONY: clean
clean:
	rm -f *.o $(EXEC)