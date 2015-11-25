CPP=gcc    #Commande du compilateur
LDFLAGS=-lSDL -lSDLmain -lSDL_ttf -lm #Linker

all: jeu

graph_model.o :graph_model.c
	${CPP} -g -c -o graph_model.o graph_model.c ${LDFLAGS}
	
plateau.o : plateau.c 
	${CPP} -g -c -o plateau.o plateau.c ${LDFLAGS}
	
palette.o :	palette.c 
	${CPP} -g -c -o palette.o palette.c ${LDFLAGS} 
	
mouvements.o : mouvements.c
	${CPP} -g -c -o mouvements.o mouvements.c ${LDFLAGS} 
	
text.o : text.c
	${CPP} -g -c -o text.o text.c ${LDFLAGS} 
	
main.o : main.c
	${CPP} -g -c -o main.o main.c ${LDFLAGS}
	
jeu: main.o plateau.o palette.o mouvements.o text.o graph_model.o
	${CPP} -g -o jeu main.o plateau.o palette.o mouvements.o text.o graph_model.o ${LDFLAGS} 


clean:	
	rm -fr *.o

mrproper: clean
	rm -fr plateau

