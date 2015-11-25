#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include "plateau.h"
#include "mouvements.h"
#include <time.h>
#include <math.h>

int main(){

	 unsigned int seed;
	 int nb_cases,nb_couleurs,choix;
	 int new=0;
	 printf("Le but du jeu est de déplacer les pièces de couleur dans des cases de même couleur en faisant le moins de changements de couleurs possibles\nOn dit qu'on a fait un changement de couleur lorsqu'on a bougé une pièce d'une couleur differente à celle qu'on a bougé precedemment.\nPour bouger les pièces il suffit de cliquer sur elles sur le plateau de jeu\nVous disposez d'une pile à droite du tableau qui montre les couleurs des pièces que vous avez bougé\n");
	 
	 printf("Entrez le nb de cases:");
	 scanf("%d",&nb_cases);
	 printf("Entrez le nb de couleur:");
	 scanf("%d",&nb_couleurs);
	 
	 while(1){
	 	if(!new){
		 	printf("Que voulez vous faire:\n0-Quitter\n1-Jouer vous meme \n2-Laisser notre premier algo jouer\n3-Laisser notre deuxieme algo jouer\n4-Aide\n");
		 	scanf("%d",&choix);
		 	if(!choix)
		 		return 0;
		 	if(choix!=4){
			 	seed=rand()*1000000;
			 	srand(seed);
			 	jeu(nb_cases,nb_couleurs,choix);
			 	new=1;
			 }
			else{
				printf("Le but du jeu est de déplacer les pièces de couleur dans des cases de même couleur en faisant le moins de changements de couleurs possibles\nOn dit qu'on a fait un changement de couleur lorsqu'on a bougé une pièce d'une couleur differente à celle qu'on a bougé precedemment.\nPour bouger les pièces il suffit de cliquer sur elles sur le plateau de jeu\nVous disposez d'une pile à droite du tableau qui montre les couleurs des pièces que vous avez bougé\n");
			
			}
		}
	 	else{
	 		printf("Que voulez vous faire:\n0-Quitter\n1-Rejouer la même instance vous meme \n2-Laisser notre premier algo jouer la meme instance \n3-Laisser notre deuxieme algo jouer la meme instance \n4-Jouer avec une autre instance\n5-Aide\n");
	 		scanf("%d",&choix);
	 		if(!choix)
	 			return 0;
	 		if(choix==1 || choix ==2 || choix ==3){
	 			srand(seed);
	 			jeu(nb_cases,nb_couleurs,choix);
	 		}
	 		if(choix==4)
	 			new=0;
	 		if(choix ==5){
				printf("Le but du jeu est de déplacer les pièces de couleur dans des cases de même couleur en faisant le moins de changements de couleurs possibles\nOn dit qu'on a fait un changement de couleur lorsqu'on a bougé une pièce d'une couleur differente à celle qu'on a bougé precedemment.\nPour bouger les pièces il suffit de cliquer sur elles sur le plateau de jeu\nVous disposez d'une pile à droite du tableau qui montre les couleurs des pièces que vous avez bougé\n");
			
			}
	 		}	
	 	}	
	 	
	 
	 
    
    return 0;

}
/*#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include "plateau.h"
#include "mouvements.h"
#include <time.h>
#include <math.h>

int main(){

    srand(time(NULL));
    jeu();
    return 0;

}*/
