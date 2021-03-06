#include "./tour.h"
#include "../Aff/aff.h"
#include "../Init/init.h"

/*
Cette fonction applique la prise des pions detectee par checkTableau.
*/
int prise(int tab[],char * plat[TAILLE][TAILLE],int ligne, int colonne, char * couleur, int direction){
  int i,j,compteur = 0;
  int notDone = 1;
  switch (direction) {
    case 0:/*vers le haut*/
      if(ligne >= 2){
        // printf("Haut\n");
        for(i = ligne - 1, j = colonne ; i > 0 && notDone; i--){
          if(tab[compteur]!=0) notDone = 0;
          if(tab[compteur++]==0) plat[i][j] = couleur;
        }
      }
      break;
    case 1:/*diagonale HD*/
      if(ligne >= 2 && colonne < TAILLE ){
        // printf("Diagonale Haut Droite\n");
        for(i = ligne - 1, j = colonne + 1 ; i >= 0 && j < TAILLE  && notDone; i--, j++){
          if(tab[compteur]!=0) notDone = 0;
          if(tab[compteur++]==0) plat[i][j] = couleur;
        }
      }
      break;
    case 3:/*vers la droite*/
      if(colonne < TAILLE){
        // printf("Droite\n");
        for(j = colonne + 1, i = ligne; j < TAILLE  && notDone; j++){
          if(tab[compteur]!=0) notDone = 0;
          if(tab[compteur++]==0) plat[i][j] = couleur;
        }
      }
      break;
    case 5:/*diagonale BD*/
      if(ligne < TAILLE && colonne < TAILLE ){
        // printf("Diagonale Bas Droite\n");
        for(i = ligne + 1, j = colonne + 1 ; i < TAILLE && j < TAILLE  && notDone; i++, j++){
          if(tab[compteur]!=0) notDone = 0;
          if(tab[compteur++]==0) plat[i][j] = couleur;
        }
      }
      break;
    case 6:/*vers le bas*/
      if(ligne < TAILLE){
        // printf("Bas\n");
        for(i = ligne + 1, j = colonne; i < TAILLE  && notDone; i++){
          if(tab[compteur]!=0) notDone = 0;
          if(tab[compteur++]==0) plat[i][j] = couleur;
        }
      }
      break;
    case 7:/*diagonale BG*/
      if(ligne < TAILLE && colonne >= 2 ){
        // printf("Diagonale Bas Gauche\n");
        for(i = ligne + 1, j = colonne - 1 ; i < TAILLE && j >= 0  && notDone; i++, j--){
          if(tab[compteur]!=0) notDone = 0;
          if(tab[compteur++]==0) plat[i][j] = couleur;
        }
      }
      break;
    case 9:/*vers la gauche*/
      if(colonne >= 2){
        // printf("Gauche\n");
        for(j = colonne - 1, i = ligne; j >= 0  && notDone; j--){
          if(tab[compteur]!=0) notDone = 0;
          if(tab[compteur++]==0) plat[i][j] = couleur;
        }
      }
      break;
    case 11:/*diagonale HG*/
      if(ligne >= 2 && colonne >= 2 ){
        // printf("Diagonale Haut Droite\n");
        for(i = ligne - 1, j = colonne - 1 ; i >= 0 && j >= 0  && notDone; i--, j--){
            if(tab[compteur]!=0) notDone = 0;
            if(tab[compteur++]==0) plat[i][j] = couleur;
        }
      }
      break;
    default:
      printf("Une erreur est survenue");
      break;
  }
  return 0;
}

