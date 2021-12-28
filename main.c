#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <time.h>
#include <limits.h>
#include "aff2.h"

#define SKIPLIST_MAX_NIVEAU 16 // cela defini le nombre maximum des niveaux qu'on peut avoir
//-------------------------------------------------------------------------------------------------
// ************************ partie LLC ***************************************************************
typedef struct maillons
 {
     int val ;
     struct maillons *next ;
 } maillons ;
 void allouer ( maillons **nouveau)
 {
     *nouveau=(maillons*) malloc (sizeof(maillons));
 }
void aff_adr(maillons *p , maillons *q)
{
     p-> next=q;
}
void aff_val (maillons *p , int valeur)
{
    p-> val=valeur;
}

maillons *suivant(maillons *p)
{
    return p->next ;
}
 int valeur(maillons *p)
 {
      return p->val;

 }
 void liberer(maillons**ancien)
 {
      free(*ancien);
      *ancien=NULL;
 }
 maillons *cree_LLC(int n)
 {
     maillons *tete,*p,*q ;
     int i,x;
     allouer(&p);
     tete=p;

     printf(" entrer la premiere valeur : \n");

     scanf("%d",&x);
     aff_val(tete,x);

     for (i=1;i<n;i++)
     {
         allouer(&q);
         printf("entrer la %d eme valeur : \n",i+1);
         scanf("%d",&x);
         aff_val(q,x);
         aff_adr(p,q);
         p=q;

     }
     aff_adr(p,NULL);
     return tete;
 }
//--------------------------------------------------------------------------------------
  void supp_val(int val,int *cpt , maillons **tete)
    {   int gpt=1;
        maillons *p, *q;
        p=*tete;
        q=NULL;
        while (p!=NULL && (valeur(p))!=val)
        {
            q=p;
            p=suivant(p);
            gpt++;
            }
         if (p!=NULL && val==(valeur(p)))
            {

            if (q==NULL)
        {




          tete=suivant(p);
            liberer(p);
        }


        else
        {

            aff_adr(q,suivant(p));
           liberer(&p);
        }
        }
     *cpt=gpt;
    }
    //------------------------------------------------------------------------------
     void afficher_LLC(maillons *p)
 { printf(" les elements de la LLC apres suppression sont : \n");

     while (p!=NULL)
     {   printf("||");
         printf(" %d || ",valeur(p));


         p=suivant(p);
     } printf(" \n ");

 }
 //---------------------------------------------------------------------------------------------------------
 void permut(maillons *p , maillons *q){
    int v=0;
    v=(p->val);
    (p->val)=(q->val);
    (q->val)=v;
  }
void tri_bulle( maillons *tete){
    int trouv=1;
   maillons *p;

while(trouv==1){

        p=tete;
        trouv=0;
              while (p->next!= NULL ) {

                    if( (p->val) > (p->next->val)){
                permut (p,p->next);
                trouv=1;}
                p=p->next;

                    }
              }

}

//------------------------------------------------------------------------------------------
typedef struct maillon { //  la structure d'un maillon dans la liste qui contient un champ cle , valeur et un pointeur de type maillon
    int indice;// indice de la valeur
    int valeur;
    int level;
    struct maillon **suivant; // ptr du maillon suivant
} maillon;

typedef struct skiplist { // la structure de la skiplist (qui sera composee de plusieurs listes) contient un champ pour le niveau de la liste , sa taille et un pointeur de type maillon pour lier entre les niveaux
    int niveau;
    int taille;
    struct maillon *tete;
} skiplist;

skiplist *initialiser_skiplist(skiplist *llc)
{
    int i;
    maillon *tete = (maillon *)malloc(sizeof(struct maillon)); // allocation du premier maillon dans la liste qui est la tete
    llc->tete = tete;
    tete->indice = INT_MAX;
    tete->suivant = (maillon **)malloc(sizeof(maillon*) * (SKIPLIST_MAX_NIVEAU+1)); //allocation du maillon suivant
    for (i = 0; i <= SKIPLIST_MAX_NIVEAU; i++) {
        tete->suivant[i] = llc->tete; // et a chaque fois on affecte l'adr de la derniere tete dans le maillon suivant(nouveau)

    }

    llc->niveau = 1; //initialiser le niveau de la skip list a 1
    llc->taille = 0;// initialiser la taille a 0

    return llc; // on retourne llc un ptr vers la skiplist initialisee
}

