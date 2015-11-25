#ifndef PLATEAU
#define PLATEAU

#include <stdio.h>
#include <SDL/SDL.h>
#include <stdlib.h>
#include <math.h>

typedef struct case_plateau case_plateau;

typedef struct Piece{
    int rayon;
    Uint32 couleur;
    case_plateau* c;
}Piece;

struct case_plateau{
    double x;
    double y;
    double taille;
    
    Uint32 couleur;
    Piece* p;
};

typedef struct cellule{
	case_plateau* c;
	struct cellule* suivant;
}cellule;

typedef struct element{
	Piece* p;
	struct element* suivant;
}element;


typedef struct elem_tab_couleur{
	//Pointeur vers le 1er element de nos listes
	Uint32 couleur;
	cellule* ListeCaseCl;
	element* ListePieceCl;
    int nbCasesCl;
	int nbPiecesCl;
}ElemTabCouleur;


void pause();

void jeu(int nb_cases,int nb_couleurs,int choix);

cellule* insertionCellule(cellule* liste,case_plateau* Case);

element* insertionElement(element* liste,Piece *Piece);

element* suppTeteElem(element* el);

cellule* suppCellule(cellule* cel,case_plateau* c);

ElemTabCouleur** creerElem(case_plateau** tabCases,Piece** tabPieces,int nb_couleurs,int nb_cases,int nb_pieces,Uint32* couleurs);

void afficher_elem_tab(ElemTabCouleur* tab,int nb_couleurs);

int plateau_correct(Uint32* couleurs_plateau,Uint32* couleurs_piece,int tailleCoulPlat,int taillePieces);

Piece* creer_piece(double rayon,Uint32 couleur);

Piece** creer_pieces(int nb_pieces,int rayon,Uint32* couleurs_piece);

case_plateau* creer_case(double x,double y,double taille,Uint32 couleur);

case_plateau** creer_cases(int taille_cases,int nb_cases,Uint32* couleurs_plateau);

Uint32** creer_palettes(SDL_Surface* ecran,int nb_couleurs,int nb_cases,int nb_pieces);

int placer_piece(Piece* p,case_plateau* c);

int placer_pieces(int nb_cases,int nb_pieces,case_plateau** tableau_case,Piece** tableau_pieces);	

void afficher_piece(Piece *p,SDL_Surface* ecran,SDL_Surface* rectangle);

void afficher_case(case_plateau* c,SDL_Surface* ecran,SDL_Surface* rectangle);

void affiche_piece_vide(case_plateau* c,SDL_Surface* surface,SDL_Surface* rectangle);

void afficher_plateau(double taille_cases,int nb_cases,case_plateau** tableau_case,SDL_Surface* surface,SDL_Surface* rectangle);

void IA(ElemTabCouleur** tab,int nb_pieces,int nb_couleurs,SDL_Surface* ecran,SDL_Surface* surface_jeu,SDL_Rect position_plateau,SDL_Rect position_cmpt);
#endif
