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
	 printf("The purpose of this game is to move the colored circles (pieces) inside the squares (spots) with the same color, while minimizing the score.\nThe score is incremented by 1 each time we move a different color from the one we moved before.\nIn order to move a piece all you have to do is click on it.\nThere is also a stack on the right to help you see how many color changes you made\n");
	 printf("How big you want the grid to be (ex : 4 squares 16 squares ...)?");
	 scanf("%d",&nb_cases);
	 printf("How many colors you want to use ?");
	 scanf("%d",&nb_couleurs);

	 while(1){
	 	if(!new){
		 	printf("Would you like to :\n0-Exit\n1-Play manually \n2-Let the first algorithme solve the puzzle \n3-Let the second algorithme solve the puzzle \n4-Help\n");
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
				printf("The purpose of this game is to move the colored circles (pieces) inside the squares (spots) with the same color, while minimizing the score.\nThe score is incremented by 1 each time we move a different color from the one we moved before.\nIn order to move a piece all you have to do is click on it.\nThere is also a stack on the right to help you see how many color changes you made\n");

			}
		}
	 	else{
			printf("Would you like to :\n0-Exit\n1-Play manually \n2-Let the first algorithme solve the puzzle \n3-Let the second algorithme solve the puzzle \n4-Help\n");
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
				printf("The purpose of this game is to move the colored circles (pieces) inside the squares (spots) with the same color, while minimizing the score.\nThe score is incremented by 1 each time we move a different color from the one we moved before.\nIn order to move a piece all you have to do is click on it.\nThere is also a stack on the right to help you see how many color changes you made\n");

			}
	 		}
	 	}




    return 0;

}