static int  rand_niveau() // la fonction permet de donner le niveau a chaque valeur
{


    int p ;
    int boole;
    int niveau = 1;
        p= rand();
        boole=p%2;
       // printf("boole = %d",boole);
        while (boole && niveau < SKIPLIST_MAX_NIVEAU) {
        niveau++;
        p=rand();
        boole=p%2;
       // printf("p:%d ",p);
        }


    return niveau ;
}

int skiplist_insert_elem(skiplist *llc, int indice, int valeur) // fonction qui permet d'inserer un element dans la skiplist sans toucher a l'ordre
{
    maillon *maj[SKIPLIST_MAX_NIVEAU+1]; // un tableau de type maillon ou on va mettre a jour les elements
    maillon *x = llc->tete; // on sauvgarde le ptr de la tete de la skiplist dans x
    int i, niveau;

    for (i = llc->niveau; i >= 1; i--) { // on commence du haut de la skiplist vers le bas
        while (x->suivant[i]->indice < indice) {  // tq l'indice a inserer est plus grand que l'indice actuel
            x = x->suivant[i];
            } // on continue a parcourir la list
        maj[i] = x;
    }
    x = x->suivant[1];

    if (indice == x->indice) { // si l'indice a inserer est egal a l'indice actuel
        x->valeur = valeur; // on insert la valeur
        return 0;
    } else {
        niveau = rand_niveau( ); // sinon on change le niveau et on cherche ou inserer plus bas
       // printf("voici le niveau : %d \n",niveau);
        if (niveau > llc->niveau) {
            for (i = llc->niveau+1; i <= niveau; i++) {
                maj[i] = llc->tete;
            }
            llc->niveau = niveau;
        }

        x = (maillon*)malloc(sizeof(maillon)); // une fois trouver ou inserer on vient allouer une place pour le nouvel element
        x->indice = indice;
        x->valeur = valeur;
        x->level=niveau ;
       // printf("%d",niveau);
        x->suivant = (maillon **)malloc(sizeof(maillon*) * (niveau + 1)); // et on chaine le reste
        for (i = 1; i <= niveau; i++) {
            x->suivant[i] = maj[i]->suivant[i];
            maj[i]->suivant[i] = x;
        }
    }
    return 0;
}


static void supprimer_maillon(maillon *x) // la proc qui vient de liberer un champ memoire
{
    if (x) {
        free(x->suivant);
        free(x);
    }
}

 int skiplist_supp_elem(skiplist *llc, int indice ,int *cpt) // module qui permet e supprimer une valeur de la liste
{
    int i;  int gpt=1 ;
    maillon *maj[SKIPLIST_MAX_NIVEAU + 1]; // definir un tableau ou on vient mettre a jour des elements
    maillon *x = llc->tete;
    for (i = llc->niveau; i >= 1; i--) {
        while (x->suivant[i]->indice < indice) {
            x = x->suivant[i];
            gpt++ ;
        }

        maj[i] = x;
    }


    x = x->suivant[1];
    if (x->indice == indice) {
        for (i = 1; i <= llc->niveau; i++) { // pour parcourir la skiplist niveau par niveau
            if (maj[i]->suivant[i] != x)
                break;
            maj[i]->suivant[i] = x->suivant[i];
        }
        supprimer_maillon(x);

        while (llc->niveau > 1 && llc->tete->suivant[llc->niveau] == llc->tete)
            llc->niveau--; //decrementer le niveau
                *cpt=gpt ;

        return 0;
    }
    *cpt=gpt ;
    return 1;
}

static void affich_skiplist(skiplist *llc)
{
    maillon *x = llc->tete;
    while (x && x->suivant[1] != llc->tete)
        {
        printf("%d[%d] niveau [%d]-> | ", x->suivant[1]->indice, x->suivant[1]->valeur , x->suivant[1]->level );// le type d'affichage de la liste
        x = x->suivant[1];
    }
    printf("NIL\n") ; // pour indiquer la fin de la liste
}