/*
Cette fonction regarde dans le tableau si on a une suite de 0 puis un 1 et si c'est le cas
elle retourne 1 car ça veut dire qu'un pion peut être pris. Si un -1 est trouve, c'est qu'il y a un espace
donc inutile de continuer.
*/
int checkTableau(int tab[],char * plat[TAILLE][TAILLE],int ligne, int colonne,char * couleur,int direction, int estTest){
  int i;
  int suite = 0;
  int prend = 0;
  int espaces = 0;
  for(i = 0 ; i < TAILLE - 1; i++){
    if(espaces == 0){
      // if(!estTest) printf("\ntab[%d] : %d \n\n",i,tab[i]);
      if(tab[i] == 0){ // si la case actuelle est un pion de l'adversaire
        suite = 1;
      }else if(tab[i] == -1){ // sinon, si la case actuelle est vide
        espaces = 1;
        suite = 0;
      }else if(tab[i] == 1 && suite){// sinon, si la case actuelle est de la couleur ET qu'il y a suite
        prend = 1;
      }else{
        suite = 0;
        espaces = 1;
      }
    }
  }
  if(prend && !estTest) prise(tab,plat,ligne,colonne,couleur,direction);
  return prend;
}

void initTableau(int tab[]){
  for(int i = 0 ; i < TAILLE - 1 ; i ++){
    tab[i] = -1;
  }
}

/*
Cette fonction renvoit si des pions vont être pris.
Elle parcourt le terrain dans chaque direction en partant du point et met les couleurs qu'elle rencontre
(-1 pour les VIDE, 0 pour la couleur adverse et 1 pour la couleur actuelle) dans un tableau
Puis après chaque direction, le tableau est verifie puis les modifications au plateau sont effectuees,
Si ne serait-ce qu'un pion a ete pris, la fonction renvoit 1. 0 sinon.
*/
int prendPion(char * plat[TAILLE][TAILLE],int ligne, int colonne,char * couleur, int estTest){
  int aPris = 0;
  int points[TAILLE - 1];
  initTableau(points);
  int i, j, compteur = 0;
  /*directions droites*/
  {
    /*vers le haut*/
    if(ligne >= 2){
      // printf("\n\n\nhaut :");
      for(i = ligne - 1, j = colonne; i > 0 ; i--){
        if(!strcmp(plat[i][j],VIDE)){
          points[compteur++] = -1;
        }else if(strcmp(plat[i][j],couleur)){
          points[compteur++] = 0;
        }else{
          points[compteur++] = 1;
        }
      }
      aPris = checkTableau(points,plat,ligne,colonne,couleur,0,estTest);
    }
    compteur = 0;
    initTableau(points);
    /*vers le bas*/
    if(ligne < TAILLE){
      // printf("\n\n\nbas :");
      for(i = ligne + 1, j = colonne; i < TAILLE ; i++){
        if(!strcmp(plat[i][j],VIDE)){
          points[compteur++] = -1;
        }else if(strcmp(plat[i][j],couleur)){
          points[compteur++] = 0;
        }else{
          points[compteur++] = 1;
        }
      }
      if(!aPris) aPris = checkTableau(points,plat,ligne,colonne,couleur,6,estTest);
      else checkTableau(points,plat,ligne,colonne,couleur,6,estTest);
    }
    compteur = 0;
    initTableau(points);
    /*vers la gauche*/
    if(colonne >= 2){
      // printf("\n\n\ngauche :");
      for(j = colonne - 1, i = ligne; j >= 0 ; j--){
        if(!strcmp(plat[i][j],VIDE)){
          points[compteur++] = -1;
        }else if(strcmp(plat[i][j],couleur)){
          points[compteur++] = 0;
        }else{
          points[compteur++] = 1;
        }
      }
      if(!aPris) aPris = checkTableau(points,plat,ligne,colonne,couleur,9,estTest);
      else checkTableau(points,plat,ligne,colonne,couleur,9,estTest);
    }
    compteur = 0;
    initTableau(points);
    /*vers la droite*/
    if(colonne < TAILLE){
      // printf("\n\n\ndroite :");
      for(j = colonne + 1, i = ligne; j < TAILLE ; j++){
        if(!strcmp(plat[i][j],VIDE)){
          points[compteur++] = -1;
        }else if(strcmp(plat[i][j],couleur)){
          points[compteur++] = 0;
        }else{
          points[compteur++] = 1;
        }
      }
      if(!aPris) aPris = checkTableau(points,plat,ligne,colonne,couleur,3,estTest);
      else checkTableau(points,plat,ligne,colonne,couleur,3,estTest);
    }
    compteur = 0;
    initTableau(points);
  }
  /*directions droites mais pas pareil*/
  {
    /*diagonale HG*/
    if(ligne >= 2 && colonne >= 2 ){
      // printf("\n\n\nhaut - gauche :");
      for(i = ligne - 1, j = colonne - 1 ; i >= 0 && j >= 0 ; i--, j--){
        if(!strcmp(plat[i][j],VIDE)){
          points[compteur++] = -1;
        }else if(strcmp(plat[i][j],couleur)){
          points[compteur++] = 0;
        }else{
          points[compteur++] = 1;
        }
      }
      if(!aPris) aPris = checkTableau(points,plat,ligne,colonne,couleur,11,estTest);
      else checkTableau(points,plat,ligne,colonne,couleur,11,estTest);
    }
    compteur = 0;
    initTableau(points);
    /*diagonale HD*/
    if(ligne >= 2 && colonne < TAILLE ){
      // printf("\n\n\nhaut - droite :");
      for(i = ligne - 1, j = colonne + 1 ; i >= 0 && j < TAILLE ; i--, j++){
          if(!strcmp(plat[i][j],VIDE)){
            points[compteur++] = -1;
          }else if(strcmp(plat[i][j],couleur)){
            points[compteur++] = 0;
          }else{
            points[compteur++] = 1;
          }
        }
      }
      if(!aPris) aPris = checkTableau(points,plat,ligne,colonne,couleur,1,estTest);
      else checkTableau(points,plat,ligne,colonne,couleur,1,estTest);
    }
    compteur = 0;
    initTableau(points);
    /*diagonale BD*/
    if(ligne < TAILLE && colonne < TAILLE ){
      // printf("\n\n\nbas - droite :");
      for(i = ligne + 1, j = colonne + 1 ; i < TAILLE && j < TAILLE ; i++, j++){
        if(!strcmp(plat[i][j],VIDE)){
          points[compteur++] = -1;
        }else if(strcmp(plat[i][j],couleur)){
          points[compteur++] = 0;
        }else{
          points[compteur++] = 1;
        }
      }
      if(!aPris) aPris = checkTableau(points,plat,ligne,colonne,couleur,5,estTest);
      else checkTableau(points,plat,ligne,colonne,couleur,5,estTest);
    }
    compteur = 0;
    initTableau(points);
    /*diagonale BG*/
    if(ligne < TAILLE && colonne >= 2 ){
      // printf("\n\n\nbas - gauche :");
      for(i = ligne + 1, j = colonne - 1 ; i < TAILLE && j >= 0 ; i++, j--){
        if(!strcmp(plat[i][j],VIDE)){
          points[compteur++] = -1;
        }else if(strcmp(plat[i][j],couleur)){
          points[compteur++] = 0;
        }else{
          points[compteur++] = 1;
        }
      }
      if(!aPris) aPris = checkTableau(points,plat,ligne,colonne,couleur,7,estTest);
      else checkTableau(points,plat,ligne,colonne,couleur,7,estTest);
    }
  return aPris;
}

