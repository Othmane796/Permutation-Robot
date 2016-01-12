#ifndef MOVE
#define MOVE

#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <math.h>

#include "plateau.h"

Uint32 getpixel(SDL_Surface *surface, int x, int y);

void recuperer_coordonees(double *x,double *y);

Uint32 recuperer_couleur(SDL_Surface *surface,double x,double y);

void recuperer_indices(double x0,double y0,double x,double y,double taille_cases,int *i,int *j);

int bougerPiece(ElemTabCouleur* tab,Piece* p);

int bougerPiece_bis(ElemTabCouleur* tab,case_plateau* c_click );



#endif
