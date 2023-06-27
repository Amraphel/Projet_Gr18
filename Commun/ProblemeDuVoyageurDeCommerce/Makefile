CC = gcc
CFLAGS = -Wall -Wextra -g
LDFLAGS =


#liste des fichiers source
SRC = $(wildcard $(DIRCOMM)*.c *.c) 

HEADERS = $(wildcard $(DIRCOMM)*.h *.h) 

#liste des fichiers objets
OBJ = $(SRC:%.c=%.o)

main: $(OBJ) $(HEADERS)
	$(CC) $(OBJ) -o $@ $(LDFLAGS)
	
affichage.o: affichage.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

arbre.o: arbre.c arbre.h
	$(CC) $(CFLAGS) -c $< -o $@


.PHONY: clean reclean

clean:
	rm -f $(OBJ)

reclean:
	rm -f $(OBJ) main