/*Cette fonction regarde dans toutes les positions possibles si la case a au moins un voisin de la couleur adverse*/
int aVoisins(char * plat[TAILLE][TAILLE],int ligne, int colonne,char * couleur){
  int nbVoisinsDiff = 0;
  if(ligne > 0){
    // haut gauche
    if(colonne > 0){
      if(strcmp(plat[ligne-1][colonne-1],couleur) && strcmp(plat[ligne-1][colonne-1],VIDE)) nbVoisinsDiff++;
    }
    // haut
    if(strcmp(plat[ligne-1][colonne],couleur) && strcmp(plat[ligne-1][colonne],VIDE)) nbVoisinsDiff++;
    // haut gauche
    if(colonne < TAILLE - 1){
      if(strcmp(plat[ligne-1][colonne+1],couleur) && strcmp(plat[ligne-1][colonne+1],VIDE)) nbVoisinsDiff++;
    }
  }
  if(colonne > 0){
    // gauche
    if(strcmp(plat[ligne][colonne-1],couleur) && strcmp(plat[ligne][colonne-1],VIDE)) nbVoisinsDiff++;
  }
  if(colonne < TAILLE - 1){
    // gauche
    if(strcmp(plat[ligne][colonne+1],couleur) && strcmp(plat[ligne][colonne+1],VIDE)) nbVoisinsDiff++;
  }
  if(ligne < TAILLE - 1){
    // bas gauche
    if(colonne > 0){
      if(strcmp(plat[ligne+1][colonne-1],couleur) && strcmp(plat[ligne+1][colonne-1],VIDE)) nbVoisinsDiff++;
    }
    // bas
    if(strcmp(plat[ligne+1][colonne],couleur) && strcmp(plat[ligne+1][colonne],VIDE)) nbVoisinsDiff++;
    // bas gauche
    if(colonne < TAILLE - 1){
      if(strcmp(plat[ligne+1][colonne+1],couleur) && strcmp(plat[ligne+1][colonne+1],VIDE)) nbVoisinsDiff++;
    }
  }
  return nbVoisinsDiff;
}

