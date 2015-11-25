#ifndef GRAPH
#define GRAPH
#include "plateau.h"
typedef struct arc  Arc;

struct arc{
	int u;//numero du sommet successeur
	Arc * suiv;
};

typedef Arc * ListeArc;

typedef struct sommet{
	int i,j;//les cordonées dans le plateau
	ListeArc Lvois;
	
}Sommet;

typedef struct graphe{
	int nbsom;
	Sommet ** TabS;
	
}Graphe;

typedef struct seqarc SeqArc;

struct seqarc {
	int u , v ;// arc (u,v)
	SeqArc * suiv ;
};
typedef struct enschemin EnsChemin;

struct enschemin {
	SeqArc * chem ;
	EnsChemin * suiv ;
};

/*prend un pointeur vers une case et trouve les(i,j) de cette case dans le tableau "plateau"*/
void trouver_case(int *indice_i,int *indice_j,case_plateau** plateau,int nb_cases,case_plateau *la_case);

Arc * inserer_arc_en_queue(Arc* liste,int u);

Arc * inserer_arc_debut(Arc * liste,int u);

/*on echange les deux arcs A1 et A2 tel que A1->u =a et A2->u=b */
Arc * echanger_arcs(Arc * list,int a,int b);

/* On prend une liste d'arcs 1->2->3->4... et on retourne 1->3->2->4 par exemple*/
Arc * melanger_arcs(Arc *list);

// retourne 1 si il existe un arc  a à b
int existe_arc(int a,int b,SeqArc * C);

int existe_chemin(int a,int b, SeqArc * C);

void afficher_sequence_arcs(SeqArc *C);

void free_sequence(SeqArc *C);

SeqArc* inserer_arc_debut_bis(SeqArc* liste,int u, int v);

SeqArc* inserer_arc_en_queue_bis(SeqArc *Sequence,int u, int v);

/*question 1.2 exercice 1 : la construction du graphe g a partir du tableau contenant les cases*/
void construire_graph(Graphe* g,ElemTabCouleur** tab ,case_plateau** plateau,int nb_cases);

/*Affiche le graphe g*/
void afficher_graph_liste(Graphe * g);

void free_graph(Graphe* g);

/*question 3.2 : Mise en place de l'algorithme expliqué dans l'heuristique 1*/
SeqArc * heuristique_1(int *Tab_E,Graphe* g,case_plateau** plateau);

EnsChemin * inserer_chemin(EnsChemin *liste,SeqArc * chem);


/*question 3.3 : on prend une sequence d'arcs C un Tab_E pour savoir qui sont les sommets sans predecesseur et on retourn un EnsChemin
 Le principe est de prendre chaque sommet sans predecesseur et en trouver un chemin*/
EnsChemin * extraire_chemins(SeqArc * C ,int * Tab_E,int nb_sommets);

void afficher_chemins(EnsChemin *les_chemins);

void free_chemins(EnsChemin *les_chemins);

SeqArc* aligner(EnsChemin *les_chemins,case_plateau** plateau);

SeqArc* inverser_sequence(SeqArc * Sequence);




#endif
