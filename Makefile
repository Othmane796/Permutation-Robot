CPP=gcc    #Commande du compilateur
LDFLAGS=-lSDL -lSDLmain -lSDL_ttf -lm #Linker

SRC= $(wildcard *.c)
OBJ= $(SRC:.c=.o)

all: jeu

%.o: %.c %.h
	${CPP} -g -c -o $@ $< ${LDFLAGS}
	echo $(SRC)
	echo $(OBJ)
	
jeu: $(OBJ)
	${CPP} -g -o $@ $^ ${LDFLAGS} 

clean:	
	rm -fr *.o

mrproper: clean
	rm -fr plateau