/*
Cette fonction verifie la validite du coup
Et renvoit un code d'erreur ou 0 si tout s'est bien passe.
*/
int estInvalide(char * plat[TAILLE][TAILLE],int ligne, int colonne,char * couleur, int estTest){
  // coup dans le plateau.estInvalide
  if(ligne >= TAILLE || ligne < 0 || colonne >= TAILLE || colonne < 0) return 1;
  // coup dans une case vide.
  if((strcmp(plat[ligne][colonne], VIDE))) return 2;
  // coup a cote d'une case adversaire
  if(!aVoisins(plat,ligne,colonne,couleur)) return 3;
  // coup prend un pion adverse.
  if(!prendPion(plat,ligne,colonne,couleur,estTest)) return 4;
  return 0;
}

// coup aleatoire IA
int coupAleatIA(char * plat[TAILLE][TAILLE],char * couleur){
  int coupInvalide = 1;
  int ligne = 0, colonne = 0;
  while(coupInvalide){
    ligne = rand()%8;
    colonne = rand()%8;
    coupInvalide = estInvalide(plat,ligne,colonne,couleur,0);
  }
  plat[ligne][colonne] = couleur;
  system("clear");
  char ligneC = 'A';
  printf("Coup precedent : %c%d\n\n",ligneC + ligne, colonne + 1);
}

// coup intelligent IA
int coupIntellIA(char * plat[TAILLE][TAILLE],char * couleur){
  /*En attendant le min max*/
  coupAleatIA(plat,couleur);
}

// Joueur contre Joueur distant
void saisieCoupJcJD(char * plat[TAILLE][TAILLE], char * couleur, int nbTours, int coupDonnee[2]){
  int coupInvalide = 1;
  int colonne = -1,ligne = -1;
  char saisieLigne = ' ';
  while(coupInvalide){
    printf("\nJoueur %s\n",couleur);
    printf("Saisissez votre coup (ligne colonne) : ");
    scanf("%c%d",&saisieLigne,&colonne);
    getchar();
    // Transformation de la lettre en indice de ligne
  if(saisieLigne != 'S' && saisieLigne != 's'){
    if(saisieLigne >= 'A' && saisieLigne <= 'A' + TAILLE){
        ligne = saisieLigne - 'A';
      }else{
        ligne = saisieLigne - 'a';
      }
      colonne--;
      coupInvalide = estInvalide(plat,ligne,colonne,couleur,0);
      if(coupInvalide){
        system("clear");
        afficherPlateau(plat);
        switch(coupInvalide){
          case 1:printf("\n\nLe coup est en dehors du plateau.\n");break;
          case 2:printf("\n\nLe coup est n'est pas dans une case vide.\n");break;
          case 3:printf("\n\nLe coup n'est pas a cote d'une case adverse.\n");break;
          case 4:printf("\n\nLe coup ne prend pas de pion adverse.\n");break;
        }
      }
    }
  }
  plat[ligne][colonne] = couleur;
  coupDonnee[0] = ligne;
  coupDonnee[1] = colonne;
  system("clear");
  char ligneC = 'A';
  printf("Coup precedent : %c%d\n\n",ligneC + ligne, colonne + 1);
}



