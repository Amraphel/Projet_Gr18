CC = gcc
CFLAGS =-lSDL2 -Wall -Wextra -lSDL2_image
LDFLAGS = -lSDL2 -Wall -Wextra -lSDL2_image

#liste des fichiers source
SRC = $(wildcard *.c) 

HEADERS = $(wildcard *.h) 

#liste des fichiers objets
OBJ = $(SRC:%.c=%.o)

drawEssai: $(HEADERS) $(OBJ) 
	$(CC) $(OBJ) -o $@ $(LDFLAGS)
	


.PHONY: clean reclean

clean:
	rm -f $(OBJ)

reclean:
	rm -f $(OBJ) drawEssai