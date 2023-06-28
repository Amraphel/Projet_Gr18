CC = gcc
CFLAGS =-g -fsanitize=undefined -Wall -Wextra 
LDFLAGS =-g -fsanitize=undefined -lSDL2 -Wall -Wextra -lSDL2_image -lm -lSDL2_ttf

#liste des fichiers source
SRC = $(wildcard *.c) 

HEADERS = $(wildcard *.h) 

#liste des fichiers objets
OBJ = $(SRC:%.c=%.o)

main : $(HEADERS) $(OBJ) 
	$(CC) $(OBJ) -o $@ $(LDFLAGS)
	
affichage.o :affichage.c 
	$(CC) $(CFLAGS) -c $< 

graphe.o :graphe.c 
	$(CC) $(CFLAGS) -c $< 

point.o : point.c 
	$(CC) $(CFLAGS) -c $< 


.PHONY: clean reclean

clean:
	rm -f $(OBJ)

reclean:
	rm -f $(OBJ) main