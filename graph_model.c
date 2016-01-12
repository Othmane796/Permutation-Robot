#include "graph_model.h"

/*prend un pointeur vers une case et trouve les(i,j) de cette case dans le tableau "plateau"*/
void trouver_case(int *indice_i,int *indice_j,case_plateau** plateau,int nb_cases,case_plateau *la_case){
	int A=0;
		while(la_case != plateau[A])
			A++;
	*indice_i=A/nb_cases;
	*indice_j=A%nb_cases;
}	
		
		
Arc* inserer_arc_en_queue(Arc* liste,int u){

	Arc * a=(Arc*)malloc(sizeof(Arc));
	a->u=u;
	a->suiv=NULL;
	
	if(liste == NULL){
		return a;
	}else{
		Arc *tmp=liste;
		while(tmp->suiv != NULL){
			
			tmp=tmp->suiv;
		}
		tmp->suiv=a;
		return liste;
	}
}

Arc * inserer_arc_debut(Arc * liste,int u){
	
	Arc * element=malloc(sizeof(Arc));
	element->u=u;
	element->suiv=liste;
	
	return element;


}

/*on echange les deux arcs A1 et A2 tel que A1->u =a et A2->u=b */
Arc * echanger_arcs(Arc * list,int a,int b){
	Arc *tmp;
	Arc *tmp1;
	Arc *tmp2;
	int tmp_changement;
	tmp=list;
	int i=1;
	while(tmp->suiv!= NULL && i < a){
		tmp=tmp->suiv;
		i++;
	}
	tmp1=tmp;

	i=1;
	
	tmp=list;
	while(tmp->suiv != NULL && i < b){
		tmp=tmp->suiv;
		i++;
	}
	tmp2=tmp;

	tmp_changement=tmp2->u;
	tmp2->u=tmp1->u;
	tmp1->u=tmp_changement;

	return list;
}   
/* On prend une liste d'arcs 1->2->3->4... et on retourne 1->3->2->4 par exemple*/
Arc * melanger_arcs(Arc *list){
	Arc * tmp=list;
	int n=0;
	while(tmp){
		tmp=tmp->suiv;
		n++;
	}
	//printf("On melange les %d arcs \n",n);
	
	tmp=list;
	int a,b;
	int i;
	for(i=0;i<n;i++){
		a=(rand()%n)+1;
		b=(rand()%n)+1;
		//printf("on echange l'arc %d et l'arc %d \n",a,b);
		echanger_arcs(tmp,a,b);
	}

	
	return tmp;
}

// retourne 1 si il existe un arc  a à b
int existe_arc(int a,int b,SeqArc * C){
	SeqArc * C_tmp=C;
	int trouve=0;
	
	while(C_tmp && trouve == 0){
		if(C_tmp->u == a && C_tmp->v == b){
			trouve=1;
		}else{
			C_tmp=C_tmp->suiv;
		}
	}
	
	return trouve;
	
	
	

}
int existe_chemin(int a,int b, SeqArc * C){
	
	int a_trouve=0,b_trouve=0;
	
	SeqArc * tmp=C;
	while(tmp && a_trouve == 0 ){
		if(tmp->u == a){
			a_trouve=1;
		}else{
			tmp=tmp->suiv;
		}
	}
	
	if(a_trouve){
		if(tmp->v == b){
		 	b_trouve=1;
		 	return b_trouve;
		 }else{
		 	return existe_chemin(tmp->v,b,C);
		 }

	}else{
		return 0;
	}


}
void afficher_sequence_arcs(SeqArc *C){

	SeqArc *tmp=C;
	while(tmp){
		printf("(%d,%d)->",tmp->u,tmp->v);
		tmp=tmp->suiv;
	
	}

}
void free_sequence(SeqArc *C){
	SeqArc * courant;
	while( (courant = C) != NULL){
		C=C->suiv;
		free(courant);
	}
}
SeqArc* inserer_arc_en_queue_bis(SeqArc *Sequence,int u, int v){

	SeqArc * S=malloc(sizeof(SeqArc));
	S->u=u;
	S->v=v;
	S->suiv=NULL;
	
	if(Sequence == NULL){
		return S;
	}else{
		SeqArc *tmp=Sequence;
		while(tmp->suiv != NULL){
			
			tmp=tmp->suiv;
		}
		tmp->suiv=S;
		return Sequence;
	}
}

SeqArc* inserer_arc_debut_bis(SeqArc* liste,int u, int v){
	
	SeqArc * S=malloc(sizeof(SeqArc));
	S->u=u;
	S->v=v;
	S->suiv=liste;
	
	return S;


}
void free_graph(Graphe* g){
	int i=0;
	for(i=0;i<g->nbsom;i++){
		free(g->TabS[i]);
	}
	free(g);
}

