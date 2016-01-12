#include "plateau.h"
#include "palette.h"
#include "mouvements.h"
#include "text.h"
#include "graph_model.h"


/*---------------------------------------------------------------------------------------------------------------------------------------*/
/*-------------------------------------------------------------AUTRES--------------------------------------------------------------------*/
/*---------------------------------------------------------------------------------------------------------------------------------------*/

/*void clear_screen() {
  printf("\x1b[2J\x1b[1;1H");  // code ANSI X3.4 pour effacer l'ecran 
}
*/

void pause()
{
    SDL_Event event = {0};
    while(event.type != SDL_QUIT && event.key.keysym.sym != SDLK_ESCAPE)
        SDL_WaitEvent(&event);
}

int plateau_correct(Uint32* couleurs_plateau,Uint32* couleurs_piece,int tailleCoulPlat,int taillePieces){
	int i,j,k;
	int cmp=0;
	int cmpBis=0;
	Uint32 coulPiece;
	
	for(i=0;i<taillePieces;i++){
		coulPiece=couleurs_piece[i];
		//on compte le nb de piece i
		for(j=0;j<taillePieces;j++){
			if(coulPiece==couleurs_piece[j])
				cmp++;
		}
		
		for(k=0;k<tailleCoulPlat;k++){
			if(couleurs_plateau[k]==coulPiece)
				cmpBis++;
		}
		
		if(cmp>cmpBis)
			return 0;
			
		cmp=0;
		cmpBis=0;
		
	}
	
	return 1;
}


int placer_piece(Piece* p,case_plateau* c){
		if(p!=NULL && c->p==NULL && p->couleur!=c->couleur){
			c->p=p;
			p->c=c;
			return 1;
		}
		
		return 0;
}

int placer_pieces(int nb_cases,int nb_pieces,case_plateau** tableau_case,Piece** tableau_pieces){
	int i,aux;
	case_plateau* c;
	Piece* p;
	aux=0;
	for(i=0;i<nb_pieces;i++){
    		//On choisit la premiere case du plateau
			aux=0;
    		c=tableau_case[aux];
    		p=tableau_pieces[i];
    		//On cherche une case qui n'a pas de pièce et qui a une couleur differente de celle de la pièce
    		while(aux < nb_cases*nb_cases && !(placer_piece(p,c)) ){
    			aux++;
    			c=tableau_case[aux];
    			
    		}
    		
    		if(aux==nb_cases*nb_cases)
    			return 0;
    	
   }
   return 1;
}
void echanger_elem_tab(Uint32 tab[], int i, int j)
	{
	Uint32 t = tab[i];
	tab[i] = tab[j];
	tab[j] = t;
	}
void triBulle(Uint32 tab[], int n)
{
int i ,j;

        for( i=0;  i < n-1 ; i++){
            for( j=0 ;	 j < n-1-i  ; j++){
              if(tab[j] > tab[j+1])
               echanger_elem_tab(tab,j ,j+1);
                
               }
           }
}

/*---------------------------------------------------------------------------------------------------------------------------------------*/
/*-------------------------------------------------------------CREATION -----------------------------------------------------------------*/
/*---------------------------------------------------------------------------------------------------------------------------------------*/
Piece* creer_piece(double rayon,Uint32 couleur){
	Piece* p=malloc(sizeof(Piece));
	p->couleur=couleur;
	p->rayon=rayon;
	p->c=NULL;
	
	return p;
}
case_plateau* creer_case(double x,double y,double taille,Uint32 couleur){
    case_plateau* c=malloc(sizeof(case_plateau));
    c->x=x;
    c->y=y;
    c->couleur=couleur;
    c->taille=taille;
    c->p=NULL;
    return c;
}

case_plateau** creer_cases(int taille_cases,int nb_cases,Uint32* couleurs_plateau){
	int i,j;
	case_plateau** tableau_case=malloc(sizeof(case_plateau*)*nb_cases*nb_cases);
	double x,y;
	x=0;
	y=0;
   
	for(i=0;i<nb_cases;i++){
        for(j=0;j<nb_cases;j++){
         tableau_case[i*nb_cases+j]=creer_case(x,y,taille_cases,couleurs_plateau[i*nb_cases+j]);  	
        	x+=taille_cases;
        }
        
        x=0;
        y+=taille_cases;
   }
   return tableau_case;
}

