CC = gcc
CFLAGS =-lSDL2 -Wall -Wextra -lSDL2_image
LDFLAGS = -lSDL2 -Wall -Wextra -lSDL2_image

#liste des fichiers source
SRC = $(wildcard *.c) 

HEADERS = $(wildcard *.h) 

#liste des fichiers objets
OBJ = $(SRC:%.c=%.o)

main : $(HEADERS) $(OBJ) 
	$(CC) $(OBJ) -o $@ $(LDFLAGS)
	
affichage.o :affichage.c 
	$(CC) $(CFLAGS) -c $< 

arbre.o :arbre.c 
	$(CC) $(CFLAGS) -c $< 

point.o : point.c 
	$(CC) $(CFLAGS) -c $< 


.PHONY: clean reclean

clean:
	rm -f $(OBJ)

reclean:
	rm -f $(OBJ) main