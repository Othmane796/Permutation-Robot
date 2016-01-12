#include "mouvements.h"

//Recupere le pixel qui se trouve dans la position x,y 
Uint32 getpixel(SDL_Surface *surface, int x, int y)
{
    int bpp = surface->format->BytesPerPixel;
    /* Here p is the address to the pixel we want to retrieve */
    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;

    switch(bpp) {
    case 1:
        return *p;

    case 2:
        return *(Uint16 *)p;

    case 3:
        if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
            return p[0] << 16 | p[1] << 8 | p[2];
        else
            return p[0] | p[1] << 8 | p[2] << 16;

    case 4:
        return *(Uint32 *)p;

    default:
        return 0;       /* shouldn't happen, but avoids warnings */
    }
}

//On recupere les cordonnées du click et on les mets dans x et y
void recuperer_coordonees(double *x,double *y){
	int continuer=1;
	SDL_Event event;
	while(continuer){
		SDL_WaitEvent(&event);
		switch(event.type)
		{	
			case SDL_KEYDOWN:
	        	if(event.key.keysym.sym == SDLK_ESCAPE)
	            	continuer = 0;
				
			case SDL_MOUSEBUTTONDOWN:
				*x=event.button.x;
				*y=event.button.y;		
				continuer=0;
				break;
		}
	}
	return ;
}

void recuperer_indices(double x0,double y0,double x,double y,double taille_cases,int *indice_i,int *indice_j){
//t est la taille de case x0 le point le plus haut a gauche en x
/*recuperer les (i;j) de la matrice en utilisant les coordonnees du click */
	*indice_i=0;
	*indice_j=0;
	int i=0;
	while(x > x0+(i*taille_cases)){
		i++;
		(*indice_j)++;
	}
	i=0;
	while(y > y0+(i*taille_cases)){
		i++;
		(*indice_i)++;
	}
	
	(*indice_i)--;
	(*indice_j)--;
	//printf("les coordonnées sont (%d,%d)\n",*indice_i,*indice_j);
	

}


//recuper la couleur du pixel a la position x ,y
Uint32 recuperer_couleur(SDL_Surface *surface,double x,double y){
		Uint32 coul;
	Uint8 rouge,vert,bleu;
	
	SDL_LockSurface(surface);
	
	x=(int)x;
	y=(int)y;

	SDL_GetRGB(getpixel(surface,x,y),surface->format,&rouge,&vert,&bleu);
	
	SDL_UnlockSurface(surface);
	coul=SDL_MapRGB(surface->format,rouge,vert,bleu);
	//printf("Uint32= %d is (%d,%d,%d) \n",coul,rouge,vert,bleu);
	return coul;

	
}

int bougerPiece(ElemTabCouleur* tab,Piece* p) {
	//tab est le tableau  de couleur coul_piece
	//Uint32 coulCase;
	//coulCase=p->c->couleur;
	
	int boolean=1,trouve=0;
	element* el=tab->ListePieceCl;//liste de pieces de cette couleur
	cellule* cel=tab->ListeCaseCl;//liste de cases de cette couleur 

	case_plateau* c;
	
	if(p->couleur==p->c->couleur)
		return 0;
		
	while(cel && boolean==1){
					c=cel->c;//on prend la premiere case de la liste
					if(c->p==NULL)
					{
					//si cette case ne contient pas de piece on met notre piece ici et on libere l'autre case
						c->p=p;
						p->c->p=NULL;
						p->c=c;
						boolean=0;
						trouve=1;
					}
					//sinon on passe a la case suivante
					else cel=cel->suivant;
				}
				if(boolean){
					boolean=0;
					trouve=0;
					}  	  	
	return trouve;
	

}
/*
int bougerPiece(ElemTabCouleur* tab,Uint32 coulCase){
	//tab est le tableau  de couleur coul_piece

	int boolean=1,trouve=0;
	element* el=tab->ListePieceCl;//liste de pieces de cette couleur
	cellule* cel=tab->ListeCaseCl;//liste de cases de cette couleur 
	Piece* p;
	case_plateau* c;
	while(el && boolean==1){
		p=el->p;
		c=p->c;
		
			if( c->couleur==coulCase){
			
				while(cel){
					c=cel->c;//on prend la premiere case de la liste
					if(c->p==NULL)
					{
					//si cette case ne contient pas de piece on met notre piece ici et on libere l'autre case

						p->c->p=NULL;
						c->p=p;
						p->c=c;
						boolean=0;
						trouve=1;
					}
					//sinon on passe a la case suivante
					else cel=cel->suivant;
				}
				if(boolean){
					boolean=0;
					trouve=0;
					}
			}
		else el=el->suivant;
	}
		   	  	
	return trouve;
}*/
int bougerPiece_bis(ElemTabCouleur* tab,case_plateau* c_click) {
	//tab est le tableau  de couleur coul_piece
	Uint32 coulCase;
	coulCase=c_click->couleur;
	
	int boolean=1,trouve=0;
	element* el=tab->ListePieceCl;//liste de pieces de cette couleur
	cellule* cel=tab->ListeCaseCl;//liste de cases de cette couleur 
	Piece* p=c_click->p;
	case_plateau* c;

				while(cel && boolean==1){
					c=cel->c;//on prend la premiere case de la liste
					if(c->p==NULL)
					{
					//si cette case ne contient pas de piece on met notre piece ici et on libere l'autre case
						c->p=p;
						p->c=c;
						c_click->p=NULL;
						boolean=0;
						trouve=1;
					}
					//sinon on passe a la case suivante
					else cel=cel->suivant;
				}
				if(boolean){
					boolean=0;
					trouve=0;
					}
			

	
		   	  	
	return trouve;
	

}



