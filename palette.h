#ifndef PALETTE
#define PALETTE

#include <stdio.h>
#include <SDL/SDL.h>
#include <stdlib.h>

void afficher_palette_pieces(ElemTabCouleur** tab,int nb_couleurs,SDL_Surface* surface);
void afficher_pile(double largeur_pile,double hauteur_pile,int nb_pieces,Uint32* tab_pile,SDL_Surface* ecran);
void afficher_palette_cases(ElemTabCouleur** tab,int nb_couleurs,SDL_Surface* surface);

#endif