// Joueur contre Joueur local (egalement utilise pour la saisie des coups d'un joueur quand ce n'est pas le tour de l'IA)
void saisieCoupJcJL(char * plat[TAILLE][TAILLE], char * couleur, int nbTours){

// Ce code est une étape qui permet de réaliser l'IA, il permet de vérifier les case jouables ainsi que sa valeur de force
// Décommentez le code et tester-le avec le menu joueur contre joueur local
/*
  int cp;
  int cda1;
  char * cda2;
  cp = NbrcoupPossible(plat,couleur);
  int case_a[MAX_C];
  int case_o[MAX_C];
  int eval[MAX_C];
  printf("Les cases jouables sont :\t");
  caseJouable(plat,couleur,case_a,case_o);
  for (int p=0;p <cp;p++){
    cda1 = case_a[p];
    cda2 = malloc(sizeof(char *));
    *cda2 = convertEtoL(cda1);
    printf("%s%d\t",cda2,case_o[p]+1);
    free(cda2);
    cda2 = NULL;
  }

  evaluation(case_a,case_o,eval,cp);
  printf("\nLes scores des cases :\t\t");
  for (int z=0;z<cp;z++){
    printf("%d\t",eval[z]);
  }
  int nbrPions;
  nbrPions = NbrpionsPlat(nbTours);
  printf("\nLe nombre de pions sur le plateau est %d\n",nbrPions);
*/
  int coupInvalide = 1;
  int colonne = -1,ligne = -1;
  char saisieLigne = ' ';
  while(coupInvalide){
    printf("\nJoueur %s\n",couleur);
    printf("Saisissez votre coup (ligne colonne) : ");
    scanf("%c%d",&saisieLigne,&colonne);
    getchar();
    // Transformation de la lettre en indice de ligne
  if(saisieLigne != 'S' && saisieLigne != 's'){
    if(saisieLigne >= 'A' && saisieLigne <= 'A' + TAILLE){
        ligne = saisieLigne - 'A';
      }else{
        ligne = saisieLigne - 'a';
      }
      colonne--;
      coupInvalide = estInvalide(plat,ligne,colonne,couleur,0);
      if(coupInvalide){
        system("clear");
        afficherPlateau(plat);
        switch(coupInvalide){
          case 1:printf("\n\nLe coup est en dehors du plateau.\n");break;
          case 2:printf("\n\nLe coup est n'est pas dans une case vide.\n");break;
          case 3:printf("\n\nLe coup n'est pas a cote d'une case adverse.\n");break;
          case 4:printf("\n\nLe coup ne prend pas de pion adverse.\n");break;
        }
      }
    } else {
      FILE * fichier;
      char fileName[30];
      printf("Saisissez le nom du fichier pour enregistrer la partie : \n");
      scanf("%s",fileName);
      getchar();
      fichier = fopen(strcat(fileName,".txt"),"w");
      savePartie(plat,fichier,nbTours,couleur);
      fclose(fichier);
      printf("Sauvegarde effectuée avec succès.\nAu revoir");
      exit(EXIT_SUCCESS);
    }
  }
  plat[ligne][colonne] = couleur;
  system("clear");
  char ligneC = 'A';
  printf("Coup precedent : %c%d\n\n",ligneC + ligne, colonne + 1);
}

// Joueur contre IA
void saisieCoupJcIA(char * plat[TAILLE][TAILLE], char * couleur, int nbTours, int difficulte, int couleurIA){
  if(nbTours % 2 == couleurIA){
    sleep(1.5);
    switch(nbTours % difficulte){
      case 0 :
        coupAleatIA(plat,couleur);
        break;
      default:
        coupIntellIA(plat,couleur);
        break;
    }
  }else{
    saisieCoupJcJL(plat,couleur,nbTours);
  }
}