void menu()
{
    skiplist llc;
    skiplist ll;
    srand(time(NULL));

    initialiser_skiplist(&llc);
  int nb_elem,i,sup,cpts,cpt,n;
  int *tab;

  deb:
  basemenu();
  switch(choix())
  {
  case 1:
      system("cls");

      textcolor(15);
      textbackground(3);
      printdirection("                                                       Affichage                                                        ","right",1,4,5);
      textcolor(0);
      gotoxy(10,8);
      affich_skiplist(&llc);


      system("pause");
      break;
  case 2:
      //--------------------------------- Affichage -------------------------------------//

      system("cls");
      textcolor(15);
      textbackground(3);
      printdirection("                                                       Insertion                                                        ","right",1,4,5);
      textcolor(0);
      gotoxy(10,6);
      printf("Quel est le nombre d'element à introduire : ");
      gotoxy(60,6);
      scanf("%d",&nb_elem);//----- lecture du nombre d'elements
      tab=malloc(nb_elem*sizeof(int));  //---- Allocation dynamique du tableau de valeurs
      gotoxy(10,8);
      printf("Introduire les %d element un par un : ",nb_elem);
      gotoxy(10,10);

      for(i=0;i<nb_elem;i++)//-------- récuperation des elements
        {   gotoxy(10,wherey());
            scanf("%d",&tab[i]);
        }

      for (i = 0; i < nb_elem; i++)
       {
        skiplist_insert_elem(&llc, tab[i], tab[i]); ///------ Insertion des elements
       }

      system("pause");

      break;

  case 3:

      system("cls");
      textcolor(15);
      textbackground(3);
      printdirection("                                                     Suppression                                                        ","right",1,4,5);
      textcolor(0);
      gotoxy(10,6);
      printf("Introduire le nombre à supprimer : ");
      gotoxy(60,6);
      scanf("%d",&sup);//----- lecture du nombre d'elements

      skiplist_supp_elem(&llc, sup,&cpts);

       system("pause");

      break;

  case 4:
      system("cls");
      textcolor(15);
      textbackground(3);
      printdirection("                                                     Simulation                                                      ","right",1,4,5);
      textcolor(0);
      gotoxy(10,6);
      printf(" voici une simulation qui compare la rapidite entre une skiplist et une LLC : \t \n \n ");
      printf (" ************************************************************************************************************\n \n");
      printf (" On va essayer de montrer combien d'element sont parcourus lors d'une suppression dans une LLC et une SKIPLIST : \n \n");
      printf("-------------------------------------------------------------------------------------------------------------\n \n");
      printf ("  veillez entrer le nombre d'element a saisir dans les deux listes :\n \n");
      scanf("%d",&n);
      maillons *tete ;
      int val ;
      tete=cree_LLC(n) ;
      tri_bulle(tete);

      printf (" Entrer la valeur a supprimer : \n");
      scanf("%d",&val);
      supp_val(val,&cpt ,&tete);


      afficher_LLC(tete);
      printf (" \n");
      printf(" le nombre d'elements parcourus dans LLC est : \t %d \n\n", cpt);
      printf(" veillez entrer les memes valeur dans la skiplist ci desous : \n \n");
      initialiser_skiplist(&ll);

      tab=malloc(n*sizeof(int));

      for(i=0;i<n;i++)//-------- récuperation des elements
        {   gotoxy(10,wherey());
            scanf("%d",&tab[i]);
        }

      for (i = 0; i < n; i++)
       {
        skiplist_insert_elem(&ll, tab[i], tab[i]);  //------ Insertion des elements
       }


       skiplist_supp_elem(&ll, val,&cpts);
       affich_skiplist(&ll);
       printf (" le nombre d'elements parcourus dans la skip list est : %d \n\n", cpts);


        system("pause");

      break;





//-----------------------------------------------------------------------------------------------



    case 5:
    goto fin ;
    break;

  }
goto deb;
fin:


fin();



}


int main()
{





















     intro();
     menu();














    return 0;
}

