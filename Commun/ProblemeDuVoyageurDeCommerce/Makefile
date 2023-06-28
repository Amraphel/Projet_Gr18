CC = clang
CFLAGS =-g -fsanitize=undefined,memory -Wall -Wextra 
LDFLAGS =-g -fsanitize=undefined,memory -lSDL2 -Wall -Wextra -lSDL2_image -lm

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