#include "plateau.h"
#include "palette.h"

void afficher_palette_pieces(ElemTabCouleur** tab,int nb_couleurs,SDL_Surface* surface){

	ElemTabCouleur* tmp;
	int i=0;
	int gFullScreenH = SDL_GetVideoInfo()->current_h;
	int gFullScreenW = SDL_GetVideoInfo()->current_w;
    double taille_case=gFullScreenH/15;
    double rayon=gFullScreenH/45;//le 1/3 la taille de la case
    double x=0;
	double y=0;
    Piece* p=malloc(sizeof(Piece*));
    case_plateau* c=malloc(sizeof(case_plateau*));
    SDL_Surface* rectangle;
    
	for(i=0;i<nb_couleurs;i++){
		tmp=tab[i];
		if(tmp){
			if(tmp->nbPiecesCl !=0){
				//il y a une piece de cette couleur			c=creer_case(x,y,rayon*3,0);
				c=creer_case(x,y,taille_case,0);
				p->rayon=rayon;
				p->couleur=tmp->couleur;
				p->c=c;
				afficher_piece(p,surface,rectangle);
				x+=taille_case;
			
			}
	}
	}

}

void afficher_palette_cases(ElemTabCouleur** tab,int nb_couleurs,SDL_Surface* surface){
	ElemTabCouleur* tmp;
	int i=0;
	int gFullScreenH = SDL_GetVideoInfo()->current_h;
	int gFullScreenW = SDL_GetVideoInfo()->current_w;
    double taille_case=gFullScreenH/15;
    double x=0;
	double y=0;
    case_plateau* c=malloc(sizeof(case_plateau*));
    SDL_Surface* rectangle;
    SDL_Rect position;
    position.x=0;
    position.y=0;

	for(i=0;i<nb_couleurs;i++){
		tmp=tab[i];
		if(tmp){
			if(tmp->nbCasesCl !=0){
				//il y a une case de cette couleur
				//case_plateau* creer_case(double x,double y,double taille,Uint32 couleur);
				c=creer_case(x,y,taille_case,tmp->couleur);
				afficher_case(c,surface,rectangle);
				position.x+=taille_case;
				x+=taille_case;
			
			}
	}
	}
}

void afficher_pile(double largeur_pile,double hauteur_pile,int nb_pieces,Uint32* tab_pile,SDL_Surface* ecran){

		double hauteur_rectangle=(double)hauteur_pile/nb_pieces;
		//largeur_rectangle=largeur_pile
		SDL_Surface * rectangle;
		SDL_Rect position_rect;
		position_rect.x=0;
		position_rect.y=hauteur_pile-hauteur_rectangle;
		int i=0;
		for(i=0;i<nb_pieces;i++){
			rectangle=SDL_CreateRGBSurface(SDL_HWSURFACE,largeur_pile,hauteur_rectangle,32,0,0,0,0);
			SDL_FillRect(rectangle,NULL,tab_pile[i]);
			SDL_BlitSurface(rectangle,NULL,ecran,&position_rect);
			position_rect.y-=hauteur_rectangle-1;
		}
		


}

	