Piece** creer_pieces(int nb_pieces,int rayon,Uint32* couleurs_piece){
	 
	 int i;
	 Piece** p=malloc(sizeof(Piece*)*nb_pieces);
	 for(i=0;i<nb_pieces;i++){
    		p[i]=creer_piece(rayon,couleurs_piece[i]);
    }
    
    return p;
}
/*les palette de couleurs*/
Uint32** creer_palettes(SDL_Surface* ecran,int nb_couleurs,int nb_cases,int nb_pieces){
	
	int i,j;
	int boolean;
	Uint32 coul_aux;
	Uint32* couleurs=malloc(sizeof(Uint32)*nb_couleurs);
   Uint32* couleurs_plateau=malloc(sizeof(Uint32)*nb_cases*nb_cases);
   Uint32* couleurs_piece=malloc(sizeof(Uint32)*nb_pieces);
   
   Uint32** tab=malloc(sizeof(Uint32*)*3);
   
   for(i=0;i<nb_couleurs;i++)
      couleurs[i]=SDL_MapRGB(ecran->format,rand()%256,rand()%256,rand()%256);
   
   
   do
   {

    	for(i=0;i<nb_cases;i++){
        	for(j=0;j<nb_cases;j++){
        		//On choisit une couleur au hasard
        		if((i*nb_cases+j)<nb_couleurs)
        			coul_aux=couleurs[i*nb_cases+j];
        		else coul_aux=couleurs[rand()%nb_couleurs];
        		
        		if((i*nb_cases+j)<nb_pieces)
        			couleurs_piece[i*nb_cases+j]=coul_aux;
        			
            couleurs_plateau[i*nb_cases+j]=coul_aux;

       		}
    	}

   }
   while(plateau_correct(couleurs_plateau,couleurs_piece,nb_cases*nb_cases,nb_pieces)==0);

	triBulle(couleurs_plateau,nb_cases*nb_cases);
	tab[0]=couleurs;
	tab[1]=couleurs_plateau;
	tab[2]=couleurs_piece;
	
	return tab;
}

/*---------------------------------------------------------------------------------------------------------------------------------------*/
/*-------------------------------------------------------------AFFICHAGE-----------------------------------------------------------------*/
/*---------------------------------------------------------------------------------------------------------------------------------------*/

void afficher_piece(Piece *p,SDL_Surface* ecran,SDL_Surface* rectangle){
	
	int i,j,k;
	double taille=p->c->taille;
	double x_coin,y_coin;
	Uint32 couleur=p->couleur;
	x_coin=p->c->x;
	y_coin=p->c->y;
	double x_centre=x_coin+(taille/2);
	double y_centre=y_coin+(taille/2);
	SDL_Rect position;

	//On parcourt notre case en question 
		for(i=x_coin;i<x_coin+taille;i++){
			for(j=y_coin;j<y_coin+taille;j++){
			//Si le point de coordonnées (i,j) se trouve dans le disque de centre (x,y) et de rayon "rayon"
				if((i-x_centre)*(i-x_centre)+(j-y_centre)*(j-y_centre)<=pow(p->rayon,2)){
				 position.x=i;
				 position.y=j;
				 //On affiche un pixel à cet endroit
				 rectangle = SDL_CreateRGBSurface(SDL_HWSURFACE,1,1, 32, 0, 0, 0, 0);
    			 SDL_FillRect(rectangle, NULL,couleur);
    			 SDL_BlitSurface(rectangle, NULL, ecran, &position);
				}
		}
	}
}

void affiche_piece_vide(case_plateau* c,SDL_Surface* surface,SDL_Surface* rectangle){
	Piece* aux=malloc(sizeof(Piece));
	aux->rayon=(1.0/3)*c->taille;
   aux->couleur=SDL_MapRGB(surface->format,0,0,1);
   aux->c=c;
   afficher_piece(aux,surface,rectangle);
}