/*
  Fonction qui renvoit si une partie est fini et qui gagne.
  0 -> la partie n'est pas encore finie
  1 -> les blancs
  2 -> les noirs
  3 -> egalite
*/
int estFinie(char * plat[TAILLE][TAILLE]){
  int done = 0;
  int plein = 1;
  int nbNoirs = 0;
  int nbBlancs = 0;
  int ligne,colonne;
  for(ligne = 0; ligne < TAILLE; ligne++){
    for(colonne = 0; colonne < TAILLE; colonne++){
      // strcmp renvoit 0 en cas d'egalite des deux termes. Donc on cherche a savoir si
      // Il y a encore au moins une case vide
      if(!(strcmp(plat[ligne][colonne], VIDE))) plein = 0;
      // Il y a encore au moins une case noire
      if(!(strcmp(plat[ligne][colonne], NOIR))) nbNoirs++;
      // Il y a encore au moins une case blanche
      if(!(strcmp(plat[ligne][colonne], BLANC))) nbBlancs++;
    }
  }
  if(plein || !nbNoirs || !nbBlancs) done = nbNoirs>nbBlancs?1:nbNoirs<nbBlancs?2:3;
  return done;
}

/*
  Fonction qui renvoit si un coup est possible dans une situation donnee et pour un joueur donne
*/
int coupPossible(char * plat[TAILLE][TAILLE] ,char * couleur){
  int possible = 0;
  int i, j;
  for(i = 0; i < TAILLE ; i++){
    for(j = 0; j < TAILLE ; j++){
      if(!estInvalide(plat,i,j,couleur,1)) possible = 1;
    }
  }
  return possible;
}

void caseJouable(char * plat[TAILLE][TAILLE] ,char * couleur,int abs[MAX_C],int ord[MAX_C]){
  int k = 0;
  for(int i = 0; i < TAILLE ; i++){
    for(int j = 0; j < TAILLE ; j++){
        if(strcmp(plat[i][j], VIDE) == 0){
          if(aVoisins(plat,i,j,couleur)){
            if(prendPion(plat,i,j,couleur,1)){
              abs[k] = i;
              ord[k] = j;
              k++;
            }
          }
        }
      }
    }

}

int NbrcoupPossible(char * plat[TAILLE][TAILLE] ,char * couleur){
  int k = 0;
  for(int i = 0; i < TAILLE ; i++){
    for(int j = 0; j < TAILLE ; j++){
        if(strcmp(plat[i][j], VIDE) == 0){
          if(aVoisins(plat,i,j,couleur)){
            if(prendPion(plat,i,j,couleur,1)){
              k++;
            }
          }
        }
      }
    }
  return k;
}

int NbrpionsPlat(int nbTours){
  int k = 4;
  if (nbTours > 0){
    k += nbTours-1;
  }
  return k;
}

char convertEtoL(int indice){

  char * lettre[8] = {"A","B","C","D","E","F","G","H"};

  switch(indice){
    case 0:return *lettre[0];break;
    case 1:return *lettre[1];break;
    case 2:return *lettre[2];break;
    case 3:return *lettre[3];break;
    case 4:return *lettre[4];break;
    case 5:return *lettre[5];break;
    case 6:return *lettre[6];break;
    case 7:return *lettre[7];break;
  }
}

void evaluation(int abs[MAX_C],int ord[MAX_C],int eval[MAX_C],int nbrcp){

  int plat_f[TAILLE][TAILLE]={ 1000,5,250,100,100,250,5,1000,
                             5,0,50,50,50,50,0,5,
                             250,50,60,70,70,60,50,250,
                             100,50,70,200,200,70,50,100,
                             100,50,70,200,200,70,50,100,
                             250,50,60,70,70,60,50,250,
                             5,0,50,50,50,50,0,5,
                             1000,5,250,100,100,250,5,1000 };

  for(int i = 0 ; i < nbrcp ; i++ ){
    eval[i] = plat_f[abs[i]][ord[i]];
  }
}
