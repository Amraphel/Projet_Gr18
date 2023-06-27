CC = gcc
CFLAGS =-lSDL2 -Wall -Wextra -lSDL2_image
LDFLAGS =

#liste des fichiers source
SRC = $(wildcard *.c) 

HEADERS = $(wildcard *.h) 

#liste des fichiers objets
OBJ = $(SRC:%.c=%.o)

main : $(HEADERS) $(OBJ) 
	$(CC) $(OBJ) -o $@ $(LDFLAGS)
	
affichage.o :point.c arbre.h affichage.h affichage.c
	$(CC) $(CFLAGS) -c $< -o $@

arbre.o :point.c arbre.c arbre.h 
	$(CC) $(CFLAGS) -c $< -o $@

point.o : point.c point.h
	$(CC) $(CFLAGS) -c $< -o $@


.PHONY: clean reclean

clean:
	rm -f $(OBJ)

reclean:
	rm -f $(OBJ) main