void afficher_case(case_plateau* c,SDL_Surface* ecran,SDL_Surface* rectangle){
	 SDL_Rect position;
	 
	 position.x=c->x;
	 position.y=c->y;
	 
	 int x=position.x;
	 int y=position.y;
	 Uint32 noir=SDL_MapRGB(ecran->format,0,0,1);
    rectangle = SDL_CreateRGBSurface(SDL_HWSURFACE,c->taille,c->taille, 32, 0, 0, 0, 0);
    SDL_FillRect(rectangle, NULL,c->couleur);
    SDL_BlitSurface(rectangle, NULL, ecran, &position);
    
    if(c->p!=NULL)
        afficher_piece(c->p,ecran,rectangle);
    else{
        affiche_piece_vide(c,ecran,rectangle);
        }
        
    //Ligne horizontale superieure
    rectangle = SDL_CreateRGBSurface(SDL_HWSURFACE,c->taille,1, 32, 0, 0, 0, 0);
    SDL_FillRect(rectangle, NULL,noir);
    SDL_BlitSurface(rectangle, NULL, ecran, &position);
    
    //Ligne horizontale inferieure
    position.y+=c->taille;
    rectangle = SDL_CreateRGBSurface(SDL_HWSURFACE,c->taille,1, 32, 0, 0, 0, 0);
    SDL_FillRect(rectangle, NULL,noir);
    SDL_BlitSurface(rectangle, NULL, ecran, &position);
    
    position.y=y;
    //Ligne verticale gauche
    rectangle = SDL_CreateRGBSurface(SDL_HWSURFACE,1,c->taille, 32, 0, 0, 0, 0);
    SDL_FillRect(rectangle, NULL,noir);
    SDL_BlitSurface(rectangle, NULL, ecran, &position);
    
    //Ligne verticale droite
    position.x+=c->taille;
    rectangle = SDL_CreateRGBSurface(SDL_HWSURFACE,1,c->taille, 32, 0, 0, 0, 0);
    SDL_FillRect(rectangle, NULL,noir);
    SDL_BlitSurface(rectangle, NULL, ecran, &position);
	 
	

}


void afficher_plateau(double taille_cases,int nb_cases,case_plateau** tableau_case,SDL_Surface* surface,SDL_Surface* rectangle){
	 int i,j;
	 Uint32 coul_aux;
	 SDL_Rect position;
    position.x = 0;
    position.y = 0;
    case_plateau* c;
	 for(i=0;i<nb_cases;i++){
        for(j=0;j<nb_cases;j++){

			c=tableau_case[i*nb_cases+j];
			coul_aux=c->couleur;
			afficher_case(c,surface,rectangle);
			position.x+=taille_cases;
        }
        position.x=0;
        position.y+=taille_cases;
    }
}

/*---------------------------------------------------------------------------------------------------------------------------------------*/
/*---------------------------------------------CREATION DE STRUCTURES+TEST AFFICHAGE----------------------------------------------------*/
/*---------------------------------------------------------------------------------------------------------------------------------------*/

cellule* insertionCellule(cellule* liste,case_plateau* Case){

	cellule* new_cellule=malloc(sizeof(cellule));
	new_cellule->c=Case;
	new_cellule->suivant=liste;
	return new_cellule;
}

element* insertionElement(element* liste,Piece *Piece){

	element* new_element=malloc(sizeof(element));
	new_element->p=Piece;
	new_element->suivant=liste;
	return new_element;

}