/*question 1.2 exercice 1 : la construction du graphe g a partir du tableau contenant les cases*/
void construire_graph(Graphe* g,ElemTabCouleur** tab ,case_plateau** plateau,int nb_cases){

	g->nbsom=nb_cases*nb_cases;
	g->TabS=(Sommet **)malloc(sizeof(Sommet *) * g->nbsom);
	int i,j;
	Sommet *s;//var temporaire
	for(i=0;i< nb_cases; i++){
		for(j=0;j< nb_cases ;j++){
		g->TabS[i*nb_cases + j]=(Sommet *)malloc(sizeof(Sommet));
		s=g->TabS[i*nb_cases + j];
		s->i=i;
		s->j=j;
		s->Lvois=NULL;
		}
	}
	//on a rempli tout les sommets
	Sommet * sommet_courant;
	case_plateau * case_courante,*case_succ;
	cellule* tmp;
	//Arc* a_tmp;
	Uint32 coul;
	int indice_i,indice_j;
	int k=0;
	for(i=0;i< nb_cases; i++){
		for(j=0;j< nb_cases ;j++){
			sommet_courant=g->TabS[i*nb_cases +j];
			case_courante=plateau[i*nb_cases +j];
			if(case_courante->p != NULL){
				coul=case_courante->p->couleur;
				k=0;
				while(tab[k]->couleur != coul){
					k++;
				}
				//coul est la couleur de la piece et tab[ĸ] contient la liste des cases de cette couleur
				tmp=tab[k]->ListeCaseCl;
				while(tmp){
					case_succ=tmp->c;
					trouver_case(&indice_i,&indice_j,plateau,nb_cases,case_succ);
					//on a trouve la case qui represent le succeseur
					//a_tmp=creer_arc((indice_i*nb_cases) + indice_j);

					sommet_courant->Lvois=inserer_arc_en_queue(sommet_courant->Lvois,indice_i*nb_cases + indice_j);
					tmp=tmp->suivant;
				}
			}
		}
		
	}
}

/*Affiche le graphe g*/
void afficher_graph_liste(Graphe * g){
	ListeArc tmp2;
	Sommet* s;
	int i;
	for(i=0;i<g->nbsom;i++){
		s=g->TabS[i];
		//printf("arc entrant:%d,arc sortant %d \n",s->entrant,s->sortant);
		printf("la case (%d,%d) le sommet %d---->",s->i,s->j,i);

		tmp2=s->Lvois;

		while(tmp2){
			printf("(%d,%d);",i,tmp2->u);
			tmp2=tmp2->suiv;
		}
		printf("\n");
	}
}



    
/*question 3.2 : Mise en place de l'algorithme expliqué dans l'heuristique 1*/
SeqArc* heuristique_1(int * Tab_E , Graphe* g,case_plateau** plateau){

	int i,s,t;
	int Tab_S[g->nbsom];//Tab_S[u]=1 u a un arc sortant Tab_S[u]=0 a n'as pas d'arc sortant
   //Tab_E[u]=1 u a un arc entrant Tab_E[u]=0 a n'as pas d'arc entrant
	ListeArc  Liste_arcs=NULL;//liste d'arcs non marques qu'on va construire plus tard
	ListeArc  Lvois_tmp;//liste temporaire pour parcouri Lvois
	ListeArc tmp;
	SeqArc *C=NULL;
	for(i=0;i<g->nbsom;i++){//on met tout les marquages a 0
		Tab_S[i]=0;
		Tab_E[i]=0;
	}

	Sommet * sommet_courant;
	for(i=0;i<g->nbsom;i++){
		sommet_courant=g->TabS[i];
		if(sommet_courant->Lvois != NULL){//Si la liste n'est pas nul alors le sommet contient une piece
			//Melanger la liste d'arcs (A FAIRE)

			Lvois_tmp=sommet_courant->Lvois;

			while(Lvois_tmp){//on recupere les arcs non marqué et on les rajoute a liste_arcs
				if(Tab_E[Lvois_tmp->u] == 0){
					Liste_arcs=inserer_arc_debut(Liste_arcs,Lvois_tmp->u);
				}
				Lvois_tmp=Lvois_tmp->suiv;

			}

			Liste_arcs=melanger_arcs(Liste_arcs);

			s=i;//sommet duquel sort l'arc (celui qu'on traite)	
			t=Liste_arcs->u;//(s,t) represente le premier arc de la liste
				if(/*existe_arc(t,s,C) || */existe_chemin(t,s,C) ){	
				//	printf("il existe deja un arc (%d,%d)\n",t,s);
					if(Liste_arcs->suiv != NULL  ){
						
					//printf("avant c'etait(%d,%d),maintenant je prend (%d,%d) \n",s,t,s,Liste_arcs->suiv->u);
						t=Liste_arcs->suiv->u;//prendre l'arc suivant

					
					
					
					
					//	printf("j'ai pris le deuxieme arc, boucle evité i= %d \n",i);//TEST REMOVE IT
					}else{
						printf("STOP \n");
						return NULL;
					}
				}

			C=inserer_arc_en_queue_bis(C,s,t);//on rajout l'arc (s,t) a la liste d'arcs
			
			Tab_S[s]=1;
			Tab_E[t]=1;
			Liste_arcs=NULL;
		}
	
	}
	
return C;	
}

