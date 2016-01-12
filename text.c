#include "text.h"

void afficher_text(SDL_Surface* ecran,char *mot,SDL_Color coul,SDL_Rect position_mot,int taille){

	
	if(TTF_Init() == -1){
		fprintf(stderr,"Erreur d'initialsiation de la SDL_TTF: %s \n",TTF_GetError());
		exit(EXIT_FAILURE);
	}
	
	TTF_Font* police=NULL;	
	
	police=TTF_OpenFont("keepcalm.ttf",taille);
	
	SDL_Surface* text=NULL;
	
	text=TTF_RenderText_Blended(police,mot,coul);
	SDL_BlitSurface(text,NULL,ecran,&position_mot);
	


}
