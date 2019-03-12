<DOCTYPE html>
  <head>
  </head>
  <body>
    <h1>
      Affichage avec SDL
    </h1>
    <h3>
      ATTENTION : IL FAUT AVOIR SDL D'INSTALLÉ ET PRÉCISER SON CHEMIN DANS LE MAKEFILE POUR POUVOIR COMPILER ET EXECUTER, SINON IL NE PEUT PAS IMPORTER LES LIBRAIRIES
    </h3>
    <h2>
        Permet l'affichage du plateau et la prise de pion via l'interface graphique SDL
    </h2>
    <h3>
        Liste des fonctions :
    </h3>
    <ul>
        <li> drawText : dessine la chaine donnée sur le renderer, a la position donnée, avec la taille et la couleur donnée.</li>
        <li> drawImage : affiche l'image sur le renderer, a une position donné, a partir de son chemin dans l'architecture.</li>
        <li> showWindow : Initialise la fenetre SDL.</li>
        <li> posClick : vérifie si le clic est dans la zone donnée.</li>
        <li> set_pixel : place un pixel.</li>
        <li> draw_circle : dessine un cercle en utilisant l'Algorithme de tracé d'arc de cercle de Bresenham.</li>
        <li> fill_circle : dessine un cercle plein.</li>
        <li> calculVarPlat : calcule les variables essentielle a l'affichage et utilisation du plateau.</li>
        <li> afficherPlateau : affiche le plateau de jeu, uniquement le quadrillage.</li>
        <li> afficherPion : affiche un pion au coordonées données, de la couleur donnée.</li>
        <li> afficherMatrice : affiche le contenu de la matrice (les pions) sur le plateau de jeu.</li>
        <li> placerPion : ajoute le pion dans la matrice, de la couleur du joueur donnée.</li>
        <li> coordCaseClic : calcul les coordonées de la case de la matrice corespondants a l'emplacement du clic.</li>
  </body>
</html>