EnsChemin * inserer_chemin(EnsChemin *liste,SeqArc * chem){
	
	EnsChemin * ens=malloc(sizeof(EnsChemin));
	ens->chem=chem;
	ens->suiv=liste;
	
	return ens;
}

/*question 3.3 : on prend une sequence d'arcs C un Tab_E pour savoir qui sont les sommets sans predecesseur et on retourn un EnsChemin
 Le principe est de prendre chaque sommet sans predecesseur et en trouver un chemin*/
EnsChemin * extraire_chemins(SeqArc * C ,int * Tab_E,int nb_sommets){
	
	EnsChemin * les_chemins=NULL;
	SeqArc *C_tmp=C;
	
	if(C == NULL){
		les_chemins=NULL;
	}else{
		SeqArc *C_tmp_2=C->suiv;
		SeqArc *sequence_tmp=NULL;

		int i,ajouter,s;

		for(i=0;i<nb_sommets;i++){
			if(Tab_E[i]==0){
				s=i;//le sommet sans predecesseur
				//printf("le sommet %d est sans predecesseur\n",s);
				//on cherche le chemin
				ajouter=0;
				sequence_tmp=NULL;
				while(ajouter ==0){
					C_tmp=C;
					while(C_tmp && C_tmp->u != s){
						C_tmp=C_tmp->suiv;
					}
					if(C_tmp == NULL){
						//on a pas trouve l'arc (s,...)
						//printf("Arc non trouvé \n");
						ajouter =1;
						les_chemins=inserer_chemin(les_chemins,sequence_tmp);
					}else{		
						//printf("Arc trouvé (%d,%d) \n",C_tmp->u,C_tmp->v);
						sequence_tmp=inserer_arc_en_queue_bis(sequence_tmp,C_tmp->u,C_tmp->v);
						s=C_tmp->v;
					}
				}
			}
		}
	}
	return les_chemins;
}

void afficher_chemins(EnsChemin *les_chemins){

	EnsChemin *tmp=les_chemins;
	if(tmp == NULL)
		printf("pas de chemins \n");
	
	while(tmp){
		afficher_sequence_arcs(tmp->chem);
		printf("\n");
		tmp=tmp->suiv;
	}


}

void free_chemins(EnsChemin *les_chemins){
	
	EnsChemin *tmp=les_chemins;
	if(tmp == NULL)
		printf("pas de chemins a liberer \n");
	
	while(tmp){
		free_sequence(tmp->chem);
		tmp=tmp->suiv;
	}
	free(les_chemins);
}
/*il suffit de prendre la liste a inverser , creer une nouvelle liste vide puis rajouter les elements de la liste a inverser un par un au debut de liste vide ..reflichis un peu ..tu comprendra ..sinon ..Tant pis */
SeqArc* inverser_sequence(SeqArc * Sequence){
	SeqArc* S=NULL;
	SeqArc* S_tmp=Sequence;
	while(S_tmp){
		S=inserer_arc_debut_bis(S,S_tmp->u,S_tmp->v);
		S_tmp=S_tmp->suiv;
	}
	
	return S;
}


SeqArc* aligner(EnsChemin *les_chemins,case_plateau** plateau){

	int trouve=0;
	SeqArc * S=NULL;//on cree une sequence d'arc qu'on va remplir a l'aide de cette algo
	SeqArc *tmp_S=S;
	SeqArc *tmp2_S;
	EnsChemin *ens_tmp;
	ens_tmp=les_chemins;
	SeqArc *ch;
	while(ens_tmp){
		ch=ens_tmp->chem;//le chemin a traiter
		while(ch){
			//la couleur de l'arc (u,v) est celle de la case d'arrivee  : plateau[v]
		//	trouve=0;
		//tmp_S=S;
		trouve=0;
			while(tmp_S && trouve == 0){
				if(plateau[ tmp_S->v ]->couleur == plateau[ ch->v ]->couleur){
					trouve=1;
					printf("trouve\n");
				}else{
					tmp_S=tmp_S->suiv;//on continue a chercher
				}
			}
		
			if(trouve){
				//inserer l'arc a(ch->u,ch->v) apres b(celui pointee par tmp_S
				printf("j'insere quelque part\n");
					tmp2_S=tmp_S->suiv;
					SeqArc * arc_inserer=malloc(sizeof(SeqArc));
					arc_inserer->u=ch->u;
					arc_inserer->v=ch->v;
					arc_inserer->suiv=tmp2_S;
					tmp_S->suiv=arc_inserer;
	
			}else{
				//on est arrivé a la fin de la liste tmp_S=S sans rien trouver
				//inserer l'arc a en queue de S
				S=inserer_arc_en_queue_bis(S,ch->u,ch->v);
			}
			ch=ch->suiv;//on traite l'arc suivant
		}
		ens_tmp=ens_tmp->suiv;//on traite le chemin suivant
	
	}

	S=inverser_sequence(S); //on inverse la lista pck Mr Pierre l'as dis 
	return S;
}