element* suppTeteElem(element* el){
	element* tmp;
	
	//Si la liste est vide on la renvoie
	if(el==NULL){
		return el;
	}else{
	tmp=el;
	el=tmp->suivant;
	tmp->p=NULL;
	free(tmp);
	return el;
	}
}
cellule* suppCellule(cellule* cel,case_plateau* c){
	cellule* tmp;
	cellule* tmp2;
	
	//Si la liste est vide on la renvoie
	if(cel==NULL)
		return cel;
	
	//Cas particulier ou la piece (plutoto la case)à enlever est en tete de liste

	tmp=cel;
	if(tmp->c==c){
		cel=tmp->suivant;
		tmp->c=NULL;
		free(tmp);
		return cel;
	}
	
	tmp2=tmp;
	tmp=tmp->suivant;
	while(tmp && tmp->c!=c){
		tmp2=tmp;
		tmp=tmp->suivant;
	}
	
	if(tmp){
		tmp2->suivant=tmp->suivant;
		tmp->c=NULL;
		free(tmp);
		return cel;
	}
}
ElemTabCouleur**  creerElem(case_plateau** tabCases,Piece** tabPieces,int nb_couleurs,int nb_cases,int nb_pieces,Uint32* couleurs){
	
	int i,j,k;
	cellule* tmp;
	element* tmp2;
	Uint32 couleur;
	ElemTabCouleur** tab=(ElemTabCouleur**)malloc(sizeof(ElemTabCouleur*)*nb_couleurs);

	for(j=0;j<nb_couleurs;j++){
		tab[j]=malloc(sizeof(ElemTabCouleur));
		tab[j]->couleur=couleurs[j];
		tab[j]->nbPiecesCl=0;
		tab[j]->nbCasesCl=0;
		
		//On fixe la premiere couleur
		for(i=0;i<nb_cases*nb_cases;i++){
		//On parcourt le tableau de cases et on incremente le compteur des qu'on a la même couleur
			if(tabCases[i]->couleur==tab[j]->couleur)
				(tab[j]->nbCasesCl)++;
		}
		//Même chose pour le tableau de pieces
		for(k=0;k<nb_pieces;k++){
			if(tabPieces[k]->couleur==tab[j]->couleur)
				(tab[j]->nbPiecesCl)++;
		}
	}

	//Donc la on a , pour chaque couleur le nombre de cases de cette couleur et le nombre de pieces de cette couleur
	for(i=0;i<nb_couleurs;i++){
	//On peut donc allouer exactement la memoire qu'il faut
		tab[i]->ListeCaseCl=malloc(sizeof(cellule)*(tab[i]->nbCasesCl));
		tab[i]->ListePieceCl=malloc(sizeof(element)*(tab[i]->nbPiecesCl));
		
		tmp=NULL;
		tmp2=NULL;

		for(j=0;j<nb_cases*nb_cases;j++){
			if(tabCases[j]->couleur==tab[i]->couleur)
				//ajout en tete de liste
				tmp=insertionCellule(tmp,tabCases[j]);
			
		}
		
		
		for(j=0;j<nb_pieces;j++){
			if(tabPieces[j]->couleur==tab[i]->couleur)	
				//pareil
				tmp2=insertionElement(tmp2,tabPieces[j]);
		}
		
		tab[i]->ListeCaseCl=tmp;
		tab[i]->ListePieceCl=tmp2;

	}
return tab;
}
void afficher_elem_tab(ElemTabCouleur* tab,int nb_couleurs){
	int i;
	
	for(i=0;i<nb_couleurs;i++){
		
		printf("tab[%d].nbCasesCl= %d \n",i,tab[i].nbCasesCl);
		//Même chose pour le tableau de pieces
		printf("tab[%d].nbPiecesCl= %d \n",i,tab[i].nbPiecesCl);
	}
	
	for(i=0;i<nb_couleurs;i++){
		printf("Dans ce plateau de jeu il y a %d cases et %d pieces de couleur %d\n",tab[i].nbCasesCl,tab[i].nbPiecesCl,tab[i].couleur);
   }
   
}
void IA(ElemTabCouleur** tab,int nb_pieces,int nb_couleurs,SDL_Surface* ecran,SDL_Surface* surface_jeu,SDL_Rect position_plateau,SDL_Rect position_cmpt){
	
	SDL_Surface* rectangle;
	SDL_Color black={0,0,0};

	case_plateau* case_courante;
	case_plateau* case_precedente;
	cellule* cel=NULL;
	element* elem=NULL;
	
	
	int cmpt=0,i;
	int bool=1;
	int cmpt_changements=0;
	ElemTabCouleur** tab_tmp = tab;
	
		while(cmpt != nb_pieces){
		
			for(i=0;i<nb_couleurs;i++){
				bool=1;
				//on prend la liste de piecs de i-eme couleur
				elem=tab_tmp[i]->ListePieceCl;
				cel=tab_tmp[i]->ListeCaseCl;
				
				while(elem != NULL && bool){//tant qu'il y des pieces et qu'on se bloque pas
					
					case_precedente=elem->p->c;
					
						if(bougerPiece(tab_tmp[i],elem->p)){
							case_courante=elem->p->c;
							
							//enlever la pieces et la case d'arriver de la liste chainée
							elem=suppTeteElem(elem);	
							cel=suppCellule(cel,case_courante);
							//Mettre a jour les deux liste vu qu'on reparcours avant de passer a une autre couleur
							tab[i]->ListeCaseCl=cel;
							tab[i]->ListePieceCl=elem;
							
							afficher_case(case_precedente,surface_jeu,rectangle);
							afficher_case(case_courante,surface_jeu,rectangle);
							SDL_BlitSurface(surface_jeu,NULL,ecran,&position_plateau);
							cmpt++;

							SDL_Flip(ecran);
		
						}else{														
							//afficher_text(ecran,"Ce deplacement n'est pas possible",black,position_mot);
							SDL_Flip(ecran);
							cmpt_changements++;
							bool=0;
							}
					}

				
				
			}
		}
		
	char changements[256];
	sprintf(changements, "cmpt: %d",cmpt_changements);//fonction chelou qui transforme du int au char
	afficher_text(ecran,changements,black,position_cmpt,50);//ma fonction afficher text prend un char  va dans text.c
	SDL_Flip(ecran);
	}



