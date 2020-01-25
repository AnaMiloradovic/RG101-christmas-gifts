PROGRAM   = main
CC        = gcc
CFLAGS    = -g -Wall
LDFLAGS   = -lGL -lGLU -lglut -lm -std=c99
FAJLOVI   = komande.c objekti.c logika.c

$(PROGRAM): $(PROGRAM).c $(FAJLOVI)
	$(CC) -o $(PROGRAM) $(PROGRAM).c $(FAJLOVI) $(LDFLAGS)

.PHONY: clean dist

clean:
	-rm *.o $(PROGRAM) *core

dist: clean
	-tar -chvj -C .. -f ../$(PROGRAM).tar.bz2 $(PROGRAM)