void jeu(int nb_cases,int nb_couleurs,int choix){

	int i,j,k;
	//int nb_couleurs,nb_cases,nb_pieces,choix;
	int gFullScreenW;
	int gFullScreenH; 
	/*printf("Entrez le nb de cases:");
	scanf("%d",&nb_cases);
	printf("Entrez le nb de couleur:");
	scanf("%d",&nb_couleurs);
	printf("Quel mode de jeu ?\n 1-Vous jouez \n 2-L'IA \n 3-graph \n");
	scanf("%d",&choix);*/

	int nb_pieces=(int)((3.0/4)*nb_cases*nb_cases);
	if(nb_pieces>=nb_cases*nb_cases){
		exit(EXIT_FAILURE);
	}

	if(SDL_Init(SDL_INIT_VIDEO) < 0){
		printf("unable to init SDL\n");
		exit(EXIT_FAILURE);
	}


	gFullScreenW = SDL_GetVideoInfo()->current_w;
	gFullScreenH = SDL_GetVideoInfo()->current_h;
	SDL_Rect position;
	SDL_Rect position_plateau;
	SDL_Rect position_palette_cases;
	SDL_Rect position_palette_pieces;

	position.x=0;
	position.y=0;
	double taille=((double)gFullScreenW)/3;
	double taille_cases=taille/nb_cases;
	double rayon=(((double)1)/3)*taille_cases;
  
   
	SDL_WM_SetCaption("Plateau de jeu", NULL);
	SDL_Surface* ecran = SDL_SetVideoMode(gFullScreenW,gFullScreenH, 32,SDL_HWSURFACE);
	SDL_Surface* fond=SDL_LoadBMP("fond.bmp");
	SDL_BlitSurface(fond,NULL,ecran,&position);	
	SDL_Surface* rectangle;


	Uint32** coul = creer_palettes(ecran,nb_couleurs,nb_cases,nb_pieces);

	case_plateau** plateau = creer_cases(taille_cases,nb_cases,coul[1]);
	
	Piece** tab_pieces = creer_pieces(nb_pieces,rayon,coul[2]);
	
	while(!placer_pieces(nb_cases,nb_pieces,plateau,tab_pieces)){
		coul = creer_palettes(ecran,nb_couleurs,nb_cases,nb_pieces);
		plateau = creer_cases(taille_cases,nb_cases,coul[1]);
		tab_pieces = creer_pieces(nb_pieces,rayon,coul[2]);
		//printf("boucle\n");
	}
	
	ElemTabCouleur** tab = creerElem(plateau,tab_pieces,nb_couleurs,nb_cases,nb_pieces,coul[0]);

   /*-----------------------------------------------------CREATION DU PLATEAU-----------------------------------------------------*/ 
	SDL_Surface* surface_jeu=SDL_CreateRGBSurface(SDL_HWSURFACE,gFullScreenW/3,gFullScreenW/3, 32, 0, 0, 0, 0);
	afficher_plateau(taille_cases,nb_cases,plateau,surface_jeu,rectangle);
	position_plateau.x = gFullScreenW/30;
    position_plateau.y = gFullScreenH/10;
	SDL_SetColorKey(surface_jeu,SDL_SRCCOLORKEY,SDL_MapRGB(ecran->format,0,0,0) ); 
    SDL_BlitSurface(surface_jeu,NULL,ecran,&position_plateau);


   /*-----------------------------------------------------CREATION DE LA PALETTE 1-----------------------------------------------------*/
   	/*int cmpP=0;
	ElemTabCouleur* tmp3;
	for(i=0;i<nb_couleurs;i++){
		tmp3=tab[i];
		if(tmp3->nbPiecesCl)
			cmpP++;
	} 
	SDL_Surface* surface_palette_pieces=SDL_CreateRGBSurface(SDL_HWSURFACE,cmpP*gFullScreenH/15,gFullScreenH/15, 32, 0, 0, 0, 0); 
	SDL_Surface* fond_palette=SDL_LoadBMP("fond2.bmp");
	//position=(0,0)
	SDL_BlitSurface(fond_palette,NULL,surface_palette_pieces,&position);
	afficher_palette_pieces(tab,nb_couleurs,surface_palette_pieces);
	position_palette_pieces.x = gFullScreenW/30+taille_cases*nb_cases+20;
    position_palette_pieces.y = gFullScreenH/10;
	SDL_BlitSurface(surface_palette_pieces,NULL,ecran,&position_palette_pieces);
   */
   /*-----------------------------------------------------CREATION DE LA PALETTE 2-----------------------------------------------------*/ 

	/*SDL_Surface* surface_palette_cases=SDL_CreateRGBSurface(SDL_HWSURFACE,nb_couleurs*gFullScreenH/15,gFullScreenH/2,32,0,0,0,0);  
	afficher_palette_cases(tab,nb_couleurs,surface_palette_cases);
	position_palette_cases.x = position_palette_pieces.x;
	position_palette_cases.y=position_palette_pieces.y+gFullScreenH/15+10;
	SDL_SetColorKey(surface_palette_cases,SDL_SRCCOLORKEY,SDL_MapRGB(ecran->format,0,0,0) ); 
	SDL_BlitSurface(surface_palette_cases,NULL,ecran,&position_palette_cases);
   

   */
   
   /*---------------------------------------AFFICHAGE DU TEXT---------------------------------------------------------------*/
   
   SDL_Color black={0,0,0};
   SDL_Rect position_mot,position_cmpt,position_close;
   position_mot.x=position_plateau.x;
   position_mot.y=position_plateau.y+taille+50;
   position_cmpt.x=taille+gFullScreenW/30+500;
   position_cmpt.y=300;
   position_close.x=40;
   position_close.y=30;
   // la fonction qui affiche le text est appelé une fois le jeu se termine ligne 563
   
   
   
   
   
   
   
   
   	/*----------CREATION DE LA PILE COULEUR-----------*/
   	double largeur_pile=200;
   	double hauteur_pile=(nb_cases-1)*taille_cases;
   	SDL_Surface* surface_pile=SDL_CreateRGBSurface(SDL_HWSURFACE,largeur_pile,hauteur_pile,32,0,0,0,0);
	SDL_Rect position_pile;
	position_pile.x=taille+gFullScreenW/30+20;
	position_pile.y=position_plateau.y+100;

   	Uint32* pile_couleurs=malloc(sizeof(Uint32)*nb_pieces);
   	int indice_pile=0;
   	for(i=0;i<nb_pieces;i++){
   		//on initialise tout les couleurs en noir par ce que le noir c'est swag
   		pile_couleurs[i]=SDL_MapRGB(ecran->format,0,0,0);
   		}
   	
   	
   	position.x=0;
   	position.y=0;
							SDL_Flip(ecran);
if(choix==1){	

	int continuer = 1,t=1,cmpt_changements=0;
	case_plateau *c_click;//la case qu'on recupere
	int click=0;
	SDL_Event event;
	int indice_i=0;
	int indice_j=0;
	int x_click,y_click;
	
while(continuer)
{
	SDL_WaitEvent(&event);
	switch(event.type)
	{
	case SDL_QUIT:
	    continuer = 0;
	    break;
	    
	case SDL_MOUSEBUTTONUP:
	      	x_click=event.button.x;
		    y_click=event.button.y;
		      
		     if( (x_click >= position_plateau.x) && (x_click <= position_plateau.x + nb_cases*taille_cases) && (y_click > position_plateau.y) && (y_click < position_plateau.y + taille_cases*nb_cases) ){
			// You only get inside if the click is inside the grid
			recuperer_indices(position_plateau.x,position_plateau.y,event.button.x,event.button.y,taille_cases,&indice_i,&indice_j);
			c_click=plateau[indice_i*nb_cases + (indice_j) ];
			click=1;
			if( c_click->p != NULL){
			pile_couleurs[indice_pile]=c_click->p->couleur;
			indice_pile++;
			}
		}
			break;
	}
	    
	 if(click && c_click->p !=NULL){
 		if(c_click->p->couleur != c_click->couleur){
			i=0;
			while(c_click->p->couleur !=tab[i]->couleur){
					i++;
				}
			if(bougerPiece_bis(tab[i],c_click)){
				click=0;
				SDL_BlitSurface(fond,NULL,ecran,&position);	
				afficher_plateau(taille_cases,nb_cases,plateau,surface_jeu,rectangle);
				SDL_BlitSurface(surface_jeu,NULL,ecran,&position_plateau);
				afficher_pile(largeur_pile,hauteur_pile,nb_pieces,pile_couleurs,surface_pile);//dans palette.C
				SDL_BlitSurface(surface_pile,NULL,ecran,&position_pile);

				SDL_Flip(ecran);
	
			}else{
				click=0;
				indice_pile--;
				afficher_text(ecran,"Ce deplacement n'est pas possible",black,position_mot,35);
				SDL_Flip(ecran);
		
				}
		}
	}else if( click && c_click->p == NULL){
		//si on clique sur une case sans piece 
			click=0;
			afficher_text(ecran,"Ce deplacement n'est pas possible",black,position_mot,35);
			SDL_Flip(ecran);
	}

	if(indice_pile==nb_pieces){
	

		//on a deplacé toutes les pieces  
		for(i=1;i<nb_pieces;i++){
			if(pile_couleurs[i] != pile_couleurs[i-1])
				cmpt_changements++;
		}

		char changements[256];
		sprintf(changements, "cmpt: %d", cmpt_changements);//fonction chelou qui transforme du int au char
		
		afficher_text(ecran,changements,black,position_cmpt,50);//ma fonction afficher text prend un char  va dans text.c
		SDL_Flip(ecran);
		afficher_text(ecran,"Fin de la partie : Pour revenir au menu tapez sur la touche \" ESC \" ou bien le bouton \" X \" ",black,position_close,25);
		SDL_Flip(ecran);
		continuer=0;//on arrete la boucle 

	}

 }
}else if(choix==2){
	clock_t start,end;
	double time_used;
	start=clock();
		IA(tab,nb_pieces,nb_couleurs,ecran,surface_jeu,position_plateau,position_cmpt);
	end=clock();
	afficher_text(ecran,"Fin de la partie : Pour revenir au menu tapez sur la touche \" ESC \" ou bien le bouton \" X \" ",black,position_close,25);
	SDL_Flip(ecran);
	time_used=(double)(end-start) /CLOCKS_PER_SEC;
	printf("temps IA : %f \n",time_used);	
}else if(choix ==3){
	/*on creer la structure graphe on la remplie en utilisant les informations trouvé dans "plateau"
	  on cherche les chemins possible dans la grille a l'aide de l'heuristique 1 on a une sequence d'arcs C 
	  on extrait les chemins de la sequence d'arcs C en utilisant la fonction extraire_chemins(...)
	  on alligne ces chemins a l'aide de la fonction aligner(..) pour avoir une sequence d'arcs qui represent la solution finale
	*/
	
	clock_t start,end;
	double time_used;
	start=clock();
	Graphe * g=(Graphe*)malloc(sizeof(Graphe));
	construire_graph(g,tab,plateau,nb_cases);
	//afficher_graph_liste(g);
	int nb_sommets=g->nbsom;
	int Tab_E[nb_sommets];
	SeqArc* C=malloc(sizeof(SeqArc));
	C=heuristique_1(Tab_E,g,plateau);		
	free_graph(g);
	if(C != NULL){
		printf("solution trouve \n");
		//printf("On affiche la sequence d'arcs \n");
		//afficher_sequence_arcs(C);		

		EnsChemin *chemins=NULL;
		chemins=extraire_chemins(C ,Tab_E,nb_sommets);
		
		/*printf("\n");	
		printf("Les chemins trouvé par l'heuristique 1 sont \n");
		afficher_chemins(chemins);*/
		
		SeqArc* solution ;
		solution=aligner(chemins,plateau);
		/*printf("On affiche la sequence d'arcs aligne \n");
		afficher_sequence_arcs(solution);	
		printf("\n");	*/
	    free_chemins(chemins);
		end=clock();
		time_used= (double)(end-start)/ CLOCKS_PER_SEC ;
	    printf("Temps graph %f \n ",time_used);
		
		/*printf("la solution final est:\n");
		afficher_sequence_arcs(solution);
		printf("\n");*/
		
		/*
			solution est une sequence d'arcs , chaque arcs (u,v) donne des informations sur les cases ; l'arc (3,7) reli plateau[3] et 			plateau[7] ..Pourquoi ? c'est comme ca que les arcs etaient crées dans les fonctions de graph.c 
			il suffit de parcourir solution et prendre chaque arc(u,v) puis designer la case c_1 comme case de depart et c_2 comme case 	         d'arrivée ..si t'as la case de depart et d'arriver tu peux echanger leur pieces et actualiser l'affichage
		
		*/
		
		SeqArc * tmp_solution=solution;
		case_plateau *c_1;
		case_plateau *c_2;
		int beug=0;
		int cmpt_changements=0;
		Uint32 couleur1=SDL_MapRGB(ecran->format,0,0,0);
		Uint32 couleur2=SDL_MapRGB(ecran->format,0,0,0);
		while(tmp_solution && beug==0){
			couleur1=couleur2;
			c_1=plateau[tmp_solution->u];
			c_2=plateau[tmp_solution->v];
			couleur2=c_1->p->couleur;
			if(couleur1 != couleur2){
				cmpt_changements++;
			}
			if((c_1->p->couleur == c_2->couleur) && (c_2->p == NULL)){
				c_2->p=c_1->p;
				c_1->p->c=c_2;
				c_1->p=NULL;
				afficher_case(c_1,surface_jeu,rectangle);
				afficher_case(c_2,surface_jeu,rectangle);
		 		SDL_BlitSurface(surface_jeu,NULL,ecran,&position_plateau);
		 		SDL_Flip(ecran);
			}else{
				printf("Deplassement impossible\n");
				beug==1;
				}
				
			
			tmp_solution=tmp_solution->suiv;
			
		}
	free_sequence(solution);
	char changements[256];
	sprintf(changements, "cmpt: %d",cmpt_changements);//fonction chelou qui transforme du int au char
	afficher_text(ecran,changements,black,position_cmpt,50);//ma fonction afficher text prend un char  va dans text.c
	SDL_Flip(ecran);
	afficher_text(ecran,"Fin de la partie : Pour revenir au menu tapez sur la touche \" ESC \" ou bien le bouton \" X \"",black,position_close,25);
	SDL_Flip(ecran);	
	}else{
	
		printf("il y a pas de solutions \n");
	
	}


	
}

   printf("fin du jeu \n \n");
   pause();
   SDL_FreeSurface(surface_jeu);

  // SDL_FreeSurface(surface_pile);
   SDL_Quit();
   
   
   for(i=0;i<nb_cases*nb_cases;i++){
   	free(plateau[i]);
   }
   
    for(i=0;i<nb_pieces;i++){
   	free(tab_pieces[i]);
   }
   free(plateau);
   free(coul);
   free(tab_pieces);
	
	
}
